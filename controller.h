#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <prometheus/counter.h>
#include <prometheus/exposer.h>
#include <prometheus/registry.h>

#include <atomic>


namespace dmxlitraglow {

int run(std::atomic<bool> &cancelled, const int dmx_universe,
        const int dmx_address_start, prometheus::Registry &registry);

}  // namespace dmxlitraglow
#endif  // CONTROLLER_H_
