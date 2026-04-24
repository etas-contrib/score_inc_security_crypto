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

#ifndef SCORE_CRYPTO_DAEMON_PROVIDER_SCORE_PROVIDER_OPENSSL_PROVIDER_OPENSSL_HPP
#define SCORE_CRYPTO_DAEMON_PROVIDER_SCORE_PROVIDER_OPENSSL_PROVIDER_OPENSSL_HPP

#include <memory>

#include "score/crypto/daemon/provider/score_provider/score_provider.hpp"

namespace score::crypto::daemon::provider::score_provider::openssl
{

/// @brief OpenSSL software-only crypto provider.
///
/// Inherits ScoreProvider for lifecycle and lazy factory creation.
/// Adds OpenSSL-specific initialization (OPENSSL_init_crypto) and
/// key management (in-process key generation/import/release with optional
/// file-backed persistence via FileBackedSlotHandler).
class OpenSSL final : public ::score::crypto::daemon::provider::score_provider::ScoreProvider
{
  public:
    OpenSSL();
    ~OpenSSL() override;

    OpenSSL(const OpenSSL&) = delete;
    OpenSSL& operator=(const OpenSSL&) = delete;
    OpenSSL(OpenSSL&&) = delete;
    OpenSSL& operator=(OpenSSL&&) = delete;

    // --- IProvider lifecycle (OpenSSL-specific) ---
    bool Initialize(const ProviderInitContext& ctx) override;
    void Shutdown() override;

    // --- Key management capability ---
    std::shared_ptr<key_management::IKeyFactory> GetKeyFactory() override;
    std::shared_ptr<key_management::IKeySlotHandler> GetKeySlotHandler(
        const key_management::KeySlotConfig& config) override;
    void SetKeyManagementService(std::shared_ptr<key_management::KeyManagementService> service) override;

  protected:
    /// Creates the OpenSSL-specific handler factory.
    [[nodiscard]] std::shared_ptr<::score::crypto::daemon::provider::handler::ICryptoHandlerFactory>
    CreateHandlerFactory() override;

  private:
    std::shared_ptr<key_management::IKeyFactory> m_factory;
    std::shared_ptr<key_management::KeyManagementService> m_keyManagementService;
};

}  // namespace score::crypto::daemon::provider::score_provider::openssl

#endif  // SCORE_CRYPTO_DAEMON_PROVIDER_SCORE_PROVIDER_OPENSSL_PROVIDER_OPENSSL_HPP
