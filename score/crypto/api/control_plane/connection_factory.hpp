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

#ifndef SCORE_CRYPTO_API_CONTROLLPLANE_CONNECTION_FACTORY_HPP
#define SCORE_CRYPTO_API_CONTROLLPLANE_CONNECTION_FACTORY_HPP

#include <memory>
#include <string_view>

#include "score/crypto/common/types.hpp"
#include "score/mw/crypto/api/common/error_domain.hpp"

#include "score/crypto/api/control_plane/i_connection.hpp"

namespace score::crypto::api::control_plane
{

/// Factory for creating control client nodes
/// Handles the creation and initialization of node connections to the daemon
class ConnectionFactory
{
  public:
    ConnectionFactory() = default;
    ~ConnectionFactory() = default;

    // Disable copy, allow move
    ConnectionFactory(const ConnectionFactory&) = delete;
    ConnectionFactory& operator=(const ConnectionFactory&) = delete;
    ConnectionFactory(ConnectionFactory&&) = default;
    ConnectionFactory& operator=(ConnectionFactory&&) = default;

    Expected<std::unique_ptr<IConnection>, score::mw::crypto::CryptoErrorCode> CreateConnection(
        std::string_view endpoint);
};

}  // namespace score::crypto::api::control_plane

#endif  // SCORE_CRYPTO_API_CONTROLLPLANE_CONNECTION_FACTORY_HPP
