load("@rules_cc//cc:defs.bzl", "cc_binary")
load("@rules_wix//:rules.bzl", "pkg_msi")

alias(
    name = "windows",
    actual = ":dmx_litraglow.msi",
)

pkg_msi(
    name = "dmx_litraglow.msi",
    src = "installer.wxs",
    arch = "x64",
    exts = [
        "WixUiExtension",
        "WixFirewallExtension",
    ],
    target_compatible_with = [
        "@platforms//os:windows",
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
        "@platforms//os:windows",
    ],
    deps = [
        "//:controller",
        "@com_github_jupp0r_prometheus_cpp//pull",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
    ],
)
