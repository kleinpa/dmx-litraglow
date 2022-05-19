load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

alias(
    name = "hidapi",
    actual =
        select({
            "@bazel_tools//src/conditions:windows": ":hidapi_windows",
            "//conditions:default": "hidapi_linux",
        }),
    visibility = ["//visibility:public"],
)

cc_library(
    name = "hidapi_libusb",
    srcs = [
        "libusb/hid.c",
        "libusb/hidapi_libusb.h",
    ],
    hdrs = ["hidapi/hidapi.h"],
    includes = ["hidapi"],
    visibility = ["//visibility:public"],
    deps = ["@com_github_libusb_libusb//:libusb"],
)

cc_library(
    name = "hidapi_windows",
    srcs = ["windows/hid.c"],
    hdrs = ["hidapi/hidapi.h"],
    includes = ["hidapi"],
    linkopts = ["setupapi.lib"],
)

cc_library(
    name = "hidapi_linux",
    srcs = ["linux/hid.c"],
    hdrs = ["hidapi/hidapi.h"],
    includes = ["hidapi"],
    linkopts = [
        "-lpthread",
        "-ludev",
    ],
)

cc_binary(
    name = "hidtest",
    srcs = ["hidtest/test.c"],
    defines = ["_WIN32"],
    deps = [":hidapi"],
)
