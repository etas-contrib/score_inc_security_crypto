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

#ifndef SCORE_MW_CRYPTO_API_OBJECTS_I_SECURE_OBJECT_HPP
#define SCORE_MW_CRYPTO_API_OBJECTS_I_SECURE_OBJECT_HPP

#include "score/mw/crypto/api/objects/i_crypto_object.hpp"
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

/// @brief Typed view of a secure storage entry.
///
/// Provides read access to opaque data stored in a secure element
/// or provider-managed area.  Resource type is kSecureObject.
class ISecureObject : public ICryptoObject
{
  public:
    using Uptr = std::unique_ptr<ISecureObject>;

    ~ISecureObject() override = default;

    ISecureObject(const ISecureObject&) = delete;
    ISecureObject& operator=(const ISecureObject&) = delete;
    ISecureObject(ISecureObject&&) = default;
    ISecureObject& operator=(ISecureObject&&) = default;

    /// @brief Reads the secure object data into the provided buffer.
    /// @param output Destination buffer
    /// @return Number of bytes written, or error if buffer is too small
    virtual score::Result<std::size_t> GetData(score::cpp::span<uint8_t> output) const = 0;

    /// @brief Returns the size of the stored data in bytes.
    virtual std::size_t GetSize() const noexcept = 0;

  protected:
    ISecureObject() = default;
};

}  // namespace crypto
}  // namespace mw
}  // namespace score

#endif  // SCORE_MW_CRYPTO_API_OBJECTS_I_SECURE_OBJECT_HPP
