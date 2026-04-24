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

#ifndef SCORE_CRYPTO_DAEMON_PROVIDER_HANDLER_CONTEXT_DATA_NODE_HPP_
#define SCORE_CRYPTO_DAEMON_PROVIDER_HANDLER_CONTEXT_DATA_NODE_HPP_

#include "score/crypto/daemon/data_manager/data_node.hpp"
#include "score/crypto/daemon/provider/handler/i_handler.hpp"
#include <memory>
#include <string>

namespace score::crypto::daemon::provider::handler
{

/**
 * @brief DataNode specialization for storing crypto operation context information
 *
 * Stores handler, algorithm, and configuration for a crypto context.
 * Used by MediatorImpl to persist context across multiple operations.
 *
 * Key binding lifecycle: when a key is bound to a context, the mediator
 * creates a child KeyDataNode under this context in the data tree.
 * Cascade deletion of this context automatically releases the key binding.
 */
class ContextDataNode : public data_manager::DataNode
{
  public:
    ContextDataNode(std::shared_ptr<score::crypto::daemon::provider::handler::Handler> handler,
                    const std::string& algorithm);

    ~ContextDataNode() override;

    [[nodiscard]] data_manager::DataNodeType GetNodeType() const noexcept override
    {
        return data_manager::DataNodeType::kContext;
    }

    std::shared_ptr<score::crypto::daemon::provider::handler::Handler> GetHandler() const;
    const std::string& GetAlgorithm() const;

  private:
    std::shared_ptr<score::crypto::daemon::provider::handler::Handler> m_handler;
    std::string m_algorithm;
};

}  // namespace score::crypto::daemon::provider::handler

#endif  // SCORE_CRYPTO_DAEMON_PROVIDER_HANDLER_CONTEXT_DATA_NODE_HPP_
