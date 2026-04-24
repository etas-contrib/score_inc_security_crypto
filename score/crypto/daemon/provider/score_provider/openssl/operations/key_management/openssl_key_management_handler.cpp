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

#include "score/crypto/daemon/provider/score_provider/openssl/operations/key_management/openssl_key_management_handler.hpp"

namespace score::crypto::daemon::provider::score_provider::openssl::handler
{

OpenSslKeyManagementHandler::OpenSslKeyManagementHandler(
    std::unique_ptr<crypto_executor::KeyManagementExecutor> executor)
    : ScoreKeyManagementHandler{std::move(executor)}
{
}

}  // namespace score::crypto::daemon::provider::score_provider::openssl::handler
