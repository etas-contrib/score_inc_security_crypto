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

#include "score/mw/log/logging.h"

#include <memory>
#include <string_view>

#include "score/crypto/common/types.hpp"

#include "score/crypto/api/control_plane/connection_factory.hpp"
#include "score/crypto/api/control_plane/i_connection.hpp"
#include "score/crypto/api/control_plane/src/connection_impl.hpp"
#include "score/mw/crypto/api/common/error_domain.hpp"

namespace score::crypto::api::control_plane
{

Expected<std::unique_ptr<IConnection>, score::mw::crypto::CryptoErrorCode> ConnectionFactory::CreateConnection(
    std::string_view endpoint)
{
    const std::string_view unixProtocolPrefix = "unix://";
    if (endpoint.rfind(unixProtocolPrefix, 0) != 0)
    {
        score::mw::log::LogError()
            << "[CONTROL_CLIENT_NODE_FACTORY] ERROR - Unsupported endpoint protocol. Only unix domain sockets "
               "are supported.";
        return make_unexpected(score::mw::crypto::CryptoErrorCode::kInvalidArgument);
    }

    const std::string_view socketPath = endpoint.substr(unixProtocolPrefix.size());

    auto connection = std::make_unique<ConnectionImpl>(socketPath);
    if (!connection)
    {
        score::mw::log::LogError() << "[CONTROL_CLIENT_NODE_FACTORY] ERROR - Failed to create connection to socket: "
                                   << socketPath;
        return make_unexpected(score::mw::crypto::CryptoErrorCode::kInternalError);
    }

    return connection;
}

}  // namespace score::crypto::api::control_plane
