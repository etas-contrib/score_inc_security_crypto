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

#ifndef SCORE_CRYPTO_DAEMON_PROVIDER_SCORE_PROVIDER_SCORE_PROVIDER_HPP
#define SCORE_CRYPTO_DAEMON_PROVIDER_SCORE_PROVIDER_SCORE_PROVIDER_HPP

#include "score/crypto/daemon/provider/handler/i_crypto_handler_factory.hpp"
#include "score/crypto/daemon/provider/i_provider.hpp"

#include <memory>

namespace score::crypto::daemon::provider::score_provider
{

/// @brief Abstract base class for providers under the score interface family.
///
/// Provides default lifecycle implementations (Initialize, Shutdown, getters)
/// and lazy handler factory creation via the CreateHandlerFactory() hook.
/// Concrete providers (e.g. OpenSSL) inherit and override as needed.
///
/// Key management methods default to nullptr / no-op. A concrete provider
/// overrides them if it supports key operations.
class ScoreProvider : public IProvider
{
  public:
    ScoreProvider() = default;
    ~ScoreProvider() override = default;

    ScoreProvider(const ScoreProvider&) = delete;
    ScoreProvider& operator=(const ScoreProvider&) = delete;
    ScoreProvider(ScoreProvider&&) = delete;
    ScoreProvider& operator=(ScoreProvider&&) = delete;

    // --- IProvider lifecycle ---
    bool Initialize(const ProviderInitContext& ctx) override;
    void Shutdown() override;
    common::ProviderId GetProviderId() const override;
    const common::ProviderName& GetProviderName() const override;

    /// Lazy-creates the handler factory via CreateHandlerFactory().
    std::shared_ptr<handler::ICryptoHandlerFactory> GetCryptoHandlerFactory() override;

  protected:
    /// Override in concrete provider to construct the provider-specific handler factory.
    [[nodiscard]] virtual std::shared_ptr<handler::ICryptoHandlerFactory> CreateHandlerFactory() = 0;

    bool m_initialized{false};
    common::ProviderId m_numeric_id{common::kInvalidProviderId};
    common::ProviderName m_provider_name{};

  private:
    handler::ICryptoHandlerFactory::Sptr m_handler_factory;
};

}  // namespace score::crypto::daemon::provider::score_provider

#endif  // SCORE_CRYPTO_DAEMON_PROVIDER_SCORE_PROVIDER_SCORE_PROVIDER_HPP
