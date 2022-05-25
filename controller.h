#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <atomic>

namespace dmxlitraglow {

int run(std::atomic<bool> &cancelled, const int dmx_universe,
        const int dmx_address_start);

}  // namespace dmxlitraglow
#endif  // CONTROLLER_H_
