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

load("@rules_cc//cc:defs.bzl", "cc_library")

# Header-only library for the OpenSSL key management primitives.
cc_library(
    name = "openssl_key_management_headers",
    hdrs = [
        "key_management/openssl_key_factory.hpp",
        "key_management/openssl_key_handler.hpp",
    ],
    visibility = ["//:__subpackages__"],
    deps = [
        "//score/crypto/daemon/key_management:key_management_headers",
    ],
)

# Header-only library for OpenSSL algorithm detail headers.
cc_library(
    name = "openssl_detail_headers",
    hdrs = ["detail/openssl_algorithm_info.hpp"],
    implementation_deps = ["//third_party/openssl"],
    visibility = ["//:__subpackages__"],
)

cc_library(
    name = "provider_openssl_headers",
    hdrs = [
        "openssl_provider_factory.hpp",
        "operations/factory/openssl_handler_factory.hpp",
        "operations/hash/openssl_hash_handler.hpp",
        "operations/key_management/openssl_key_management_handler.hpp",
        "operations/mac/openssl_hmac_handler.hpp",
        "provider_openssl.hpp",
    ],
    includes = ["."],
    visibility = ["//:__subpackages__"],
    deps = [
        ":openssl_key_management_headers",
        "//score/crypto/daemon/key_management:key_management_headers",
        "//score/crypto/daemon/provider/executors:key_mgmt_executor",
        "//score/crypto/daemon/provider/score_provider",
        "//score/crypto/daemon/provider/score_provider/operations/factory:score_handler_factory",
        "//score/crypto/daemon/provider/score_provider/operations/hash:score_hash_handler",
        "//score/crypto/daemon/provider/score_provider/operations/key_management:score_key_management_handler",
        "//score/crypto/daemon/provider/score_provider/operations/mac:score_mac_handler",
    ],
)

cc_library(
    name = "provider_openssl_library",
    srcs = [
        "detail/openssl_algorithm_info.hpp",
        "key_management/openssl_key_factory.cpp",
        "key_management/openssl_key_handler.cpp",
        "operations/factory/openssl_handler_factory.cpp",
        "operations/hash/openssl_hash_handler.cpp",
        "operations/key_management/openssl_key_management_handler.cpp",
        "operations/mac/openssl_hmac_handler.cpp",
        "provider_openssl.cpp",
    ],
    implementation_deps = [
        "//third_party/openssl",
    ],
    includes = ["."],
    linkstatic = True,
    visibility = ["//:__subpackages__"],
    deps = [
        ":openssl_detail_headers",
        ":openssl_key_management_headers",
        ":provider_openssl_headers",
        "//score/crypto/daemon/common",
        "//score/crypto/daemon/common:algorithm_info",
        "//score/crypto/daemon/data_manager",
        "//score/crypto/daemon/key_management",
        "//score/crypto/daemon/provider:provider_headers",
        "//score/crypto/daemon/provider/handler:handler_utils_impl",
    ],
)

cc_library(
    name = "provider_openssl_factory",
    srcs = ["openssl_provider_factory.cpp"],
    hdrs = ["openssl_provider_factory.hpp"],
    visibility = ["//:__subpackages__"],
    deps = [
        ":provider_openssl_library",
        "//score/crypto/daemon/provider:provider_headers",
    ],
)
