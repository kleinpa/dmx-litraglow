load("@rules_cc//cc:defs.bzl", "cc_binary")
load("@rules_wix//:rules.bzl", "pkg_msi")

alias(
    name = "installer",
    actual = ":installer.msi",
)

pkg_msi(
    name = "installer.msi",
    src = "installer.wxs",
    arch = "x64",
    exts = [
        "WixUiExtension",
        "WixFirewallExtension",
    ],
    target_compatible_with = [
        "@bazel_tools//platforms:windows",
    ],
    deps = [
        ":service",
    ],
)

cc_binary(
    name = "service",
    srcs = ["service.cc"],
    linkopts = ["advapi32.lib"],
    target_compatible_with = [
        "@bazel_tools//platforms:windows",
    ],
    deps = [
        "//:controller",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
    ],
)
