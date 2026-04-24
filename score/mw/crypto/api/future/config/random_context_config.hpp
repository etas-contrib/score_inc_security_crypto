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

#ifndef SCORE_MW_CRYPTO_API_CONFIG_RANDOM_CONTEXT_CONFIG_HPP
#define SCORE_MW_CRYPTO_API_CONFIG_RANDOM_CONTEXT_CONFIG_HPP

#include "score/mw/crypto/api/config/base_context_config.hpp"

namespace score
{
namespace mw
{
namespace crypto
{

/// @brief Configuration for random number generation context creation.
///
/// Algorithm is optional — when omitted, the daemon selects the default
/// RNG source. Provider preference can be used to request hardware
/// entropy sources (e.g., TRNG) when available.
///
/// @par Example
/// @code
///   RandomContextConfig config;
///   config.SetProviderType(ProviderType::kHardwarePreferred);
///   auto ctx = crypto_context->CreateRandomContext(config);
/// @endcode
struct RandomContextConfig : public BaseContextConfig
{
    // -- Fluent builder --

    RandomContextConfig& SetAlgorithm(const AlgorithmId& alg) noexcept
    {
        BaseContextConfig::SetAlgorithm(alg);
        return *this;
    }

    RandomContextConfig& SetProvider(const CryptoResourceId& prov) noexcept
    {
        BaseContextConfig::SetProvider(prov);
        return *this;
    }

    RandomContextConfig& SetProviderType(ProviderType type) noexcept
    {
        BaseContextConfig::SetProviderType(type);
        return *this;
    }

    RandomContextConfig& SetExtendedParameter(const std::string& key, const std::string& value)
    {
        BaseContextConfig::SetExtendedParameter(key, value);
        return *this;
    }
};

}  // namespace crypto
}  // namespace mw
}  // namespace score

#endif  // SCORE_MW_CRYPTO_API_CONFIG_RANDOM_CONTEXT_CONFIG_HPP
