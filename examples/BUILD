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

load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "hashing_example",
    srcs = ["hashing_example.cpp"],
    deps = [
        "//score/mw/crypto/api:crypto_stack",
        "//score/mw/crypto/api/config:context_configs",
        "//score/mw/crypto/api/contexts:crypto_contexts",
    ],
)

cc_binary(
    name = "memory_allocator_example",
    srcs = ["memory_allocator_example.cpp"],
    deps = [
        "//score/mw/crypto/api:crypto_stack",
        "//score/mw/crypto/api/common:crypto_common",
        "//score/mw/crypto/api/config:context_configs",
        "//score/mw/crypto/api/contexts:crypto_contexts",
    ],
)

# =============================================================================
# FUTURE: Examples below depend on APIs not yet in scope.
# =============================================================================
# cc_binary(name = "encryption_example",   srcs = ["encryption_example.cpp"],   ...)
# cc_binary(name = "pqc_signing_example",  srcs = ["pqc_signing_example.cpp"],  ...)
# cc_binary(name = "certificate_example",  srcs = ["certificate_example.cpp"],  ...)
# cc_binary(name = "ephemeral_key_example",srcs = ["ephemeral_key_example.cpp"],...) # needs cipher context
# cc_binary(name = "cross_provider_example",srcs = ["cross_provider_example.cpp"],...)
# cc_binary(name = "key_lifecycle_complete",srcs = ["key_lifecycle_complete.cpp"],..)
