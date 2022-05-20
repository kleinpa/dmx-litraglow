load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "basic",
    srcs = ["basic.cc"],
    deps = [
        "@com_github_libusb_hidapi//:hidapi",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
    ],
)

cc_binary(
    name = "dmx",
    srcs = [
        "device.cc",
        "device.h",
        "dmx.cc",
    ],
    deps = [
        "@com_github_etclabs_sacn//:sacn_cpp",
        "@com_github_jupp0r_prometheus_cpp//pull",
        "@com_github_libusb_hidapi//:hidapi",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
    ],
)
