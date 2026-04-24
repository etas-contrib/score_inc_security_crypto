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

# Hash executor + abstract base hash handler for the score interface family.
cc_library(
    name = "score_hash_handler",
    srcs = [
        "src/hash_executor.cpp",
        "src/score_hash_handler.cpp",
    ],
    hdrs = [
        "hash_executor.hpp",
        "score_hash_handler.hpp",
    ],
    visibility = ["//:__subpackages__"],
    deps = [
        "//score/crypto/daemon/common",
        "//score/crypto/daemon/common:algorithm_info",
        "//score/crypto/daemon/provider/handler:handler_headers",
        "//score/crypto/daemon/provider/handler:handler_utils_impl",
        "//score/crypto/daemon/provider/handler:hash_handler_operations",
    ],
)
