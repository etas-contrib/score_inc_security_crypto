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

#ifndef SCORE_CRYPTO_DAEMON_CONTROL_PLANE_REQUEST_HANDLER_FACTORY_HPP_
#define SCORE_CRYPTO_DAEMON_CONTROL_PLANE_REQUEST_HANDLER_FACTORY_HPP_

#include "score/crypto/daemon/control_plane/i_request_handler.hpp"
#include <memory>

namespace score::crypto::daemon::control_plane
{

/**
 * @interface IHandlerChainFactory
 * @brief Factory interface for creating IRequestHandler instances.
 *
 * This interface enables creation of handler instances per thread context,
 * supporting thread-safe request processing with isolated handler state.
 */
class IHandlerChainFactory
{
  public:
    /**
     * @brief Default constructor.
     */
    IHandlerChainFactory() = default;

    /**
     * @brief Virtual destructor.
     */
    virtual ~IHandlerChainFactory() = default;

    // Non-copyable - factories should not be duplicated
    IHandlerChainFactory(const IHandlerChainFactory&) = delete;
    IHandlerChainFactory& operator=(const IHandlerChainFactory&) = delete;

    // Movable - factories can be transferred (unique_ptr ownership transfer)

    /**
     * @brief Creates a new request handler instance.
     *
     * Each call creates a fresh handler with the complete chain of responsibility.
     * This enables per-thread handler isolation in multi-threaded environments.
     *
     * @return std::unique_ptr<control_plane::IRequestHandler> New handler instance
     *
     * @par Thread-safety Requirements
     * Implementations must be thread-safe
     */
    virtual std::unique_ptr<IRequestHandler> CreateRequestHandler() = 0;
};

}  // namespace score::crypto::daemon::control_plane

#endif  // SCORE_CRYPTO_DAEMON_CONTROL_PLANE_REQUEST_HANDLER_FACTORY_HPP_
