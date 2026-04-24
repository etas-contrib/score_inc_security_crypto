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

load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "crypto_daemon",
    srcs = ["src/daemon.cpp"],
    copts = select({
        "//conditions:default": [],
        ":tsan_enabled": [
            "-fsanitize=thread",
            "-g",
            "-O1",
        ],
    }),
    dynamic_deps = [
        "//third_party/openssl:openssl_shared",
        "//third_party/grpc:libgrpc_shared",
    ],
    includes = ["IPC"],
    linkopts = select({
        "//conditions:default": [],
        ":tsan_enabled": [
            "-fsanitize=thread",
        ],
    }),
    linkstatic = True,
    visibility = ["//tests:__subpackages__"],
    deps = [
        "//score/crypto/daemon/config",
        "//score/crypto/daemon/control_plane",
        "//score/crypto/daemon/data_manager",
        "//score/crypto/daemon/mediator",
        "//score/crypto/daemon/provider:provider_manager",
        "//score/crypto/daemon/provider/pkcs11:provider_pkcs11_factory",
        "//score/crypto/daemon/provider/score_provider:score_provider_factory",
        "//score/crypto/ipc:ipc_config",
        "//score/crypto/ipc/grpc_adapter:grpc_control_server",
    ],
)

# Configuration for enabling ThreadSanitizer
config_setting(
    name = "tsan_enabled",
    values = {
        "define": "tsan=1",
    },
)
