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

#include <unistd.h>
#include <atomic>
#include <cstdint>
#include <iostream>
#include <mutex>

#include "score/crypto/daemon/control_plane/control_protocol.h"
#include "score/crypto/ipc/grpc_adapter/src/grpc_id_helpers.h"

namespace score::crypto::ipc
{

std::atomic_uint32_t RequestId::counter = 0;

std::uint64_t RequestId::getRequestId()
{
    static_assert(sizeof(pid_t) == EXPECTED_PID_TYPE_SIZE, "Error: The size of pid_t is not the expected size.");

    uint64_t request_id = getpid();
    request_id <<= EXPECTED_PID_TYPE_SIZE * BITS_PER_BYTE;
    request_id |= counter.fetch_add(1);

    return request_id;
}

decltype(daemon::control_plane::protocol::ControlRequest::uid) InsecureClientId::getUid()
{
    return getuid();
}

decltype(daemon::control_plane::protocol::ControlRequest::pid) InsecureClientId::getPid()
{
    return getpid();
}

}  // namespace score::crypto::ipc
