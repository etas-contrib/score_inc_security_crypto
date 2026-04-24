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

#ifndef SCORE_MW_CRYPTO_API_CONTEXTS_I_CONTEXT_HPP
#define SCORE_MW_CRYPTO_API_CONTEXTS_I_CONTEXT_HPP

#include "score/mw/crypto/api/common/error_domain.hpp"

#include <memory>

namespace score
{
namespace mw
{
namespace crypto
{

/// @brief Root base interface for all crypto operation contexts.
///
/// Provides the common Uptr typedef and virtual destructor. All concrete
/// operation contexts (hash, encrypt, sign, etc.) ultimately derive from
/// this interface, either directly or via IStreamingContext /
/// IStreamingOutputContext.
class IContext
{
  public:
    using Uptr = std::unique_ptr<IContext>;

    virtual ~IContext() = default;

    IContext(const IContext&) = delete;
    IContext& operator=(const IContext&) = delete;
    IContext(IContext&&) = default;
    IContext& operator=(IContext&&) = default;

  protected:
    IContext() = default;
};

}  // namespace crypto
}  // namespace mw
}  // namespace score

#endif  // SCORE_MW_CRYPTO_API_CONTEXTS_I_CONTEXT_HPP
