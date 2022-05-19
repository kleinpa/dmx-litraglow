load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "hidapitester",
    srcs = ["hidapitester.c"],
    visibility = ["//visibility:public"],
    deps = [
        "@com_github_libusb_hidapi//:hidapi",
        "@com_github_libusb_libusb//:getopt",
    ],
)
