// This program is a proof-of-concept for controlling Logitech's Litra Glow
// using hidapi on Linux and Windows. All matching devices will be configured
// according to the provided flag values.

#include <iostream>
#include <stdexcept>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "device.h"


ABSL_FLAG(bool, power, true, "on/off");
ABSL_FLAG(int, brightness, 245, "brightness 20 - 250");
ABSL_FLAG(int, color, 6500, "color temperature 2700 - 6500");

int main(int argc, char *argv[]) {
  absl::ParseCommandLine(argc, argv);

  try {
    HidDeviceManager device_manager;

    device_manager.for_each([](const LitraGlowDevice &handle) {
      handle.send_power(absl::GetFlag(FLAGS_power));
      handle.send_color(absl::GetFlag(FLAGS_color));
      handle.send_brightness(absl::GetFlag(FLAGS_brightness));
    });
  } catch (const std::exception &err) {
    std::cerr << "error: " << err.what() << std::endl;
    return 1;
  }
  return 0;
}
