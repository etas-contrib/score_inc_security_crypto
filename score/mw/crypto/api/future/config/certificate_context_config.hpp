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

#ifndef SCORE_MW_CRYPTO_API_CONFIG_CERTIFICATE_CONTEXT_CONFIG_HPP
#define SCORE_MW_CRYPTO_API_CONFIG_CERTIFICATE_CONTEXT_CONFIG_HPP

#include "score/mw/crypto/api/config/base_context_config.hpp"

namespace score
{
namespace mw
{
namespace crypto
{

/// @brief Configuration for certificate management context creation.
///
/// Provider is optional — certificate operations use the provider
/// associated with each certificate's storage or the signing key's
/// primary_provider as appropriate. Setting a provider explicitly
/// scopes all certificate operations to that provider.
///
/// @par Example
/// @code
///   CertificateContextConfig config;
///   auto ctx = crypto_context->CreateCertificateManagementContext(config);
/// @endcode
struct CertificateContextConfig : public BaseContextConfig
{
    // -- Fluent builder --

    CertificateContextConfig& SetAlgorithm(const AlgorithmId& alg) noexcept
    {
        BaseContextConfig::SetAlgorithm(alg);
        return *this;
    }

    CertificateContextConfig& SetProvider(const CryptoResourceId& prov) noexcept
    {
        BaseContextConfig::SetProvider(prov);
        return *this;
    }

    CertificateContextConfig& SetProviderType(ProviderType type) noexcept
    {
        BaseContextConfig::SetProviderType(type);
        return *this;
    }

    CertificateContextConfig& SetExtendedParameter(const std::string& key, const std::string& value)
    {
        BaseContextConfig::SetExtendedParameter(key, value);
        return *this;
    }
};

}  // namespace crypto
}  // namespace mw
}  // namespace score

#endif  // SCORE_MW_CRYPTO_API_CONFIG_CERTIFICATE_CONTEXT_CONFIG_HPP
