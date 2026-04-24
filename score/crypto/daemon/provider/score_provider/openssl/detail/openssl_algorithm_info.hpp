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

#ifndef CRYPTO_DAEMON_PROVIDER_OPENSSL_DETAIL_OPENSSL_ALGORITHM_INFO_HPP
#define CRYPTO_DAEMON_PROVIDER_OPENSSL_DETAIL_OPENSSL_ALGORITHM_INFO_HPP

#include <openssl/evp.h>

#include <cstddef>
#include <string_view>

namespace score::crypto::daemon::provider::openssl::detail
{

/// @brief Algorithm → OpenSSL EVP_MD mapping entry.
struct OpensslDigestInfo
{
    std::string_view name;
    const EVP_MD* (*evp_md_fn)();  ///< Function pointer returning the EVP_MD (avoids static init order)
};

/// @brief Static table of supported hash algorithms and their OpenSSL EVP_MD providers.
inline const OpensslDigestInfo kDigestAlgorithms[] = {
    {"SHA256", EVP_sha256},
    {"SHA384", EVP_sha384},
    {"SHA512", EVP_sha512},
    {"SHA224", EVP_sha224},
    {"SHA1", EVP_sha1},
    {"MD5", EVP_md5},
};

/// @brief Look up the EVP_MD for a hash algorithm name.
/// @return EVP_MD pointer, or nullptr if the algorithm is not supported.
[[nodiscard]] inline const EVP_MD* LookupHashEVPMD(std::string_view algorithm) noexcept
{
    for (const auto& entry : kDigestAlgorithms)
    {
        if (entry.name == algorithm)
        {
            return entry.evp_md_fn();
        }
    }
    return nullptr;
}

/// @brief Algorithm → OpenSSL EVP_MD mapping for HMAC algorithms.
///
/// HMAC algorithms use the same EVP_MD as their underlying digest.
/// The algorithm name is the HMAC-prefixed form (e.g. "HMAC-SHA256").
struct OpensslHmacInfo
{
    std::string_view name;
    const EVP_MD* (*evp_md_fn)();
};

inline const OpensslHmacInfo kHmacAlgorithms[] = {
    {"HMAC-SHA256", EVP_sha256},
    {"HMAC-SHA384", EVP_sha384},
    {"HMAC-SHA512", EVP_sha512},
};

/// @brief Look up the EVP_MD for an HMAC algorithm name.
/// @return EVP_MD pointer, or nullptr if the algorithm is not supported.
[[nodiscard]] inline const EVP_MD* LookupHmacEVPMD(std::string_view algorithm) noexcept
{
    for (const auto& entry : kHmacAlgorithms)
    {
        if (entry.name == algorithm)
        {
            return entry.evp_md_fn();
        }
    }
    return nullptr;
}

}  // namespace score::crypto::daemon::provider::openssl::detail

#endif  // CRYPTO_DAEMON_PROVIDER_OPENSSL_DETAIL_OPENSSL_ALGORITHM_INFO_HPP
