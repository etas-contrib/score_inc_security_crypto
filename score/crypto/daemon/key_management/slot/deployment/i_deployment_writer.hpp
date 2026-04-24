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

#ifndef SCORE_CRYPTO_DAEMON_KEY_MANAGEMENT_SLOT_DEPLOYMENT_I_DEPLOYMENT_WRITER_HPP
#define SCORE_CRYPTO_DAEMON_KEY_MANAGEMENT_SLOT_DEPLOYMENT_I_DEPLOYMENT_WRITER_HPP

#include "score/crypto/common/types.hpp"
#include "score/crypto/daemon/common/daemon_error.hpp"
#include "score/crypto/daemon/key_management/interfaces/key_slot_config.hpp"

#include <string>
#include <variant>

namespace score::crypto::daemon::key_management
{

/// @brief Interface for format-specific deployment descriptor writers.
///
/// Mirrors IDeploymentLoader: one concrete class per serialization format.
/// The path safety pre-check is performed by DeploymentWriterFactory *before*
/// calling Write(), so implementations can assume a valid path.
///
/// ### Adding a new format
/// 1. Implement this interface in a new class (e.g., `JsonDeploymentWriter`).
/// 2. Place the class under `slot/deployment/<format>/`.
/// 3. Register it in `DeploymentWriterFactory::Create()`.
class IDeploymentWriter
{
  public:
    virtual ~IDeploymentWriter() = default;

    /// @brief Write a SlotDeploymentInfo to the given (pre-validated) path.
    ///
    /// @param path  Absolute path to the deployment descriptor file. The caller
    ///              (factory) has already verified it is safe.
    /// @param info  The deployment info to persist.
    /// @return std::monostate on success, or DaemonErrorCode on failure.
    [[nodiscard]] virtual score::crypto::Expected<std::monostate, score::crypto::daemon::common::DaemonErrorCode> Write(
        const std::string& path,
        const SlotDeploymentInfo& info) = 0;
};

}  // namespace score::crypto::daemon::key_management

#endif  // SCORE_CRYPTO_DAEMON_KEY_MANAGEMENT_SLOT_DEPLOYMENT_I_DEPLOYMENT_WRITER_HPP
