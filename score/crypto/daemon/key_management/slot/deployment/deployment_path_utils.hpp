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

#ifndef SCORE_CRYPTO_DAEMON_KEY_MANAGEMENT_SLOT_DEPLOYMENT_DEPLOYMENT_PATH_UTILS_HPP
#define SCORE_CRYPTO_DAEMON_KEY_MANAGEMENT_SLOT_DEPLOYMENT_DEPLOYMENT_PATH_UTILS_HPP

#include <string>

namespace score::crypto::daemon::key_management
{

/// @brief Returns true if the path is absolute and contains no ".." path traversal components.
///
/// Used as a single shared security pre-check by DeploymentLoaderFactory and
/// DeploymentWriterFactory before dispatching to a format-specific implementation.
/// Centralises path validation so it is not duplicated across every format class.
[[nodiscard]] inline bool IsDeploymentPathSafe(const std::string& path) noexcept
{
    if (path.empty())
    {
        return false;
    }

    // Require absolute path (Unix: starts with '/').
    const bool is_absolute = (path[0] == '/') || (path.size() >= 3U && path[1] == ':');
    if (!is_absolute)
    {
        return false;
    }

    // Reject path traversal: ".." as a standalone component.
    if (path.find("..") != std::string::npos)
    {
        return false;
    }

    return true;
}

}  // namespace score::crypto::daemon::key_management

#endif  // SCORE_CRYPTO_DAEMON_KEY_MANAGEMENT_SLOT_DEPLOYMENT_DEPLOYMENT_PATH_UTILS_HPP
