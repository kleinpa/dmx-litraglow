#include <prometheus/counter.h>
#include <prometheus/exposer.h>
#include <prometheus/registry.h>

#include <chrono>
#include <string>
#include <thread>

#include "absl/flags/flag.h"
#include "absl/flags/marshalling.h"
#include "absl/flags/parse.h"
#include "absl/log/globals.h"
#include "absl/log/initialize.h"
#include "absl/log/log.h"
#include "dmx_server.h"
#include "openrgb/rgb_client_manager.h"

ABSL_FLAG(int, dmx_universe, 1, "DMX universe");
ABSL_FLAG(int, dmx_address_start, 1, "First DMX address to use");

ABSL_FLAG(std::string, openrgb_host, "localhost", "OpenRGB server host");
ABSL_FLAG(int, openrgb_port, 6742, "OpenRGB server port");
ABSL_FLAG(std::string, openrgb_client_name, "demo_client",
          "name to report to OpenRGB server");

ABSL_FLAG(std::string, metrics_address, "[::1]:20308",
          "Metrics HTTP endpoint bind address");

RGBColor from_dmx(const dmxlitraglow::DmxServer::DmxArray &dmx_data,
                  int offset) {
  return 0xFF0000;
}

int main(int argc, char *argv[]) {
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();

  LOG(INFO) << "starting";

  prometheus::Exposer exposer{absl::GetFlag(FLAGS_metrics_address)};
  auto metrics_registry = std::make_shared<prometheus::Registry>();
  exposer.RegisterCollectable(metrics_registry);

  RGBClientManager rcm(absl::GetFlag(FLAGS_openrgb_host),
                       absl::GetFlag(FLAGS_openrgb_port),
                       absl::GetFlag(FLAGS_openrgb_client_name));
  rcm.WaitForOnline();

  dmxlitraglow::DmxServer server(
      absl::GetFlag(FLAGS_dmx_universe),
      [&rcm](const dmxlitraglow::DmxServer::DmxArray &dmx_data) {
        // calculate the current output and stop if it is unchanged
        auto value = from_dmx(dmx_data, absl::GetFlag(FLAGS_dmx_address_start));

        rcm.UpdateAll(value);
      },
      *metrics_registry);

  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}
