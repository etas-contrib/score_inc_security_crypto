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
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <type_traits>

namespace score::crypto::ipc::control
{

/// Maximum size (bytes) of a serialized FlatBuffer payload that can be
/// transported via mw::com Method RPC. This is an ABI boundary: changing this
/// value requires rebuilding both sides of the IPC (client and server) together.
constexpr std::size_t kMaxIpcBufferSize = 4096U;

/// Trivially copyable envelope for transporting a size-prefixed FlatBuffer over
/// S-CORE LoLa shared-memory Method RPC.
///
/// S-CORE LoLa requires method argument and return types to be trivially
/// copyable (used via reinterpret_cast in shared memory). The payload is stored
/// in size-prefixed FlatBuffer format: the first 4 bytes are a little-endian
/// uint32 encoding the size of the remaining data, so no separate length field
/// is needed.
struct IpcBuffer
{
    std::array<std::byte, kMaxIpcBufferSize> payload{};
};

static_assert(std::is_trivially_copyable_v<IpcBuffer>,
              "IpcBuffer must be trivially copyable for LoLa shared-memory transport");
static_assert(sizeof(IpcBuffer) == kMaxIpcBufferSize, "IpcBuffer layout must have no padding");

/// Serialize raw size-prefixed FlatBuffer bytes into an IpcBuffer.
/// Returns a zero-initialised buffer (IsValid() == false) if size exceeds kMaxIpcBufferSize.
inline IpcBuffer PackFlatBuffer(const std::uint8_t* data, const std::size_t size) noexcept
{
    IpcBuffer buf{};
    if (size <= kMaxIpcBufferSize)
    {
        std::memcpy(buf.payload.data(), data, size);
    }
    return buf;
}

/// Write size-prefixed FlatBuffer bytes directly into an existing IpcBuffer (e.g. a
/// MethodInArgPtr-backed SHM slot) to avoid an intermediate copy.
/// On success returns true; if size exceeds kMaxIpcBufferSize the buffer is
/// zero-initialised and false is returned.
inline bool PackFlatBufferInto(IpcBuffer& buf, const std::uint8_t* data, const std::size_t size) noexcept
{
    if (size > kMaxIpcBufferSize)
    {
        buf = IpcBuffer{};
        return false;
    }
    std::memcpy(buf.payload.data(), data, size);
    return true;
}

/// Read the size prefix embedded in a size-prefixed FlatBuffer.
/// Returns the total number of valid bytes (4-byte prefix + data).
inline std::uint32_t GetPayloadSize(const IpcBuffer& buf) noexcept
{
    std::uint32_t prefix{};
    std::memcpy(&prefix, buf.payload.data(), sizeof(prefix));
    return prefix + static_cast<std::uint32_t>(sizeof(prefix));
}

/// Returns true if the buffer contains a non-empty, in-bounds payload.
inline bool IsValid(const IpcBuffer& buf) noexcept
{
    std::uint32_t prefix{};
    std::memcpy(&prefix, buf.payload.data(), sizeof(prefix));
    const auto total = static_cast<std::size_t>(prefix) + sizeof(prefix);
    return prefix > 0U && total <= kMaxIpcBufferSize;
}

}  // namespace score::crypto::ipc::control
