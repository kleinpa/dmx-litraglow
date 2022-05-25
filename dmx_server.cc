#include "dmx_server.h"

#include <iostream>

namespace dmxlitraglow {

DmxServer::DmxServer(int channel, DmxCallback callback)
    : sacn_handler_(callback) {
  sacn::Init();
  sacn::MergeReceiver::Settings sacn_config(channel);
  std::cerr << "starting sACN handler" << std::endl;
  merge_receiver_.Startup(sacn_config, sacn_handler_);
}

DmxServer::~DmxServer() {
  std::cerr << "stopping" << std::endl;
  merge_receiver_.Shutdown();
  sacn::Deinit();
}

void DmxServer::CallbackNotifyHandler::HandleMergedData(
    sacn::MergeReceiver::Handle handle, const SacnRecvMergedData &merged_data) {
  ++data_count_;
  std::lock_guard<std::mutex> lock(dmx_data_mutex_);
  for (int i = 0; i < merged_data.slot_range.address_count; i++) {
    dmx_data_[merged_data.slot_range.start_address + i] = merged_data.slots[i];
  }
  callback_(dmx_data_);
}

}  // namespace dmxlitraglow
