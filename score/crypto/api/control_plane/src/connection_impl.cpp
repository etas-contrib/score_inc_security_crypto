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

#include "score/crypto/api/control_plane/src/connection_impl.hpp"
#include "score/crypto/common/types.hpp"
#include "score/crypto/daemon/control_plane/control_operations.h"
#include "score/crypto/daemon/control_plane/control_protocol.h"
#include "score/crypto/ipc/grpc_adapter/grpc_control_client.h"
#include "score/mw/crypto/api/common/error_domain.hpp"

namespace score::crypto::api::control_plane
{

ConnectionImpl::ConnectionImpl(std::string_view endpoint) : mClient(std::make_unique<ipc::GrpcControlClient>(endpoint))
{
}

ConnectionImpl::~ConnectionImpl()
{
    // Send CONNECTION_CLOSE when the last reference to this connection is destroyed
    if (m_connection_id == 0)
    {
        return;  // Connection not fully opened
    }

    namespace proto = ::score::crypto::daemon::control_plane::protocol;
    namespace ctrl_ops = ::score::crypto::daemon::control_plane::operations;

    auto requestRes =
        proto::ControlRequestBuilder().forDataNodeId(m_connection_id).operation(ctrl_ops::CloseConnection()).build();

    if (!requestRes.has_value())
    {
        score::mw::log::LogError() << "[IPC][ConnectionImpl] ERROR: Failed to build CONNECTION_CLOSE request";
        return;
    }

    auto responseRes = mClient->SendRequest(requestRes.value());

    auto validator = proto::ControlResponseValidator::FromResult(responseRes);
    validator.expectOperation(ctrl_ops::CloseConnection()).expectSuccess();

    if (!validator.isValid())
    {
        score::mw::log::LogError() << "[IPC][ConnectionImpl] ERROR: CONNECTION_CLOSE response validation failed: "
                                   << validator.getError();
        return;
    }
}

Expected<daemon::control_plane::protocol::ControlResponse, score::mw::crypto::CryptoErrorCode>
ConnectionImpl::SendRequest(const daemon::control_plane::protocol::ControlRequest& request)
{
    // HINT: We expect, that the IPC
    // - Ensures Blocking behaviour (RPC style)
    // - Ensures Responses are matching the Request
    // - Enhances the request with UserId and RequestId
    return mClient->SendRequest(request);
}

daemon::control_plane::protocol::DataNodeId ConnectionImpl::GetConnectionNodeId() const
{
    return m_connection_id;
}

void ConnectionImpl::SetConnectionNodeId(daemon::control_plane::protocol::DataNodeId id)
{
    m_connection_id = id;
}

}  // namespace score::crypto::api::control_plane
