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
