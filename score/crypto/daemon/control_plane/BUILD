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
    name = "control_operations",
    hdrs = ["control_operations.h"],
    visibility = [
        "//:__subpackages__",
    ],
    deps = ["//score/crypto/daemon/common"],
)

cc_library(
    name = "request_handler_hdr",
    hdrs = [
        "control_protocol.h",
        "i_request_handler.hpp",
    ],
    visibility = ["//:__subpackages__"],
    deps = [
        "//score/crypto/daemon/data_manager",
        "@score_baselibs//score/result",
    ],
)

cc_library(
    name = "control_plane",
    srcs = [
        "src/basic_handler_chain_factory.cpp",
        "src/connection_handler.cpp",
        "src/connection_handler.hpp",
    ],
    hdrs = [
        "basic_handler_chain_factory.hpp",
        "control_protocol.h",
        "i_control_server.h",
        "i_handler_chain_factory.hpp",
        "i_request_handler.hpp",
    ],
    linkstatic = True,  # Internal library should only be statically linked
    visibility = ["//:__subpackages__"],
    deps = [
        ":control_operations",
        ":request_handler_hdr",
        "//score/crypto/daemon/config",
        "//score/crypto/daemon/data_manager",
        "//score/crypto/daemon/mediator",
        "//score/crypto/daemon/provider:provider_manager",
        "@score_baselibs//score/result",
    ],
)
