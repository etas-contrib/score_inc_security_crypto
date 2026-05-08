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
    name = "control_plane",
    srcs = [
    ],
    hdrs = [
        "connection_factory.hpp",
        "i_connection.hpp",
    ],
    visibility = ["//:__subpackages__"],
    deps = [
        "//score/crypto/common:common_types",
        "//score/crypto/daemon/common",
        "//score/crypto/daemon/control_plane:request_handler_hdr",
    ],
)

cc_library(
    name = "control_plane_impl",
    srcs = [
        "src/connection_factory.cpp",
        "src/connection_impl.cpp",
    ],
    hdrs = [
        "src/connection_impl.hpp",
    ],
    visibility = ["//:__subpackages__"],
    deps = [
        ":control_plane",
        "//score/crypto/daemon/control_plane",
        "//score/crypto/ipc:ipc_config",
        "//score/crypto/ipc/grpc_adapter:grpc_control_client",
        "@score_baselibs//score/mw/log",
    ],
)
