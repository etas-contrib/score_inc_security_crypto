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

#include "score/mw/crypto/api/src/crypto_stack_impl.hpp"

#include "score/mw/crypto/api/common/error_domain.hpp"
#include "score/mw/crypto/api/common/i_memory_allocator.hpp"
#include "score/mw/crypto/api/crypto_stack_factory.hpp"
#include "score/mw/crypto/api/i_crypto_context.hpp"
#include "score/mw/crypto/api/src/crypto_context_impl.hpp"

#include "score/crypto/api/control_plane/i_connection.hpp"

#include "score/result/result.h"

#include <iostream>
#include <memory>
#include <utility>

namespace score
{
namespace mw
{
namespace crypto
{

CryptoStackImpl::CryptoStackImpl(const CryptoStackConfig& config,
                                 std::shared_ptr<score::crypto::api::control_plane::IConnection> connection)
    : m_config(config), m_connection(std::move(connection))
{
}

CryptoStackImpl::~CryptoStackImpl()
{
    // No cleanup needed - connection is managed by shared_ptr
    // If this is the last reference, the connection will be destroyed
    // CONNECTION_CLOSE is caller's responsibility
}

score::Result<ICryptoContext::Uptr> CryptoStackImpl::CreateCryptoContext()
{
    // Create a context with the established connection.
    // The connection is managed by the stack and was established during CreateCryptoStack.

    if (!m_connection)
    {
        std::cerr << "[API][CryptoStackImpl] ERROR: Connection is not initialized\n";
        return score::Result<ICryptoContext::Uptr>{
            score::unexpect, MakeError(CryptoErrorCode::kConnectionFailed, "Connection is not initialized")};
    }

    auto ctx = std::make_unique<CryptoContextImpl>(m_connection);
    return ctx;
}

score::Result<IMemoryAllocator::Uptr> CryptoStackImpl::GetMemoryAllocator()
{
    // TODO: Implement shared-memory allocator for data-plane zero-copy path.
    //       For now, this is not needed by the hash example test.
    std::cerr << "[API][CryptoStackImpl] ERROR: GetMemoryAllocator not yet implemented\n";
    return score::Result<IMemoryAllocator::Uptr>{
        score::unexpect, MakeError(CryptoErrorCode::kInternalError, "GetMemoryAllocator not yet implemented")};
}

}  // namespace crypto
}  // namespace mw
}  // namespace score
