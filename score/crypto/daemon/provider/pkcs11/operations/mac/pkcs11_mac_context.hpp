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

#ifndef SCORE_CRYPTO_DAEMON_PROVIDER_PKCS11_MAC_CONTEXT_HPP
#define SCORE_CRYPTO_DAEMON_PROVIDER_PKCS11_MAC_CONTEXT_HPP

#include "score/mw/crypto/api/common/types.hpp"  // OperationMode

#include <cryptoki.h>
#include <pkcs11.h>

#include <cstddef>

namespace score::crypto::daemon::provider::pkcs11
{

/// Groups the stable per-context parameters for Pkcs11MacExecutor operations.
///
/// These values are established once during InitializeContext() and remain
/// constant for the lifetime of the handler context.  Passing them as a
/// struct reduces the executor's Execute() call from 9 parameters to 5,
/// improving readability and MISRA C++ Rule 8-0-1 compliance.
struct Pkcs11MacExecutionContext
{
    CK_SESSION_HANDLE session{CK_INVALID_HANDLE};
    CK_MECHANISM mechanism{};
    CK_OBJECT_HANDLE key_object{CK_INVALID_HANDLE};
    std::size_t mac_size{0U};
    score::mw::crypto::OperationMode operation_mode{score::mw::crypto::OperationMode::kGenerate};
};

}  // namespace score::crypto::daemon::provider::pkcs11

#endif  // SCORE_CRYPTO_DAEMON_PROVIDER_PKCS11_MAC_CONTEXT_HPP
