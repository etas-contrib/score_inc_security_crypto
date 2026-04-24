# =============================================================================
#  C O P Y R I G H T
# -----------------------------------------------------------------------------
#Copyright(c) 2026 by ETAS GmbH.All rights reserved.
#
#  The reproduction, distribution and utilization of this file as
#  well as the communication of its contents to others without express
#  authorization is prohibited. Offenders will be held liable for the
#  payment of damages. All rights reserved in the event of the grant
#  of a patent, utility model or design.
# =============================================================================

load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "context_configs",
    hdrs = [
        "base_context_config.hpp",
        "hash_context_config.hpp",
        "key_management_context_config.hpp",
        "key_operation_params.hpp",
        "mac_context_config.hpp",
        "permission_builder.hpp",
    ],
    includes = ["."],
    visibility = ["//visibility:public"],
    deps = [
        "//score/mw/crypto/api/common:crypto_common",
    ],
)
