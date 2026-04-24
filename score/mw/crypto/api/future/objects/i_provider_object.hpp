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

#ifndef SCORE_MW_CRYPTO_API_OBJECTS_I_PROVIDER_OBJECT_HPP
#define SCORE_MW_CRYPTO_API_OBJECTS_I_PROVIDER_OBJECT_HPP

#include "score/mw/crypto/api/objects/i_crypto_object.hpp"

#include <memory>
#include <string_view>
#include <vector>

namespace score
{
namespace mw
{
namespace crypto
{

/// @brief Typed view of a crypto provider resource.
///
/// Provides provider type, name, and supported algorithm queries
/// for a resource whose type is kProvider.  Obtained via
/// ICryptoContext::GetProviderObject().
class IProviderObject : public ICryptoObject
{
  public:
    using Uptr = std::unique_ptr<IProviderObject>;

    ~IProviderObject() override = default;

    IProviderObject(const IProviderObject&) = delete;
    IProviderObject& operator=(const IProviderObject&) = delete;
    IProviderObject(IProviderObject&&) = default;
    IProviderObject& operator=(IProviderObject&&) = default;

    /// @brief Returns the provider type (kHardware, kSoftware, etc.).
    virtual ProviderType GetProviderType() const noexcept = 0;

    /// @brief Returns the provider's human-readable name.
    virtual std::string_view GetName() const noexcept = 0;

    /// @brief Returns the list of algorithms supported by this provider.
    virtual std::vector<AlgorithmCapabilities> GetSupportedAlgorithms() const = 0;

  protected:
    IProviderObject() = default;
};

}  // namespace crypto
}  // namespace mw
}  // namespace score

#endif  // SCORE_MW_CRYPTO_API_OBJECTS_I_PROVIDER_OBJECT_HPP
