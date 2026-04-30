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

#include "score/crypto/daemon/provider/score_provider/operations/hash/score_hash_handler.hpp"
#include "score/crypto/daemon/provider/score_provider/operations/hash/hash_executor.hpp"

namespace score::crypto::daemon::provider::score_provider::operations::hash
{

using common::DaemonErrorCode;
using common::ResponseParameters;
using common::StreamOperationState;

ScoreHashHandler::ScoreHashHandler(std::unique_ptr<HashExecutor> executor, const common::AlgorithmId& algorithm)
    : m_algorithm{algorithm}, m_state{StreamOperationState::IDLE}, m_executor{std::move(executor)}
{
}

Expected<ResponseParameters, DaemonErrorCode> ScoreHashHandler::Execute(const common::OperationIdentifier& operationId,
                                                                        common::RequestParameters& request)
{
    return m_executor->Execute(*this, operationId, request);
}

Expected<std::monostate, DaemonErrorCode> ScoreHashHandler::InitializeContext(
    const handler::InitializationParams& /*init_params*/)
{
    m_state = StreamOperationState::IDLE;
    return std::monostate{};
}

Expected<std::monostate, DaemonErrorCode> ScoreHashHandler::Reset()
{
    m_state = StreamOperationState::IDLE;
    return std::monostate{};
}

// ---------------------------------------------------------------------------
// Default typed operations — return unsupported unless overridden
// ---------------------------------------------------------------------------

Expected<std::monostate, DaemonErrorCode> ScoreHashHandler::InitHash(
    const std::optional<common::RequestParameter> /*initialDataOrIV*/)
{
    return make_unexpected(DaemonErrorCode::kUnsupportedOperation);
}

Expected<std::monostate, DaemonErrorCode> ScoreHashHandler::UpdateHash(const common::RequestParameter& /*dataToHash*/)
{
    return make_unexpected(DaemonErrorCode::kUnsupportedOperation);
}

Expected<ResponseParameters, DaemonErrorCode> ScoreHashHandler::FinalizeHash(
    std::optional<common::RequestParameter> /*hashOutput*/,
    const std::optional<common::RequestParameter> /*finalDataToHash*/)
{
    return make_unexpected(DaemonErrorCode::kUnsupportedOperation);
}

Expected<ResponseParameters, DaemonErrorCode> ScoreHashHandler::SingleShotHash(
    const common::RequestParameter& /*dataToHash*/,
    std::optional<common::RequestParameter> /*outputHash*/,
    std::optional<common::RequestParameter> /*iv*/)
{
    return make_unexpected(DaemonErrorCode::kUnsupportedOperation);
}

Expected<ResponseParameters, DaemonErrorCode> ScoreHashHandler::GetDigestSize() const
{
    const auto size = common::LookupDigestSize(std::string_view{m_algorithm.data(), m_algorithm.size()});
    ResponseParameters response;
    response.push_back(size.value_or(64U));
    return response;
}

}  // namespace score::crypto::daemon::provider::score_provider::operations::hash
