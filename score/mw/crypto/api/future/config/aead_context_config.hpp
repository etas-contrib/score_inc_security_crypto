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

#ifndef SCORE_MW_CRYPTO_API_CONFIG_AEAD_CONTEXT_CONFIG_HPP
#define SCORE_MW_CRYPTO_API_CONFIG_AEAD_CONTEXT_CONFIG_HPP

#include "score/mw/crypto/api/common/types.hpp"
#include "score/mw/crypto/api/config/base_context_config.hpp"

namespace score
{
namespace mw
{
namespace crypto
{

/// @brief Configuration for AEAD context creation.
///
/// Requires an algorithm, key, and cipher direction. Typical algorithms
/// include AES-128-GCM, AES-256-GCM, ChaCha20-Poly1305.
///
/// @par Example
/// @code
///   AeadContextConfig config;
///   config.SetAlgorithm("AES-256-GCM")
///         .SetKey(aead_key)
///         .SetDirection(CipherDirection::kEncrypt);
///   auto ctx = crypto_context->CreateAeadContext(config);
/// @endcode
struct AeadContextConfig : public BaseContextConfig
{
    /// @brief Handle to the AEAD key (required).
    /// Must be a CryptoResourceId with type == kKey.
    CryptoResourceId key{};

    /// @brief Cipher direction: encrypt or decrypt (required).
    CipherDirection direction{CipherDirection::kEncrypt};

    // -- Fluent builder --

    AeadContextConfig& SetAlgorithm(const AlgorithmId& alg) noexcept
    {
        BaseContextConfig::SetAlgorithm(alg);
        return *this;
    }

    AeadContextConfig& SetKey(const CryptoResourceId& k) noexcept
    {
        key = k;
        return *this;
    }

    AeadContextConfig& SetDirection(CipherDirection dir) noexcept
    {
        direction = dir;
        return *this;
    }

    AeadContextConfig& SetProvider(const CryptoResourceId& prov) noexcept
    {
        BaseContextConfig::SetProvider(prov);
        return *this;
    }

    AeadContextConfig& SetProviderType(ProviderType type) noexcept
    {
        BaseContextConfig::SetProviderType(type);
        return *this;
    }

    AeadContextConfig& SetExtendedParameter(const std::string& key, const std::string& value)
    {
        BaseContextConfig::SetExtendedParameter(key, value);
        return *this;
    }
};

}  // namespace crypto
}  // namespace mw
}  // namespace score

#endif  // SCORE_MW_CRYPTO_API_CONFIG_AEAD_CONTEXT_CONFIG_HPP
