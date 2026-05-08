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

#ifndef SCORE_CRYPTO_DAEMON_KEY_MANAGEMENT_CONFIG_DRIVEN_SLOT_CATALOG_HPP
#define SCORE_CRYPTO_DAEMON_KEY_MANAGEMENT_CONFIG_DRIVEN_SLOT_CATALOG_HPP

#include "score/crypto/daemon/config/inc/config.hpp"
#include "score/crypto/daemon/key_management/interfaces/i_key_slot_catalog.hpp"

#include <string_view>

namespace score::crypto::daemon::key_management
{

/// @brief IKeySlotCatalog that reads key slot definitions from the daemon's
///        parsed configuration (KeyConfig).
///
/// This is the **production catalog**. It converts each `KeyConfig::KeySlotEntry`
/// into a `KeySlotConfig` and calls `registry.RegisterSlot()`.
///
/// The configuration source (JSON file, flatbuffer, environment) is parsed
/// upstream by Config::ParseConfig(). This catalog is format-agnostic — it only
/// reads the already-parsed `KeySlotEntry` vector from `KeyConfig`.
///
/// ### PKCS#11 slot integration
/// An integrator adds PKCS#11 key slot entries to the configuration manifest
/// with a `deployment_path` pointing to a kv-format deployment descriptor.
/// The descriptor's `[key]` section carries PKCS#11 identifiers:
///   - `pkcs11.label` → CKA_LABEL
///   - `pkcs11.object_id` → CKA_ID (hex string)
///   - `pkcs11.object_class` → "secret_key", "private_key", etc.
///
/// The catalog stores the deployment_path unchanged — the PKCS#11 slot handler
/// loads and interprets the descriptor at LoadKey time.
///
class ConfigDrivenSlotCatalog final : public IKeySlotCatalog
{
  public:
    /// @param key_config  Reference to the parsed key configuration section.
    explicit ConfigDrivenSlotCatalog(const config::KeyConfig& key_config);
    ~ConfigDrivenSlotCatalog() override = default;

    /// @copydoc IKeySlotCatalog::Load
    void Load(SlotRegistry& registry) override;

  private:
    const config::KeyConfig& m_key_config;

    static constexpr std::string_view LOG_PREFIX = "[CONFIG_DRIVEN_CATALOG]";
};

}  // namespace score::crypto::daemon::key_management

#endif  // SCORE_CRYPTO_DAEMON_KEY_MANAGEMENT_CONFIG_DRIVEN_SLOT_CATALOG_HPP
