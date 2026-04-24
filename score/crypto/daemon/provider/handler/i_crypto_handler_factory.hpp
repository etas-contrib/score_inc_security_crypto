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

#ifndef ICRYPTO_HANDLER_FACTORY_HPP
#define ICRYPTO_HANDLER_FACTORY_HPP
#include "i_handler.hpp"
#include "score/crypto/daemon/common/types.hpp"
#include "score/result/result.h"
#include <memory>
#include <string>

namespace score::crypto
{
namespace daemon
{
namespace provider
{
namespace handler
{

/**
 * @brief Abstract interface for cryptographic handler creation.
 */
class ICryptoHandlerFactory
{
  public:
    using Sptr = std::shared_ptr<ICryptoHandlerFactory>;

    virtual ~ICryptoHandlerFactory() = default;

    /**
     * @brief Create a handler for the given handler type and algorithm.
     *
     * @param handlerId  Handler type (e.g. "HASH", "MAC", "KEY_MANAGEMENT").
     * @param algorithm  Requested algorithm (e.g. "SHA256", "HMAC-SHA256").
     * @return The created Handler on success, or an error if the type or
     *         algorithm is not supported.
     */
    virtual ::score::Result<Handler::Sptr> CreateHandler(const common::HandlerId& handlerId,
                                                         const common::AlgorithmId& algorithm) = 0;
};

}  // namespace handler
}  // namespace provider
}  // namespace daemon
}  // namespace score::crypto

#endif  // ICRYPTO_HANDLER_FACTORY_HPP
