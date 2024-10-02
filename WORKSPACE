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
    sha256 = "6f03495ec2fdc582b2e858e04a268caf2415c12633f7634a3b99c1698950f05f",
    strip_prefix = "abseil-cpp-03b8d6ea3dc6a0b8c6bcf42503c2053754dab2e4",
    urls = ["https://github.com/abseil/abseil-cpp/archive/03b8d6ea3dc6a0b8c6bcf42503c2053754dab2e4.zip"],
)

http_archive(
    name = "com_github_etclabs_etcpal",
    build_file = "@//external:etcpal-BUILD.bazel",
    sha256 = "8bedb83b07d910396eb4f2b7a225cd4f7bfb50a32ae98348f6c95d3dad378b57",
    strip_prefix = "EtcPal-b0bd0b0d0294e98ef135b501d18cf82b4f8fa6f4",
    urls = ["https://github.com/ETCLabs/etcpal/archive/b0bd0b0d0294e98ef135b501d18cf82b4f8fa6f4.zip"],
)

http_archive(
    name = "com_github_etclabs_sacn",
    build_file = "@//external:sacn-BUILD.bazel",
    sha256 = "5493088f402c3dbb85bd166df372e201f514f5afdd8da7b10b660b7a96cdf358",
    strip_prefix = "sACN-4508d4b0ef70d31b438316be02cfb016401e848b",
    urls = ["https://github.com/ETCLabs/sACN/archive/4508d4b0ef70d31b438316be02cfb016401e848b.zip"],
)

http_archive(
    name = "com_github_jupp0r_prometheus_cpp",
    sha256 = "b8494562f988af35ec12561b6eb352d0cbed7e3f7d68a69eda786c6610afc46e",
    strip_prefix = "prometheus-cpp-6492e820cdff7e7345d46d82b43735aaea542098",
    urls = ["https://github.com/jupp0r/prometheus-cpp/archive/6492e820cdff7e7345d46d82b43735aaea542098.zip"],
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
