// =============================================================================
//  C O P Y R I G H T
// -----------------------------------------------------------------------------
//  Copyright (c) 2025-2026 by ETAS GmbH. All rights reserved.
//
//  The reproduction, distribution and utilization of this file as
//  well as the communication of its contents to others without express
//  authorization is prohibited. Offenders will be held liable for the
//  payment of damages. All rights reserved in the event of the grant
//  of a patent, utility model or design.
// =============================================================================

#include "score/crypto/daemon/provider/score_provider/openssl/provider_openssl.hpp"
#include "score/crypto/daemon/key_management/slot/file_backed_slot_handler.hpp"
#include "score/crypto/daemon/provider/score_provider/openssl/key_management/openssl_key_factory.hpp"
#include "score/crypto/daemon/provider/score_provider/openssl/operations/factory/openssl_handler_factory.hpp"
#include "score/mw/log/logging.h"
#include <openssl/crypto.h>

namespace score::crypto::daemon::provider::score_provider::openssl
{

OpenSSL::OpenSSL() : m_factory(nullptr) {}

OpenSSL::~OpenSSL()
{
    Shutdown();
}

bool OpenSSL::Initialize(const ProviderInitContext& ctx)
{
    if (m_initialized)
    {
        return true;
    }

    // Base class stores ID and name.
    ScoreProvider::Initialize(ctx);

    if (!OPENSSL_init_crypto(OPENSSL_INIT_LOAD_CRYPTO_STRINGS | OPENSSL_INIT_ADD_ALL_CIPHERS |
                                 OPENSSL_INIT_ADD_ALL_DIGESTS | OPENSSL_INIT_LOAD_CONFIG,
                             nullptr))
    {
        score::mw::log::LogError() << "[OpenSSL] Error: Failed to initialize OpenSSL";
        m_initialized = false;
        return false;
    }
    score::mw::log::LogDebug() << "[OpenSSL] Initialized successfully (ID: " << m_numeric_id
                               << ", Name: " << m_provider_name << ")";

    // Create key factory.
    m_factory = std::make_shared<::score::crypto::daemon::provider::openssl::OpenSslKeyFactory>(m_numeric_id);

    m_initialized = true;
    return m_initialized;
}

void OpenSSL::Shutdown()
{
    if (!m_initialized)
    {
        return;
    }

    m_factory.reset();
    m_keyManagementService.reset();

    // Clean up OpenSSL resources
    OPENSSL_cleanup();

    // Base class resets factory and flags.
    ScoreProvider::Shutdown();
}

std::shared_ptr<::score::crypto::daemon::provider::handler::ICryptoHandlerFactory> OpenSSL::CreateHandlerFactory()
{
    return std::make_shared<handler::OpenSslHandlerFactory>(m_factory, GetKeySlotHandler({}), m_keyManagementService);
}

std::shared_ptr<key_management::IKeyFactory> OpenSSL::GetKeyFactory()
{
    return m_factory;
}

::score::crypto::daemon::key_management::IKeySlotHandler::Sptr OpenSSL::GetKeySlotHandler(
    const ::score::crypto::daemon::key_management::KeySlotConfig& /*config*/)
{
    return std::make_shared<key_management::FileBackedSlotHandler>(m_factory);
}

void OpenSSL::SetKeyManagementService(std::shared_ptr<key_management::KeyManagementService> service)
{
    m_keyManagementService = std::move(service);
}

}  // namespace score::crypto::daemon::provider::score_provider::openssl
