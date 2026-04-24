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

#ifndef SCORE_MW_CRYPTO_API_OBJECTS_I_DATA_OBJECT_HPP
#define SCORE_MW_CRYPTO_API_OBJECTS_I_DATA_OBJECT_HPP

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

/// @brief Typed view of a generic data blob resource.
///
/// Provides read access to arbitrary data stored within the
/// crypto daemon.  Resource type is kDataObject.
class IDataObject : public ICryptoObject
{
  public:
    using Uptr = std::unique_ptr<IDataObject>;

    ~IDataObject() override = default;

    IDataObject(const IDataObject&) = delete;
    IDataObject& operator=(const IDataObject&) = delete;
    IDataObject(IDataObject&&) = default;
    IDataObject& operator=(IDataObject&&) = default;

    /// @brief Reads the data object contents into the provided buffer.
    /// @param output Destination buffer
    /// @return Number of bytes written, or error if buffer is too small
    virtual score::Result<std::size_t> GetData(score::cpp::span<uint8_t> output) const = 0;

    /// @brief Returns the size of the stored data in bytes.
    virtual std::size_t GetSize() const noexcept = 0;

  protected:
    IDataObject() = default;
};

}  // namespace crypto
}  // namespace mw
}  // namespace score

#endif  // SCORE_MW_CRYPTO_API_OBJECTS_I_DATA_OBJECT_HPP
