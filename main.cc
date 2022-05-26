#include <prometheus/counter.h>
#include <prometheus/exposer.h>
#include <prometheus/registry.h>

#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/marshalling.h"
#include "absl/flags/parse.h"
#include "controller.h"

ABSL_FLAG(int, dmx_universe, 1, "DMX universe");
ABSL_FLAG(int, dmx_address_start, 1, "First DMX address to use");
ABSL_FLAG(std::string, metrics_address, "[::1]:20309",
          "Metrics HTTP endpoint bind address");

int main(int argc, char *argv[]) {
  absl::ParseCommandLine(argc, argv);

  prometheus::Exposer exposer{absl::GetFlag(FLAGS_metrics_address)};
  auto metrics_registry = std::make_shared<prometheus::Registry>();
  exposer.RegisterCollectable(metrics_registry);

  std::atomic stop(false);
  return dmxlitraglow::run(stop, absl::GetFlag(FLAGS_dmx_universe),
                           absl::GetFlag(FLAGS_dmx_address_start),
                           *metrics_registry);
}
