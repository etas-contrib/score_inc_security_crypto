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

# Abstract base provider for the score interface family.
cc_library(
    name = "score_provider",
    srcs = ["src/score_provider.cpp"],
    hdrs = ["score_provider.hpp"],
    visibility = ["//:__subpackages__"],
    deps = [
        "//score/crypto/daemon/provider:provider_headers",
        "//score/crypto/daemon/provider/handler:crypto_handler_factory_headers",
    ],
)

# Score provider configuration (header-only entry struct + config class).
cc_library(
    name = "score_provider_config",
    hdrs = ["score_provider_config.hpp"],
    visibility = ["//:__subpackages__"],
)

# Top-level factory for the score interface family.
cc_library(
    name = "score_provider_factory",
    srcs = [
        "src/score_provider_config.cpp",
        "src/score_provider_factory.cpp",
    ],
    hdrs = ["score_provider_factory.hpp"],
    visibility = ["//:__subpackages__"],
    deps = [
        ":score_provider",
        ":score_provider_config",
        "//score/crypto/daemon/provider:provider_headers",
        "//score/crypto/daemon/provider/score_provider/openssl:provider_openssl_factory",
    ],
)
