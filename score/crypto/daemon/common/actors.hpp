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

#ifndef SCORE_CRYPTO_DAEMON_COMMON_OPERATION_ACTORS_HPP
#define SCORE_CRYPTO_DAEMON_COMMON_OPERATION_ACTORS_HPP

#include <limits>

#include "score/crypto/daemon/common/types.hpp"

namespace score::crypto::daemon::common::actors
{

inline constexpr OperationActor OP_ACTOR_CONTROL = 1;
inline constexpr OperationActor OP_ACTOR_MEDIATOR = 2;
inline constexpr OperationActor OP_ACTOR_PROVIDER = 3;
inline constexpr OperationActor OP_ACTOR_HASH_HANDLER = 4;
inline constexpr OperationActor OP_ACTOR_KEY_MANAGEMENT = 5;
inline constexpr OperationActor OP_ACTOR_MAC_HANDLER = 6;

// Starting point for custom actors
inline constexpr OperationActor CUSTOM_ACTOR_START = 1 << (std::numeric_limits<OperationActor>::digits - 1);

}  // namespace score::crypto::daemon::common::actors

#endif  // SCORE_CRYPTO_DAEMON_COMMON_OPERATION_ACTORS_HPP
