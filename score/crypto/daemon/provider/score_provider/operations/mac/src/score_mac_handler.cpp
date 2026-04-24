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

#include "score/crypto/daemon/provider/score_provider/operations/mac/score_mac_handler.hpp"
#include "score/crypto/daemon/provider/score_provider/operations/mac/mac_executor.hpp"

namespace score::crypto::daemon::provider::score_provider::operations::mac
{

using common::DaemonErrorCode;
using common::ResponseParameters;
using common::StreamOperationState;

ScoreMacHandler::ScoreMacHandler(std::unique_ptr<MacExecutor> executor, const common::AlgorithmId& algorithm)
    : m_algorithm{algorithm}, m_state{StreamOperationState::IDLE}, m_executor{std::move(executor)}
{
}

Expected<ResponseParameters, DaemonErrorCode> ScoreMacHandler::Execute(const common::OperationIdentifier& operationId,
                                                                       common::RequestParameters& request)
{
    return m_executor->Execute(*this, operationId, request);
}

Expected<std::monostate, DaemonErrorCode> ScoreMacHandler::InitializeContext(
    const handler::InitializationParams& /*init_params*/)
{
    m_state = StreamOperationState::IDLE;
    return std::monostate{};
}

Expected<std::monostate, DaemonErrorCode> ScoreMacHandler::Reset()
{
    m_state = StreamOperationState::IDLE;
    return std::monostate{};
}

// ---------------------------------------------------------------------------
// Default typed operations — return unsupported unless overridden
// ---------------------------------------------------------------------------

std::size_t ScoreMacHandler::GetMacSize() const noexcept
{
    return 0U;
}

Expected<std::monostate, DaemonErrorCode> ScoreMacHandler::StartMac(
    const std::optional<common::RequestParameter> /*initialDataOrIV*/)
{
    return make_unexpected(DaemonErrorCode::kUnsupportedOperation);
}

Expected<std::monostate, DaemonErrorCode> ScoreMacHandler::UpdateMac(const common::RequestParameter& /*dataToMac*/)
{
    return make_unexpected(DaemonErrorCode::kUnsupportedOperation);
}

Expected<ResponseParameters, DaemonErrorCode> ScoreMacHandler::FinalizeMac(
    std::optional<common::RequestParameter> /*macOutput*/,
    const std::optional<common::RequestParameter> /*finalDataToMac*/)
{
    return make_unexpected(DaemonErrorCode::kUnsupportedOperation);
}

Expected<bool, DaemonErrorCode> ScoreMacHandler::VerifyMac(const common::RequestParameter& /*expectedTag*/)
{
    return make_unexpected(DaemonErrorCode::kUnsupportedOperation);
}

}  // namespace score::crypto::daemon::provider::score_provider::operations::mac
