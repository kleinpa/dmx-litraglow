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

http_archive(
    name = "com_github_etclabs_etcpal",
    build_file = "@//external:etcpal-BUILD.bazel",
    sha256 = "e94d0f492a142ee998acf64e84c1cd17cefb962c0ac389a8083232ad13f2c77b",
    strip_prefix = "EtcPal-eb5f906aafdbc6a4cd3e00670bbd2824e34705cd",
    urls = ["https://github.com/ETCLabs/etcpal/archive/eb5f906aafdbc6a4cd3e00670bbd2824e34705cd.zip"],
)

http_archive(
    name = "com_github_etclabs_sacn",
    build_file = "@//external:sacn-BUILD.bazel",
    sha256 = "baee0ec371bd435f85e5717f8a6762270202872e77ffc788b5692c3110d53196",
    strip_prefix = "sACN-af246e04106f2342937566097322ac1ebb86fae0",
    urls = ["https://github.com/ETCLabs/sACN/archive/af246e04106f2342937566097322ac1ebb86fae0.zip"],
)

http_archive(
    name = "com_github_jupp0r_prometheus_cpp",
    sha256 = "4b4241542a0ee807a2e351600c342b915ea02fac5ccb2235d4794812f46b50b6",
    strip_prefix = "prometheus-cpp-722fbcf18695976b23f81d1e852b8fdb4690cfd9",
    urls = ["https://github.com/jupp0r/prometheus-cpp/archive/722fbcf18695976b23f81d1e852b8fdb4690cfd9.zip"],
)

load("@com_github_jupp0r_prometheus_cpp//bazel:repositories.bzl", "prometheus_cpp_repositories")

prometheus_cpp_repositories()
