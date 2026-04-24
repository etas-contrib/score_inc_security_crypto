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

#ifndef SCORE_MW_CRYPTO_API_COMMON_SRC_I_RELEASE_CALLBACK_HPP
#define SCORE_MW_CRYPTO_API_COMMON_SRC_I_RELEASE_CALLBACK_HPP

#include "score/mw/crypto/api/common/types.hpp"
#include "score/result/result.h"

#include <memory>
#include <variant>

namespace score
{
namespace mw
{
namespace crypto
{

/// @brief Narrow callback interface for releasing transient crypto resources.
///
/// Used internally by CryptoResourceGuard to dispatch Release IPC calls to
/// the daemon. Concrete implementations (in the IPC layer) hold the daemon
/// connection and translate ReleaseResource() into a protocol message.
class IReleaseCallback
{
  public:
    /// @brief Destructor.
    virtual ~IReleaseCallback() = default;

    IReleaseCallback(const IReleaseCallback&) = delete;
    IReleaseCallback& operator=(const IReleaseCallback&) = delete;
    IReleaseCallback(IReleaseCallback&&) = default;
    IReleaseCallback& operator=(IReleaseCallback&&) = default;

    // TODO: What shall be the deallocation strategy? zeroing, random filling etc?
    // TODO: Do we need to consider user input to determine the cleanup strategy and hence exposing an API?
    /// @brief Releases a single transient crypto resource.
    ///
    /// Called by CryptoResourceGuard destructor and Release(). Dispatches
    /// a release request to the daemon. Always callable as long as the
    /// guard is active.
    ///
    /// @param id Handle of the transient resource to release
    /// @return std::monostate on success; error if the resource is invalid or still
    ///         referenced by an active operation context
    virtual score::Result<std::monostate> ReleaseResource(const CryptoResourceId& id) noexcept = 0;

  protected:
    IReleaseCallback() = default;
};

}  // namespace crypto
}  // namespace mw
}  // namespace score

#endif  // SCORE_MW_CRYPTO_API_COMMON_SRC_I_RELEASE_CALLBACK_HPP
