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

#ifndef SCORE_MW_CRYPTO_API_OBJECTS_I_SYMMETRIC_KEY_OBJECT_HPP
#define SCORE_MW_CRYPTO_API_OBJECTS_I_SYMMETRIC_KEY_OBJECT_HPP

#include "score/mw/crypto/api/objects/i_key_object.hpp"

#include <memory>
#include <string>
#include <vector>

namespace score
{
namespace mw
{
namespace crypto
{

/// @brief Typed view of symmetric key material.
///
/// Extends IKeyObject with symmetric-specific queries such as
/// allowed cipher modes.  Obtained by down-casting an IKeyObject
/// whose algorithm is symmetric.
class ISymmetricKeyObject : public IKeyObject
{
  public:
    using Uptr = std::unique_ptr<ISymmetricKeyObject>;

    ~ISymmetricKeyObject() override = default;

    ISymmetricKeyObject(const ISymmetricKeyObject&) = delete;
    ISymmetricKeyObject& operator=(const ISymmetricKeyObject&) = delete;
    ISymmetricKeyObject(ISymmetricKeyObject&&) = default;
    ISymmetricKeyObject& operator=(ISymmetricKeyObject&&) = default;

    /// @brief Returns the cipher modes allowed for this key (e.g., "CBC", "GCM").
    virtual std::vector<std::string> GetAllowedModes() const = 0;

  protected:
    ISymmetricKeyObject() = default;
};

}  // namespace crypto
}  // namespace mw
}  // namespace score

#endif  // SCORE_MW_CRYPTO_API_OBJECTS_I_SYMMETRIC_KEY_OBJECT_HPP
