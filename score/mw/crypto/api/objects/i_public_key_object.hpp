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

#ifndef SCORE_MW_CRYPTO_API_OBJECTS_I_PUBLIC_KEY_OBJECT_HPP
#define SCORE_MW_CRYPTO_API_OBJECTS_I_PUBLIC_KEY_OBJECT_HPP

#include "score/mw/crypto/api/objects/i_key_object.hpp"
#include "score/result/result.h"
#include "score/span.hpp"

#include <cstddef>
#include <cstdint>
#include <memory>

namespace score
{
namespace mw
{
namespace crypto
{

/// @brief Typed view of public key material.
///
/// Extends IKeyObject with the ability to export the public key bytes.
/// Obtained by down-casting an IKeyObject whose role is "public".
class IPublicKeyObject : public IKeyObject
{
  public:
    using Uptr = std::unique_ptr<IPublicKeyObject>;

    ~IPublicKeyObject() override = default;

    IPublicKeyObject(const IPublicKeyObject&) = delete;
    IPublicKeyObject& operator=(const IPublicKeyObject&) = delete;
    IPublicKeyObject(IPublicKeyObject&&) = default;
    IPublicKeyObject& operator=(IPublicKeyObject&&) = default;

    /// @brief Exports the public key bytes into the provided buffer.
    /// @param output Destination buffer
    /// @return Number of bytes written, or error if buffer is too small
    virtual score::Result<std::size_t> ExportPublicKey(score::cpp::span<uint8_t> output) const = 0;

  protected:
    IPublicKeyObject() = default;
};

}  // namespace crypto
}  // namespace mw
}  // namespace score

#endif  // SCORE_MW_CRYPTO_API_OBJECTS_I_PUBLIC_KEY_OBJECT_HPP
