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

#ifndef CRYPTO_IPC_CONFIG_H
#define CRYPTO_IPC_CONFIG_H

#include <string_view>

namespace score::crypto::ipc
{

// Default Unix domain socket path for control communication
constexpr std::string_view kControlSocket = "/tmp/crypto_daemon.sock";

}  // namespace score::crypto::ipc

#endif  // CRYPTO_IPC_CONFIG_H
