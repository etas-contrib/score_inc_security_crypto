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

#ifndef SCORE_CRYPTO_DAEMON_CONTROL_PLANE_CONTROL_OPERATIONS_H
#define SCORE_CRYPTO_DAEMON_CONTROL_PLANE_CONTROL_OPERATIONS_H

#include "control_protocol.h"
#include "score/crypto/daemon/common/actors.hpp"
#include "score/crypto/daemon/common/types.hpp"

#include <limits>

namespace score::crypto::daemon::control_plane::operations
{

using OperationAction = common::OperationAction;

// ============================================================================
// Common Control Plane Operations
// ============================================================================

// CONNECTION_OPEN
// Request:  data_node_id = 0 (no parent),
//           no operation parameters
// Response: status_code (SUCCESS/error)
//           uint64_t — daemon-assigned connection_id (root DataNodeId)
// Effect:   Creates a root DataNode, initializes connection context
inline constexpr OperationAction CONNECTION_OPEN = 1;

// CONNECTION_CLOSE
// Request:  data_node_id = connection_id,
//           no operation parameters
// Response: status_code (SUCCESS)
//           no output parameters
// Effect:   Deletes the connection node and cascade-deletes all child context nodes
inline constexpr OperationAction CONNECTION_CLOSE = 2;

// Starting point for custom OPs
inline constexpr OperationAction CUSTOM_OP_START = 1 << (std::numeric_limits<OperationAction>::digits - 1);

// Helpers
inline protocol::OperationIdentifier OpenConnection()
{
    return protocol::OperationIdentifier{.operationActor = common::actors::OP_ACTOR_CONTROL,
                                         .operationAction = operations::CONNECTION_OPEN};
}

inline protocol::OperationIdentifier CloseConnection()
{
    return protocol::OperationIdentifier{.operationActor = common::actors::OP_ACTOR_CONTROL,
                                         .operationAction = operations::CONNECTION_CLOSE};
}

}  // namespace score::crypto::daemon::control_plane::operations

#endif  // SCORE_CRYPTO_DAEMON_CONTROL_PLANE_CONTROL_OPERATIONS_H
