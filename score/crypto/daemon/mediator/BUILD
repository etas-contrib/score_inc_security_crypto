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
    name = "mediator_operations",
    hdrs = ["mediator_operations.hpp"],
    visibility = [
        "//:__subpackages__",
    ],
    deps = ["//score/crypto/daemon/common"],
)

cc_library(
    name = "mediator",
    srcs = [
        "src/mediator_impl.cpp",
    ],
    hdrs = [
        "i_mediator.hpp",
        "src/mediator_impl.hpp",
    ],
    includes = ["."],
    visibility = ["//:__subpackages__"],
    deps = [
        ":mediator_operations",
        "//score/crypto/daemon/common",
        "//score/crypto/daemon/common:operation_names",
        "//score/crypto/daemon/config",
        "//score/crypto/daemon/control_plane:request_handler_hdr",
        "//score/crypto/daemon/data_manager",
        "//score/crypto/daemon/key_management",
        "//score/crypto/daemon/key_management:key_management_headers",
        "//score/crypto/daemon/provider:provider_headers",
        "//score/crypto/daemon/provider:provider_manager",
    ],
)
