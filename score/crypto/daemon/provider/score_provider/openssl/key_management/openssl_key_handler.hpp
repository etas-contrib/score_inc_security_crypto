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

#ifndef SCORE_CRYPTO_DAEMON_PROVIDER_OPENSSL_KEY_MANAGEMENT_OPENSSL_KEY_HANDLER_HPP
#define SCORE_CRYPTO_DAEMON_PROVIDER_OPENSSL_KEY_MANAGEMENT_OPENSSL_KEY_HANDLER_HPP

#include "score/crypto/daemon/key_management/interfaces/i_key_handler.hpp"

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

namespace score::crypto::daemon::provider::openssl
{

/// Owns a single heap-allocated key material buffer.
///
/// Crypto operation handlers (MAC, cipher) downcast the IKeyHandler to this
/// type and call GetRawKeyBytes() for direct access to the managed memory.
///
/// Destruction calls Release() as a safety net; Release() is idempotent.
class OpenSslKeyHandler final : public key_management::IKeyHandler
{
  public:
    OpenSslKeyHandler(std::vector<std::uint8_t> key_bytes, const key_management::ProviderKeyHandle& handle) noexcept;

    ~OpenSslKeyHandler() override;

    OpenSslKeyHandler(const OpenSslKeyHandler&) = delete;
    OpenSslKeyHandler& operator=(const OpenSslKeyHandler&) = delete;
    OpenSslKeyHandler(OpenSslKeyHandler&&) = delete;
    OpenSslKeyHandler& operator=(OpenSslKeyHandler&&) = delete;

    [[nodiscard]] const key_management::ProviderKeyHandle& GetHandle() const noexcept override;

    [[nodiscard]] ::score::crypto::Expected<std::monostate, ::score::crypto::daemon::common::DaemonErrorCode> Release()
        override;

    [[nodiscard]] ::score::crypto::Expected<key_management::SecureKeyBytes,
                                            ::score::crypto::daemon::common::DaemonErrorCode>
    Export() const override;

    [[nodiscard]] common::ProviderId GetProviderId() const noexcept override;

    /// Direct access to managed key material without opaque_id round-trip.
    [[nodiscard]] const std::uint8_t* GetRawKeyBytes(std::size_t& out_size) const noexcept;

  private:
    std::vector<std::uint8_t> m_key_bytes;
    key_management::ProviderKeyHandle m_handle;
    bool m_released;
};

}  // namespace score::crypto::daemon::provider::openssl

#endif  // SCORE_CRYPTO_DAEMON_PROVIDER_OPENSSL_KEY_MANAGEMENT_OPENSSL_KEY_HANDLER_HPP
