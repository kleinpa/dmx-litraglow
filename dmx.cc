#include <hidapi.h>
#include <prometheus/counter.h>
#include <prometheus/exposer.h>
#include <prometheus/registry.h>
#include <stdint.h>

#include <array>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "absl/flags/flag.h"
#include "absl/flags/marshalling.h"
#include "absl/flags/parse.h"
#include "device.h"
#include "etcpal/cpp/inet.h"
#include "sacn/common.h"
#include "sacn/cpp/common.h"
#include "sacn/cpp/merge_receiver.h"

ABSL_FLAG(int, dmx_universe, 1, "DMX universe");
ABSL_FLAG(int, dmx_address_start, 1, "First DMX address to use");
ABSL_FLAG(int, dmx_address_end, DMX_ADDRESS_COUNT, "Last DMX address to use");

const uint16_t litraglow_vid = 0x046D;
const uint16_t litraglow_pid = 0xC900;
const uint16_t litraglow_usagepage = 0xff43;

std::vector<LitraGlowDevice> hid_open_all(const uint16_t vid,
                                          const uint16_t pid,
                                          const uint16_t usage_page) {
  hid_device_info *devs = hid_enumerate(vid, pid);
  std::vector<LitraGlowDevice> handles;
  for (hid_device_info *dev = devs; dev; dev = dev->next) {
    if ((!usage_page || dev->usage_page == usage_page)) {
      if (dev->path[0]) {
        handles.emplace_back(hid_open_path(dev->path));
      }
    }
  }
  hid_free_enumeration(devs);
  return std::move(handles);
}

// CallbackNotifyHandler wraps a std::function and calls it whenever new merged
// DMX values are available.
class CallbackNotifyHandler : public sacn::MergeReceiver::NotifyHandler {
 public:
  using CallbackFn = std::function<void(const SacnRecvMergedData &)>;
  using Handle = sacn::MergeReceiver::Handle;

  CallbackNotifyHandler(CallbackFn cb) : cb_(cb) {}

  void HandleMergedData(Handle handle,
                        const SacnRecvMergedData &merged_data) override {
    ++data_count_;
    if (cb_) {
      cb_(merged_data);
    }
  }
  void HandleNonDmxData(Handle receiver_handle,
                        const etcpal::SockAddr &source_addr,
                        const SacnRemoteSource &source_info,
                        const SacnRecvUniverseData &universe_data) override {
    ++non_dmx_data_count_;
  };

  void HandleSourceLimitExceeded(Handle handle, uint16_t universe) override{};

 private:
  int data_count_ = 0;
  int non_dmx_data_count_ = 0;
  const CallbackFn cb_;
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
    if (hid_init() != 0) {
      throw std::runtime_error("unable to hid_init");
    }

    const std::vector<LitraGlowDevice> handles(
        hid_open_all(litraglow_vid, litraglow_pid, litraglow_usagepage));
    if (handles.size() == 0) {
      throw std::runtime_error("no devices found");
    }

    // Prepare sACN callback and DMX buffer
    std::array<uint8_t, DMX_ADDRESS_COUNT> dmx_data = {};
    std::mutex dmx_data_mutex;
    CallbackNotifyHandler sacn_handler(
        [&sacn_dmx_data_packet_counter, &dmx_data, &dmx_data_mutex,
         &handles](const SacnRecvMergedData &data) {
          sacn_dmx_data_packet_counter.Increment();
          std::cerr << "got sacn data" << std::endl;
          {
            std::lock_guard<std::mutex> lock(dmx_data_mutex);
            for (int i = 0; i < data.slot_range.address_count; i++) {
              dmx_data[data.slot_range.start_address + i] = data.slots[i];
            }
          }

          for (const auto &handle : handles) {
            try {
              if (dmx_data[1] >= 20) {
                handle.send_power(true);
                handle.send_brightness(dmx_data[1]);
              } else {
                handle.send_brightness(20);
                handle.send_power(false);
              }
            } catch (const std::exception &err) {
              std::cerr << "error: " << err.what() << std::endl;
            }
          }
        });

    // Start sACN receiver
    sacn::Init();
    sacn::MergeReceiver::Settings sacn_config(
        absl::GetFlag(FLAGS_dmx_universe));
    sacn::MergeReceiver merge_receiver;

    std::cerr << "starting sACN handler" << std::endl;
    merge_receiver.Startup(sacn_config, sacn_handler);

    auto next = std::chrono::system_clock::now();
    auto frame_rate = 1;  // 1-44hz?
    auto frame_time = std::chrono::milliseconds(1000) / frame_rate;

    while (true) {
      std::this_thread::sleep_until(next += frame_time);
    }

    std::cerr << "stopping" << std::endl;
    merge_receiver.Shutdown();
    sacn::Deinit();

    // TODO: let devices go out of scope first
    if (hid_exit() != 0) {
      throw std::runtime_error("unable to hid_exit");
    }
  } catch (const std::exception &err) {
    std::cerr << "error: " << err.what() << std::endl;
    return 1;
  }
  return 0;
}
