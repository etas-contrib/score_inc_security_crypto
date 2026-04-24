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

#ifndef SCORE_MW_CRYPTO_API_OBJECTS_I_CERT_SLOT_OBJECT_HPP
#define SCORE_MW_CRYPTO_API_OBJECTS_I_CERT_SLOT_OBJECT_HPP

#include "score/mw/crypto/api/objects/i_crypto_object.hpp"

#include <memory>

namespace score
{
namespace mw
{
namespace crypto
{

/// @brief Typed view of a persistent certificate storage location.
///
/// Provides occupancy query for a resource whose type is kCertSlot.
/// Obtained via ICryptoContext::GetCertSlotObject().
class ICertSlotObject : public ICryptoObject
{
  public:
    using Uptr = std::unique_ptr<ICertSlotObject>;

    ~ICertSlotObject() override = default;

    ICertSlotObject(const ICertSlotObject&) = delete;
    ICertSlotObject& operator=(const ICertSlotObject&) = delete;
    ICertSlotObject(ICertSlotObject&&) = default;
    ICertSlotObject& operator=(ICertSlotObject&&) = default;

    /// @brief Whether the certificate slot currently holds a certificate.
    virtual bool IsOccupied() const noexcept = 0;

  protected:
    ICertSlotObject() = default;
};

}  // namespace crypto
}  // namespace mw
}  // namespace score

#endif  // SCORE_MW_CRYPTO_API_OBJECTS_I_CERT_SLOT_OBJECT_HPP
