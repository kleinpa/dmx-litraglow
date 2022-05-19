load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "bazel_skylib",
    sha256 = "f7be3474d42aae265405a592bb7da8e171919d74c16f082a5457840f06054728",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/releases/download/1.2.1/bazel-skylib-1.2.1.tar.gz",
        "https://github.com/bazelbuild/bazel-skylib/releases/download/1.2.1/bazel-skylib-1.2.1.tar.gz",
    ],
)

load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")

bazel_skylib_workspace()

http_archive(
    name = "com_github_libusb_hidapi",
    build_file = "@//external:hidapi.BUILD",
    sha256 = "1a75bccfb19801b7852284caa0de4b4c6fc3633aa81002845704e0c8ae3fc8dc",
    strip_prefix = "hidapi-hidapi-0.11.2",
    urls = ["https://github.com/libusb/hidapi/archive/refs/tags/hidapi-0.11.2.zip"],
)

http_archive(
    name = "com_google_absl",
    sha256 = "bb2a0b57c92b6666e8acb00f4cbbfce6ddb87e83625fb851b0e78db581340617",
    strip_prefix = "abseil-cpp-b9b925341f9e90f5e7aa0cf23f036c29c7e454eb",
    urls = ["https://github.com/abseil/abseil-cpp/archive/b9b925341f9e90f5e7aa0cf23f036c29c7e454eb.zip"],
)
