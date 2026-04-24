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

# Abstract base key management handler for the score interface family.
cc_library(
    name = "score_key_management_handler",
    srcs = ["src/score_key_management_handler.cpp"],
    hdrs = ["score_key_management_handler.hpp"],
    visibility = ["//:__subpackages__"],
    deps = [
        "//score/crypto/daemon/provider/executors:key_mgmt_executor",
        "//score/crypto/daemon/provider/handler:handler_headers",
    ],
)
