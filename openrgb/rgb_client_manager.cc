#include "openrgb/rgb_client_manager.h"

#include "RGBController.h"
#include "absl/log/log.h"

RGBClientManager::RGBClientManager(std::string host, int port, std::string name)
    : rgb_client_(rgb_controllers_) {
  rgb_client_.SetIP(host);
  rgb_client_.SetPort(port);
  rgb_client_.SetName(name);

  rgb_client_.RegisterClientInfoChangeCallback(UpdateOpenRGBClientListCallback,
                                               this);

  rgb_client_.StartClient();
  LOG(INFO) << "OpenRGB client started " << rgb_client_.GetIP() << ":"
            << rgb_client_.GetPort();
}

RGBClientManager::~RGBClientManager() {
  rgb_client_.StopClient();

  LOG(INFO) << "OpenRGB client stopped " << rgb_client_.GetIP() << ":"
            << rgb_client_.GetPort();
}

void RGBClientManager::UpdateAll(RGBColor color) {
  const std::lock_guard<std::mutex> lock(rgb_client_.ControllerListMutex);

  for (const auto &controller : rgb_client_.server_controllers) {
    if (controller->modes[controller->active_mode].name != "Direct") {
      continue;
    }
    for (auto &c : controller->colors) {
      c = color;
    }

    controller->DeviceUpdateLEDs();
  }
}

void RGBClientManager::ClientInfoChanged() {
  LOG(INFO) << "client info: "
            << (rgb_client_.GetConnected() ? "" : "disconnected, ")
            << (rgb_client_.GetOnline() ? "" : "offline, ")
            << rgb_client_.server_controllers.size() << " controllers";
}

// Wait for the server to be online
void RGBClientManager::WaitForOnline() {
  // TODO: use async primatives here?
  while (!rgb_client_.GetOnline()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}
