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

#include "score/crypto/daemon/key_management/slot/deployment/kv/kv_deployment_loader.hpp"

#include "score/mw/log/logging.h"
#include <cstddef>
#include <cstdint>
#include <fstream>

#include <string>

namespace score::crypto::daemon::key_management
{

score::crypto::Expected<SlotDeploymentInfo, score::crypto::daemon::common::DaemonErrorCode> KvDeploymentLoader::Load(
    const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        score::mw::log::LogError() << kLogPrefix << "Cannot open deployment descriptor: " << path << '\n';
        return score::crypto::make_unexpected(score::crypto::daemon::common::DaemonErrorCode::kInvalidArgument);
    }

    SlotDeploymentInfo info{};

    enum class Section : uint8_t
    {
        kMetadata,
        kKey
    };
    auto current_section = Section::kMetadata;

    std::string line;
    while (std::getline(file, line))
    {
        // Trim leading/trailing whitespace.
        std::size_t start = line.find_first_not_of(" \t\r");
        if (start == std::string::npos)
        {
            continue;  // blank line
        }
        std::size_t end = line.find_last_not_of(" \t\r");
        line = line.substr(start, end - start + 1U);

        // Skip comments.
        if (line[0] == '#')
        {
            continue;
        }

        // Section headers.
        if (line == "[metadata]")
        {
            current_section = Section::kMetadata;
            continue;
        }
        if (line == "[key]")
        {
            current_section = Section::kKey;
            continue;
        }

        // Parse key=value pairs.
        const auto eq_pos = line.find('=');
        if (eq_pos == std::string::npos)
        {
            continue;  // malformed line — skip
        }

        std::string key = line.substr(0U, eq_pos);
        std::string value = line.substr(eq_pos + 1U);

        // Trim key and value.
        auto trim = [](std::string& s) {
            std::size_t s_start = s.find_first_not_of(" \t");
            std::size_t s_end = s.find_last_not_of(" \t");
            if (s_start == std::string::npos)
            {
                s.clear();
            }
            else
            {
                s = s.substr(s_start, s_end - s_start + 1U);
            }
        };
        trim(key);
        trim(value);

        if (key.empty())
        {
            continue;
        }

        switch (current_section)
        {
            case Section::kMetadata:
                info.metadata[std::move(key)] = std::move(value);
                break;
            case Section::kKey:
                info.key_properties[std::move(key)] = std::move(value);
                break;
        }
    }

    return info;
}

}  // namespace score::crypto::daemon::key_management
