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

#include "score/crypto/daemon/provider/score_provider/operations/key_management/score_key_management_handler.hpp"

#include <iostream>
#include <string_view>

namespace score::crypto::daemon::provider::score_provider::operations::key_management
{

namespace
{
constexpr std::string_view LOG_PREFIX = "[SCORE_KEY_MGMT_HANDLER] ";
}

ScoreKeyManagementHandler::ScoreKeyManagementHandler(std::unique_ptr<crypto_executor::KeyManagementExecutor> executor)
    : m_executor{std::move(executor)}, m_ctx{}
{
}

Expected<std::monostate, common::DaemonErrorCode> ScoreKeyManagementHandler::InitializeContext(
    const handler::InitializationParams& init_params)
{
    m_ctx.client_id = init_params.client_id;
    m_ctx.context_node_id = init_params.context_node_id;
    if (init_params.provider_id != common::kInvalidProviderId)
    {
        m_ctx.provider_id = init_params.provider_id;
    }
    return std::monostate{};
}

Expected<common::ResponseParameters, common::DaemonErrorCode> ScoreKeyManagementHandler::Execute(
    const common::OperationIdentifier& operationId,
    common::RequestParameters& request)
{
    if (!m_executor)
    {
        std::cerr << LOG_PREFIX << "Execute: executor not injected\n";
        return make_unexpected(common::DaemonErrorCode::kInvalidArgument);
    }
    return m_executor->Execute(m_ctx, operationId, request);
}

Expected<std::monostate, common::DaemonErrorCode> ScoreKeyManagementHandler::Reset()
{
    return std::monostate{};
}

}  // namespace score::crypto::daemon::provider::score_provider::operations::key_management
