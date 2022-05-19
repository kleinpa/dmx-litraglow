#include <hidapi.h>
#include <stdint.h>

#include <array>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"

ABSL_FLAG(bool, power, true, "on/off");
ABSL_FLAG(int, brightness, 245, "brightness 20 - 250");
ABSL_FLAG(int, color, 6500, "color temperature 2700 - 6500");

const uint16_t litraglow_vid = 0x046D;
const uint16_t litraglow_pid = 0xC900;
const uint16_t litraglow_usagepage = 0xff43;

void send(hid_device *handle, const std::array<uint8_t, 20> &data) {
  if (hid_write(handle, data.data(), data.size()) != (int)data.size()) {
    throw std::runtime_error("unable to send data");
  }
}

void send_power(hid_device *handle, const bool power) {
  const uint8_t x = power ? 0x01 : 0x00;
  send(handle, std::array<uint8_t, 20>{0x11, 0xff, 0x04, 0x1c, x});
}

void send_brightness(hid_device *handle, const uint8_t brightness) {
  if (brightness < 20 || brightness > 250) {
    throw std::out_of_range("brightness out of range 20 - 250");
  }
  const uint8_t x0 = 0, x1 = brightness;
  send(handle, std::array<uint8_t, 20>{0x11, 0xff, 0x04, 0x4c, x0, x1});
}

void send_color(hid_device *handle, const uint16_t color) {
  if (color < 2700 || color > 6500) {
    throw std::out_of_range("color out of range 2700 - 6500");
  }
  const uint8_t x0 = (color >> 8) & 0xFF, x1 = color & 0xFF;
  send(handle, std::array<uint8_t, 20>{0x11, 0xff, 0x04, 0x9c, x0, x1});
}

std::vector<hid_device *> hid_open_usagepage(const uint16_t vid,
                                             const uint16_t pid,
                                             const uint16_t usage_page) {
  hid_device_info *devs = hid_enumerate(vid, pid);
  std::vector<hid_device *> handles;
  for (hid_device_info *dev = devs; dev; dev = dev->next) {
    if ((!usage_page || dev->usage_page == usage_page)) {
      if (dev->path[0]) {
        hid_device *handle = hid_open_path(dev->path);
        if (handle == NULL) {
          std::cerr << "error: unable to open device" << std::endl;
        } else {
          handles.push_back(handle);
        }
      }
    }
  }
  hid_free_enumeration(devs);
  return handles;
}

int main(int argc, char *argv[]) {
  absl::ParseCommandLine(argc, argv);

  try {
    if (hid_init() != 0) {
      throw std::runtime_error("unable to hid_init");
    }

    std::vector<hid_device *> handles =
        hid_open_usagepage(litraglow_vid, litraglow_pid, litraglow_usagepage);
    if (handles.size() == 0) {
      throw std::runtime_error("no devices found");
    }

    for (const auto &handle : handles) {
      send_power(handle, absl::GetFlag(FLAGS_power));
      send_color(handle, absl::GetFlag(FLAGS_color));
      send_brightness(handle, absl::GetFlag(FLAGS_brightness));
    }

    for (const auto &handle : handles) hid_close(handle);

    if (hid_exit() != 0) {
      throw std::runtime_error("unable to hid_exit");
    }

    std::cerr << "updated " << handles.size()
              << (handles.size() > 1 ? " devices" : " device") << std::endl;

  } catch (std::exception const &err) {
    std::cerr << "error: " << err.what() << std::endl;
    return 1;
  }
  return 0;
}
