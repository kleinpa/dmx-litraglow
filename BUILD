load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_binary(
    name = "basic",
    srcs = [
        "basic.cc",
        "device.cc",
        "device.h",
    ],
    deps = [
        "@com_github_libusb_hidapi//:hidapi",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
    ],
)

cc_library(
    name = "controller",
    srcs = [
        "controller.cc",
        "device.cc",
        "device.h",
        "dmx_server.cc",
        "dmx_server.h",
    ],
    hdrs = [
        "controller.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@com_github_etclabs_sacn//:sacn_cpp",
        "@com_github_jupp0r_prometheus_cpp//pull",
        "@com_github_libusb_hidapi//:hidapi",
    ],
)

cc_binary(
    name = "main",
    srcs = [
        "main.cc",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":controller",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
    ],
)
