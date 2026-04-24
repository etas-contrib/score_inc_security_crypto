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

#include "score/mw/crypto/api/contexts/src/key_management_context_impl.hpp"

#include "score/mw/crypto/api/common/crypto_resource_guard.hpp"
#include "score/mw/crypto/api/common/error_domain.hpp"
#include "score/mw/crypto/api/common/src/crypto_resource_guard_factory.hpp"
#include "score/mw/crypto/api/common/src/i_release_callback.hpp"
#include "score/mw/crypto/api/common/types.hpp"
#include "score/mw/crypto/api/config/key_operation_params.hpp"

#include "score/crypto/api/control_plane/i_connection.hpp"
#include "score/crypto/daemon/common/actors.hpp"
#include "score/crypto/daemon/control_plane/control_protocol.h"
#include "score/crypto/daemon/key_management/interfaces/key_management_operations.hpp"
#include "score/crypto/daemon/mediator/mediator_operations.hpp"

#include "score/result/result.h"
#include "score/span.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>
#include <optional>
#include <utility>
#include <variant>

namespace score
{
namespace mw
{
namespace crypto
{

namespace proto = ::score::crypto::daemon::control_plane::protocol;
namespace actors = ::score::crypto::daemon::common::actors;
namespace keymgmt_ops = ::score::crypto::daemon::key_management::operations;

// ---------------------------------------------------------------------------
// IReleaseCallback implementation — sends CTX_CLOSE on last reference drop
// ---------------------------------------------------------------------------
class KeyManagementContextImpl::ContextReleaseCallbackImpl final : public IReleaseCallback
{
  public:
    ContextReleaseCallbackImpl(std::shared_ptr<score::crypto::api::control_plane::IConnection> connection,
                               proto::DataNodeId context_id)
        : m_connection(std::move(connection)), m_context_id(context_id)
    {
    }

    // No copy, no move. Just handled via shared_ptr
    ContextReleaseCallbackImpl(const ContextReleaseCallbackImpl&) = delete;
    ContextReleaseCallbackImpl& operator=(const ContextReleaseCallbackImpl&) = delete;
    ContextReleaseCallbackImpl(ContextReleaseCallbackImpl&&) = delete;
    ContextReleaseCallbackImpl& operator=(ContextReleaseCallbackImpl&&) = delete;

    ~ContextReleaseCallbackImpl() override
    {
        if (!m_connection)
        {
            std::cerr << "[API][KeyMgmtContextImpl] ERROR: Connection is not initialized during CTX_CLOSE\n";
            return;
        }

        auto context_close_res = proto::ControlRequestBuilder()
                                     .forDataNodeId(m_context_id)
                                     .operation(score::crypto::daemon::mediator::operations::CloseContext())
                                     .build();

        if (!context_close_res.has_value())
        {
            std::cerr << "[API][KeyMgmtContextImpl] ERROR: Failed to build CTX_CLOSE request\n";
            return;
        }

        auto response_res = m_connection->SendRequest(context_close_res.value());

        auto validator = proto::ControlResponseValidator::FromResult(response_res);
        validator.expectOperation(score::crypto::daemon::mediator::operations::CloseContext()).expectSuccess();

        if (!validator.isValid())
        {
            std::cerr << "[API][KeyMgmtContextImpl] ERROR: CTX_CLOSE response validation failed: "
                      << validator.getError() << "\n";
            return;
        }
    }

    score::Result<std::monostate> ReleaseResource(const CryptoResourceId& /*id*/) noexcept override
    {
        return std::monostate{};
    }

  private:
    std::shared_ptr<score::crypto::api::control_plane::IConnection> m_connection;
    proto::DataNodeId m_context_id;
};

// ---------------------------------------------------------------------------
// IReleaseCallback implementation — sends KEY_RELEASE to daemon
// ---------------------------------------------------------------------------
class KeyManagementContextImpl::ReleaseCallbackImpl final : public IReleaseCallback
{
  public:
    ReleaseCallbackImpl(std::shared_ptr<score::crypto::api::control_plane::IConnection> connection,
                        proto::DataNodeId context_id,
                        std::shared_ptr<IReleaseCallback> context_release_callback)
        : m_connection(std::move(connection)),
          m_context_id(context_id),
          m_context_release_callback(std::move(context_release_callback))
    {
    }

    score::Result<std::monostate> ReleaseResource(const CryptoResourceId& id) noexcept override
    {
        auto control_req_result = proto::ControlRequestBuilder()
                                      .forDataNodeId(m_context_id)
                                      .operation({actors::OP_ACTOR_KEY_MANAGEMENT, keymgmt_ops::KEY_RELEASE})
                                      .with_in_val_uint64(id.id)
                                      .build();
        if (!control_req_result.has_value())
        {
            std::cerr << "[API][KeyMgmtRelease] ERROR: Failed to build KEY_RELEASE request\n";
            return score::Result<std::monostate>{
                score::unexpect, MakeError(CryptoErrorCode::kOperationFailed, "Failed to build KEY_RELEASE request")};
        }

        auto control_response_res = m_connection->SendRequest(control_req_result.value());

        auto validator = proto::ControlResponseValidator::FromResult(control_response_res);
        validator.expectOperation({actors::OP_ACTOR_KEY_MANAGEMENT, keymgmt_ops::KEY_RELEASE}).expectSuccess();

        if (!validator.isValid())
        {
            std::cerr << "[API][KeyMgmtRelease] ERROR: " << validator.getError() << "\n";
            return score::Result<std::monostate>{
                score::unexpect, MakeError(CryptoErrorCode::kOperationFailed, "KEY_RELEASE daemon response invalid")};
        }

        return std::monostate{};
    }

  private:
    std::shared_ptr<score::crypto::api::control_plane::IConnection> m_connection;
    proto::DataNodeId m_context_id;
    std::shared_ptr<IReleaseCallback> m_context_release_callback;
};

KeyManagementContextImpl::KeyManagementContextImpl(
    std::shared_ptr<score::crypto::api::control_plane::IConnection> connection,
    uint64_t context_id)
    : m_connection(std::move(connection)),
      m_context_id(context_id),
      m_context_release_callback(std::make_shared<ContextReleaseCallbackImpl>(m_connection, m_context_id)),
      m_release_callback(std::make_shared<ReleaseCallbackImpl>(m_connection, m_context_id, m_context_release_callback))
{
}

KeyManagementContextImpl::~KeyManagementContextImpl() = default;

// ---------------------------------------------------------------------------
// Key Generation — Ephemeral
// ---------------------------------------------------------------------------

score::Result<CryptoResourceGuard> KeyManagementContextImpl::GenerateKey(const GenerateKeyParams& params)
{
    auto control_req_result = proto::ControlRequestBuilder()
                                  .forDataNodeId(m_context_id)
                                  .operation({actors::OP_ACTOR_KEY_MANAGEMENT, keymgmt_ops::KEY_GENERATE})
                                  .with_in_string(params.algorithm)
                                  .with_in_val_uint32(static_cast<std::uint32_t>(params.permissions))
                                  .build();

    if (!control_req_result.has_value())
    {
        std::cerr << "[API][KeyMgmtContextImpl] ERROR: Failed to build KEY_GENERATE request\n";
        return score::Result<CryptoResourceGuard>{
            score::unexpect, MakeError(CryptoErrorCode::kKeyGenerationFailed, "Failed to build KEY_GENERATE request")};
    }

    auto control_response_res = m_connection->SendRequest(control_req_result.value());

    auto validator = proto::ControlResponseValidator::FromResult(control_response_res);
    validator.expectOperation({actors::OP_ACTOR_KEY_MANAGEMENT, keymgmt_ops::KEY_GENERATE}).expectSuccess();

    if (!validator.isValid())
    {
        std::cerr << "[API][KeyMgmtContextImpl] ERROR: " << validator.getError() << "\n";
        return score::Result<CryptoResourceGuard>{
            score::unexpect, MakeError(CryptoErrorCode::kKeyGenerationFailed, "KEY_GENERATE daemon response invalid")};
    }

    // Extract the daemon-assigned resource id from the response
    auto resource_id_result = validator.getParameterAt<std::uint64_t>(0, 0);
    if (!resource_id_result.has_value())
    {
        std::cerr << "[API][KeyMgmtContextImpl] ERROR: KEY_GENERATE response has invalid resource_id type\n";
        return score::Result<CryptoResourceGuard>{
            score::unexpect,
            MakeError(CryptoErrorCode::kKeyGenerationFailed, "KEY_GENERATE response has invalid resource_id type")};
    }

    CryptoResourceId resource_id{};
    resource_id.id = resource_id_result.value();
    resource_id.type = ResourceType::kKey;
    resource_id.persistence = ResourcePersistence::kEphemeral;

    // Extract optional provider id from response (param 0, index 1)
    auto provider_result = validator.getParameterAt<std::uint16_t>(0, 1);
    if (provider_result.has_value())
    {
        resource_id.primary_provider = provider_result.value();
    }

    return CryptoResourceGuardFactory::Make(m_release_callback, resource_id);
}

score::Result<CryptoResourceGuard> KeyManagementContextImpl::LoadKey(const CryptoResourceId& slot)
{
    if (slot.type != ResourceType::kKeySlot)
    {
        std::cerr << "[API][KeyMgmtContextImpl] ERROR: LoadKey called with invalid slot resource type\n";
        return score::Result<CryptoResourceGuard>{
            score::unexpect,
            MakeError(CryptoErrorCode::kInvalidArgument, "LoadKey called with invalid slot resource type")};
    }

    auto control_req_result = proto::ControlRequestBuilder()
                                  .forDataNodeId(m_context_id)
                                  .operation({actors::OP_ACTOR_KEY_MANAGEMENT, keymgmt_ops::KEY_LOAD})
                                  .with_in_val_uint64(slot.id)
                                  .build();

    if (!control_req_result.has_value())
    {
        std::cerr << "[API][KeyMgmtContextImpl] ERROR: Failed to build KEY_LOAD request\n";
        return score::Result<CryptoResourceGuard>{
            score::unexpect, MakeError(CryptoErrorCode::kInternalError, "Failed to build KEY_LOAD request")};
    }

    auto control_response_res = m_connection->SendRequest(control_req_result.value());

    auto validator = proto::ControlResponseValidator::FromResult(control_response_res);
    validator.expectOperation({actors::OP_ACTOR_KEY_MANAGEMENT, keymgmt_ops::KEY_LOAD}).expectSuccess();

    if (!validator.isValid())
    {
        std::cerr << "[API][KeyMgmtContextImpl] ERROR: " << validator.getError() << "\n";
        return score::Result<CryptoResourceGuard>{
            score::unexpect, MakeError(CryptoErrorCode::kInternalError, "KEY_LOAD daemon response invalid")};
    }

    // Extract the daemon-assigned resource id for the loaded key material
    auto resource_id_result = validator.getParameterAt<std::uint64_t>(0, 0);
    if (!resource_id_result.has_value())
    {
        std::cerr << "[API][KeyMgmtContextImpl] ERROR: KEY_LOAD response has invalid resource_id type\n";
        return score::Result<CryptoResourceGuard>{
            score::unexpect,
            MakeError(CryptoErrorCode::kInternalError, "KEY_LOAD response has invalid resource_id type")};
    }

    CryptoResourceId resource_id{};
    resource_id.id = resource_id_result.value();
    resource_id.type = ResourceType::kKey;
    resource_id.persistence = ResourcePersistence::kEphemeral;

    // Extract optional provider id from response (param 0, index 1)
    auto provider_result = validator.getParameterAt<std::uint16_t>(0, 1);
    if (provider_result.has_value())
    {
        resource_id.primary_provider = provider_result.value();
    }

    return CryptoResourceGuardFactory::Make(m_release_callback, resource_id);
}

// ---------------------------------------------------------------------------
// Stubs — not yet implemented
// ---------------------------------------------------------------------------
score::Result<std::monostate> KeyManagementContextImpl::GenerateKey(
    const CryptoResourceId& /*target_slot*/,
    const std::optional<CryptoResourceId>& /*public_slot*/,
    const GenerateKeyParams& /*params*/)
{
    std::cerr << "[API][KeyMgmtContextImpl] ERROR: GenerateKey with target_slot not yet implemented\n";
    return score::Result<std::monostate>{
        score::unexpect,
        MakeError(CryptoErrorCode::kUnsupportedOperation, "GenerateKey with target_slot not yet implemented")};
}

score::Result<CryptoResourceGuard> KeyManagementContextImpl::DeriveKey(const DeriveKeyParams& /*params*/)
{
    std::cerr << "[API][KeyMgmtContextImpl] ERROR: DeriveKey not yet implemented\n";
    return score::Result<CryptoResourceGuard>{
        score::unexpect, MakeError(CryptoErrorCode::kUnsupportedOperation, "DeriveKey not yet implemented")};
}

score::Result<std::monostate> KeyManagementContextImpl::DeriveKey(const CryptoResourceId& /*target_slot*/,
                                                                  const DeriveKeyParams& /*params*/)
{
    std::cerr << "[API][KeyMgmtContextImpl] ERROR: DeriveKey not yet implemented\n";
    return score::Result<std::monostate>{
        score::unexpect, MakeError(CryptoErrorCode::kUnsupportedOperation, "DeriveKey not yet implemented")};
}

score::Result<CryptoResourceGuard> KeyManagementContextImpl::AgreeKey(const AgreeKeyParams& /*params*/)
{
    std::cerr << "[API][KeyMgmtContextImpl] ERROR: AgreeKey not yet implemented\n";
    return score::Result<CryptoResourceGuard>{
        score::unexpect, MakeError(CryptoErrorCode::kUnsupportedOperation, "AgreeKey not yet implemented")};
}

score::Result<std::monostate> KeyManagementContextImpl::AgreeKey(const CryptoResourceId& /*target_slot*/,
                                                                 const AgreeKeyParams& /*params*/)
{
    std::cerr << "[API][KeyMgmtContextImpl] ERROR: AgreeKey not yet implemented\n";
    return score::Result<std::monostate>{
        score::unexpect, MakeError(CryptoErrorCode::kUnsupportedOperation, "AgreeKey not yet implemented")};
}

score::Result<std::monostate> KeyManagementContextImpl::PersistKey(const CryptoResourceId& /*target_slot*/,
                                                                   const CryptoResourceId& /*ephemeral_key*/)
{
    std::cerr << "[API][KeyMgmtContextImpl] ERROR: PersistKey not yet implemented\n";
    return score::Result<std::monostate>{
        score::unexpect, MakeError(CryptoErrorCode::kUnsupportedOperation, "PersistKey not yet implemented")};
}

score::Result<CryptoResourceGuard> KeyManagementContextImpl::UnwrapKey(const UnwrapKeyParams& /*params*/)
{
    std::cerr << "[API][KeyMgmtContextImpl] ERROR: UnwrapKey not yet implemented\n";
    return score::Result<CryptoResourceGuard>{
        score::unexpect, MakeError(CryptoErrorCode::kUnsupportedOperation, "UnwrapKey not yet implemented")};
}

score::Result<std::monostate> KeyManagementContextImpl::UnwrapKey(const CryptoResourceId& /*target_slot*/,
                                                                  const UnwrapKeyParams& /*params*/)
{
    std::cerr << "[API][KeyMgmtContextImpl] ERROR: UnwrapKey not yet implemented\n";
    return score::Result<std::monostate>{
        score::unexpect, MakeError(CryptoErrorCode::kUnsupportedOperation, "UnwrapKey not yet implemented")};
}

score::Result<CryptoResourceGuard> KeyManagementContextImpl::ImportKey(const ImportKeyParams& /*params*/)
{
    std::cerr << "[API][KeyMgmtContextImpl] ERROR: ImportKey not yet implemented\n";
    return score::Result<CryptoResourceGuard>{
        score::unexpect, MakeError(CryptoErrorCode::kUnsupportedOperation, "ImportKey not yet implemented")};
}

score::Result<std::monostate> KeyManagementContextImpl::ImportKey(const CryptoResourceId& /*target_slot*/,
                                                                  const ImportKeyParams& /*params*/)
{
    std::cerr << "[API][KeyMgmtContextImpl] ERROR: ImportKey not yet implemented\n";
    return score::Result<std::monostate>{
        score::unexpect, MakeError(CryptoErrorCode::kUnsupportedOperation, "ImportKey not yet implemented")};
}

score::Result<std::size_t> KeyManagementContextImpl::WrapKey(const WrapKeyParams& /*params*/,
                                                             score::cpp::span<uint8_t> /*output*/)
{
    std::cerr << "[API][KeyMgmtContextImpl] ERROR: WrapKey not yet implemented\n";
    return score::Result<std::size_t>{score::unexpect,
                                      MakeError(CryptoErrorCode::kUnsupportedOperation, "WrapKey not yet implemented")};
}

score::Result<std::size_t> KeyManagementContextImpl::GetWrapKeySize(const WrapKeyParams& /*params*/)
{
    std::cerr << "[API][KeyMgmtContextImpl] ERROR: GetWrapKeySize not yet implemented\n";
    return score::Result<std::size_t>{
        score::unexpect, MakeError(CryptoErrorCode::kUnsupportedOperation, "GetWrapKeySize not yet implemented")};
}

score::Result<std::size_t> KeyManagementContextImpl::ExportKey(const CryptoResourceId& /*key*/,
                                                               score::cpp::span<uint8_t> /*output*/,
                                                               FormatType /*format*/)
{
    std::cerr << "[API][KeyMgmtContextImpl] ERROR: ExportKey not yet implemented\n";
    return score::Result<std::size_t>{
        score::unexpect, MakeError(CryptoErrorCode::kUnsupportedOperation, "ExportKey not yet implemented")};
}

score::Result<std::size_t> KeyManagementContextImpl::GetExportKeySize(const CryptoResourceId& /*key*/,
                                                                      FormatType /*format*/)
{
    std::cerr << "[API][KeyMgmtContextImpl] ERROR: GetExportKeySize not yet implemented\n";
    return score::Result<std::size_t>{
        score::unexpect, MakeError(CryptoErrorCode::kUnsupportedOperation, "GetExportKeySize not yet implemented")};
}

score::Result<std::monostate> KeyManagementContextImpl::ClearKey(const CryptoResourceId& /*key*/)
{
    std::cerr << "[API][KeyMgmtContextImpl] ERROR: ClearKey not yet implemented\n";
    return score::Result<std::monostate>{
        score::unexpect, MakeError(CryptoErrorCode::kUnsupportedOperation, "ClearKey not yet implemented")};
}

score::Result<KeySlotInfo> KeyManagementContextImpl::GetKeySlotInfo(const CryptoResourceId& /*slot*/)
{
    std::cerr << "[API][KeyMgmtContextImpl] ERROR: GetKeySlotInfo not yet implemented\n";
    return score::Result<KeySlotInfo>{
        score::unexpect, MakeError(CryptoErrorCode::kUnsupportedOperation, "GetKeySlotInfo not yet implemented")};
}

}  // namespace crypto
}  // namespace mw
}  // namespace score
