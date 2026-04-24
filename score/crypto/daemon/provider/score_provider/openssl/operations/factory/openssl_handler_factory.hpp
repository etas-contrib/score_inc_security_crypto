// =============================================================================
//  C O P Y R I G H T
// -----------------------------------------------------------------------------
//  Copyright (c) 2025-2026 by ETAS GmbH. All rights reserved.
// =============================================================================

#ifndef SCORE_CRYPTO_DAEMON_PROVIDER_SCORE_PROVIDER_OPENSSL_OPERATIONS_FACTORY_OPENSSL_HANDLER_FACTORY_HPP
#define SCORE_CRYPTO_DAEMON_PROVIDER_SCORE_PROVIDER_OPENSSL_OPERATIONS_FACTORY_OPENSSL_HANDLER_FACTORY_HPP

#include "score/crypto/daemon/common/types.hpp"
#include "score/crypto/daemon/key_management/core/key_management_service.hpp"
#include "score/crypto/daemon/key_management/interfaces/i_key_factory.hpp"
#include "score/crypto/daemon/key_management/interfaces/i_key_slot_handler.hpp"
#include "score/crypto/daemon/provider/score_provider/operations/factory/score_handler_factory.hpp"
#include "score/result/result.h"

#include <memory>

namespace score::crypto::daemon::provider::score_provider::openssl::handler
{

class OpenSslHandlerFactory final
    : public ::score::crypto::daemon::provider::score_provider::operations::factory::ScoreHandlerFactory
{
  public:
    OpenSslHandlerFactory(std::shared_ptr<key_management::IKeyFactory> factory,
                          std::shared_ptr<key_management::IKeySlotHandler> slot_handler,
                          key_management::KeyManagementService::Sptr km_service);

    ~OpenSslHandlerFactory() override = default;

  protected:
    [[nodiscard]] ::score::Result<::score::crypto::daemon::provider::handler::Handler::Sptr> CreateHashHandler(
        const common::AlgorithmId& algorithm) override;
    [[nodiscard]] ::score::Result<::score::crypto::daemon::provider::handler::Handler::Sptr> CreateMacHandler(
        const common::AlgorithmId& algorithm) override;
    [[nodiscard]] ::score::Result<::score::crypto::daemon::provider::handler::Handler::Sptr>
    CreateKeyManagementHandler() override;
};

}  // namespace score::crypto::daemon::provider::score_provider::openssl::handler

#endif  // SCORE_CRYPTO_DAEMON_PROVIDER_SCORE_PROVIDER_OPENSSL_OPERATIONS_FACTORY_OPENSSL_HANDLER_FACTORY_HPP
