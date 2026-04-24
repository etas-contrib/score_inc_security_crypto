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

load("@rules_cc//cc:defs.bzl", "cc_library")

# MAC executor + abstract base MAC handler for the score interface family.
cc_library(
    name = "score_mac_handler",
    srcs = [
        "src/mac_executor.cpp",
        "src/score_mac_handler.cpp",
    ],
    hdrs = [
        "mac_executor.hpp",
        "score_mac_handler.hpp",
    ],
    visibility = ["//:__subpackages__"],
    deps = [
        "//score/crypto/daemon/common",
        "//score/crypto/daemon/provider/handler:handler_headers",
        "//score/crypto/daemon/provider/handler:handler_utils_impl",
        "//score/crypto/daemon/provider/handler:mac_handler_operations",
    ],
)
