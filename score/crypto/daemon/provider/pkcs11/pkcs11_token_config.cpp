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

#include "score/crypto/daemon/provider/pkcs11/pkcs11_token_config.hpp"

// pkcs11_module.hpp brings in Pkcs11ProviderConfig + Pkcs11SessionCleanupStrategy;
// pkcs11_provider_factory.hpp brings in SetTokenConfigs() and the full class definition.
#include "score/crypto/daemon/provider/pkcs11/pkcs11_module.hpp"
#include "score/crypto/daemon/provider/pkcs11/pkcs11_provider_factory.hpp"

namespace score::crypto::daemon::provider::pkcs11
{

void Pkcs11Config::PopulateDefaults()
{
    if (!m_tokens.empty())
    {
        return;  // Entries already present (from config file or test fixture).
    }
    Pkcs11TokenEntry softHsm{};
    softHsm.tokenLabel = "SoftHSM";
    softHsm.userPin = "1234";
    softHsm.providerName = "SOFTHSM";
    softHsm.useHardCleanup = true;
    m_tokens.push_back(std::move(softHsm));
}

void Pkcs11Config::Configure(Pkcs11ProviderFactory& factory) const
{
    std::vector<Pkcs11ProviderConfig> configs;
    configs.reserve(m_tokens.size());
    for (const auto& entry : m_tokens)
    {
        Pkcs11ProviderConfig cfg{};
        cfg.tokenLabel = entry.tokenLabel;
        cfg.tokenModel = entry.tokenModel;
        cfg.userPin = entry.userPin;
        cfg.providerName = entry.providerName;
        cfg.cleanupStrategy = entry.useHardCleanup ? Pkcs11SessionCleanupStrategy::kHardCleanup
                                                   : Pkcs11SessionCleanupStrategy::kSoftCleanup;
        configs.push_back(std::move(cfg));
    }
    factory.SetTokenConfigs(std::move(configs));
}

}  // namespace score::crypto::daemon::provider::pkcs11
