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

# Bazel build file for AES-128-ECB block cipher tests

load("@rules_cc//cc:cc_test.bzl", "cc_test")

cc_test(
    name = "test_ecb_aes128",
    timeout = "short",
    srcs = ["test_ecb_aes128.cpp"],
    data = [
        "//tests/test_vectors/block_cipher/ECB-AES128:block_cipher_test_vectors",
    ],
    dynamic_deps = [
        "//third_party/openssl:openssl_shared",
    ],
    deps = [
        "//tests/utility",
        "//third_party/openssl",
        "@googletest//:gtest",
    ],
)
