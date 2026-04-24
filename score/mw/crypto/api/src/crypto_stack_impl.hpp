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

#ifndef SCORE_MW_CRYPTO_API_SRC_CRYPTO_STACK_IMPL_HPP
#define SCORE_MW_CRYPTO_API_SRC_CRYPTO_STACK_IMPL_HPP

#include "score/mw/crypto/api/crypto_stack_factory.hpp"
#include "score/mw/crypto/api/i_crypto_stack.hpp"

#include "score/crypto/api/control_plane/i_connection.hpp"

#include <memory>

namespace score
{
namespace mw
{
namespace crypto
{

/// @brief Concrete ICryptoStack implementation connected to the crypto daemon.
///
/// Each instance is associated with a single connection.
/// Construction receives the established connection; destruction releases
/// all associated resources including the node.
class CryptoStackImpl final : public ICryptoStack
{
  public:
    /// @brief Constructs a crypto stack with an established connection.
    /// @param config Stack configuration with connection endpoint
    /// @param connection Established connection to the crypto daemon (with DataNodeId already set)
    explicit CryptoStackImpl(const CryptoStackConfig& config,
                             std::shared_ptr<score::crypto::api::control_plane::IConnection> connection);

    ~CryptoStackImpl() override;

    CryptoStackImpl(const CryptoStackImpl&) = delete;
    CryptoStackImpl& operator=(const CryptoStackImpl&) = delete;
    CryptoStackImpl(CryptoStackImpl&&) = delete;
    CryptoStackImpl& operator=(CryptoStackImpl&&) = delete;

    // -- ICryptoStack --
    score::Result<ICryptoContext::Uptr> CreateCryptoContext() override;
    score::Result<IMemoryAllocator::Uptr> GetMemoryAllocator() override;

  private:
    CryptoStackConfig m_config;
    std::shared_ptr<score::crypto::api::control_plane::IConnection> m_connection;
};

}  // namespace crypto
}  // namespace mw
}  // namespace score

#endif  // SCORE_MW_CRYPTO_API_SRC_CRYPTO_STACK_IMPL_HPP
