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

#include "score/crypto/daemon/provider/score_provider/score_provider_config.hpp"

#include "score/crypto/daemon/provider/score_provider/score_provider_factory.hpp"

namespace score::crypto::daemon::provider::score_provider
{

void ScoreProviderConfig::PopulateDefaults()
{
    if (!m_providers.empty())
    {
        return;  // Entries already present (from config file or test fixture).
    }
    ScoreProviderEntry openssl{};
    openssl.providerName = "OPENSSL";
    openssl.providerImpl = "openssl";
    m_providers.push_back(std::move(openssl));
}

void ScoreProviderConfig::Configure(ScoreProviderFactory& factory) const
{
    factory.SetConfigs(m_providers);
}

}  // namespace score::crypto::daemon::provider::score_provider
