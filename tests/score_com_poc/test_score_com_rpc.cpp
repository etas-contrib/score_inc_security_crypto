// =============================================================================
//  C O P Y R I G H T
// -----------------------------------------------------------------------------
//  Copyright (c) 2026 by ETAS GmbH. All rights reserved.
//
//  The reproduction, distribution and utilization of this file as
//  well as the communication of its contents to others without express
//  authorization is prohibited. Offenders will be held liable for the
//  payment of damages. All rights reserved in the event of the grant
//  of a patent, utility model or design.
// =============================================================================

/// POC: FlatBuffer transport via S-CORE mw::com Method
///
/// Validates that ControlRequest / ControlResponse FlatBuffer messages (as
/// defined in poc_message.fbs, mirroring score.crypto.ipc.control) can
/// round-trip through the S-CORE LoLa shared-memory Method API (skeleton +
/// proxy in the same process on separate threads, communicating through
/// /dev/shm).
///
/// The request carries a String parameter and a ValueUint64 parameter.
/// The handler concatenates them and returns the result as a
/// single String response parameter.
///
/// No crypto dependencies — only FlatBuffers + score_communication.

#include <atomic>
#include <chrono>
#include <string>
#include <thread>
#include <vector>

#include "flatbuffers/flatbuffers.h"
#include "gtest/gtest.h"
#include "score/mw/com/impl/proxy_base.h"
#include "score/mw/com/runtime.h"
#include "score/mw/com/runtime_configuration.h"
#include "score/mw/com/types.h"
#include "tests/score_com_poc/ipc_buffer.h"
#include "tests/score_com_poc/poc_control_generated.h"
#include "tests/score_com_poc/control_plane_interface.h"

namespace score::crypto::ipc::control
{
namespace
{

// ---------------------------------------------------------------------------
// Runtime initialisation — once per process via gtest GlobalEnvironment
// ---------------------------------------------------------------------------

class ScoreComEnvironment : public ::testing::Environment
{
  public:
    void SetUp() override
    {
        score::mw::com::runtime::InitializeRuntime(score::mw::com::runtime::RuntimeConfiguration{
            score::filesystem::Path{"tests/score_com_poc/mw_com_config.json"}});
    }
};

// ---------------------------------------------------------------------------
// FlatBuffer helpers
// ---------------------------------------------------------------------------

IpcBuffer BuildControlResponse(const std::uint64_t request_id, const std::string& combined)
{
    flatbuffers::FlatBufferBuilder fbb(512);

    // Response parameter: a single String containing the combined value.
    auto str_val = fbb.CreateString(combined);
    auto str_tbl = CreateString(fbb, str_val);

    std::vector<uint8_t> resp_param_types{OperationParameter_String};
    std::vector<flatbuffers::Offset<void>> resp_param_values{str_tbl.Union()};

    auto resp_op = CreateSingleOperationResponse(
        fbb,
        /*operation_id=*/CreateOperationIdentifier(fbb, 0U, 0U),
        /*result=*/CreateOperationResult(fbb, 0U),
        /*parameter_type=*/fbb.CreateVector(resp_param_types),
        /*parameter=*/fbb.CreateVector(resp_param_values));

    auto resp_batch = CreateOperationResponseBatch(fbb, fbb.CreateVector({resp_op}));
    fbb.FinishSizePrefixed(CreateControlResponse(fbb, request_id, resp_batch));
    return PackFlatBuffer(fbb.GetBufferPointer(), fbb.GetSize());
}

// ---------------------------------------------------------------------------
// Test fixture
// ---------------------------------------------------------------------------

/// ScoreComRpcFixture spins up the server (skeleton) on a background thread
/// and connects the client (proxy) during SetUp, leaving only the actual
/// call and assertions in each TEST_F body.
///
/// Server side (SetUp):
///   ControlPlaneSkeleton::Create  — allocates the service-side SHM regions.
///   RegisterHandler      — installs the synchronous RPC handler; LoLa
///                          invokes it on the skeleton thread when the proxy
///                          calls execute().  The handler receives the
///                          IpcBuffer by value (copied from the SHM call-queue
///                          slot) and returns a response IpcBuffer by value
///                          (copied into the SHM return slot by LoLa).
///   OfferService         — publishes the SHM regions and makes the service
///                          discoverable via FindService().
///
/// Client side (SetUp):
///   FindService          — scans the LoLa registry; blocks until the skeleton
///                          has called OfferService().
///   ControlPlaneProxy::Create     — opens the SHM call-queue.  {"Execute"} limits
///                          queue allocation to the one subscribed method.
///
/// Transport: LoLa (Low Latency) — /dev/shm segments.
///   IpcBuffer is trivially copyable; kMaxIpcBufferSize (4096 bytes) is an
///   ABI boundary — both sides must be rebuilt together if changed.
/// FlatBuffer encoding: size-prefixed ControlRequest / ControlResponse;
///   the first 4 bytes of the payload encode the data length.
///
/// Missing IPC requirement — caller UID not available on the server side:
///   LoLa transports method payloads via shared memory; the mw::com
///   RegisterHandler callback signature only carries payload spans
///   and provides no caller identity metadata.  The score::message_passing
///   layer (Unix domain sockets) does expose ClientIdentity
///   (pid/uid/gid via SO_PEERCRED), but that is used solely for service
///   discovery signalling and is not surfaced through the mw::com API.
///   There is currently no supported way to retrieve the caller's UID
///   for this abstraction level.
///
/// Concurrency model:
///   Client — one outstanding call per ProxyMethod instance at a time.
///     ProxyMethodBase::kCallQueueSize is hardcoded to 1, so a second
///     execute() on the same proxy blocks until the first returns.
///     For N concurrent callers, N separate ControlPlaneProxy instances are needed.
///   Server — the skeleton thread processes call-queue entries sequentially.
///     The RegisterHandler lambda may dispatch to a thread pool internally
///     (blocking the skeleton thread on future.get() until the work is done),
///     which allows parallel execution of multiple requests from different
///     proxy instances without changing the mw::com API surface.
class ScoreComRpcFixture : public ::testing::Test
{
  public:
    void SetUp() override
    {
        using score::mw::com::InstanceSpecifier;
        using score::mw::com::impl::ProxyBase;

        // Both sides share the same InstanceSpecifier; LoLa resolves it to the
        // SHM region and method-queue described in mw_com_config.json.
        const auto instance_specifier = InstanceSpecifier::Create("poc/PocControlPort").value();

        // ---- Server (skeleton) -------------------------------------------
        skeleton_thread_ = std::thread([this, instance_specifier] {
            auto skel_result = ControlPlaneSkeleton::Create(instance_specifier);
            ASSERT_TRUE(skel_result.has_value()) << "ControlPlaneSkeleton::Create failed";
            skeleton_ = std::move(skel_result.value());

            // RegisterHandler installs a synchronous callback.  LoLa invokes
            // it on this thread when the proxy calls execute().
            // The handler receives the IpcBuffer by value (copied from SHM),
            // deserialises in-place (zero allocation), and returns a response.
            auto reg_result = skeleton_->execute.RegisterHandler([](IpcBuffer request_buf) -> IpcBuffer {
                flatbuffers::Verifier verifier{reinterpret_cast<const uint8_t*>(request_buf.payload.data()),
                                               GetPayloadSize(request_buf)};
                EXPECT_TRUE(VerifySizePrefixedControlRequestBuffer(verifier));

                const auto* req =
                    flatbuffers::GetSizePrefixedRoot<ControlRequest>(request_buf.payload.data());
                if (req == nullptr || req->operation_batch() == nullptr ||
                    req->operation_batch()->operations() == nullptr ||
                    req->operation_batch()->operations()->size() == 0U)
                {
                    return IpcBuffer{};
                }

                const auto* op = req->operation_batch()->operations()->Get(0U);
                if (op == nullptr || op->parameter() == nullptr || op->parameter_type() == nullptr)
                {
                    return IpcBuffer{};
                }

                // Extract String (index 0) and ValueUint64 (index 1) from parameters.
                std::string str_value;
                std::uint64_t uint64_value = 0U;
                for (flatbuffers::uoffset_t i = 0U; i < op->parameter()->size(); ++i)
                {
                    const auto param_type = static_cast<OperationParameter>(op->parameter_type()->Get(i));
                    if (param_type == OperationParameter_String)
                    {
                        const auto* s = reinterpret_cast<const String*>(op->parameter()->Get(i));
                        if (s != nullptr && s->val() != nullptr)
                        {
                            str_value = s->val()->str();
                        }
                    }
                    else if (param_type == OperationParameter_ValueUint64)
                    {
                        const auto* v = reinterpret_cast<const ValueUint64*>(op->parameter()->Get(i));
                        if (v != nullptr)
                        {
                            uint64_value = v->val();
                        }
                    }
                }

                const std::string combined = str_value + "_" + std::to_string(uint64_value);
                return BuildControlResponse(req->request_id(), combined);
            });
            ASSERT_TRUE(reg_result.has_value()) << "RegisterHandler failed";

            // OfferService publishes the SHM regions; FindService() on the
            // proxy side will succeed only after this point.
            ASSERT_TRUE(skeleton_->OfferService().has_value()) << "OfferService failed";
            skeleton_ready_.store(true, std::memory_order_release);

            while (!test_done_.load(std::memory_order_acquire))
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
            skeleton_->StopOfferService();
        });

        // ---- Client (proxy) ----------------------------------------------
        while (!skeleton_ready_.load(std::memory_order_acquire))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }

        // FindService scans the LoLa registry for offered instances.
        auto handles = ProxyBase::FindService(instance_specifier);
        ASSERT_TRUE(handles.has_value() && !handles->empty()) << "FindService failed";

        // Create opens the SHM call-queue; {"Execute"} limits queue
        // allocation to the one subscribed method.
        auto proxy_result = ControlPlaneProxy::Create(handles.value()[0], {"Execute"});
        ASSERT_TRUE(proxy_result.has_value()) << "ControlPlaneProxy::Create failed";
        proxy_ = std::move(proxy_result.value());
    }

    void TearDown() override
    {
        test_done_.store(true, std::memory_order_release);
        if (skeleton_thread_.joinable())
        {
            skeleton_thread_.join();
        }
    }

  protected:
    std::optional<ControlPlaneSkeleton> skeleton_;
    std::optional<ControlPlaneProxy> proxy_;

  private:
    std::thread skeleton_thread_;
    std::atomic<bool> skeleton_ready_{false};
    std::atomic<bool> test_done_{false};
};

// ---------------------------------------------------------------------------
// Tests
// ---------------------------------------------------------------------------

TEST_F(ScoreComRpcFixture, ControlRequestRoundTripViaMethodRpc)
{
    const std::uint64_t kRequestId = 7U;
    const std::string kStrParam = "hello";
    const std::uint64_t kUint64Param = 42U;
    const std::string kExpectedCombined = kStrParam + "_" + std::to_string(kUint64Param);

    // Allocate() returns a MethodInArgPtr<IpcBuffer> pointing directly into
    // the SHM call-queue slot — no intermediate stack IpcBuffer.
    auto alloc_result = proxy_->execute.Allocate();
    ASSERT_TRUE(alloc_result.has_value()) << "Method Allocate() failed";
    auto& arg = std::get<0>(alloc_result.value());

    {
        // Build ControlRequest with a String parameter and a ValueUint64 parameter.
        flatbuffers::FlatBufferBuilder fbb(512);

        // String param
        auto str_val = fbb.CreateString(kStrParam);
        auto str_tbl = CreateString(fbb, str_val);

        // ValueUint64 param
        auto u64_tbl = CreateValueUint64(fbb, kUint64Param);

        std::vector<uint8_t> param_types{OperationParameter_String, OperationParameter_ValueUint64};
        std::vector<flatbuffers::Offset<void>> param_values{str_tbl.Union(), u64_tbl.Union()};

        auto op_id = CreateOperationIdentifier(fbb, /*actor=*/1U, /*action=*/1U);
        auto single_op = CreateSingleOperationRequest(
            fbb, op_id,
            fbb.CreateVector(param_types),
            fbb.CreateVector(param_values));

        auto batch = CreateOperationRequestBatch(fbb, fbb.CreateVector({single_op}));
        fbb.FinishSizePrefixed(
            CreateControlRequest(fbb, kRequestId, /*client_id=*/0U, /*data_node_id=*/0U, batch));

        ASSERT_TRUE(PackFlatBufferInto(*arg, fbb.GetBufferPointer(), fbb.GetSize()));
    }

    // Moving the MethodInArgPtr transfers SHM-slot ownership to LoLa, which
    // forwards it to the skeleton handler. The call blocks until it returns.
    auto call_result = proxy_->execute(std::move(arg));
    ASSERT_TRUE(call_result.has_value()) << "Method call failed";

    // Dereferencing copies the IpcBuffer from the SHM return slot into a
    // local value; FlatBuffers then accesses it in-place (zero allocation).
    const IpcBuffer response_buf = *call_result.value();
    ASSERT_TRUE(IsValid(response_buf));

    const auto* resp =
        flatbuffers::GetSizePrefixedRoot<ControlResponse>(response_buf.payload.data());
    ASSERT_NE(resp, nullptr);
    EXPECT_EQ(resp->request_id(), kRequestId);

    ASSERT_NE(resp->operation_batch(), nullptr);
    ASSERT_NE(resp->operation_batch()->operations(), nullptr);
    ASSERT_EQ(resp->operation_batch()->operations()->size(), 1U);

    const auto* resp_op = resp->operation_batch()->operations()->Get(0U);
    ASSERT_NE(resp_op, nullptr);
    ASSERT_NE(resp_op->parameter(), nullptr);
    ASSERT_EQ(resp_op->parameter()->size(), 1U);
    ASSERT_NE(resp_op->parameter_type(), nullptr);
    EXPECT_EQ(static_cast<OperationParameter>(resp_op->parameter_type()->Get(0U)),
              OperationParameter_String);

    const auto* resp_str =
        reinterpret_cast<const String*>(resp_op->parameter()->Get(0U));
    ASSERT_NE(resp_str, nullptr);
    ASSERT_NE(resp_str->val(), nullptr);
    EXPECT_EQ(resp_str->val()->str(), kExpectedCombined);
}

}  // namespace
}  // namespace score::crypto::ipc::control

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new score::crypto::ipc::control::ScoreComEnvironment{});
    return RUN_ALL_TESTS();
}
