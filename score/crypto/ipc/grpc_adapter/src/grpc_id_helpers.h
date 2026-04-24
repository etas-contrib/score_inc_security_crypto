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

#ifndef GRPC_ID_HELPERS_H
#define GRPC_ID_HELPERS_H

#include <atomic>
#include <cstddef>
#include <cstdint>

#include "score/crypto/daemon/control_plane/control_protocol.h"

namespace score::crypto::ipc
{

constexpr size_t EXPECTED_PID_TYPE_SIZE = sizeof(std::uint32_t);
constexpr size_t EXPECTED_UID_TYPE_SIZE = sizeof(std::uint32_t);
constexpr size_t BITS_PER_BYTE = 8;

class RequestId
{
  public:
    static std::uint64_t getRequestId();

  private:
    static std::atomic_uint32_t counter;
};

class InsecureClientId
{
  public:
    static decltype(daemon::control_plane::protocol::ControlRequest::uid) getUid();
    static decltype(daemon::control_plane::protocol::ControlRequest::pid) getPid();
};

}  // namespace score::crypto::ipc

#endif  // GRPC_ID_HELPERS_H
