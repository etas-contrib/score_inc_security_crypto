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

#ifndef SCORE_MW_CRYPTO_API_CONFIG_VERIFY_SIGNATURE_CONTEXT_CONFIG_HPP
#define SCORE_MW_CRYPTO_API_CONFIG_VERIFY_SIGNATURE_CONTEXT_CONFIG_HPP

#include "score/mw/crypto/api/config/base_context_config.hpp"

namespace score
{
namespace mw
{
namespace crypto
{

/// @brief Configuration for signature verification context creation.
///
/// Requires an algorithm and a public key. Supports classical
/// algorithms (RSA-PSS, ECDSA) and PQC algorithms (ML-DSA-65, SLH-DSA-SHA2-128s).
///
/// @par Example
/// @code
///   VerifySignatureContextConfig config;
///   config.SetAlgorithm("ML-DSA-65").SetKey(public_key);
///   auto ctx = crypto_context->CreateVerifySignatureContext(config);
/// @endcode
struct VerifySignatureContextConfig : public BaseContextConfig
{
    /// @brief Handle to the public verification key (required).
    /// Must be a CryptoResourceId with type == kKey.
    CryptoResourceId key{};

    // -- Fluent builder --

    VerifySignatureContextConfig& SetAlgorithm(const AlgorithmId& alg) noexcept
    {
        BaseContextConfig::SetAlgorithm(alg);
        return *this;
    }

    VerifySignatureContextConfig& SetKey(const CryptoResourceId& k) noexcept
    {
        key = k;
        return *this;
    }

    VerifySignatureContextConfig& SetProvider(const CryptoResourceId& prov) noexcept
    {
        BaseContextConfig::SetProvider(prov);
        return *this;
    }

    VerifySignatureContextConfig& SetProviderType(ProviderType type) noexcept
    {
        BaseContextConfig::SetProviderType(type);
        return *this;
    }

    VerifySignatureContextConfig& SetExtendedParameter(const std::string& key, const std::string& value)
    {
        BaseContextConfig::SetExtendedParameter(key, value);
        return *this;
    }
};

}  // namespace crypto
}  // namespace mw
}  // namespace score

#endif  // SCORE_MW_CRYPTO_API_CONFIG_VERIFY_SIGNATURE_CONTEXT_CONFIG_HPP
