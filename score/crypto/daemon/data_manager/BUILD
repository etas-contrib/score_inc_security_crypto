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
    name = "data_manager",
    srcs = [
        "src/data_manager.cpp",
        "src/data_node.cpp",
        "src/data_node_manager_token.hpp",
    ],
    hdrs = [
        "i_data_manager.hpp",
        "data_node.hpp",
        "data_node_accessor.hpp",
        # Public due to missing Factory
        "data_manager.hpp",
    ],
    visibility = ["//:__subpackages__"],
    deps = [
        "//score/crypto/common:common_types",
        "//score/crypto/daemon/common",
        "//score/crypto/daemon/provider/handler:handler_headers",
    ],
)
