/********************************************************************************
 * Copyright (c) 2026 Contributors to the Eclipse Foundation
 *
 * See the NOTICE file(s) distributed with this work for additional
 * information regarding copyright ownership.
 *
 * This program and the accompanying materials are made available under the
 * terms of the Apache License Version 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0
 *
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "score/crypto/src/api/common/error_domain.hpp"

#include <map>

namespace score
{

namespace crypto
{

std::string_view CryptoErrorDomain::MessageFor(const score::result::ErrorCode& code) const noexcept
{
    static const std::map<CryptoErrorCode, std::string_view> messages{
        {CryptoErrorCode::kUninitializedStack, "Crypto stack not initialized"},
        {CryptoErrorCode::kAlreadyInitialized, "Crypto stack already initialized"},
        {CryptoErrorCode::kConnectionFailed, "Failed to connect to crypto daemon"},
        {CryptoErrorCode::kInternalError, "Internal error"},
        {CryptoErrorCode::kUnsupportedOperation, "Unsupported operation"},
        {CryptoErrorCode::kInvalidOperation, "Invalid operation in current state"},
        {CryptoErrorCode::kOperationFailed, "Operation failed"},
        {CryptoErrorCode::kOperationTimedOut, "Operation exceeded configured timeout deadline"},
        {CryptoErrorCode::kInvalidArgument, "Invalid argument"},
        {CryptoErrorCode::kResourceNotFound, "Resource not found or no longer live"},
        {CryptoErrorCode::kInvalidResourceId, "Invalid resource identifier"},
        {CryptoErrorCode::kInvalidResourceType, "Resource type mismatch"},
        {CryptoErrorCode::kInsufficientBufferSize, "Output buffer too small"},
        {CryptoErrorCode::kInvalidFormat, "Invalid data format"},
        {CryptoErrorCode::kParamTruncated,
         "Parameter truncated: input exceeds fixed-capacity storage (reduce salt or seed size)"},
        {CryptoErrorCode::kStreamNotInitialized, "Stream not initialized"},
        {CryptoErrorCode::kStreamAlreadyActive, "Stream already active"},
        {CryptoErrorCode::kStreamIncomplete, "Stream incomplete"},
        {CryptoErrorCode::kUnsupportedAlgorithm, "Unsupported algorithm"},
        {CryptoErrorCode::kAlgorithmMismatch, "Algorithm mismatch with key or slot"},
        {CryptoErrorCode::kAllocationFailed, "Memory allocation failed"},
        {CryptoErrorCode::kQuotaExceeded, "Memory quota exceeded"},
        {CryptoErrorCode::kInvalidMemoryRegion, "Invalid memory region"},
        {CryptoErrorCode::kContextCreationFailed, "Context creation failed"},
        {CryptoErrorCode::kContextAlreadyDestroyed, "Context already destroyed"},
        {CryptoErrorCode::kContextResetFailed, "Context reset failed"},
        {CryptoErrorCode::kSessionExpired, "Session expired (context destroyed)"},
        {CryptoErrorCode::kKeySlotEmpty, "Key slot is empty"},
        {CryptoErrorCode::kKeySlotOccupied, "Key slot is already occupied"},
        {CryptoErrorCode::kKeyNotExportable, "Key is not exportable"},
        {CryptoErrorCode::kKeyGenerationFailed, "Key generation failed"},
        {CryptoErrorCode::kKeyDerivationFailed, "Key derivation failed"},
        {CryptoErrorCode::kKeyAgreementFailed, "Key agreement failed"},
        {CryptoErrorCode::kWrapUnwrapFailed, "Key wrap/unwrap failed"},
        {CryptoErrorCode::kPersistFailed, "Key persist failed"},
        {CryptoErrorCode::kIncompatibleKeyType, "Incompatible key type"},
        {CryptoErrorCode::kKeyOperationNotPermitted, "Key operation not permitted by slot policy"},
        {CryptoErrorCode::kCertificateParsingFailed, "Certificate parsing failed"},
        {CryptoErrorCode::kCsrGenerationFailed, "CSR generation failed"},
        {CryptoErrorCode::kOcspError, "OCSP error"},
        {CryptoErrorCode::kProviderNotAvailable, "Provider not available"},
        {CryptoErrorCode::kProviderBusy, "Provider busy"},
        {CryptoErrorCode::kCrossProviderIncompatible, "Cross-provider incompatible"},
        {CryptoErrorCode::kAccessDenied, "Access denied"},
        {CryptoErrorCode::kResourceNotAllocated, "Resource not allocated to application"},
    };

    const auto message = messages.find(static_cast<CryptoErrorCode>(code));
    return message != messages.end() ? message->second : "Unrecognized crypto error code";
}

}  // namespace crypto

}  // namespace score
