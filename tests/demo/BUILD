# =============================================================================
#  C O P Y R I G H T
# =============================================================================
#  Copyright (c) 2026 by ETAS GmbH. All rights reserved.
#
#  The reproduction, distribution and utilization of this file as
#  well as the communication of its contents to others without express
#  authorization is prohibited. Offenders will be held liable for the
#  payment of damages. All rights reserved in the event of the grant
#  of a patent, utility model or design.
# =============================================================================

load("@rules_cc//cc:cc_test.bzl", "cc_test")

cc_test(
    name = "mac_multi_provider_demo",
    srcs = ["mac_multi_provider_demo.cpp"],
    data = [
        "//tests/test_vectors/key_management:key_management_test_vectors",
    ],
    deps = [
        "//score/crypto/daemon/key_management",
        "//score/crypto/daemon/provider:provider_headers",
        "//score/crypto/daemon/provider/score_provider/openssl:provider_openssl_library",
        "//score/crypto/daemon/provider/score_provider/operations/mac:score_mac_handler",
        "//third_party/openssl",
        "@googletest//:gtest_main",
    ],
)
