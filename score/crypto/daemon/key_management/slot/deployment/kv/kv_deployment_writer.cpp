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

#include "score/crypto/daemon/key_management/slot/deployment/kv/kv_deployment_writer.hpp"

#include "score/mw/log/logging.h"
#include <fstream>

#include <string>

namespace score::crypto::daemon::key_management
{

score::crypto::Expected<std::monostate, score::crypto::daemon::common::DaemonErrorCode> KvDeploymentWriter::Write(
    const std::string& path,
    const SlotDeploymentInfo& info)
{
    std::ofstream file(path, std::ios::trunc);
    if (!file.is_open())
    {
        score::mw::log::LogError() << kLogPrefix << "Cannot open deployment descriptor for writing: " << path << '\n';
        return score::crypto::make_unexpected(score::crypto::daemon::common::DaemonErrorCode::kInvalidArgument);
    }

    file << "[metadata]";
    for (const auto& [key, value] : info.metadata)
    {
        file << key << '=' << value << '\n';
    }

    file << "\n[key]";
    for (const auto& [key, value] : info.key_properties)
    {
        file << key << '=' << value << '\n';
    }

    if (!file.good())
    {
        score::mw::log::LogError() << kLogPrefix << "Write error for deployment descriptor: " << path << '\n';
        return score::crypto::make_unexpected(score::crypto::daemon::common::DaemonErrorCode::kInternalError);
    }

    return std::monostate{};
}

}  // namespace score::crypto::daemon::key_management
