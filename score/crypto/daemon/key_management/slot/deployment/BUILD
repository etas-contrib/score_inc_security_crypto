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

load("@rules_cc//cc:cc_library.bzl", "cc_library")

# Header-only: interfaces + shared path validation utility.
# No format-specific deps — adding a new format (json, flatbuffer, ...) only
# requires adding a new cc_library target in this file; nothing else changes.
cc_library(
    name = "deployment_iface",
    hdrs = [
        "deployment_path_utils.hpp",
        "i_deployment_loader.hpp",
        "i_deployment_writer.hpp",
    ],
    visibility = ["//:__subpackages__"],
    deps = [
        "//score/crypto/common:common_types",
        "//score/crypto/daemon/common",
        "//score/crypto/daemon/key_management:key_management_headers",
    ],
)

# KV format implementation.  Stdlib-only — no extra library deps required.
# To add a new format, create an analogous target here (e.g. json_deployment)
# and add it as a dep to //score/crypto/daemon/key_management:key_management.
cc_library(
    name = "kv_deployment",
    srcs = [
        "kv/kv_deployment_loader.cpp",
        "kv/kv_deployment_writer.cpp",
    ],
    hdrs = [
        "kv/kv_deployment_loader.hpp",
        "kv/kv_deployment_writer.hpp",
    ],
    visibility = ["//:__subpackages__"],
    deps = [":deployment_iface"],
)
