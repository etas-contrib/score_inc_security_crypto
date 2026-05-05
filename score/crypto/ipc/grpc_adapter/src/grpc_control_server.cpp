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

#include "score/crypto/ipc/grpc_adapter/grpc_control_server.h"
#include "score/crypto/ipc/grpc_adapter/grpc_control_handler.h"
#include "score/mw/log/logging.h"
#include <grpcpp/grpcpp.h>
#include <unistd.h>
#include <cstring>

namespace score::crypto::ipc
{

struct GrpcControlServer::Impl
{
    std::unique_ptr<GrpcControlServiceAdapter> service;
    std::unique_ptr<grpc::Server> server;
    std::string socket_path;

    explicit Impl(std::unique_ptr<daemon::control_plane::IHandlerChainFactory> factory)
        : service(std::make_unique<GrpcControlServiceAdapter>(std::move(factory)))
    {
    }
};

GrpcControlServer::GrpcControlServer(std::unique_ptr<daemon::control_plane::IHandlerChainFactory> factory)
    : _impl(std::make_unique<Impl>(std::move(factory)))
{
}

GrpcControlServer::~GrpcControlServer()
{
    Stop();
}

void GrpcControlServer::Start(std::string_view socket_path)
{
    _impl->socket_path = std::string(socket_path);
    // Clean up stale socket file if it exists
    unlink(_impl->socket_path.data());

    grpc::ServerBuilder builder;
    // Add "unix:" prefix for gRPC (transport-specific detail)
    builder.AddListeningPort("unix:" + _impl->socket_path, grpc::InsecureServerCredentials());
    builder.RegisterService(_impl->service.get());
    // to limit the number of threads used by gRPC for time being
    // TODO
    builder.SetSyncServerOption(grpc::ServerBuilder::SyncServerOption::MIN_POLLERS, 1);
    builder.SetSyncServerOption(grpc::ServerBuilder::SyncServerOption::MAX_POLLERS, 1);

    _impl->server = builder.BuildAndStart();
    if (!_impl->server)
    {
        throw std::runtime_error("Failed to start gRPC server on unix:" + std::string(socket_path));
    }

    score::mw::log::LogDebug() << "[GrpcControlServer] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
    score::mw::log::LogDebug() << "[GrpcControlServer] !!! WARNING: Using insecure mechanism for uid and pid !!!";
    score::mw::log::LogDebug() << "[GrpcControlServer] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
    score::mw::log::LogDebug() << "[GrpcControlServer] Listening on unix:" << _impl->socket_path;
}

void GrpcControlServer::Stop()
{
    if (_impl->server)
    {
        _impl->server->Shutdown();
        _impl->server.reset();

        // Cleanup socket file
        if (!_impl->socket_path.empty())
        {
            if (unlink(_impl->socket_path.c_str()) == 0)
            {
                score::mw::log::LogDebug() << "[GrpcControlServer] Cleaned up socket file: " << _impl->socket_path;
            }
            else if (errno != ENOENT)
            {
                score::mw::log::LogError() << "[GrpcControlServer] Warning: Failed to remove socket file "
                                           << _impl->socket_path << ": " << strerror(errno);
            }
            _impl->socket_path.clear();
        }

        score::mw::log::LogDebug() << "[GrpcControlServer] gRPC Control Server shutdown complete";
    }
}

void GrpcControlServer::WaitForTermination()
{
    if (_impl->server)
    {
        _impl->server->Wait();
    }
}

}  // namespace score::crypto::ipc
