#ifndef DMX_SERVER_H_
#define DMX_SERVER_H_

#include <prometheus/counter.h>
#include <prometheus/exposer.h>
#include <prometheus/registry.h>

#include <functional>
#include <mutex>

#include "etcpal/cpp/inet.h"
#include "sacn/common.h"
#include "sacn/cpp/common.h"
#include "sacn/cpp/merge_receiver.h"

namespace dmxlitraglow {

// DmxServer listens to incoming DMX data and calls the provided callback
// when that data changes. It also handles the lifecycle of the sacn library.
// TODO: handle metrics here
class DmxServer {
 public:
  using DmxArray = std::array<uint8_t, DMX_ADDRESS_COUNT>;
  using DmxCallback = std::function<void(const DmxArray &)>;

  DmxServer(int channel, DmxCallback callback, prometheus::Registry &registry);
  ~DmxServer();

  DmxServer(const DmxServer &) = delete;
  void operator=(const DmxServer &x) = delete;

 private:
  class CallbackNotifyHandler : public sacn::MergeReceiver::NotifyHandler {
   public:
    CallbackNotifyHandler(DmxCallback callback, prometheus::Registry &registry);
    void HandleMergedData(sacn::MergeReceiver::Handle handle,
                          const SacnRecvMergedData &merged_data) override;
    void HandleNonDmxData(sacn::MergeReceiver::Handle receiver_handle,
                          const etcpal::SockAddr &source_addr,
                          const SacnRemoteSource &source_info,
                          const SacnRecvUniverseData &universe_data) override {
      sacn_nondmx_data_packet_counter_.Increment();
    };

    void HandleSourceLimitExceeded(sacn::MergeReceiver::Handle handle,
                                   uint16_t universe) override {}

   private:
    const DmxCallback callback_;
    std::array<uint8_t, DMX_ADDRESS_COUNT> dmx_data_ = {};
    std::mutex dmx_data_mutex_;
    prometheus::Counter &sacn_dmx_data_packet_counter_;
    prometheus::Counter &sacn_nondmx_data_packet_counter_;
  };
  sacn::MergeReceiver merge_receiver_;
  CallbackNotifyHandler sacn_handler_;
};
}  // namespace dmxlitraglow
#endif  // DMX_SERVER_H_
