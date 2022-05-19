load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("@bazel_skylib//rules:write_file.bzl", "write_file")

alias(
    name = "libusb",
    actual =
        select({
            "@bazel_tools//src/conditions:windows": ":libusb_windows",
            "//conditions:default": "libusb_linux",
        }),
    visibility = ["//visibility:public"],
)

write_file(
    name = "linux_config",
    out = "linux_config/config.h",
    content = [
        "#define DEFAULT_VISIBILITY __attribute__ ((visibility (\"default\")))",
        "#define ENABLE_LOGGING 1",
        "#define HAVE_CLOCK_GETTIME 1",
        "#define HAVE_DECL_EFD_CLOEXEC 1",
        "#define HAVE_DECL_EFD_NONBLOCK 1",
        "#define HAVE_DECL_TFD_CLOEXEC 1",
        "#define HAVE_DECL_TFD_NONBLOCK 1",
        "#define HAVE_DLFCN_H 1",
        "#define HAVE_EVENTFD 1",
        "#define HAVE_INTTYPES_H 1",
        "#define HAVE_LIBUDEV 1",
        "#define HAVE_MEMORY_H 1",
        "#define HAVE_NFDS_T 1",
        "#define HAVE_PIPE2 1",
        "#define HAVE_PTHREAD_CONDATTR_SETCLOCK 1",
        "#define HAVE_PTHREAD_SETNAME_NP 1",
        "#define HAVE_STDINT_H 1",
        "#define HAVE_STDLIB_H 1",
        "#define HAVE_STRINGS_H 1",
        "#define HAVE_STRING_H 1",
        "#define HAVE_SYS_STAT_H 1",
        "#define HAVE_SYS_TIME_H 1",
        "#define HAVE_SYS_TYPES_H 1",
        "#define HAVE_TIMERFD 1",
        "#define HAVE_UNISTD_H 1",
        "#define PLATFORM_POSIX 1",
        "#define PRINTF_FORMAT(a, b) __attribute__ ((__format__ (__printf__, a, b)))",
        "#define STDC_HEADERS 1",
        "#define _GNU_SOURCE 1",
    ],
)

cc_library(
    name = "libusb_linux",
    srcs = [
        "libusb/core.c",
        "libusb/descriptor.c",
        "libusb/hotplug.c",
        "libusb/io.c",
        "libusb/libusb.h",
        "libusb/libusbi.h",
        "libusb/os/events_posix.c",
        "libusb/os/events_posix.h",
        "libusb/os/linux_netlink.c",
        "libusb/os/linux_udev.c",
        "libusb/os/linux_usbfs.c",
        "libusb/os/linux_usbfs.h",
        "libusb/os/threads_posix.c",
        "libusb/os/threads_posix.h",
        "libusb/strerror.c",
        "libusb/sync.c",
        "libusb/version.h",
        "libusb/version_nano.h",
        ":linux_config",
    ],
    hdrs = ["libusb/libusb.h"],
    copts = ["-Ilinux_config"],
    includes = ["libusb"],
    linkopts = [
        "-lpthread",
        "-ludev",
    ],
    deps = [":getopt"],
)

cc_library(
    name = "libusb_windows",
    srcs = [
        "libusb/core.c",
        "libusb/descriptor.c",
        "libusb/hotplug.c",
        "libusb/io.c",
        "libusb/libusb.h",
        "libusb/libusbi.h",
        "libusb/os/events_windows.c",
        "libusb/os/events_windows.h",
        "libusb/os/threads_windows.c",
        "libusb/os/threads_windows.h",
        "libusb/os/windows_common.c",
        "libusb/os/windows_common.h",
        "libusb/os/windows_usbdk.c",
        "libusb/os/windows_usbdk.h",
        "libusb/os/windows_winusb.c",
        "libusb/os/windows_winusb.h",
        "libusb/strerror.c",
        "libusb/sync.c",
        "libusb/version.h",
        "libusb/version_nano.h",
        "msvc/config.h",
    ],
    hdrs = ["libusb/libusb.h"],
    copts = [
        "/I msvc",
    ],
    includes = ["libusb"],
    deps = [":getopt"],
)

cc_library(
    name = "getopt",
    srcs = [
        "msvc/getopt/getopt.c",
        "msvc/getopt/getopt1.c",
    ],
    hdrs = ["msvc/getopt/getopt.h"],
    defines = ["HAVE_STRING_H"],
    includes = [
        "msvc/getopt",
    ],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "dpfp",
    srcs = ["examples/dpfp.c"],
    visibility = ["//visibility:public"],
    deps = [":libusb"],
)

cc_library(
    name = "ezusb",
    srcs = ["examples/ezusb.c"],
    hdrs = ["examples/ezusb.h"],
    includes = ["examples"],
    visibility = ["//visibility:public"],
    deps = [":libusb"],
)

cc_binary(
    name = "fxload",
    srcs = [
        "examples/fxload.c",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":ezusb",
        ":libusb",
    ],
)

cc_binary(
    name = "hotplugtest",
    srcs = ["examples/hotplugtest.c"],
    visibility = ["//visibility:public"],
    deps = [":libusb"],
)

cc_binary(
    name = "listdevs",
    srcs = ["examples/listdevs.c"],
    visibility = ["//visibility:public"],
    deps = [":libusb"],
)

cc_binary(
    name = "sam3u_benchmark",
    srcs = ["examples/sam3u_benchmark.c"],
    visibility = ["//visibility:public"],
    deps = [":libusb"],
)

cc_binary(
    name = "testlibusb",
    srcs = ["examples/testlibusb.c"],
    visibility = ["//visibility:public"],
    deps = [":libusb"],
)

cc_binary(
    name = "xusb",
    srcs = ["examples/xusb.c"],
    visibility = ["//visibility:public"],
    deps = [":libusb"],
)

cc_binary(
    name = "stress",
    srcs = [
        "tests/libusb_testlib.h",
        "tests/stress.c",
        "tests/testlib.c",
        ":windows_config",
    ],
    includes = [
        "libusb",
    ],
    visibility = ["//visibility:public"],
    deps = [":libusb"],
)
