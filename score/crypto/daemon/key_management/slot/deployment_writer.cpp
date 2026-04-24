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

#include "score/crypto/daemon/key_management/slot/deployment_writer.hpp"

#include "score/crypto/daemon/key_management/slot/deployment/deployment_path_utils.hpp"
#include "score/crypto/daemon/key_management/slot/deployment/kv/kv_deployment_writer.hpp"

#include <iostream>
#include <string>

namespace score::crypto::daemon::key_management
{

score::crypto::Expected<std::monostate, score::crypto::daemon::common::DaemonErrorCode>
DeploymentWriter::Write(const std::string& path, const std::string& format, const SlotDeploymentInfo& info)
{
    if (!IsDeploymentPathSafe(path))
    {
        std::cerr << LOG_PREFIX << "Unsafe deployment path rejected: " << path << '\n';
        return score::crypto::make_unexpected(score::crypto::daemon::common::DaemonErrorCode::kInvalidArgument);
    }

    if (format == "kv")
    {
        return KvDeploymentWriter{}.Write(path, info);
    }
    // To add a new format: include its header above and add a branch here.
    // Example: if (format == "json") { return JsonDeploymentWriter{}.Write(path, info); }

    std::cerr << LOG_PREFIX << "Unsupported deployment format: " << format << '\n';
    return score::crypto::make_unexpected(score::crypto::daemon::common::DaemonErrorCode::kUnsupportedOperation);
}

}  // namespace score::crypto::daemon::key_management
