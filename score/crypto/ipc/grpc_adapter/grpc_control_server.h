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

#ifndef GRPC_CONTROL_SERVER_H
#define GRPC_CONTROL_SERVER_H

#include <memory>
#include <string_view>

#include "score/crypto/daemon/control_plane/i_control_server.h"
#include "score/crypto/daemon/control_plane/i_handler_chain_factory.hpp"

namespace score::crypto::ipc
{

// gRPC implementation of IControlServer
// Manages server lifecycle and socket cleanup
class GrpcControlServer final : public daemon::control_plane::IControlServer
{
  public:
    explicit GrpcControlServer(std::unique_ptr<daemon::control_plane::IHandlerChainFactory> factory);
    ~GrpcControlServer() override;

    // Disable copy and move
    GrpcControlServer(const GrpcControlServer&) = delete;
    GrpcControlServer& operator=(const GrpcControlServer&) = delete;
    GrpcControlServer(GrpcControlServer&&) = delete;
    GrpcControlServer& operator=(GrpcControlServer&&) = delete;

    // IControlServer implementation
    void Start(std::string_view socket_path) override;
    void Stop() override;
    void WaitForTermination() override;

  private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};

}  // namespace score::crypto::ipc

#endif  // GRPC_CONTROL_SERVER_H
