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

#ifndef SCORE_MW_CRYPTO_API_CONTEXTS_I_MAC_CONTEXT_HPP
#define SCORE_MW_CRYPTO_API_CONTEXTS_I_MAC_CONTEXT_HPP

#include "score/mw/crypto/api/contexts/i_streaming_output_context.hpp"
#include "score/result/result.h"
#include "score/span.hpp"

#include <cstddef>
#include <cstdint>

namespace score
{
namespace mw
{
namespace crypto
{

/// @brief Interface for message authentication code (MAC) operations.
///
/// Exposes Init, Update, Reset, and Finalize from base classes plus
/// MAC-specific Verify() and GetMacSize().
/// Init() uses the optional-IV base signature; passing a value enables
/// algorithms like GMAC, while std::nullopt (the default) is used for
/// HMAC/CMAC.
///
/// Compatible with HMAC-SHA256, CMAC-AES, GMAC, and other MAC algorithms.
class IMacContext : public IStreamingOutputContext
{
  public:
    using Uptr = std::unique_ptr<IMacContext>;

    ~IMacContext() override = default;

    IMacContext(const IMacContext&) = delete;
    IMacContext& operator=(const IMacContext&) = delete;
    IMacContext(IMacContext&&) = default;
    IMacContext& operator=(IMacContext&&) = default;

    // -- Streaming API (from base classes) --
    using IStreamingContext::Init;
    using IStreamingContext::Reset;
    using IStreamingContext::Update;
    using IStreamingOutputContext::Finalize;

    /// @brief Verifies a MAC against the accumulated data.
    /// @param mac The MAC value to verify
    /// @return true if MAC is valid, false if invalid, error on failure
    /// @note Must be called after Update() calls. Alternative to Finalize()
    ///       when you want to verify rather than produce a MAC.
    virtual score::Result<bool> Verify(score::cpp::span<const uint8_t> mac) = 0;

    /// @brief Returns the MAC size in bytes for the configured algorithm.
    virtual std::size_t GetMacSize() const noexcept = 0;

  protected:
    IMacContext() = default;
};

}  // namespace crypto
}  // namespace mw
}  // namespace score

#endif  // SCORE_MW_CRYPTO_API_CONTEXTS_I_MAC_CONTEXT_HPP
