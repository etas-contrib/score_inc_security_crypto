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

#ifndef SCORE_MW_CRYPTO_API_CONFIG_CSR_GENERATION_CONTEXT_CONFIG_HPP
#define SCORE_MW_CRYPTO_API_CONFIG_CSR_GENERATION_CONTEXT_CONFIG_HPP

#include "score/mw/crypto/api/config/base_context_config.hpp"

namespace score
{
namespace mw
{
namespace crypto
{

/// @brief Configuration for CSR generation context creation.
///
/// Provider is optional — CSR generation uses the provider associated
/// with the signing key's primary_provider. Setting a provider explicitly
/// scopes the CSR generation to that provider.
///
/// @par Example
/// @code
///   CsrGenerationContextConfig config;
///   auto ctx = crypto_context->CreateCsrGenerationContext(config);
///   ctx->SetSubjectKey(signing_key);
///   ctx->SetSignatureAlgorithm("ML-DSA-65");
///   ctx->SetSubjectDn("CN=MyDevice,O=Corp,C=DE");
///   auto csr = ctx->Generate();
/// @endcode
struct CsrGenerationContextConfig : public BaseContextConfig
{
    // -- Fluent builder --

    CsrGenerationContextConfig& SetAlgorithm(const AlgorithmId& alg) noexcept
    {
        BaseContextConfig::SetAlgorithm(alg);
        return *this;
    }

    CsrGenerationContextConfig& SetProvider(const CryptoResourceId& prov) noexcept
    {
        BaseContextConfig::SetProvider(prov);
        return *this;
    }

    CsrGenerationContextConfig& SetProviderType(ProviderType type) noexcept
    {
        BaseContextConfig::SetProviderType(type);
        return *this;
    }

    CsrGenerationContextConfig& SetExtendedParameter(const std::string& key, const std::string& value)
    {
        BaseContextConfig::SetExtendedParameter(key, value);
        return *this;
    }
};

}  // namespace crypto
}  // namespace mw
}  // namespace score

#endif  // SCORE_MW_CRYPTO_API_CONFIG_CSR_GENERATION_CONTEXT_CONFIG_HPP
