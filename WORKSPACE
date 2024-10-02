load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# http_archive(
#     name = "bazel_skylib",
#     sha256 = "f7be3474d42aae265405a592bb7da8e171919d74c16f082a5457840f06054728",
#     urls = [
#         "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/releases/download/1.2.1/bazel-skylib-1.2.1.tar.gz",
#         "https://github.com/bazelbuild/bazel-skylib/releases/download/1.2.1/bazel-skylib-1.2.1.tar.gz",
#     ],
# )
http_archive(
    name = "bazel_skylib",
    sha256 = "66ffd9315665bfaafc96b52278f57c7e2dd09f5ede279ea6d39b2be471e7e3aa",
    urls = ["https://github.com/bazelbuild/bazel-skylib/releases/download/1.4.2/bazel-skylib-1.4.2.tar.gz"],
)

http_archive(
    name = "com_github_libusb_hidapi",
    build_file = "@//external:hidapi.BUILD",
    sha256 = "68217a595ffc517e7b88e7bfedddaef0558ceb8a8937327ecc3de2016cdf8cfc",
    strip_prefix = "hidapi-hidapi-0.14.0",
    urls = ["https://github.com/libusb/hidapi/archive/refs/tags/hidapi-0.14.0.zip"],
)

http_archive(
    name = "com_google_absl",
    sha256 = "6c7b209e73667e351e78f96599ce6c395e427be5589b511a648840b64b9c3467",
    strip_prefix = "abseil-cpp-b1fb259ef793de57c2acefeeec07a6e3286ab9bc",
    urls = ["https://github.com/abseil/abseil-cpp/archive/b1fb259ef793de57c2acefeeec07a6e3286ab9bc.zip"],
)

http_archive(
    name = "com_github_etclabs_etcpal",
    build_file = "@//external:etcpal-BUILD.bazel",
    sha256 = "066b3b5ea47a3970ca189457235becc8a178fa02b78056187fb7d0c73da35c1f",
    strip_prefix = "EtcPal-0aa91907b93f7969e712a1af126e7af84cba3707",
    urls = ["https://github.com/ETCLabs/etcpal/archive/0aa91907b93f7969e712a1af126e7af84cba3707.zip"],
)

http_archive(
    name = "com_github_etclabs_sacn",
    build_file = "@//external:sacn-BUILD.bazel",
    sha256 = "4577129abdea3437b03ebbb4e34f4c5cfeb7085d6c9830bb9d9b1786047c6ce3",
    strip_prefix = "sACN-4d601e1952f0d66b379afce996a725d9f9371d35",
    urls = ["https://github.com/ETCLabs/sACN/archive/4d601e1952f0d66b379afce996a725d9f9371d35.zip"],
)

http_archive(
    name = "com_github_jupp0r_prometheus_cpp",
    sha256 = "159d013c81b564dfc628f23e6b4560c8ba1992b555e4258194436d8585500b50",
    strip_prefix = "prometheus-cpp-4b03769662cfdbfa2f31c21bb162cf495aa2a607",
    urls = ["https://github.com/jupp0r/prometheus-cpp/archive/4b03769662cfdbfa2f31c21bb162cf495aa2a607.zip"],
)

load("@com_github_jupp0r_prometheus_cpp//bazel:repositories.bzl", "prometheus_cpp_repositories")

prometheus_cpp_repositories()

http_archive(
    name = "rules_wix",
    sha256 = "33a8487079f494125cc5ae8e6d4df068870ad680dd8cf1b225492c9954761f9b",
    strip_prefix = "rules_wix-07d3331f38ff3152384cc8c6c5e844e9d2dd50fe",
    url = "https://github.com/kleinpa/rules_wix/archive/07d3331f38ff3152384cc8c6c5e844e9d2dd50fe.zip",
)

load("@rules_wix//:deps.bzl", "add_wix_deps")

add_wix_deps()

http_archive(
    name = "org_kernel_util_linux",  # for libuuid
    build_file = "@//external:util-linux-BUILD.bazel",
    sha256 = "",
    strip_prefix = "util-linux-2.39",
    urls = ["https://mirrors.edge.kernel.org/pub/linux/utils/util-linux/v2.39/util-linux-2.39.tar.gz"],
)
