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

#ifndef CONTROL_SERVER_H
#define CONTROL_SERVER_H

#include <string_view>

namespace score::crypto::daemon::control_plane
{

/// Abstract interface for control plane server lifecycle management
class IControlServer
{
  public:
    virtual ~IControlServer() = default;

    /// Start the server listening on the specified socket path
    /// @param socket_path Path to Unix domain socket
    virtual void Start(std::string_view socket_path) = 0;

    /// Block until server termination
    virtual void WaitForTermination() = 0;

    /// Stop the server gracefully, cleaning up resources
    virtual void Stop() = 0;
};

}  // namespace score::crypto::daemon::control_plane

#endif  // CONTROL_SERVER_H
