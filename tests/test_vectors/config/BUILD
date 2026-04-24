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

genrule(
    name = "generate_integration_test_config",
    srcs = [
        "//score/crypto/daemon/config:crypto_config_fbs_schema",
        "integration_test_config.json",
    ],
    outs = ["integration_test_config.bin"],
    cmd = "$(location @flatbuffers//:flatc) -b -o $(@D) $(SRCS)",
    tools = ["@flatbuffers//:flatc"],
    visibility = ["//:__subpackages__"],
)

filegroup(
    name = "integration_test_config",
    srcs = [
        "integration_openssl_hmac.kv",
        "integration_softhsm_hmac.kv",
        ":generate_integration_test_config",
    ],
    visibility = ["//:__subpackages__"],
)
