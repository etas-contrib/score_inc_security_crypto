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
    name = "provider_headers",
    hdrs = [
        "i_provider.hpp",
        "i_provider_factory.hpp",
        "provider_manager.hpp",
    ],
    visibility = ["//:__subpackages__"],
    deps = [
        "//score/crypto/daemon/common",
        "//score/crypto/daemon/config",
        "//score/crypto/daemon/provider/handler:context_node",
        "//score/crypto/daemon/provider/handler:crypto_handler_factory_headers",
    ],
)

cc_library(
    name = "provider_manager",
    srcs = ["src/provider_manager.cpp"],
    visibility = ["//:__subpackages__"],
    deps = [
        ":provider_headers",
    ],
)
