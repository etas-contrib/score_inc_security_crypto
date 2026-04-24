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

#ifndef SCORE_CRYPTO_DAEMON_PROVIDER_SCORE_PROVIDER_OPENSSL_OPERATIONS_KEY_MANAGEMENT_HANDLER_HPP
#define SCORE_CRYPTO_DAEMON_PROVIDER_SCORE_PROVIDER_OPENSSL_OPERATIONS_KEY_MANAGEMENT_HANDLER_HPP

#include "score/crypto/daemon/provider/executors/key_mgmt_executor.hpp"
#include "score/crypto/daemon/provider/score_provider/operations/key_management/score_key_management_handler.hpp"

#include <memory>

namespace score::crypto::daemon::provider::score_provider::openssl::handler
{

/// OpenSSL-specific key management handler.
/// Currently delegates entirely to ScoreKeyManagementHandler base.
class OpenSslKeyManagementHandler final
    : public ::score::crypto::daemon::provider::score_provider::operations::key_management::ScoreKeyManagementHandler
{
  public:
    explicit OpenSslKeyManagementHandler(std::unique_ptr<crypto_executor::KeyManagementExecutor> executor);
    ~OpenSslKeyManagementHandler() override = default;

    OpenSslKeyManagementHandler(const OpenSslKeyManagementHandler&) = delete;
    OpenSslKeyManagementHandler& operator=(const OpenSslKeyManagementHandler&) = delete;
    OpenSslKeyManagementHandler(OpenSslKeyManagementHandler&&) = delete;
    OpenSslKeyManagementHandler& operator=(OpenSslKeyManagementHandler&&) = delete;
};

}  // namespace score::crypto::daemon::provider::score_provider::openssl::handler

#endif  // SCORE_CRYPTO_DAEMON_PROVIDER_SCORE_PROVIDER_OPENSSL_OPERATIONS_KEY_MANAGEMENT_HANDLER_HPP
