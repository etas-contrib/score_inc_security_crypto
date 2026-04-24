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

#include "score/crypto/daemon/provider/handler/context_data_node.hpp"
#include "score/crypto/daemon/data_manager/data_node.hpp"
#include "score/crypto/daemon/provider/handler/i_handler.hpp"
#include <memory>
#include <string>
#include <utility>

namespace score::crypto::daemon::provider::handler
{

ContextDataNode::ContextDataNode(std::shared_ptr<score::crypto::daemon::provider::handler::Handler> handler,
                                 const std::string& algorithm)
    : DataNode(true), m_handler(std::move(handler)), m_algorithm(algorithm)
{
}

ContextDataNode::~ContextDataNode() = default;

std::shared_ptr<score::crypto::daemon::provider::handler::Handler> ContextDataNode::GetHandler() const
{
    return m_handler;
}

const std::string& ContextDataNode::GetAlgorithm() const
{
    return m_algorithm;
}

}  // namespace score::crypto::daemon::provider::handler
