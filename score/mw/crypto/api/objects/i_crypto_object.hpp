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

#ifndef SCORE_MW_CRYPTO_API_OBJECTS_I_CRYPTO_OBJECT_HPP
#define SCORE_MW_CRYPTO_API_OBJECTS_I_CRYPTO_OBJECT_HPP

#include "score/mw/crypto/api/common/types.hpp"

#include <memory>

namespace score
{
namespace mw
{
namespace crypto
{

/// @brief Root base for all typed crypto objects.
///
/// Provides the common identity and type accessors shared by every
/// specialised object interface.  Objects are lightweight proxies
/// into daemon state, not owned data copies.
///
/// Obtain typed objects via ICryptoContext accessor methods
/// (e.g., GetKeyObject(), GetKeySlotObject()).
class ICryptoObject
{
  public:
    using Uptr = std::unique_ptr<ICryptoObject>;

    virtual ~ICryptoObject() = default;

    ICryptoObject(const ICryptoObject&) = delete;
    ICryptoObject& operator=(const ICryptoObject&) = delete;
    ICryptoObject(ICryptoObject&&) = default;
    ICryptoObject& operator=(ICryptoObject&&) = default;

    /// @brief Returns the underlying CryptoResourceId handle.
    virtual CryptoResourceId GetId() const noexcept = 0;

    /// @brief Returns the resource type (kKey, kKeySlot, kCertificate, etc.).
    virtual ResourceType GetType() const noexcept = 0;

  protected:
    ICryptoObject() = default;
};

}  // namespace crypto
}  // namespace mw
}  // namespace score

#endif  // SCORE_MW_CRYPTO_API_OBJECTS_I_CRYPTO_OBJECT_HPP
