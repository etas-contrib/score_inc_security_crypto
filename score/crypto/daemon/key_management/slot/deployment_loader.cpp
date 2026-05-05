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

#include "score/crypto/daemon/key_management/slot/deployment_loader.hpp"

#include "score/crypto/daemon/key_management/slot/deployment/deployment_path_utils.hpp"
#include "score/crypto/daemon/key_management/slot/deployment/kv/kv_deployment_loader.hpp"

#include "score/mw/log/logging.h"

#include <string>

namespace score::crypto::daemon::key_management
{

score::crypto::Expected<SlotDeploymentInfo, score::crypto::daemon::common::DaemonErrorCode> DeploymentLoader::Load(
    const std::string& path,
    const std::string& format)
{
    if (!IsDeploymentPathSafe(path))
    {
        score::mw::log::LogError() << LOG_PREFIX << "Unsafe deployment path rejected: " << path << '\n';
        return score::crypto::make_unexpected(score::crypto::daemon::common::DaemonErrorCode::kInvalidArgument);
    }

    if (format == "kv")
    {
        return KvDeploymentLoader{}.Load(path);
    }
    // To add a new format: include its header above and add a branch here.
    // Example: if (format == "json") { return JsonDeploymentLoader{}.Load(path); }

    score::mw::log::LogError() << LOG_PREFIX << "Unsupported deployment format: " << format << '\n';
    return score::crypto::make_unexpected(score::crypto::daemon::common::DaemonErrorCode::kUnsupportedOperation);
}

}  // namespace score::crypto::daemon::key_management
