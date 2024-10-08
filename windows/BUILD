load("@rules_cc//cc:defs.bzl", "cc_binary")
load("@mjbots_rules_wix//:defs.bzl", "pkg_msi")

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
        "@abseil-cpp//absl/flags:flag",
        "@abseil-cpp//absl/flags:parse",
        "@prometheus-cpp//pull",
    ],
)
