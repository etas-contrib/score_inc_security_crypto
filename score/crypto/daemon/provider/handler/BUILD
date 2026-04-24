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

cc_library(
    name = "handler_headers",
    hdrs = [
        "handler_init_params.hpp",
        "i_handler.hpp",
    ],
    visibility = ["//:__subpackages__"],
    deps = [
        "//score/crypto/common:common_types",
        "//score/crypto/daemon/common",
        "//score/crypto/daemon/key_management:key_handler_iface",
        "//score/mw/crypto/api/common:crypto_common",
    ],
)

cc_library(
    name = "crypto_handler_factory_headers",
    hdrs = ["i_crypto_handler_factory.hpp"],
    visibility = ["//visibility:public"],
    deps = [
        ":handler_headers",
        ":handler_utils_hdr",
        "//score/crypto/daemon/common",
        "@score_baselibs//score/result",
    ],
)

# Handler utilities header library
cc_library(
    name = "handler_utils_hdr",
    hdrs = ["src/handler_utils.hpp"],
    visibility = [
        "//score/crypto/daemon/provider:__subpackages__",
        "//score/crypto/daemon/src/provider:__subpackages__",
    ],
    deps = [
        "//score/crypto/common:common_types",
        "//score/crypto/daemon/common",
    ],
)

# Handler utilities implementation library
cc_library(
    name = "handler_utils_impl",
    srcs = ["src/handler_utils.cpp"],
    hdrs = ["src/handler_utils.hpp"],
    visibility = [
        "//score/crypto/daemon/provider:__subpackages__",
        "//score/crypto/daemon/src/provider:__subpackages__",
    ],
    deps = [
        ":handler_utils_hdr",
        "//score/crypto/daemon/common",
    ],
)

# Hash handler operations header-only library
cc_library(
    name = "hash_handler_operations",
    hdrs = ["operations/hash_handler_operations.hpp"],
    visibility = [
        "//:__subpackages__",
    ],
    deps = ["//score/crypto/daemon/common"],
)

cc_library(
    name = "context_node",
    srcs = ["src/context_data_node.cpp"],
    hdrs = ["context_data_node.hpp"],
    visibility = ["//visibility:public"],
    deps = [
        ":handler_headers",
        "//score/crypto/daemon/common",
        "//score/crypto/daemon/data_manager",
        "//score/crypto/daemon/key_management:key_management_headers",
    ],
)

# MAC handler operations header-only library
cc_library(
    name = "mac_handler_operations",
    hdrs = ["operations/mac_handler_operations.hpp"],
    visibility = ["//:__subpackages__"],
    deps = ["//score/crypto/daemon/common"],
)
