/******************************************************************************************\
* *
*   main.cpp *
* *
*       Main function for OpenAuraSDK GUI project *
* *
\******************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <thread>
#include <vector>

#include "LogManager.h"
#include "NetworkClient.h"
#include "ProfileManager.h"
#include "RGBController.h"
// #include "ResourceManager.h"
//  #include "i2c_smbus.h"

using namespace std::chrono_literals;

/*-------------------------------------------------------------*\
| Command line functionality and return flags                   |
\*-------------------------------------------------------------*/
extern unsigned int cli_pre_detection(int argc, char *argv[]);
extern unsigned int cli_post_detection(int argc, char *argv[]);

enum {
  RET_FLAG_PRINT_HELP = 1,
  RET_FLAG_START_GUI = 2,
  RET_FLAG_I2C_TOOLS = 4,
  RET_FLAG_START_MINIMIZED = 8,
  RET_FLAG_NO_DETECT = 16,
  RET_FLAG_CLI_POST_DETECTION = 32,
  RET_FLAG_START_SERVER = 64,
  RET_FLAG_NO_AUTO_CONNECT = 128,
};

/* Attempts an SDK connection to the local server.  Returns true if success */
bool AttemptLocalConnection() {
  bool success = false;

  NetworkClient *client =
      new NetworkClient(ResourceManager::get()->GetRGBControllers());

  std::string titleString = "OpenRGB ";
  titleString.append(VERSION_STRING);

  client->SetName(titleString.c_str());
  client->StartClient();

  for (int timeout = 0; timeout < 10; timeout++) {
    if (client->GetConnected()) {
      break;
    }
    std::this_thread::sleep_for(5ms);
  }

  if (!client->GetConnected()) {
    client->StopClient();

    delete client;

    client = NULL;
  } else {
    ResourceManager::get()->RegisterNetworkClient(client);

    success = true;

    // Wait up to 5 seconds for the client connection to
    // retrieve all controllers
    for (int timeout = 0; timeout < 1000; timeout++) {
      if (client->GetOnline()) {
        break;
      }
      std::this_thread::sleep_for(5ms);
    }
  }

  return success;
}

int main(int argc, char *argv[]) {
  // Process command line arguments before detection
  unsigned int ret_flags = cli_pre_detection(argc, argv);

  // Perform local connection and/or hardware detection if not
  // disabled from CLI

  if (!(ret_flags & RET_FLAG_NO_AUTO_CONNECT)) {
    printf("Attempting to connect to local OpenRGB server.\r\n");

    if (!AttemptLocalConnection()) {
      printf("Local OpenRGB server unavailable.\r\n");
    } else {
      printf("Local OpenRGB server connected, running in client mode\r\n");

      ResourceManager::get()->DisableDetection();
    }
  }
}
