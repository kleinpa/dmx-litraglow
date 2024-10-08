load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_library(
    name = "rgb_client_manager",
    srcs = ["rgb_client_manager.cc"],
    hdrs = ["rgb_client_manager.h"],
    deps = [
        "@abseil-cpp//absl/log",
        "@openrgb//:sdk",
    ],
)

cc_binary(
    name = "demo_client",
    srcs = ["demo_client.cc"],
    deps = [
        ":rgb_client_manager",
        "@abseil-cpp//absl/flags:flag",
        "@abseil-cpp//absl/flags:parse",
        "@abseil-cpp//absl/log",
        "@abseil-cpp//absl/log:flags",
        "@abseil-cpp//absl/log:initialize",
        "@openrgb//:sdk",
    ],
)

cc_binary(
    name = "dmx_openrgb_server",
    srcs = ["dmx_openrgb_server.cc"],
    deps = [
        ":rgb_client_manager",
        "//:controller",  # TODO: this includes extra junk
        "@abseil-cpp//absl/flags:flag",
        "@abseil-cpp//absl/flags:parse",
        "@abseil-cpp//absl/log",
        "@abseil-cpp//absl/log:flags",
        "@abseil-cpp//absl/log:initialize",
        "@openrgb//:sdk",
        "@prometheus-cpp//pull",
    ],
)
# cc_binary(
#     name = "main",
#     srcs = ["main.cc"],
#     deps = [
#         "@prometheus-cpp//pull",
#         "@abseil-cpp//absl/flags:flag",
#         "@abseil-cpp//absl/flags:parse",
#         "@abseil-cpp//absl/log",
#         "@abseil-cpp//absl/log:flags",
#         "@abseil-cpp//absl/log:initialize",
#         "@openrgb//:client",
#     ],
# )

cc_binary(
    name = "logi_direct",
    srcs = ["logi_direct.cc"],
    deps = [
        "@abseil-cpp//absl/flags:flag",
        "@abseil-cpp//absl/flags:parse",
        "@abseil-cpp//absl/log",
        "@abseil-cpp//absl/log:flags",
        "@abseil-cpp//absl/log:initialize",
        "@openrgb//:logitech_controller",
        "@prometheus-cpp//pull",
    ],
)
