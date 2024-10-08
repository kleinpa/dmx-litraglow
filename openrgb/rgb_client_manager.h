
#ifndef OPENRGB_RGB_CLIENT_MANAGER_
#define OPENRGB_RGB_CLIENT_MANAGER_

#include "NetworkClient.h"

// RGBClientManager is a RAII-style manager for OpenRGB clients.
class RGBClientManager {
 public:
  RGBClientManager(std::string host, int port, std::string name);
  ~RGBClientManager();

  // Update all lights to the same color.
  void UpdateAll(RGBColor color);

  static void UpdateOpenRGBClientListCallback(void *this_ptr) {
    static_cast<RGBClientManager *>(this_ptr)->ClientInfoChanged();
  }

  void RGBClientManager::ClientInfoChanged();

  // Wait for the server to be online
  void RGBClientManager::WaitForOnline();

 private:
  NetworkClient rgb_client_;

  // This seems like NetworkClient internal data.
  std::vector<RGBController *> rgb_controllers_;
};

#endif  // OPENRGB_RGB_CLIENT_MANAGER_
