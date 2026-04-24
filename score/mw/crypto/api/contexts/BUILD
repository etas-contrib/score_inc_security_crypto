# =============================================================================
#  C O P Y R I G H T
# -----------------------------------------------------------------------------
#Copyright(c) 2026 by ETAS GmbH.All rights reserved.
#
#  The reproduction, distribution and utilization of this file as
#  well as the communication of its contents to others without express
#  authorization is prohibited. Offenders will be held liable for the
#  payment of damages. All rights reserved in the event of the grant
#  of a patent, utility model or design.
# =============================================================================

load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "context_bases",
    hdrs = [
        "i_context.hpp",
        "i_streaming_context.hpp",
        "i_streaming_output_context.hpp",
    ],
    includes = ["."],
    visibility = ["//visibility:public"],
    deps = [
        "//score/mw/crypto/api/common:crypto_common",
        "@score_baselibs//score/language/futurecpp",
        "@score_baselibs//score/result",
    ],
)

cc_library(
    name = "crypto_contexts",
    hdrs = [
        "i_hash_context.hpp",
        "i_key_management_context.hpp",
        "i_mac_context.hpp",
    ],
    includes = ["."],
    visibility = ["//visibility:public"],
    deps = [
        ":context_bases",
        "//score/mw/crypto/api/common:crypto_common",
        "//score/mw/crypto/api/config:context_configs",
        "//score/mw/crypto/api/objects:crypto_objects",
        "@score_baselibs//score/language/futurecpp",
        "@score_baselibs//score/result",
    ],
)

cc_library(
    name = "crypto_contexts_impl",
    srcs = [
        "src/hash_context_impl.cpp",
        "src/key_management_context_impl.cpp",
        "src/mac_context_impl.cpp",
    ],
    hdrs = [
        "src/hash_context_impl.hpp",
        "src/key_management_context_impl.hpp",
        "src/mac_context_impl.hpp",
    ],
    includes = ["."],
    visibility = ["//:__subpackages__"],
    deps = [
        ":crypto_contexts",
        "//score/crypto/api:operations",
        "//score/crypto/api/control_plane",
        "//score/mw/crypto/api/common:crypto_common",
        "//score/mw/crypto/api/common:release_callback_iface",
    ],
)
