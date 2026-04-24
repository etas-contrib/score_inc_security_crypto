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

#include "score/crypto/daemon/provider/score_provider/openssl/operations/factory/openssl_handler_factory.hpp"
#include "score/crypto/daemon/common/daemon_error.hpp"
#include "score/crypto/daemon/provider/executors/key_mgmt_executor.hpp"
#include "score/crypto/daemon/provider/score_provider/openssl/operations/hash/openssl_hash_handler.hpp"
#include "score/crypto/daemon/provider/score_provider/openssl/operations/key_management/openssl_key_management_handler.hpp"
#include "score/crypto/daemon/provider/score_provider/openssl/operations/mac/openssl_hmac_handler.hpp"
#include "score/crypto/daemon/provider/score_provider/operations/hash/hash_executor.hpp"
#include "score/crypto/daemon/provider/score_provider/operations/mac/mac_executor.hpp"
#include "score/result/result.h"
#include <iostream>

namespace score::crypto::daemon::provider::score_provider::openssl::handler
{

using HandlerSptr = ::score::crypto::daemon::provider::handler::Handler::Sptr;

OpenSslHandlerFactory::OpenSslHandlerFactory(std::shared_ptr<key_management::IKeyFactory> km_handler,
                                             std::shared_ptr<key_management::IKeySlotHandler> slot_handler,
                                             key_management::KeyManagementService::Sptr km_service)
    : ScoreHandlerFactory{std::move(km_handler), std::move(slot_handler), std::move(km_service)}
{
}

score::Result<HandlerSptr> OpenSslHandlerFactory::CreateHashHandler(const common::AlgorithmId& algorithm)
{
    if (!OpenSslHashHandler::IsAlgorithmSupported(algorithm))
    {
        score::result::Error error(
            static_cast<score::result::ErrorCode>(score::mw::crypto::CryptoErrorCode::kUnsupportedAlgorithm),
            score::mw::crypto::kCryptoErrorDomain,
            "Algorithm not supported for handler: " + algorithm);
        return score::Result<HandlerSptr>(score::unexpect, error);
    }
    auto hash_executor = std::make_unique<operations::hash::HashExecutor>();
    return std::make_shared<OpenSslHashHandler>(std::move(hash_executor), algorithm);
}

score::Result<HandlerSptr> OpenSslHandlerFactory::CreateMacHandler(const common::AlgorithmId& algorithm)
{
    if (!OpenSslHmacHandler::IsAlgorithmSupported(algorithm))
    {
        score::result::Error error(
            static_cast<score::result::ErrorCode>(score::mw::crypto::CryptoErrorCode::kUnsupportedAlgorithm),
            score::mw::crypto::kCryptoErrorDomain,
            "Algorithm not supported for handler: " + algorithm);
        return score::Result<HandlerSptr>(score::unexpect, error);
    }
    auto mac_executor = std::make_unique<operations::mac::MacExecutor>();
    return std::make_shared<OpenSslHmacHandler>(std::move(mac_executor), algorithm);
}

score::Result<HandlerSptr> OpenSslHandlerFactory::CreateKeyManagementHandler()
{
    auto executor =
        std::make_unique<crypto_executor::KeyManagementExecutor>(m_key_factory, m_slot_handler, m_km_service);
    return std::make_shared<OpenSslKeyManagementHandler>(std::move(executor));
}

}  // namespace score::crypto::daemon::provider::score_provider::openssl::handler
