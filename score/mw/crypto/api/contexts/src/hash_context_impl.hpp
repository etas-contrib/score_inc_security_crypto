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

#ifndef SCORE_MW_CRYPTO_API_SRC_HASH_CONTEXT_IMPL_HPP
#define SCORE_MW_CRYPTO_API_SRC_HASH_CONTEXT_IMPL_HPP

#include "score/mw/crypto/api/contexts/i_hash_context.hpp"

#include "score/mw/crypto/api/common/types.hpp"

#include "score/crypto/api/control_plane/i_connection.hpp"

#include <cstdint>
#include <memory>
#include <optional>

namespace score
{
namespace mw
{
namespace crypto
{

/// @brief Concrete IHashContext implementation that delegates to the crypto daemon via IPC.
///
/// Each instance is bound to a daemon-side hash context (identified by context_id)
/// created during construction. All streaming and single-shot operations are
/// forwarded to the daemon through the session's RequestOperation() API.
class HashContextImpl final : public IHashContext
{
  public:
    /// @brief Constructs a hash context bound to an existing daemon-side context.
    /// @param connection Shared connection for IPC communication (contains DataNodeId)
    /// @param context_id Daemon-assigned context identifier (from CTX_CREATE response)
    /// @param algorithm Algorithm name (e.g., "SHA-256") for digest size queries
    HashContextImpl(std::shared_ptr<score::crypto::api::control_plane::IConnection> connection,
                    uint64_t context_id,
                    AlgorithmId algorithm);

    ~HashContextImpl() override;

    // -- IStreamingContext --
    score::Result<std::monostate> Init(std::optional<score::cpp::span<const uint8_t>> iv) override;
    score::Result<std::monostate> Update(score::cpp::span<const uint8_t> data) override;
    score::Result<std::monostate> Reset() override;

    // -- IStreamingOutputContext --
    score::Result<std::size_t> Finalize(score::cpp::span<uint8_t> output) override;
    std::size_t GetOutputSize() const noexcept override;

    // -- IHashContext --
    score::Result<std::size_t> SingleShot(score::cpp::span<const uint8_t> input,
                                          score::cpp::span<uint8_t> output) override;
    std::size_t GetDigestSize() const noexcept override;

  private:
    std::shared_ptr<score::crypto::api::control_plane::IConnection> m_connection;
    score::crypto::daemon::control_plane::protocol::DataNodeId m_context_id;
    AlgorithmId m_algorithm;
};

}  // namespace crypto
}  // namespace mw
}  // namespace score

#endif  // SCORE_MW_CRYPTO_API_SRC_HASH_CONTEXT_IMPL_HPP
