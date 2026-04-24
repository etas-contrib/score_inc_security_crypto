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

#ifndef SCORE_CRYPTO_DAEMON_PROVIDER_SCORE_PROVIDER_OPERATIONS_MAC_MAC_EXECUTOR_HPP
#define SCORE_CRYPTO_DAEMON_PROVIDER_SCORE_PROVIDER_OPERATIONS_MAC_MAC_EXECUTOR_HPP

#include "score/crypto/common/types.hpp"
#include "score/crypto/daemon/common/daemon_error.hpp"
#include "score/crypto/daemon/common/types.hpp"

namespace score::crypto::daemon::provider::score_provider::operations::mac
{

class ScoreMacHandler;

/// @brief Stateless executor implementing the strategy / visitor pattern for MAC
///        operations under the score interface family.
///
/// Mirrors the HashExecutor pattern:
///   - Orchestrates operation flow and validates stream state transitions
///   - Extracts IPC buffer parameters from RequestParameters
///   - Routes operations to the typed ScoreMacHandler methods
///   - Packs results back into ResponseParameters
class MacExecutor
{
  public:
    [[nodiscard]] Expected<common::ResponseParameters, common::DaemonErrorCode> Execute(
        ScoreMacHandler& handler,
        const common::OperationIdentifier& operationId,
        common::RequestParameters& request);

  private:
    [[nodiscard]] Expected<std::monostate, common::DaemonErrorCode> ExecuteInit(ScoreMacHandler& handler,
                                                                                common::RequestParameters& request);

    [[nodiscard]] Expected<std::monostate, common::DaemonErrorCode> ExecuteUpdate(ScoreMacHandler& handler,
                                                                                  common::RequestParameters& request);

    [[nodiscard]] Expected<common::ResponseParameters, common::DaemonErrorCode> ExecuteFinalize(
        ScoreMacHandler& handler,
        common::RequestParameters& request);

    [[nodiscard]] Expected<common::ResponseParameters, common::DaemonErrorCode> ExecuteVerify(
        ScoreMacHandler& handler,
        common::RequestParameters& request);

    [[nodiscard]] Expected<std::monostate, common::DaemonErrorCode> ExecuteReset(ScoreMacHandler& handler,
                                                                                 common::RequestParameters& request);

    [[nodiscard]] Expected<common::ResponseParameters, common::DaemonErrorCode> ExecuteSingleShot(
        ScoreMacHandler& handler,
        common::RequestParameters& request);

    [[nodiscard]] Expected<common::ResponseParameters, common::DaemonErrorCode> GetMacSize(
        const ScoreMacHandler& handler,
        common::RequestParameters& request);

    [[nodiscard]] static Expected<std::monostate, common::DaemonErrorCode> ValidateStreamTransition(
        common::OperationAction action,
        common::StreamOperationState currentState,
        common::StreamOperationState& nextState);
};

}  // namespace score::crypto::daemon::provider::score_provider::operations::mac

#endif  // SCORE_CRYPTO_DAEMON_PROVIDER_SCORE_PROVIDER_OPERATIONS_MAC_MAC_EXECUTOR_HPP
