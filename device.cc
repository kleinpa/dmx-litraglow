
#include "device.h"

#include <hidapi.h>

#include <iostream>
#include <stdexcept>

namespace dmxlitraglow {

constexpr uint16_t litraglow_vid = 0x046D;
constexpr uint16_t litraglow_pid = 0xC900;
constexpr uint16_t litraglow_usagepage = 0xff43;

void LitraGlowDevice::send(const std::array<uint8_t, 20>& data) const {
  if (hid_write(handle_, data.data(), data.size()) != (int)data.size()) {
    throw std::runtime_error("unable to send data");
  }
}

void LitraGlowDevice::send_power(const bool power) const {
  const uint8_t x = power ? 0x01 : 0x00;
  send(std::array<uint8_t, 20>{0x11, 0xff, 0x04, 0x1c, x});
}

void LitraGlowDevice::send_brightness(const uint8_t brightness) const {
  if (brightness < 20 || brightness > 250) {
    throw std::out_of_range("brightness out of range 20 - 250");
  }
  const uint8_t x0 = 0, x1 = brightness;
  send(std::array<uint8_t, 20>{0x11, 0xff, 0x04, 0x4c, x0, x1});
}

void LitraGlowDevice::send_color(const uint16_t color) const {
  if (color < 2700 || color > 6500) {
    throw std::out_of_range("color out of range 2700 - 6500");
  }
  const uint8_t x0 = (color >> 8) & 0xff, x1 = color & 0xff;
  send(std::array<uint8_t, 20>{0x11, 0xff, 0x04, 0x9c, x0, x1});
}

HidDeviceManager::HidDeviceManager() {
  if (hid_init() != 0) {
    throw std::runtime_error("unable to hid_init");
  }
  scan();
}

HidDeviceManager::~HidDeviceManager() {
  if (hid_exit() != 0) {
    std::cerr << "unable to hid_exit";
  }
}
const void HidDeviceManager::for_each(
    std::function<void(const LitraGlowDevice&)> fn) {
  std::unique_lock<std::mutex> lock(handles_mu_);
  for (const auto& handle : handles_) {
    fn(handle);
  }
}

void HidDeviceManager::scan() {
  std::unique_lock<std::mutex> lock(handles_mu_);
  handles_.clear();
  hid_device_info* devs = hid_enumerate(litraglow_vid, litraglow_pid);
  for (hid_device_info* dev = devs; dev; dev = dev->next) {
    if (dev->usage_page == litraglow_usagepage) {
      if (dev->path[0]) {
        hid_device* handle = hid_open_path(dev->path);
        if (handle != nullptr) {
          handles_.emplace_back(hid_open_path(dev->path));
        }
      }
    }
  }
  hid_free_enumeration(devs);
}

}  // namespace dmxlitraglow
