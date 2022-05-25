#ifndef DEVICE_H_
#define DEVICE_H_

#include <hidapi.h>

#include <array>
#include <functional>
#include <mutex>
#include <vector>

namespace dmxlitraglow {

class LitraGlowDevice {
 public:
  LitraGlowDevice(hid_device* handle) : handle_(handle) {}
  ~LitraGlowDevice() { hid_close(handle_); }

  void send_power(const bool power) const;
  void send_brightness(const uint8_t brightness) const;
  void send_color(const uint16_t color) const;

 private:
  void send(const std::array<uint8_t, 20>& data) const;

  hid_device* handle_;
};

// This class manages the lifecycle of the hidapi library.
class HidDeviceManager {
 public:
  HidDeviceManager();
  ~HidDeviceManager();

  // Call the supplied callback once for each available controllable device.
  const void for_each(std::function<void(const LitraGlowDevice&)> fn);

  // Enumerate devices connected to the system and find controllable devices.
  void scan();

  HidDeviceManager(const HidDeviceManager&) = delete;
  void operator=(const HidDeviceManager& x) = delete;

 private:
  std::vector<LitraGlowDevice> handles_;
  std::mutex handles_mu_;
};

}  // namespace dmxlitraglow
#endif  // DEVICE_H_
