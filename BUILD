load("@bazel_skylib//rules:build_test.bzl", "build_test")
load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_binary(
    name = "basic",
    srcs = [
        "basic.cc",
        "device.cc",
        "device.h",
    ],
    deps = [
        "@abseil-cpp//absl/flags:flag",
        "@abseil-cpp//absl/flags:parse",
        "@com_github_libusb_hidapi//:hidapi",
        "@prometheus-cpp//pull",
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
        "@com_github_libusb_hidapi//:hidapi",
        "@prometheus-cpp//pull",
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
        "@abseil-cpp//absl/flags:flag",
        "@abseil-cpp//absl/flags:parse",
    ],
)

build_test(
    name = "main_build_test",
    targets = [
        ":main",
    ],
)
