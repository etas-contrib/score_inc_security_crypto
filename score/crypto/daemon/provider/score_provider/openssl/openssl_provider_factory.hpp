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

#ifndef SCORE_CRYPTO_DAEMON_PROVIDER_SCORE_PROVIDER_OPENSSL_PROVIDER_FACTORY_HPP
#define SCORE_CRYPTO_DAEMON_PROVIDER_SCORE_PROVIDER_OPENSSL_PROVIDER_FACTORY_HPP

#include "score/crypto/daemon/provider/i_provider_factory.hpp"

namespace score::crypto::daemon::provider::score_provider::openssl
{

/**
 * @brief Factory that creates and registers the OpenSSL software provider.
 *
 * Constructs an openssl::OpenSSL instance and registers it under the
 * common::kProviderNameOpenSSL name with CryptoProviderType::SOFTWARE.
 *
 * No configuration fields are required — the OpenSSL provider needs no
 * per-token setup beyond what is compiled in.
 */
class OpenSSLProviderFactory final : public IProviderFactory
{
  public:
    OpenSSLProviderFactory() = default;
    ~OpenSSLProviderFactory() override = default;

    /**
     * @brief Constructs an OpenSSL provider and registers it as SOFTWARE.
     *
     * @param manager  The ProviderManager to register the provider into.
     * @return true if the provider was registered successfully.
     */
    bool CreateAndRegister(ProviderManager& manager) override;
};

}  // namespace score::crypto::daemon::provider::score_provider::openssl

#endif  // SCORE_CRYPTO_DAEMON_PROVIDER_SCORE_PROVIDER_OPENSSL_PROVIDER_FACTORY_HPP
