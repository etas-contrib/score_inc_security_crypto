// =============================================================================
//  C O P Y R I G H T
// -----------------------------------------------------------------------------
//  Copyright (c) 2026 by ETAS GmbH. All rights reserved.
//
//  The reproduction, distribution and utilization of this file as
//  well as the communication of its contents to others without express
//  authorization is prohibited. Offenders will be held liable for the
//  payment of damages. All rights reserved in the event of the grant
//  of a patent, utility model or design.
// =============================================================================

#ifndef SCORE_CRYPTO_DAEMON_PROVIDER_EXECUTORS_KEY_MGMT_CONTEXT_HPP
#define SCORE_CRYPTO_DAEMON_PROVIDER_EXECUTORS_KEY_MGMT_CONTEXT_HPP

#include "score/crypto/daemon/common/types.hpp"

#include <cstdint>

namespace score::crypto::daemon::provider::crypto_executor
{

/// Groups the stable per-context parameters for KeyManagementExecutor operations.
///
/// These values are set once during InitializeContext() and remain constant for
/// the lifetime of the handler context.  Passing them as a struct reduces the
/// executor's Execute() call from 5 parameters to 3 (context, operationId, request).
struct KeyMgmtExecutionContext
{
    common::ProviderId provider_id{common::kInvalidProviderId};
    std::uint64_t client_id{0U};
    std::uint64_t context_node_id{0U};
};

}  // namespace score::crypto::daemon::provider::crypto_executor

#endif  // SCORE_CRYPTO_DAEMON_PROVIDER_EXECUTORS_KEY_MGMT_CONTEXT_HPP
