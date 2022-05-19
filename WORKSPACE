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
    name = "com_github_libusb_libusb",
    build_file = "@//external:libusb.BUILD",
    sha256 = "4175f942e74f3c34b71d01b107d33e713f9ff47563f49bcc6e8b2534f414dd54",
    strip_prefix = "libusb-1.0.26",
    urls = ["https://github.com/libusb/libusb/archive/refs/tags/v1.0.26.zip"],
)

http_archive(
    name = "com_github_libusb_hidapi",
    build_file = "@//external:hidapi.BUILD",
    sha256 = "1a75bccfb19801b7852284caa0de4b4c6fc3633aa81002845704e0c8ae3fc8dc",
    strip_prefix = "hidapi-hidapi-0.11.2",
    urls = ["https://github.com/libusb/hidapi/archive/refs/tags/hidapi-0.11.2.zip"],
)

http_archive(
    name = "com_github_todbot_hidapitester",
    build_file = "@//external:hidapitester.BUILD",
    sha256 = "0505dcf2fd08c371f90948d7cbb278fff78ad6eb53ec879d8fa5fb391dd4941d",
    strip_prefix = "hidapitester-601c50c908515a25743558ae788129ea3b9bed16",
    urls = ["https://github.com/todbot/hidapitester/archive/601c50c908515a25743558ae788129ea3b9bed16.zip"],
)

http_archive(
    name = "com_google_absl",
    sha256 = "bb2a0b57c92b6666e8acb00f4cbbfce6ddb87e83625fb851b0e78db581340617",
    strip_prefix = "abseil-cpp-b9b925341f9e90f5e7aa0cf23f036c29c7e454eb",
    urls = ["https://github.com/abseil/abseil-cpp/archive/b9b925341f9e90f5e7aa0cf23f036c29c7e454eb.zip"],
)
