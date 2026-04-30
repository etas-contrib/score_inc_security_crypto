# =============================================================================
#  C O P Y R I G H T
# -----------------------------------------------------------------------------
#  Copyright (c) 2026 by ETAS GmbH. All rights reserved.
#
#  The reproduction, distribution and utilization of this file as
#  well as the communication of its contents to others without express
#  authorization is prohibited. Offenders will be held liable for the
#  payment of damages. All rights reserved in the event of the grant
#  of a patent, utility model or design.
# =============================================================================

load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

# Generate C++ header from the FlatBuffer schema.
# No --grpc flag: we only need plain C++ data tables, not gRPC stubs.
genrule(
    name = "generated_poc_control",
    srcs = ["poc_control.fbs"],
    outs = ["poc_control_generated.h"],
    cmd = "$(location @flatbuffers//:flatc) --cpp --size-prefixed -o $(@D) $(SRCS)",
    tools = ["@flatbuffers//:flatc"],
)

cc_library(
    name = "control_plane_service",
    hdrs = [
        ":generated_poc_control",
        "control_plane_interface.h",
        "ipc_buffer.h",
    ],
    include_prefix = "tests/score_com_poc",
    deps = [
        "@flatbuffers",
        "@score_communication//score/mw/com",
    ],
)

cc_test(
    name = "test_score_com_rpc",
    srcs = ["test_score_com_rpc.cpp"],
    data = ["mw_com_config.json"],
    deps = [
        ":control_plane_service",
        "@googletest//:gtest",
    ],
)
