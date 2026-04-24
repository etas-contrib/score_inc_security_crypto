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

#ifndef CRYPTO_DAEMON_DATA_MANAGER_DATA_NODE_MANAGER_TOKEN_HPP_
#define CRYPTO_DAEMON_DATA_MANAGER_DATA_NODE_MANAGER_TOKEN_HPP_

namespace score::crypto::daemon::data_manager
{

class DataManager;  // forward-declare

/**
 * @brief Capability token restricting mutation of DataNode fields to the DataManager.
 *
 * All DataNode APIs that modify internal state (e.g. setNodeId(), setClientId(),
 * setParent(), addChild(), removeChild()) require a @c DataNodeManagerToken to be
 * passed by the caller.
 *
 * The constructor is private and only @c DataManager is declared as a friend,
 * so only the DataManager can create tokens.  This prevents arbitrary code from
 * directly mutating a node's identity or topology outside of the manager.
 */
class DataNodeManagerToken
{
  private:
    DataNodeManagerToken() = default;
    friend class DataManager;
};

}  // namespace score::crypto::daemon::data_manager

#endif  // CRYPTO_DAEMON_DATA_MANAGER_DATA_NODE_MANAGER_TOKEN_HPP_
