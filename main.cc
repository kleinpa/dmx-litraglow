#include "absl/flags/flag.h"
#include "absl/flags/marshalling.h"
#include "absl/flags/parse.h"
#include "controller.h"

ABSL_FLAG(int, dmx_universe, 1, "DMX universe");
ABSL_FLAG(int, dmx_address_start, 1, "First DMX address to use");

int main(int argc, char *argv[]) {
  absl::ParseCommandLine(argc, argv);
  std::atomic stop(false);
  return dmxlitraglow::run(stop, absl::GetFlag(FLAGS_dmx_universe),
                           absl::GetFlag(FLAGS_dmx_address_start));
}
