#include <corecrt_math.h>
#include <prometheus/counter.h>
#include <prometheus/exposer.h>
#include <prometheus/registry.h>
#include <stdint.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <stdexcept>

#include "absl/flags/flag.h"
#include "absl/flags/marshalling.h"
#include "absl/flags/parse.h"
#include "device.h"
#include "dmx_server.h"

ABSL_FLAG(int, dmx_universe, 1, "DMX universe");
ABSL_FLAG(int, dmx_address_start, 1, "First DMX address to use");

constexpr uint8_t kControlModeDisabled = 0;
constexpr uint8_t kControlModeWhite = 1;
constexpr uint8_t kControlModeColor = 2;

constexpr int kRefreshDevicesPeriod = 5000;  // ms

struct LightControl {
  float brightness;
  float temperature;
  static LightControl from_dmx(
      const std::array<uint8_t, DMX_ADDRESS_COUNT> &dmx, int offset) {
    if (dmx[offset + 0] == kControlModeWhite) {
      return LightControl{dmx[offset + 1] / (float)UINT8_MAX,
                          dmx[offset + 2] / (float)UINT8_MAX};
    } else {
      return LightControl{0, 0};
    }
  }
  bool operator==(const LightControl &other) const {
    return brightness == other.brightness && temperature == other.temperature;
  }
};

int main(int argc, char *argv[]) {
  absl::ParseCommandLine(argc, argv);

  // Configure metrics
  prometheus::Exposer exposer{"0.0.0.0:5469"};
  auto registry = std::make_shared<prometheus::Registry>();
  auto &sacn_dmx_data_packet_family = prometheus::BuildCounter()
                                          .Name("sacn_dmx_data_packet")
                                          .Help("Number of observed packets")
                                          .Register(*registry);
  auto &sacn_dmx_data_packet_counter = sacn_dmx_data_packet_family.Add({});
  exposer.RegisterCollectable(registry);

  try {
    HidDeviceManager device_manager;

    LightControl last_value;
    DmxServer server(
        absl::GetFlag(FLAGS_dmx_universe),
        [&device_manager, &last_value](const DmxServer::DmxArray &dmx_data) {
          // calculate the current output and stop if it is unchanged
          auto value = LightControl::from_dmx(
              dmx_data, absl::GetFlag(FLAGS_dmx_address_start));
          if (value == last_value) {
            return;
          }
          last_value = value;

          uint8_t brightness = value.brightness * UINT8_MAX;
          uint16_t temperature = 2700 + value.temperature * (6500 - 2700);
          device_manager.for_each(
              [brightness, temperature](const LitraGlowDevice &handle) {
                try {
                  if (brightness >= 20) {
                    handle.send_color(
                        std::clamp<uint16_t>(temperature, 2700, 6500));
                    handle.send_power(true);
                    handle.send_brightness(
                        std::clamp<uint8_t>(brightness, 20, 250));
                  } else {
                    handle.send_power(false);
                  }
                } catch (const std::exception &err) {
                  std::cerr << "error: " << err.what() << std::endl;
                }
              });
        });

    // check for new usb devices every second
    const auto period = std::chrono::milliseconds(kRefreshDevicesPeriod);
    auto next = std::chrono::system_clock::now();
    while (true) {
      std::this_thread::sleep_until(next += period);
      device_manager.scan();
    }

  } catch (const std::exception &err) {
    std::cerr << "error: " << err.what() << std::endl;
    return 1;
  }
  return 0;
}
