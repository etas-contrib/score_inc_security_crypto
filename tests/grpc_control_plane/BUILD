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

load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_test")
load("@score_itf//:defs.bzl", "py_itf_test")

cc_test(
    name = "test_control_plane",
    timeout = "short",
    srcs = ["test_control_plane.cpp"],
    dynamic_deps = ["//third_party/grpc:libgrpc_shared"],
    deps = [
        "//score/crypto/api:operations",
        "//score/crypto/api/control_plane:control_plane_impl",
        "//score/crypto/daemon/control_plane",
        "//score/crypto/daemon/mediator",
        "//score/crypto/ipc/grpc_adapter:grpc_control_server",
        "@googletest//:gtest",
    ],
)
