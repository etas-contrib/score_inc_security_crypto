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

cc_library(
    name = "key_mgmt_executor",
    srcs = ["src/key_mgmt_executor.cpp"],
    hdrs = [
        "key_mgmt_context.hpp",
        "key_mgmt_executor.hpp",
        "key_mgmt_request_parser.hpp",
    ],
    visibility = [
        "//score/crypto/daemon/provider:__subpackages__",
        "//tests:__subpackages__",
    ],
    deps = [
        "//score/crypto/daemon/common",
        "//score/crypto/daemon/key_management",
        "//score/crypto/daemon/provider/handler:handler_headers",
    ],
)
