// =============================================================================
//  C O P Y R I G H T
// =============================================================================
//  Copyright (c) 2026 by ETAS GmbH. All rights reserved.
//
//  The reproduction, distribution and utilization of this file as
//  well as the communication of its contents to others without express
//  authorization is prohibited. Offenders will be held liable for the
//  payment of damages. All rights reserved in the event of the grant
//  of a patent, utility model or design.
// =============================================================================

#include "score/crypto/daemon/provider/pkcs11/operations/key_management/pkcs11_key_management_handler.hpp"

#include "score/crypto/daemon/provider/pkcs11/pkcs11_provider.hpp"

#include <iostream>

namespace score::crypto::daemon::provider::pkcs11
{

Pkcs11KeyManagementHandler::Pkcs11KeyManagementHandler(std::shared_ptr<Pkcs11Provider> provider,
                                                       std::unique_ptr<crypto_executor::KeyManagementExecutor> executor,
                                                       common::ProviderId provider_id)
    : m_provider{std::move(provider)}, m_executor{std::move(executor)}, m_ctx{provider_id, 0U, 0U}
{
}

Expected<std::monostate, score::crypto::daemon::common::DaemonErrorCode> Pkcs11KeyManagementHandler::InitializeContext(
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

Expected<std::monostate, score::crypto::daemon::common::DaemonErrorCode> Pkcs11KeyManagementHandler::Reset()
{
    return std::monostate{};
}

Expected<common::ResponseParameters, score::crypto::daemon::common::DaemonErrorCode>
Pkcs11KeyManagementHandler::Execute(const common::OperationIdentifier& operationId, common::RequestParameters& request)
{
    if (!m_executor)
    {
        std::cerr << LOG_PREFIX << "Execute: executor not injected\n";
        return score::crypto::make_unexpected(score::crypto::daemon::common::DaemonErrorCode::kInvalidArgument);
    }
    return m_executor->Execute(m_ctx, operationId, request);
}

static constexpr const char* kSupportedAlgorithms[] =
    {"HMAC-SHA256", "HMAC-SHA384", "HMAC-SHA512", "AES-128", "AES-192", "AES-256"};

bool Pkcs11KeyManagementHandler::IsAlgorithmSupported(const common::AlgorithmId& algorithm) noexcept
{
    for (const char* supported : kSupportedAlgorithms)
    {
        if (algorithm == supported)
        {
            return true;
        }
    }
    return false;
}

}  // namespace score::crypto::daemon::provider::pkcs11
