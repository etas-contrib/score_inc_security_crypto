// =============================================================================
//  C O P Y R I G H T
// =============================================================================
//  Copyright (c) 2026 by ETAS GmbH. All rights reserved.
//
//  The reproduction, distribution and utilization of this file as
//  well as the communication of its contents to others without express
//  authorization is prohibited. Offenders will be held liable for the
//  payment of damages. All rights reserved in the event of the grant
//  of a patent, utility model or design.
// =============================================================================

#include <fstream>
#include <iostream>
#include <limits>
#include <variant>
#include <vector>

#include "score/crypto/daemon/config/src/flatbuffer_config_parser.hpp"

// Include FlatBuffers generated file
#include "score/crypto/daemon/config/crypto_config_generated.h"

using namespace score::crypto::daemon::config::keyslot;

namespace score::crypto::daemon::config
{

Expected<std::monostate, common::DaemonErrorCode> FlatBufferConfigParser::ValidateBuffer(const uint8_t* data,
                                                                                         size_t size)
{
    if (!data || size < kMinBufferSize)
    {
        std::cerr << LOG_PREFIX << "Buffer too small or null pointer. Required: >=4 bytes, Got: " << size << "\n";
        return make_unexpected(common::DaemonErrorCode::kInvalidArgument);
    }

    if (!CryptoConfigBufferHasIdentifier(data))
    {
        std::cerr << LOG_PREFIX << "Buffer does not have expected file identifier\n";
        return make_unexpected(common::DaemonErrorCode::kInternalError);
    }

    return std::monostate{};
}

Expected<std::monostate, common::DaemonErrorCode> FlatBufferConfigParser::ParseKeySlotConfig(const CryptoConfig* root,
                                                                                             KeyConfig& out_config)
{
    if (!root)
    {
        std::cerr << LOG_PREFIX << "Failed to get FlatBuffers root object\n";
        return make_unexpected(common::DaemonErrorCode::kInvalidArgument);
    }

    // Get key slot config from root
    const auto* key_slot_config = root->key_slot_config();
    if (!key_slot_config)
    {
        std::cerr << LOG_PREFIX << "Failed to get key_slot_config from root object\n";
        return make_unexpected(common::DaemonErrorCode::kInvalidArgument);
    }

    // Parse slot entries
    auto slot_entries_result = ParseSlotEntries(key_slot_config, out_config);
    if (!slot_entries_result.has_value())
    {
        return make_unexpected(slot_entries_result.error());
    }

    // Parse app resource entries
    auto app_resource_result = ParseAppResourceEntries(key_slot_config, out_config);
    if (!app_resource_result.has_value())
    {
        return make_unexpected(app_resource_result.error());
    }

    std::cout << LOG_PREFIX << "Successfully parsed configuration. Loaded " << out_config.GetSlotEntries().size()
              << " slot(s) and " << out_config.GetAppResourceEntries().size() << " app resource mapping(s).\n";

    return std::monostate{};
}

Expected<std::monostate, common::DaemonErrorCode> FlatBufferConfigParser::ParseSlotEntries(
    const KeySlotConfig* key_slot_config,
    KeyConfig& out_config)
{
    const auto* slot_entries = key_slot_config->slot_entries();
    if (!slot_entries)
    {
        return std::monostate{};  // No slot entries is not an error
    }

    for (const auto* entry : *slot_entries)
    {
        if (!entry)
        {
            std::cerr << LOG_PREFIX << "Null slot entry encountered - invalid configuration\n";
            return make_unexpected(common::DaemonErrorCode::kInternalError);
        }

        KeyConfig::KeySlotEntry slot_entry;

        if (!entry->slot_name())
        {
            std::cerr << LOG_PREFIX << "Slot entry missing required field 'slot_name'\n";
            return make_unexpected(common::DaemonErrorCode::kInternalError);
        }
        slot_entry.slot_name = entry->slot_name()->str();

        if (!entry->algorithm())
        {
            std::cerr << LOG_PREFIX << "Slot entry missing required field 'algorithm'\n";
            return make_unexpected(common::DaemonErrorCode::kInternalError);
        }
        slot_entry.algorithm = entry->algorithm()->str();

        if (!entry->provider_names())
        {
            std::cerr << LOG_PREFIX << "Slot entry missing required field 'provider_names'\n";
            return make_unexpected(common::DaemonErrorCode::kInternalError);
        }
        for (const auto* provider : *entry->provider_names())
        {
            if (provider)
            {
                slot_entry.provider_names.push_back(provider->str());
            }
        }

        if (!entry->allowed_operations())
        {
            std::cerr << LOG_PREFIX << "Slot entry missing required field 'allowed_operations'\n";
            return make_unexpected(common::DaemonErrorCode::kInternalError);
        }
        slot_entry.allowed_operations = entry->allowed_operations()->str();

        if (!entry->allowed_uids())
        {
            std::cerr << LOG_PREFIX << "Slot entry missing required field 'allowed_uids'\n";
            return make_unexpected(common::DaemonErrorCode::kInternalError);
        }
        for (auto uid : *entry->allowed_uids())
        {
            slot_entry.allowed_uids.push_back(uid);
        }

        if (!entry->allowed_write_uids())
        {
            std::cerr << LOG_PREFIX << "Slot entry missing required field 'allowed_write_uids'\n";
            return make_unexpected(common::DaemonErrorCode::kInternalError);
        }
        for (auto uid : *entry->allowed_write_uids())
        {
            slot_entry.allowed_write_uids.push_back(uid);
        }

        if (!entry->deployment_path())
        {
            std::cerr << LOG_PREFIX << "Slot entry missing required field 'deployment_path'\n";
            return make_unexpected(common::DaemonErrorCode::kInternalError);
        }
        slot_entry.deployment_path = entry->deployment_path()->str();

        if (!entry->deployment_format())
        {
            std::cerr << LOG_PREFIX << "Slot entry missing required field 'deployment_format'\n";
            return make_unexpected(common::DaemonErrorCode::kInternalError);
        }
        slot_entry.deployment_format = entry->deployment_format()->str();

        out_config.AddSlotEntry(std::move(slot_entry));

        std::cout << LOG_PREFIX << "Loaded slot: '" << out_config.GetSlotEntries().back().slot_name << "'\n";
    }

    return std::monostate{};
}

Expected<std::monostate, common::DaemonErrorCode> FlatBufferConfigParser::ParseFromFile(std::string_view filepath,
                                                                                        KeyConfig& out_config)
{
    std::ifstream file(std::string(filepath), std::ios::binary | std::ios::ate);
    if (!file.is_open())
    {
        std::cerr << LOG_PREFIX << "Failed to open file: " << filepath << "\n";
        return make_unexpected(common::DaemonErrorCode::kInvalidArgument);
    }

    // Get file size
    std::streamsize size = file.tellg();
    if (size <= 0)
    {
        std::cerr << LOG_PREFIX << "File is empty: " << filepath << "\n";
        return make_unexpected(common::DaemonErrorCode::kInvalidArgument);
    }

    file.seekg(0, std::ios::beg);

    // Read entire file into buffer
    if (size > std::numeric_limits<size_t>::max())
    {
        std::cerr << LOG_PREFIX << "File size exceeds maximum allowed size: " << filepath << "\n";
        return make_unexpected(common::DaemonErrorCode::kInvalidArgument);
    }

    std::vector<uint8_t> buffer(static_cast<size_t>(size));
    if (!file.read(reinterpret_cast<char*>(buffer.data()), size))
    {
        std::cerr << LOG_PREFIX << "Failed to read file: " << filepath << "\n";
        return make_unexpected(common::DaemonErrorCode::kInvalidArgument);
    }

    return ParseFromBuffer(buffer.data(), buffer.size(), out_config);
}

Expected<std::monostate, common::DaemonErrorCode> FlatBufferConfigParser::ParseAppResourceEntries(
    const KeySlotConfig* key_slot_config,
    KeyConfig& out_config)
{
    const auto* app_resource_entries = key_slot_config->app_resource_entries();
    if (!app_resource_entries)
    {
        return std::monostate{};  // No app resource entries is not an error
    }

    for (const auto* entry : *app_resource_entries)
    {
        if (!entry)
        {
            std::cerr << LOG_PREFIX << "Null app resource entry encountered - invalid configuration\n";
            return make_unexpected(common::DaemonErrorCode::kInternalError);
        }

        KeyConfig::AppResourceEntry resource_entry;
        resource_entry.uid = entry->uid();

        // All fields below are required per schema - add defensive checks
        if (!entry->app_resource_id())
        {
            std::cerr << LOG_PREFIX << "App resource entry missing required field 'app_resource_id'\n";
            return make_unexpected(common::DaemonErrorCode::kInternalError);
        }
        resource_entry.app_resource_id = entry->app_resource_id()->str();

        if (!entry->slot_name())
        {
            std::cerr << LOG_PREFIX << "App resource entry missing required field 'slot_name'\n";
            return make_unexpected(common::DaemonErrorCode::kInternalError);
        }
        resource_entry.slot_name = entry->slot_name()->str();

        out_config.AddAppResourceEntry(std::move(resource_entry));
    }

    return std::monostate{};
}

Expected<std::monostate, common::DaemonErrorCode> FlatBufferConfigParser::ParseFromBuffer(const uint8_t* data,
                                                                                          size_t size,
                                                                                          KeyConfig& out_config)
{
    if (!data || size == 0)
    {
        std::cerr << LOG_PREFIX << "Invalid buffer: null pointer or zero size\n";
        return make_unexpected(common::DaemonErrorCode::kInvalidArgument);
    }

    auto validateRes = ValidateBuffer(data, size);
    if (!validateRes.has_value())
    {
        std::cerr << LOG_PREFIX << "Buffer validation failed\n";
        return make_unexpected(validateRes.error());
    }

    // Get root FlatBuffers object (CryptoConfig is the root_type)
    const auto* root = flatbuffers::GetRoot<CryptoConfig>(data);
    if (!root)
    {
        std::cerr << LOG_PREFIX << "Failed to get FlatBuffers root object from buffer\n";
        return make_unexpected(common::DaemonErrorCode::kInternalError);
    }

    return ParseKeySlotConfig(root, out_config);
}

}  // namespace score::crypto::daemon::config
