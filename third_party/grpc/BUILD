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

# Helper library to work around grpc not having proper symbol visibility for shared libraries.
#
# Bazel's cc_shared_library documentation states: "The rule implementation does not take
# care of informing the linker about which symbols should be exported. The user should
# take care of this via linker scripts or visibility declarations in the source code."
#
# Since grpc from Bazel Central Registry doesn't have visibility attributes (it's designed
# for static linking), we need this helper to ensure commonly-used APIs are included in
# the shared library by creating references to them.
cc_library(
    name = "grpc_symbol_reference",
    srcs = ["grpc_symbol_reference.cpp"],
    visibility = ["//visibility:private"],
    deps = ["@grpc//:grpc++_unsecure"],
    alwayslink = True,
)

cc_shared_library(
    name = "libgrpc_shared",
    shared_lib_name = "libgrpc++.so.1",
    visibility = ["//visibility:public"],
    deps = [
        ":grpc_symbol_reference",  # Forces inclusion of commonly-used grpc symbols
        "@grpc//:grpc++_unsecure",
    ],
)
