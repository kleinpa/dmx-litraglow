load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

alias(
    name = "hidapi",
    actual =
        select({
            "@platforms//os:windows": ":hidapi_windows",
            "//conditions:default": "hidapi_linux",
        }),
    visibility = ["//visibility:public"],
)

cc_library(
    name = "hidapi_windows",
    srcs = [
        "windows/hid.c",
        "windows/hidapi_cfgmgr32.h",
        "windows/hidapi_descriptor_reconstruct.c",
        "windows/hidapi_descriptor_reconstruct.h",
        "windows/hidapi_hidclass.h",
        "windows/hidapi_hidpi.h",
        "windows/hidapi_hidsdi.h",
        "windows/hidapi_winapi.h",
    ],
    hdrs = ["hidapi/hidapi.h"],
    copts = ["-Dhidapi_winapi_EXPORTS"],
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
