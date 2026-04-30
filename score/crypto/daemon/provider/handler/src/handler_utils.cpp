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
    StreamOperation streamOperation,
    common::StreamOperationState& nextState) noexcept
{
    switch (streamOperation)
    {
        case StreamOperation::kInit:
            // Init is allowed from any state; transitions to STREAM_INITIALIZED
            nextState = common::StreamOperationState::STREAM_INITIALIZED;
            return std::monostate{};

        case StreamOperation::kUpdate:
            if (currentState == common::StreamOperationState::STREAM_INITIALIZED)
            {
                nextState = common::StreamOperationState::STREAM_ACTIVE;
                return std::monostate{};
            }
            else if (currentState == common::StreamOperationState::STREAM_ACTIVE)
            {
                nextState = common::StreamOperationState::STREAM_ACTIVE;
                return std::monostate{};
            }
            else
            {
                return make_unexpected(score::crypto::daemon::common::DaemonErrorCode::kInvalidStreamOperation);
            }

        case StreamOperation::kFinalize:
            if (currentState != common::StreamOperationState::STREAM_ACTIVE)
            {
                return make_unexpected(score::crypto::daemon::common::DaemonErrorCode::kInvalidStreamOperation);
            }
            nextState = common::StreamOperationState::IDLE;
            return std::monostate{};
    }

    // Unreachable with a well-formed enum; satisfies compilers that warn on missing return
    return make_unexpected(score::crypto::daemon::common::DaemonErrorCode::kInvalidArgument);
}

}  // namespace handler_utils

}  // namespace handler
}  // namespace provider
}  // namespace daemon
}  // namespace crypto
}  // namespace score
