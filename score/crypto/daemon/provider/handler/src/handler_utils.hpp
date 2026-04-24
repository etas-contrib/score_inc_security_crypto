// =============================================================================
//  C O P Y R I G H T
// -----------------------------------------------------------------------------
//  Copyright (c) 2025-2026 by ETAS GmbH. All rights reserved.
//
//  The reproduction, distribution and utilization of this file as
//  well as the communication of its contents to others without express
//  authorization is prohibited. Offenders will be held liable for the
//  payment of damages. All rights reserved in the event of the grant
//  of a patent, utility model or design.
// =============================================================================

#ifndef SCORE_CRYPTO_DAEMON_PROVIDER_HANDLER_HANDLER_UTILS_HPP
#define SCORE_CRYPTO_DAEMON_PROVIDER_HANDLER_HANDLER_UTILS_HPP

#include "score/crypto/common/types.hpp"
#include "score/crypto/daemon/common/daemon_error.hpp"
#include "score/crypto/daemon/common/types.hpp"
#include <cstddef>
#include <cstdint>
#include <string_view>
#include <variant>

namespace score
{
namespace crypto
{
namespace daemon
{
namespace provider
{
namespace handler
{

/**
 * @brief Utility functions for cryptographic handlers
 *
 * This namespace provides common validation and data extraction functions
 * that can be reused across different handler implementations (Hash, MAC, Sign, etc.)
 */
namespace handler_utils
{

/**
 * @brief Extract buffer data from RequestParameter structure
 *
 * Supports extraction of data from virtual mapped memory regions.
 * Currently assumes VIR_MAPPED data type, but can be extended for other types.
 *
 * @param userData The RequestParameter structure containing the buffer information
 * @param buffer Output pointer to the extracted buffer
 * @param size Output parameter for the buffer size in bytes
 * @return std::monostate on success, error code otherwise
 *
 * @retval std::monostate Buffer successfully extracted
 * @retval score::crypto::daemon::common::DaemonErrorCode::kInsufficientBufferSize Invalid buffer address or zero size
 * @retval score::crypto::daemon::common::DaemonErrorCode::kInvalidDataType) Unsupported data type
 */
[[nodiscard]] Expected<std::monostate, ::score::crypto::daemon::common::DaemonErrorCode>
ExtractBufferData(const common::RequestParameter& userData, const uint8_t*& buffer, size_t& size) noexcept;

/**
 * @brief Extract non-const buffer data from RequestParameter structure
 *
 * Similar to ExtractBufferData but returns non-const pointer for output buffers.
 * Supports extraction of data from virtual mapped memory regions.
 *
 * @param userData The RequestParameter structure containing the buffer information
 * @param buffer Output pointer to the extracted buffer (non-const)
 * @param size Output parameter for the buffer size in bytes
 * @return std::monostate on success, error code otherwise
 *
 * @retval std::monostate Buffer successfully extracted
 * @retval score::crypto::daemon::common::DaemonErrorCode::kInsufficientBufferSize Invalid buffer address or zero size
 * @retval score::crypto::daemon::common::DaemonErrorCode::kInvalidDataType) Unsupported data type
 */
[[nodiscard]] Expected<std::monostate, ::score::crypto::daemon::common::DaemonErrorCode>
ExtractOutputBufferData(common::RequestParameter& userData, uint8_t*& buffer, size_t& size) noexcept;

/**
 * @brief Validate and determine next state for streaming operations
 *
 * Enforces the stream state machine:
 * - IDLE --(START)--> STREAM_INIT
 * - STREAM_INIT --(START)--> STREAM_INIT (restart)
 * - STREAM_INIT --(UPDATE 1+)--> STREAM_ACTIVE
 * - STREAM_ACTIVE --(UPDATE)--> STREAM_ACTIVE
 * - STREAM_ACTIVE --(START)--> STREAM_INIT (restart)
 * - STREAM_ACTIVE --(FINISH)--> IDLE
 *
 * This function focuses only on streaming operation validation (START, UPDATE, FINISH) and
 * decouples from single-shot operation IDs for handler-specific implementation.
 *
 * @param currentState The current operation state (IDLE, STREAM_INIT, or STREAM_ACTIVE)
 * @param streamOperation The streaming operation being requested: "START", "UPDATE", or "FINISH"
 * @param nextState Output parameter that receives the next state on SUCCESS
 * @return Expected containing std::monostate on success, or the failing score::crypto::daemon::common::DaemonErrorCode
 *
 * @retval std::monostate Transition valid; nextState contains the new state
 * @retval make_unexpected(ERROR_INVALID_STREAM_OPERATION) UPDATE/FINISH from wrong state
 * @retval make_unexpected(ERROR_INVALID_PARAMETER) Unknown or non-streaming operation
 *
 * @note Single-shot operations are NOT validated here (handler-specific)
 * @note Valid streaming operations: "START", "UPDATE", "FINISH"
 */
[[nodiscard]] Expected<std::monostate, ::score::crypto::daemon::common::DaemonErrorCode>
ValidateStreamOperationSequence(common::StreamOperationState currentState,
                                std::string_view streamOperation,
                                common::StreamOperationState& nextState) noexcept;

}  // namespace handler_utils

}  // namespace handler
}  // namespace provider
}  // namespace daemon
}  // namespace crypto
}  // namespace score

#endif  // SCORE_CRYPTO_DAEMON_PROVIDER_HANDLER_HANDLER_UTILS_HPP
