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

load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_test")
load("@score_itf//:defs.bzl", "py_itf_test")

cc_binary(
    name = "control_client_app",
    srcs = ["control_client_app.cpp"],
    dynamic_deps = ["//third_party/grpc:libgrpc_shared"],
    deps = [
        "//score/crypto/api:operations",
        "//score/crypto/api/control_plane:control_plane_impl",
        "@googletest//:gtest",
    ],
)

cc_binary(
    name = "init_softhsm_token",
    srcs = ["init_softhsm_token.cpp"],
    deps = [
        "//third_party/soft_hsm:libsofthsm_shared",
    ],
)

cc_binary(
    name = "score_api_hash_example",
    srcs = ["score_api_hash_example.cpp"],
    data = [
        "//tests/test_vectors/config:integration_test_config",
        "//tests/test_vectors/hash:hash_test_vectors",
    ],
    dynamic_deps = ["//third_party/grpc:libgrpc_shared"],
    deps = [
        "//score/mw/crypto/api:crypto_stack",
        "//tests/utility",
        "@googletest//:gtest",
    ],
)

cc_binary(
    name = "score_api_mac_example",
    srcs = ["score_api_mac_example.cpp"],
    data = [
        "//tests/test_vectors/config:integration_test_config",
        "//tests/test_vectors/mac:mac_test_vectors",
    ],
    dynamic_deps = ["//third_party/grpc:libgrpc_shared"],
    deps = [
        "//score/mw/crypto/api:crypto_stack",
        "//tests/utility",
        "@googletest//:gtest",
    ],
)

cc_binary(
    name = "score_demo",
    srcs = ["score_demo.cpp"],
    data = [
        "//tests/test_vectors/config:integration_test_config",
        "//tests/test_vectors/mac:mac_test_vectors",
    ],
    dynamic_deps = ["//third_party/grpc:libgrpc_shared"],
    deps = [
        "//score/mw/crypto/api:crypto_stack",
        "//tests/utility",
    ],
)

py_itf_test(
    name = "integration_test_docker",
    size = "small",
    srcs = ["integration_test.py"],
    args = [
        "--docker-image=ubuntu:24.04",
        "--log-level=WARNING",
    ],
    data = [
        ":control_client_app",
        ":init_softhsm_token",
        ":score_api_hash_example",
        ":score_api_mac_example",
        ":score_demo",
        "//score/crypto/api/control_plane",
        "//score/crypto/daemon:crypto_daemon",
        "//third_party/grpc:libgrpc_shared",
        "//third_party/openssl:openssl_shared",
        "//third_party/soft_hsm:soft_hsm_cmake",
    ],
    plugins = [
        "itf.plugins.docker",
    ],
)
