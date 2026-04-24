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

# Header-only fixture shared by all SoftHSM-based integration tests.
cc_library(
    name = "softhsm_test_fixture",
    hdrs = ["softhsm_test_fixture.hpp"],
    includes = ["."],
    visibility = ["//:__subpackages__"],
    deps = [
        "//third_party/soft_hsm:libsofthsm_shared",
        "@googletest//:gtest",
    ],
)
