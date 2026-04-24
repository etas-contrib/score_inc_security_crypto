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

cc_library(
    name = "common_types",
    srcs = [
        "types.hpp",
    ],
    copts = [
        # Use baselibs expected implementation by default
        "-DSTD_LIB_CPP17=0",
    ],
    visibility = ["//:__subpackages__"],
    # Default: use baselibs/futurecpp expected
    # To switch to C++17 std lib: remove the deps below and set -DSTD_LIB_CPP17=1
    deps = [
        # Use results for deatils/expected, as it is not directly visible
        "@score_baselibs//score/result",
    ],
)
