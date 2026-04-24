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

#include "score/crypto/daemon/provider/score_provider/score_provider_factory.hpp"
#include "score/crypto/daemon/provider/provider_manager.hpp"
#include "score/crypto/daemon/provider/score_provider/openssl/openssl_provider_factory.hpp"

#include <iostream>

namespace score::crypto::daemon::provider::score_provider
{

ScoreProviderFactory::ScoreProviderFactory(std::vector<ScoreProviderEntry> configs) : m_configs{std::move(configs)} {}

void ScoreProviderFactory::SetConfigs(std::vector<ScoreProviderEntry> configs)
{
    m_configs = std::move(configs);
}

bool ScoreProviderFactory::CreateAndRegister(ProviderManager& manager)
{
    bool all_ok = true;
    for (const auto& entry : m_configs)
    {
        if (entry.providerImpl == "openssl")
        {
            openssl::OpenSSLProviderFactory openssl_factory;
            if (!openssl_factory.CreateAndRegister(manager))
            {
                std::cerr << "[ScoreProviderFactory] Failed to create OpenSSL provider: " << entry.providerName << "\n";
                all_ok = false;
            }
        }
        else
        {
            std::cerr << "[ScoreProviderFactory] Unknown provider implementation: " << entry.providerImpl << "\n";
            all_ok = false;
        }
    }
    return all_ok;
}

}  // namespace score::crypto::daemon::provider::score_provider
