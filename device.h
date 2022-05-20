#ifndef DEVICE_H_
#define DEVICE_H_

#include <hidapi.h>

#include <array>
#include <iostream>

class LitraGlowDevice {
 public:
  LitraGlowDevice(hid_device* handle) : handle_(handle) {}
  ~LitraGlowDevice() { hid_close(handle_); }

  void send_power(const bool power) const;
  void send_brightness(const uint8_t brightness) const;
  void send_color(const uint16_t color) const;

  // LitraGlowDevice(const LitraGlowDevice&) = delete; // TODO: uncomment
  void operator=(const LitraGlowDevice& x) = delete;

 private:
  void send(const std::array<uint8_t, 20>& data) const;

  hid_device* handle_;
};

#endif  // DEVICE_H_
