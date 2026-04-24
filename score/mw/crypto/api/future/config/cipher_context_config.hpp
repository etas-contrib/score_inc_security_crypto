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

#ifndef SCORE_MW_CRYPTO_API_CONFIG_CIPHER_CONTEXT_CONFIG_HPP
#define SCORE_MW_CRYPTO_API_CONFIG_CIPHER_CONTEXT_CONFIG_HPP

#include "score/mw/crypto/api/common/crypto_resource_guard.hpp"
#include "score/mw/crypto/api/common/types.hpp"
#include "score/mw/crypto/api/config/base_context_config.hpp"

namespace score
{
namespace mw
{
namespace crypto
{

/// @brief Configuration for cipher context creation (encryption or decryption).
///
/// Requires an algorithm, a key, and a cipher direction. Typical algorithms
/// include AES-128-CBC, AES-256-CBC, AES-256-CTR, ChaCha20.
/// When provider is omitted, the daemon auto-resolves from the key's
/// underlying primary_provider.
///
/// @par Example — encryption
/// @code
///   CipherContextConfig config;
///   config.SetAlgorithm("AES-256-CBC")
///         .SetKey(key_id)
///         .SetDirection(CipherDirection::kEncrypt);
///   auto ctx = crypto_context->CreateCipherContext(config);
/// @endcode
///
/// @par Example — decryption
/// @code
///   CipherContextConfig config;
///   config.SetAlgorithm("AES-256-CBC")
///         .SetKey(key_id)
///         .SetDirection(CipherDirection::kDecrypt);
///   auto ctx = crypto_context->CreateCipherContext(config);
/// @endcode
struct CipherContextConfig : public BaseContextConfig
{
    /// @brief Handle to the cipher key (required).
    /// Must be a CryptoResourceId with type == kKey.
    CryptoResourceId key{};

    /// @brief Cipher direction: encrypt or decrypt (required).
    CipherDirection direction{CipherDirection::kEncrypt};

    // -- Fluent builder --

    CipherContextConfig& SetAlgorithm(const AlgorithmId& alg) noexcept
    {
        BaseContextConfig::SetAlgorithm(alg);
        return *this;
    }

    CipherContextConfig& SetKey(const CryptoResourceId& k) noexcept
    {
        key = k;
        return *this;
    }

    CipherContextConfig& SetDirection(CipherDirection dir) noexcept
    {
        direction = dir;
        return *this;
    }

    CipherContextConfig& SetProvider(const CryptoResourceId& prov) noexcept
    {
        BaseContextConfig::SetProvider(prov);
        return *this;
    }

    CipherContextConfig& SetProviderType(ProviderType type) noexcept
    {
        BaseContextConfig::SetProviderType(type);
        return *this;
    }

    CipherContextConfig& SetExtendedParameter(const std::string& key, const std::string& value)
    {
        BaseContextConfig::SetExtendedParameter(key, value);
        return *this;
    }
};

}  // namespace crypto
}  // namespace mw
}  // namespace score

#endif  // SCORE_MW_CRYPTO_API_CONFIG_CIPHER_CONTEXT_CONFIG_HPP
