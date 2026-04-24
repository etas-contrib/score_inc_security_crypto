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

load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "test_provider",
    srcs = ["test_provider.cpp"],
    data = ["//tests/test_vectors/hash:hash_test_vectors"],
    deps = [
        "//score/crypto/daemon/common",
        "//score/crypto/daemon/data_manager",
        "//score/crypto/daemon/provider/handler:crypto_handler_factory_headers",
        "//score/crypto/daemon/provider/handler:hash_handler_operations",
        "//score/crypto/daemon/provider/score_provider/openssl:provider_openssl_library",
        "//tests/utility",
        "@googletest//:gtest",
    ],
)

cc_test(
    name = "test_pkcs11_provider",
    srcs = ["test_pkcs11_provider.cpp"],
    data = ["//tests/test_vectors/hash:hash_test_vectors"],
    deps = [
        "//score/crypto/daemon/common",
        "//score/crypto/daemon/provider:provider_headers",
        "//score/crypto/daemon/provider/handler:hash_handler_operations",
        "//score/crypto/daemon/provider/pkcs11:provider_pkcs11_library",
        "//tests/utility",
        "//third_party/soft_hsm:libsofthsm_shared",
        "@googletest//:gtest",
    ],
)

cc_test(
    name = "test_pkcs11_multi_token",
    srcs = ["test_pkcs11_multi_token.cpp"],
    deps = [
        "//score/crypto/daemon/common",
        "//score/crypto/daemon/provider:provider_headers",
        "//score/crypto/daemon/provider:provider_manager",
        "//score/crypto/daemon/provider/pkcs11:provider_pkcs11_library",
        "//third_party/soft_hsm:libsofthsm_shared",
        "@googletest//:gtest",
    ],
)

cc_test(
    name = "test_provider_manager",
    srcs = ["test_provider_manager.cpp"],
    deps = [
        "//score/crypto/daemon/common",
        "//score/crypto/daemon/data_manager",
        "//score/crypto/daemon/provider:provider_headers",
        "//score/crypto/daemon/provider:provider_manager",
        "//score/crypto/daemon/provider/handler:context_node",
        "@googletest//:gtest_main",
    ],
)
