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

// Renamed from grpc_client.h to grpc_control_client.h
#ifndef GRPC_CONTROL_CLIENT_H
#define GRPC_CONTROL_CLIENT_H

#include "score/crypto/api/control_plane/i_connection.hpp"

#include <memory>
#include <string_view>

namespace score::crypto::ipc
{

/// gRPC implementation of IConnection
/// Handles transport-specific details (FlatBuffers serialization, gRPC calls)
/// and converts between business logic types and wire protocol
class GrpcControlClient : public api::control_plane::IConnection
{
  public:
    /// Create a gRPC client connected to the specified socket pathpconnection_impl.hpp:30:
    /// @param socket_path Path to Unix domain socket
    explicit GrpcControlClient(std::string_view socket_path);
    ~GrpcControlClient() override;

    /// Disable copy and move
    GrpcControlClient(const GrpcControlClient&) = delete;
    GrpcControlClient& operator=(const GrpcControlClient&) = delete;
    GrpcControlClient(GrpcControlClient&&) = delete;
    GrpcControlClient& operator=(GrpcControlClient&&) = delete;

    /// Send a control request and receive response (IConnection implementation)
    /// @param request Business logic request
    /// @return Business logic response
    Expected<daemon::control_plane::protocol::ControlResponse, score::mw::crypto::CryptoErrorCode> SendRequest(
        const daemon::control_plane::protocol::ControlRequest& request) override;

    /// Get the connection node ID (IConnection implementation)
    daemon::control_plane::protocol::DataNodeId GetConnectionNodeId() const override;

  private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};

}  // namespace score::crypto::ipc

#endif  // GRPC_CONTROL_CLIENT_H
