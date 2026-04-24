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

# Abstract base handler factory for the score interface family.
cc_library(
    name = "score_handler_factory",
    srcs = ["src/score_handler_factory.cpp"],
    hdrs = ["score_handler_factory.hpp"],
    visibility = ["//:__subpackages__"],
    deps = [
        "//score/crypto/daemon/common",
        "//score/crypto/daemon/key_management",
        "//score/crypto/daemon/provider/handler:crypto_handler_factory_headers",
        "@score_baselibs//score/result",
    ],
)
