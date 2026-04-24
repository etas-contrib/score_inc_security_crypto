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

#ifndef SCORE_MW_CRYPTO_API_CONFIG_MAC_CONTEXT_CONFIG_HPP
#define SCORE_MW_CRYPTO_API_CONFIG_MAC_CONTEXT_CONFIG_HPP

#include "score/mw/crypto/api/config/base_context_config.hpp"

namespace score
{
namespace mw
{
namespace crypto
{

/// @brief Configuration for MAC context creation.
///
/// Requires an algorithm and a key. Typical algorithms include
/// HMAC-SHA-256, HMAC-SHA-384, CMAC-AES-128, CMAC-AES-256.
///
/// @par Example
/// @code
///   MacContextConfig config;
///   config.SetAlgorithm("HMAC-SHA-256").SetKey(mac_key);
///   auto ctx = crypto_context->CreateMacContext(config);
/// @endcode
struct MacContextConfig : public BaseContextConfig
{
    /// @brief Handle to the MAC key (required).
    /// Must be a CryptoResourceId with type == kKey.
    CryptoResourceId key{};

    // -- Fluent builder --

    MacContextConfig& SetAlgorithm(const AlgorithmId& alg) noexcept
    {
        BaseContextConfig::SetAlgorithm(alg);
        return *this;
    }

    MacContextConfig& SetKey(const CryptoResourceId& k) noexcept
    {
        key = k;
        return *this;
    }

    MacContextConfig& SetProvider(const CryptoResourceId& prov) noexcept
    {
        BaseContextConfig::SetProvider(prov);
        return *this;
    }

    MacContextConfig& SetProviderType(ProviderType type) noexcept
    {
        BaseContextConfig::SetProviderType(type);
        return *this;
    }

    MacContextConfig& SetOperationMode(OperationMode mode) noexcept
    {
        BaseContextConfig::SetOperationMode(mode);
        return *this;
    }

    MacContextConfig& SetExtendedParameter(const std::string& key, const std::string& value)
    {
        BaseContextConfig::SetExtendedParameter(key, value);
        return *this;
    }
};

}  // namespace crypto
}  // namespace mw
}  // namespace score

#endif  // SCORE_MW_CRYPTO_API_CONFIG_MAC_CONTEXT_CONFIG_HPP
