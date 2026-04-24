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
    name = "crypto_common",
    srcs = [
        "src/crypto_resource_guard.cpp",
        "src/crypto_resource_guard_factory.hpp",  # implementation-private; not exposed via hdrs
        "src/error_domain.cpp",
        "src/i_release_callback.hpp",  # implementation-private; not exposed via hdrs
    ],
    hdrs = [
        "crypto_resource_guard.hpp",
        "error_domain.hpp",
        "fixed_capacity_string.hpp",
        "i_memory_allocator.hpp",
        "i_memory_region.hpp",
        "types.hpp",
    ],
    includes = ["."],
    visibility = ["//visibility:public"],
    deps = [
        "@score_baselibs//score/language/futurecpp",
        "@score_baselibs//score/result",
    ],
)

# Internal target for IPC-layer code that implements IReleaseCallback.
# Application code must not depend on this target.
cc_library(
    name = "release_callback_iface",
    hdrs = ["src/i_release_callback.hpp"],
    includes = ["."],
    visibility = [
        "//score/crypto:__subpackages__",
        "//score/mw/crypto:__subpackages__",
    ],
    deps = [
        "@score_baselibs//score/result",
    ],
)
