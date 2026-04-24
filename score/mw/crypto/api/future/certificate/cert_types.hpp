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

#ifndef SCORE_MW_CRYPTO_API_CERTIFICATE_CERT_TYPES_HPP
#define SCORE_MW_CRYPTO_API_CERTIFICATE_CERT_TYPES_HPP

#include "score/mw/crypto/api/common/types.hpp"

#include <cstdint>

namespace score
{
namespace mw
{
namespace crypto
{

/// @brief Result of a certificate verification operation.
enum class CertVerifyResult : uint8_t
{
    kValid,             ///< Certificate is valid and trusted
    kExpired,           ///< Certificate has expired
    kNotYetValid,       ///< Certificate is not yet valid (future notBefore)
    kRevoked,           ///< Certificate has been revoked
    kNoRootFound,       ///< Root CA is not in the trust store
    kChainIncomplete,   ///< Intermediate certificate missing
    kSignatureInvalid,  ///< Signature verification failed
    kInvalidPurpose,    ///< Key usage or extended key usage mismatch
    kUnknownAlgorithm,  ///< Unsupported or unknown algorithm in certificate
    kUnknownError       ///< Unspecified verification failure
};

/// @brief Status of an OCSP response.
enum class OcspStatus : uint8_t
{
    kGood,     ///< Certificate is not revoked
    kRevoked,  ///< Certificate has been revoked
    kUnknown,  ///< Responder does not know the certificate
    kError     ///< OCSP response could not be parsed or verified
};

}  // namespace crypto
}  // namespace mw
}  // namespace score

#endif  // SCORE_MW_CRYPTO_API_CERTIFICATE_CERT_TYPES_HPP
