load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "com_github_libusb_hidapi",
    build_file = "@//external:hidapi.BUILD",
    sha256 = "68217a595ffc517e7b88e7bfedddaef0558ceb8a8937327ecc3de2016cdf8cfc",
    strip_prefix = "hidapi-hidapi-0.14.0",
    urls = ["https://github.com/libusb/hidapi/archive/refs/tags/hidapi-0.14.0.zip"],
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
    integrity = "sha256-sfWXrRcqLuF7Cnrkvnq34bGm+TlN29PY7JCuTtczNXk=",
    strip_prefix = "util-linux-2.39",
    urls = ["https://mirrors.edge.kernel.org/pub/linux/utils/util-linux/v2.39/util-linux-2.39.tar.gz"],
)
