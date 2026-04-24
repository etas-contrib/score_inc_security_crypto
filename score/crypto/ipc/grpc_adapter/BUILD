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

load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("@rules_cc//cc:defs.bzl", "cc_shared_library")

genrule(
    name = "generated_grpc_control_server",
    srcs = ["control.fbs"],
    outs = [
        "control_generated.h",
        "control.grpc.fb.h",
        "control.grpc.fb.cc",
    ],
    cmd = "$(location @flatbuffers//:flatc) --cpp --grpc -o $(@D) $(SRCS)",
    tools = ["@flatbuffers//:flatc"],
)

cc_library(
    name = "grpc_control_server",
    srcs = [
        "grpc_control_handler.h",
        "src/grpc_control_handler.cpp",
        "src/grpc_control_server.cpp",
        ":generated_grpc_control_server",
    ],
    hdrs = [
        "grpc_control_server.h",
    ],
    implementation_deps = [
        "@grpc//:grpc++_unsecure",
    ],
    linkstatic = True,  # Internal library should only be statically linked
    visibility = ["//:__subpackages__"],
    deps = [
        "//score/crypto/daemon/control_plane",
        "@flatbuffers",
    ],
)

cc_library(
    name = "grpc_control_client",
    srcs = [
        "src/grpc_control_client.cpp",
        "src/grpc_id_helpers.cpp",
        ":generated_grpc_control_server",
    ],
    hdrs = [
        "grpc_control_client.h",  # No factory yet
        "src/grpc_id_helpers.h",
    ],
    implementation_deps = [
        "@grpc//:grpc++_unsecure",
    ],
    linkstatic = True,  # Internal library should only be statically linked
    visibility = [
        "//score/crypto/api:__subpackages__",
        "//score/crypto/daemon/IPC:__pkg__",
        "//tests:__subpackages__",
    ],
    deps = [
        "//score/crypto/api/control_plane",
        "//score/crypto/daemon/control_plane:request_handler_hdr",
        "@flatbuffers",
    ],
)
