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

#ifndef SCORE_MW_CRYPTO_API_SRC_CRYPTO_CONTEXT_IMPL_HPP
#define SCORE_MW_CRYPTO_API_SRC_CRYPTO_CONTEXT_IMPL_HPP

#include "score/mw/crypto/api/common/types.hpp"
#include "score/mw/crypto/api/i_crypto_context.hpp"

#include "score/crypto/api/control_plane/i_connection.hpp"
#include "score/crypto/daemon/control_plane/control_protocol.h"

#include "score/result/result.h"

#include <cstdint>
#include <memory>

namespace score
{
namespace mw
{
namespace crypto
{

/// @brief Concrete ICryptoContext implementation that delegates to the crypto daemon via IPC.
///
/// Factory methods to create CryptoContext (CreateHashContext, etc.)
/// send context-creation requests to the daemon and wrap the returned context_id
/// in the corresponding concrete context implementation.
class CryptoContextImpl final : public ICryptoContext
{
  public:
    /// @brief Constructs a crypto context with an established connection.
    /// @param connection Shared ownership of the connection (which contains the DataNodeId)
    CryptoContextImpl(std::shared_ptr<score::crypto::api::control_plane::IConnection> connection);

    ~CryptoContextImpl() override;

    // Deleted special members to prevent copying and moving
    CryptoContextImpl(const CryptoContextImpl&) = delete;
    CryptoContextImpl& operator=(const CryptoContextImpl&) = delete;
    CryptoContextImpl(CryptoContextImpl&&) = delete;
    CryptoContextImpl& operator=(CryptoContextImpl&&) = delete;

    // -- Resource Resolution --
    score::Result<CryptoResourceId> ResolveResource(const ResourceId& resource_id, ResourceType type) override;

    // -- Context Factory --
    score::Result<std::unique_ptr<IHashContext>> CreateHashContext(const HashContextConfig& config) override;
    score::Result<std::unique_ptr<IMacContext>> CreateMacContext(const MacContextConfig& config) override;
    score::Result<std::unique_ptr<IKeyManagementContext>> CreateKeyManagementContext(
        const KeyManagementContextConfig& config) override;

    // -- Queries --
    score::Result<AlgorithmCapabilities> QueryCapabilities(const AlgorithmId& algorithm) override;
    score::Result<SystemCapabilities> QueryCapabilities() override;
    score::Result<ProviderInfo> GetProviderInfo(uint16_t provider_id) override;
    score::Result<ProviderInfo> GetProviderInfo(const CryptoResourceId& resourceId) override;

    // -- Typed Object Access --
    score::Result<std::unique_ptr<IKeyObject>> GetKeyObject(const CryptoResourceId& id) override;
    score::Result<std::unique_ptr<IKeySlotObject>> GetKeySlotObject(const CryptoResourceId& id) override;

  private:
    std::shared_ptr<score::crypto::api::control_plane::IConnection> m_connection;
};

}  // namespace crypto
}  // namespace mw
}  // namespace score

#endif  // SCORE_MW_CRYPTO_API_SRC_CRYPTO_CONTEXT_IMPL_HPP
