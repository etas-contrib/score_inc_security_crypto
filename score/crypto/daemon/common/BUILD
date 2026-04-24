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
    name = "common",
    hdrs = [
        "actors.hpp",
        "daemon_error.hpp",
        "secure_memory.hpp",
        "types.hpp",
    ],
    visibility = ["//:__subpackages__"],
    deps = [
        "//score/mw/crypto/api/common:crypto_common",
        "@score_baselibs//score/result",
    ],
)

# Header-only utility: algorithm sizing tables for hash, MAC, and key algorithms.
cc_library(
    name = "algorithm_info",
    hdrs = ["algorithm_info.hpp"],
    visibility = ["//:__subpackages__"],
)

# Header-only utility: human-readable names for OperationActor / OperationAction values.
# Depends on the three operation-constants headers (each only deps on :common).
cc_library(
    name = "operation_names",
    hdrs = ["operation_names.hpp"],
    visibility = ["//:__subpackages__"],
    deps = [
        ":common",
        "//score/crypto/daemon/key_management:key_management_operations",
        "//score/crypto/daemon/provider/handler:hash_handler_operations",
        "//score/crypto/daemon/provider/handler:mac_handler_operations",
    ],
)
