load("@bazel_skylib//rules:build_test.bzl", "build_test")
load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("@bazel_skylib//rules:build_test.bzl", "build_test")

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
        "@hidapi",
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
        "@hidapi",
        "@prometheus-cpp//pull",
        "@sacn//:sacn_cpp",
    ],
)

cc_binary(
    name = "dmx-litraglow",
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
    name = "build_test",
    targets = [
        ":basic",
        ":dmx-litraglow",
    ],
)
