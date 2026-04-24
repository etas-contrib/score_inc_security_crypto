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

#ifndef SCORE_MW_CRYPTO_API_CONTEXTS_I_HASH_CONTEXT_HPP
#define SCORE_MW_CRYPTO_API_CONTEXTS_I_HASH_CONTEXT_HPP

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

/// @brief Interface for hash/digest operations.
///
/// Exposes Init, Update, Reset, and Finalize from base classes plus
/// hash-specific SingleShot() and GetDigestSize().
/// Init() is exposed with the base default (iv = std::nullopt);
/// hash implementations reject a non-null IV.
///
/// Compatible with classical algorithms (SHA-256, SHA-3) and PQC hash-based
/// schemes (e.g., XMSS/LMS hash functions, SHAKE for ML-DSA).
class IHashContext : public IStreamingOutputContext
{
  public:
    using Uptr = std::unique_ptr<IHashContext>;

    virtual ~IHashContext() = default;

    IHashContext(const IHashContext&) = delete;
    IHashContext& operator=(const IHashContext&) = delete;
    IHashContext(IHashContext&&) = default;
    IHashContext& operator=(IHashContext&&) = default;

    // -- Streaming API (from base classes) --
    using IStreamingContext::Init;
    using IStreamingContext::Reset;
    using IStreamingContext::Update;
    using IStreamingOutputContext::Finalize;

    /// @brief Computes the hash digest in a single call.
    /// @param input Data to hash
    /// @param output Buffer to receive the digest
    /// @return Number of bytes written on success, error on failure
    /// @note Equivalent to Init() + Update(input) + Finalize(output).
    virtual score::Result<std::size_t> SingleShot(score::cpp::span<const uint8_t> input,
                                                  score::cpp::span<uint8_t> output) = 0;

    /// @brief Returns the digest size in bytes for the configured algorithm.
    /// @note For variable-output hash functions (e.g., SHAKE), returns the
    ///       default output length configured at context creation.
    virtual std::size_t GetDigestSize() const noexcept = 0;

  protected:
    IHashContext() = default;
};

}  // namespace crypto
}  // namespace mw
}  // namespace score

#endif  // SCORE_MW_CRYPTO_API_CONTEXTS_I_HASH_CONTEXT_HPP
