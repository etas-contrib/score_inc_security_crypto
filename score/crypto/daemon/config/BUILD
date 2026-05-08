# =============================================================================
#  C O P Y R I G H T
# -----------------------------------------------------------------------------
#  Copyright (c) 2025-2026 by ETAS GmbH. All rights reserved.
#
#  The reproduction, distribution and utilization of this file as
#  well as the communication of its contents to others without express
#  authorization is prohibited. Offenders will be held liable for the
#  payment of damages. All rights reserved in the event of the grant
#  of a patent, utility model or design.
# =============================================================================

load("@rules_cc//cc:defs.bzl", "cc_library")

# Export FlatBuffers schema for use by tests
filegroup(
    name = "crypto_config_fbs_schema",
    srcs = ["crypto_config.fbs"],
    visibility = ["//:__subpackages__"],
)

genrule(
    name = "generated_crypto_config",
    srcs = ["crypto_config_fbs_schema"],
    outs = [
        "crypto_config_generated.h",
    ],
    cmd = "$(location @flatbuffers//:flatc) --cpp -o $(@D) $(SRCS)",
    tools = ["@flatbuffers//:flatc"],
)

# Configuration types and structures (headers only)
cc_library(
    name = "config_types",
    hdrs = ["inc/config.hpp"],
    includes = ["inc"],
    visibility = ["//:__subpackages__"],
    deps = [
        "//score/crypto/daemon/common",
        "//score/crypto/daemon/provider/pkcs11:pkcs11_token_config",
        "//score/crypto/daemon/provider/score_provider:score_provider_config",
    ],
)

# FlatBuffers configuration parser
cc_library(
    name = "flatbuffer_config_parser",
    srcs = [
        "src/flatbuffer_config_parser.cpp",
        ":generated_crypto_config",
    ],
    hdrs = [
        "src/flatbuffer_config_parser.hpp",
        ":generated_crypto_config",
    ],
    includes = ["inc"],
    visibility = ["//:__subpackages__"],
    deps = [
        ":config_types",
        "//score/crypto/common:common_types",
        "//score/crypto/daemon/common",
        "@flatbuffers",
        "@score_baselibs//score/mw/log",
    ],
)

cc_library(
    name = "config",
    srcs = ["src/config.cpp"],
    includes = ["inc"],
    visibility = ["//:__subpackages__"],
    deps = [
        ":config_types",
        ":flatbuffer_config_parser",
        "//score/crypto/daemon/common",
    ],
)
