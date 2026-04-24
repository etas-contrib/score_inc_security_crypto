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

#ifndef SCORE_MW_CRYPTO_API_CONFIG_KEY_MANAGEMENT_CONTEXT_CONFIG_HPP
#define SCORE_MW_CRYPTO_API_CONFIG_KEY_MANAGEMENT_CONTEXT_CONFIG_HPP

#include "score/mw/crypto/api/config/base_context_config.hpp"

namespace score
{
namespace mw
{
namespace crypto
{

/// @brief Configuration for key management context creation.
///
/// Provider is optional — operations will use the provider associated
/// with each key's CryptoResourceId::primary_provider as needed.
/// Setting a provider explicitly scopes all key management operations
/// to that specific provider.
///
/// @par Example
/// @code
///   KeyManagementContextConfig config;
///   config.SetProviderType(ProviderType::kHardware);
///   auto ctx = crypto_context->CreateKeyManagementContext(config);
/// @endcode
struct KeyManagementContextConfig : public BaseContextConfig
{
    // -- Fluent builder --

    KeyManagementContextConfig& SetProvider(const CryptoResourceId& prov) noexcept
    {
        BaseContextConfig::SetProvider(prov);
        return *this;
    }

    KeyManagementContextConfig& SetProviderType(ProviderType type) noexcept
    {
        BaseContextConfig::SetProviderType(type);
        return *this;
    }

    KeyManagementContextConfig& SetExtendedParameter(const std::string& key, const std::string& value)
    {
        BaseContextConfig::SetExtendedParameter(key, value);
        return *this;
    }
};

}  // namespace crypto
}  // namespace mw
}  // namespace score

#endif  // SCORE_MW_CRYPTO_API_CONFIG_KEY_MANAGEMENT_CONTEXT_CONFIG_HPP
