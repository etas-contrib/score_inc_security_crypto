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

#ifndef SCORE_MW_CRYPTO_API_OBJECTS_I_KEY_OBJECT_HPP
#define SCORE_MW_CRYPTO_API_OBJECTS_I_KEY_OBJECT_HPP

#include "score/mw/crypto/api/objects/i_crypto_object.hpp"

#include <cstddef>
#include <memory>

namespace score
{
namespace mw
{
namespace crypto
{

/// @brief Typed view of key material (symmetric or asymmetric).
///
/// Provides algorithm, persistence, exportability, and length queries
/// for a resource whose type is kKey.  Obtained via
/// ICryptoContext::GetKeyObject().
///
/// Sub-types ISymmetricKeyObject, IPublicKeyObject, and
/// IPrivateKeyObject add role-specific queries.
class IKeyObject : public ICryptoObject
{
  public:
    using Uptr = std::unique_ptr<IKeyObject>;

    ~IKeyObject() override = default;

    IKeyObject(const IKeyObject&) = delete;
    IKeyObject& operator=(const IKeyObject&) = delete;
    IKeyObject(IKeyObject&&) = default;
    IKeyObject& operator=(IKeyObject&&) = default;

    /// @brief Returns the algorithm bound to this key.
    virtual AlgorithmId GetAlgorithm() const noexcept = 0;

    /// @brief Returns the persistence model (kPersistent or kEphemeral).
    virtual ResourcePersistence GetPersistence() const noexcept = 0;

    /// @brief Whether the key material can be exported / unwrapped.
    virtual bool IsExportable() const noexcept = 0;

    /// @brief Returns the key length in bits.
    virtual std::size_t GetKeyLength() const noexcept = 0;

    /// @brief Returns the operations this key is permitted to perform.
    ///
    /// For keys loaded from a slot, this reflects the slot's provisioned
    /// permissions. For ephemeral keys generated with explicit permissions,
    /// this reflects the requested permission set. For ephemeral keys
    /// generated without explicit permissions, returns kAll.
    ///
    /// @return Bitmask of KeyOperationPermission values.
    virtual KeyOperationPermission GetPermittedOperations() const noexcept = 0;

  protected:
    IKeyObject() = default;
};

}  // namespace crypto
}  // namespace mw
}  // namespace score

#endif  // SCORE_MW_CRYPTO_API_OBJECTS_I_KEY_OBJECT_HPP
