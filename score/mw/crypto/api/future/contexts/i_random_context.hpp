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

#ifndef SCORE_MW_CRYPTO_API_CONTEXTS_I_RANDOM_CONTEXT_HPP
#define SCORE_MW_CRYPTO_API_CONTEXTS_I_RANDOM_CONTEXT_HPP

#include "score/mw/crypto/api/contexts/i_context.hpp"
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

/// @brief Interface for random number generation.
///
/// Non-streaming context — provides direct Generate() and Seed() operations.
/// The RNG source is bound at context creation via RandomContextConfig
/// (algorithm and optional provider).
///
/// Suitable for generating IVs, nonces, key material, and other
/// cryptographic random data. For PQC key generation (e.g., ML-KEM),
/// the RNG is used internally by the key generation operation.
class IRandomContext : public IContext
{
  public:
    using Uptr = std::unique_ptr<IRandomContext>;

    ~IRandomContext() override = default;

    IRandomContext(const IRandomContext&) = delete;
    IRandomContext& operator=(const IRandomContext&) = delete;
    IRandomContext(IRandomContext&&) = default;
    IRandomContext& operator=(IRandomContext&&) = default;

    /// @brief Generates cryptographically secure random bytes.
    /// @param output Buffer to fill with random data
    /// @return Number of bytes generated on success, error on failure
    virtual score::Result<std::size_t> Generate(score::cpp::span<uint8_t> output) = 0;

    /// @brief Seeds the random number generator with additional entropy.
    /// @param seed Entropy data to mix into the RNG state
    /// @return std::monostate on success, error on failure
    /// @note Not all providers support explicit seeding. Some hardware RNGs
    ///       may ignore this call (returning success without action).
    virtual score::Result<std::monostate> Seed(score::cpp::span<const uint8_t> seed) = 0;

  protected:
    IRandomContext() = default;
};

}  // namespace crypto
}  // namespace mw
}  // namespace score

#endif  // SCORE_MW_CRYPTO_API_CONTEXTS_I_RANDOM_CONTEXT_HPP
