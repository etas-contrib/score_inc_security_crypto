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

#include "handler_utils.hpp"
#include "score/crypto/daemon/common/daemon_error.hpp"

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
namespace handler_utils
{

Expected<std::monostate, score::crypto::daemon::common::DaemonErrorCode>
ExtractBufferData(const common::RequestParameter& userData, const uint8_t*& buffer, size_t& size) noexcept
{
    // Check if data is VirtualMemoryBufferConst type variant
    if (auto providerBuffer = std::get_if<common::VirtualMemoryBufferConst>(&userData))
    {
        if (providerBuffer->data == nullptr || providerBuffer->size == 0)
        {
            buffer = nullptr;
            size = 0;
            return make_unexpected(score::crypto::daemon::common::DaemonErrorCode::kInsufficientBufferSize);
        }

        buffer = providerBuffer->data;
        size = providerBuffer->size;

        return std::monostate{};
    }

    // Default: Unsupported type in variant
    buffer = nullptr;
    size = 0;
    return make_unexpected(score::crypto::daemon::common::DaemonErrorCode::kInvalidDataType);
}

Expected<std::monostate, score::crypto::daemon::common::DaemonErrorCode>
ExtractOutputBufferData(common::RequestParameter& userData, uint8_t*& buffer, size_t& size) noexcept
{
    // Extract from VirtualMemoryBufferConst variant
    if (auto bufferPtr = std::get_if<common::VirtualMemoryBuffer>(&userData))
    {
        if (bufferPtr->data == nullptr || bufferPtr->size == 0)
        {
            buffer = nullptr;
            size = 0;
            return make_unexpected(score::crypto::daemon::common::DaemonErrorCode::kInsufficientBufferSize);
        }

        buffer = static_cast<uint8_t*>(bufferPtr->data);
        size = bufferPtr->size;

        return std::monostate{};
    }

    // Unsupported type in variant (e.g., CString, or integral types as output buffers)
    buffer = nullptr;
    size = 0;
    return make_unexpected(score::crypto::daemon::common::DaemonErrorCode::kInvalidDataType);
}

Expected<std::monostate, score::crypto::daemon::common::DaemonErrorCode> ValidateStreamOperationSequence(
    common::StreamOperationState currentState,
    const std::string_view streamOperation,
    common::StreamOperationState& nextState) noexcept
{
    // START operation: IDLE -> STREAM_INIT, STREAM_INIT -> STREAM_INIT (restart), STREAM_ACTIVE -> STREAM_INIT
    // (restart)
    if (streamOperation == "START")
    {
        // START is allowed from IDLE, STREAM_INIT, or STREAM_ACTIVE
        // All transitions lead to STREAM_INIT
        nextState = common::StreamOperationState::STREAM_INIT;
        return std::monostate{};
    }

    // UPDATE operation: STREAM_INIT -> STREAM_ACTIVE, STREAM_ACTIVE -> STREAM_ACTIVE
    if (streamOperation == "UPDATE")
    {
        if (currentState == common::StreamOperationState::STREAM_INIT)
        {
            // First UPDATE transitions from STREAM_INIT to STREAM_ACTIVE
            nextState = common::StreamOperationState::STREAM_ACTIVE;
            return std::monostate{};
        }
        else if (currentState == common::StreamOperationState::STREAM_ACTIVE)
        {
            // Subsequent UPDATEs stay in STREAM_ACTIVE
            nextState = common::StreamOperationState::STREAM_ACTIVE;
            return std::monostate{};
        }
        else
        {
            // UPDATE not allowed from IDLE
            return make_unexpected(score::crypto::daemon::common::DaemonErrorCode::kInvalidStreamOperation);
        }
    }

    // FINISH operation: STREAM_ACTIVE -> IDLE
    if (streamOperation == "FINISH")
    {
        if (currentState != common::StreamOperationState::STREAM_ACTIVE)
        {
            // FINISH only allowed from STREAM_ACTIVE
            return make_unexpected(score::crypto::daemon::common::DaemonErrorCode::kInvalidStreamOperation);
        }
        nextState = common::StreamOperationState::IDLE;
        return std::monostate{};
    }

    // Unknown or non-streaming operation
    return make_unexpected(score::crypto::daemon::common::DaemonErrorCode::kInvalidArgument);
}

}  // namespace handler_utils

}  // namespace handler
}  // namespace provider
}  // namespace daemon
}  // namespace crypto
}  // namespace score
