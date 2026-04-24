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

#include "score/crypto/daemon/provider/pkcs11/pkcs11_provider_factory.hpp"

#include <memory>

#include "score/crypto/daemon/common/daemon_error.hpp"
#include "score/crypto/daemon/common/types.hpp"
#include "score/crypto/daemon/provider/pkcs11/pkcs11_module.hpp"
#include "score/crypto/daemon/provider/pkcs11/pkcs11_provider.hpp"
#include "score/crypto/daemon/provider/provider_manager.hpp"

namespace score::crypto::daemon::provider::pkcs11
{

Pkcs11ProviderFactory::Pkcs11ProviderFactory(std::vector<Pkcs11ProviderConfig> configs)
    : m_injected_configs{std::move(configs)}
{
}

void Pkcs11ProviderFactory::SetTokenConfigs(std::vector<Pkcs11ProviderConfig> configs)
{
    m_injected_configs = std::move(configs);
}

bool Pkcs11ProviderFactory::CreateAndRegister(ProviderManager& manager)
{
    if (m_injected_configs.empty())
    {
        return true;
    }

    // All tokens on the same linked library MUST share a single Pkcs11Module
    // so that C_Initialize is called exactly once and C_Finalize is deferred
    // until the very last provider (and therefore all its sessions) is destroyed.
    auto pkcs11Module = std::make_shared<Pkcs11Module>();
    const auto initResult = pkcs11Module->Init();
    if (!initResult.has_value())
    {
        return false;
    }

    for (const auto& config : m_injected_configs)
    {
        auto provider = std::make_shared<Pkcs11Provider>(config, pkcs11Module);
        if (!manager.RegisterProvider(config.providerName, provider, common::CryptoProviderType::HARDWARE))
        {
            return false;
        }
    }

    return true;
}

}  // namespace score::crypto::daemon::provider::pkcs11
