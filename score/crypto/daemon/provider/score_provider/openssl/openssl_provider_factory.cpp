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

#include "score/crypto/daemon/provider/score_provider/openssl/openssl_provider_factory.hpp"

#include <memory>

#include "score/crypto/daemon/common/types.hpp"
#include "score/crypto/daemon/provider/provider_manager.hpp"
#include "score/crypto/daemon/provider/score_provider/openssl/provider_openssl.hpp"

namespace score::crypto::daemon::provider::score_provider::openssl
{

bool OpenSSLProviderFactory::CreateAndRegister(ProviderManager& manager)
{
    auto openSSLProvider = std::make_shared<OpenSSL>();
    return manager.RegisterProvider(
        common::kProviderNameOpenSSL, openSSLProvider, common::CryptoProviderType::SOFTWARE);
}

}  // namespace score::crypto::daemon::provider::score_provider::openssl
