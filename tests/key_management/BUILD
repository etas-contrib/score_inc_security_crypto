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

load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "test_key_config_manager",
    srcs = ["test_key_config_manager.cpp"],
    data = [
        "//tests/key_management/config:key_management_test_config",
    ],
    deps = [
        "//score/crypto/daemon/config",
        "//score/crypto/daemon/key_management",
        "//score/crypto/daemon/key_management:key_management_headers",
        "//score/crypto/daemon/provider:provider_manager",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "test_access_policy_enforcer",
    srcs = ["test_access_policy_enforcer.cpp"],
    deps = [
        "//score/crypto/daemon/key_management",
        "//score/crypto/daemon/key_management:key_management_headers",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "test_openssl_key_handler",
    srcs = ["test_openssl_key_handler.cpp"],
    deps = [
        "//score/crypto/daemon/key_management:key_management_headers",
        "//score/crypto/daemon/provider/score_provider/openssl:provider_openssl_library",
        "//third_party/openssl",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "test_key_management_context",
    srcs = ["test_key_management_context.cpp"],
    data = [
        "//tests/key_management/config:key_management_test_config",
    ],
    deps = [
        "//score/crypto/daemon/common",
        "//score/crypto/daemon/config",
        "//score/crypto/daemon/data_manager",
        "//score/crypto/daemon/key_management",
        "//score/crypto/daemon/key_management:key_management_headers",
        "//score/crypto/daemon/provider/executors:key_mgmt_executor",
        "//score/crypto/daemon/provider/score_provider/openssl:provider_openssl_library",
        "//score/mw/crypto/api/common:crypto_common",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "test_pkcs11_key_handler",
    srcs = ["test_pkcs11_key_handler.cpp"],
    deps = [
        "//score/crypto/daemon/data_manager",
        "//score/crypto/daemon/key_management",
        "//score/crypto/daemon/key_management:key_management_headers",
        "//score/crypto/daemon/provider/executors:key_mgmt_executor",
        "//score/crypto/daemon/provider/pkcs11:provider_pkcs11_library",
        "//tests/softhsm:softhsm_test_fixture",
        "//third_party/soft_hsm:libsofthsm_shared",
        "@googletest//:gtest_main",
    ],
)
