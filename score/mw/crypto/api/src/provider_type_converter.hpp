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

#ifndef SCORE_MW_CRYPTO_API_SRC_PROVIDER_TYPE_CONVERTER_HPP
#define SCORE_MW_CRYPTO_API_SRC_PROVIDER_TYPE_CONVERTER_HPP

#include "score/mw/crypto/api/common/types.hpp"

#include <cstdint>

namespace score
{
namespace mw
{
namespace crypto
{

namespace ProviderTypeConverter
{

/// @brief Encode a client-side ProviderType preference as its IPC wire value.
///
/// The wire protocol carries the raw uint8_t representation of the ProviderType
/// enumerator.  The daemon decodes this with its own FromWireProviderType()
/// function and maps it to its internal CryptoProviderType classification.
///
/// This function must NOT depend on daemon-internal headers — the client library
/// and the daemon are independently deployable components.
///
/// Wire encoding (matches ProviderType enumerator positions):
///   0 = kDefault
///   1 = kHardware
///   2 = kSoftware
///   3 = kHardwarePreferred
///   4 = kSoftwarePreferred
inline constexpr std::uint8_t ToWireValue(ProviderType api_type) noexcept
{
    return static_cast<std::uint8_t>(api_type);
}

}  // namespace ProviderTypeConverter

}  // namespace crypto
}  // namespace mw
}  // namespace score

#endif  // SCORE_MW_CRYPTO_API_SRC_PROVIDER_TYPE_CONVERTER_HPP
