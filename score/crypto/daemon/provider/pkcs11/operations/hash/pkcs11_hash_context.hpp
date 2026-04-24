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

#ifndef SCORE_CRYPTO_DAEMON_PROVIDER_PKCS11_HASH_CONTEXT_HPP
#define SCORE_CRYPTO_DAEMON_PROVIDER_PKCS11_HASH_CONTEXT_HPP

#include <cryptoki.h>
#include <pkcs11.h>

#include <cstddef>

namespace score::crypto::daemon::provider::pkcs11
{

/// Groups the stable per-context parameters for Pkcs11HashExecutor operations.
///
/// These values are established once during handler construction / InitializeContext()
/// and remain constant for the lifetime of the handler context.  Passing them as a
/// struct reduces the executor's Execute() parameter count, improving readability
/// and MISRA C++ Rule 8-0-1 compliance.
struct Pkcs11HashExecutionContext
{
    CK_SESSION_HANDLE session{CK_INVALID_HANDLE};
    CK_MECHANISM mechanism{};
    std::size_t digest_size{0U};
};

}  // namespace score::crypto::daemon::provider::pkcs11

#endif  // SCORE_CRYPTO_DAEMON_PROVIDER_PKCS11_HASH_CONTEXT_HPP
