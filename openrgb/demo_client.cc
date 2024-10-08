

#include <chrono>
#include <string>
#include <thread>

#include "absl/flags/flag.h"
#include "absl/flags/marshalling.h"
#include "absl/flags/parse.h"
#include "absl/log/globals.h"
#include "absl/log/initialize.h"
#include "absl/log/log.h"
#include "openrgb/rgb_client_manager.h"

ABSL_FLAG(std::string, openrgb_host, "localhost", "OpenRGB server host");
ABSL_FLAG(int, openrgb_port, 6742, "OpenRGB server port");
ABSL_FLAG(std::string, openrgb_client_name, "demo_client",
          "name to report to OpenRGB server");

ABSL_FLAG(int, color, 0x0000FF, "color to set on devices");

int main(int argc, char *argv[]) {
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();
  LOG(INFO) << "starting";

  // Start a timer to measure initial connection speed.
  auto start = std::chrono::high_resolution_clock::now();

  RGBClientManager rcm(absl::GetFlag(FLAGS_openrgb_host),
                       absl::GetFlag(FLAGS_openrgb_port),
                       absl::GetFlag(FLAGS_openrgb_client_name));
  rcm.WaitForOnline();

  auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::high_resolution_clock::now() - start);
  LOG(INFO) << "OpenRGB connected in " << diff.count() << " ms";

  rcm.UpdateAll(RGBColor(absl::GetFlag(FLAGS_color)));

  LOG(INFO) << "sent update";
}
