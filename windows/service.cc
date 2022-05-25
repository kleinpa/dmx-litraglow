#include <Windows.h>
#include <tchar.h>

#include <atomic>
#include <cstdio>
#include <string>
#include <thread>

#include "absl/flags/flag.h"
#include "absl/flags/marshalling.h"
#include "absl/flags/parse.h"
#include "controller.h"

ABSL_FLAG(int, dmx_universe, 1, "DMX universe");
ABSL_FLAG(int, dmx_address_start, 1, "First DMX address to use");

SERVICE_STATUS_HANDLE status_handle = nullptr;

// Used to communicate a stop request to the program. Only service control
// code should modify this value.
std::atomic<bool> canceled = false;

#define SERVICE_NAME _T("dmx-litraglow")

BOOL report_service_status(const SERVICE_STATUS_HANDLE &status_handle,
                           const DWORD state, const DWORD error_code) {
  SERVICE_STATUS status = {0};
  status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
  status.dwCurrentState = state;
  status.dwWin32ExitCode = error_code;

  switch (state) {
    case SERVICE_START_PENDING:
    case SERVICE_RUNNING:
      status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
      break;
    default:
      status.dwControlsAccepted = 0;
      break;
  }

  return SetServiceStatus(status_handle, &status);
}

VOID WINAPI service_control_handler(const DWORD code) {
  switch (code) {
    case SERVICE_CONTROL_STOP:
      if (!canceled) {
        canceled = true;
        report_service_status(status_handle, SERVICE_STOP_PENDING, NO_ERROR);
      }
      break;
  }
}

VOID WINAPI service_main(DWORD argc, LPTSTR *argv) {
  absl::ParseCommandLine(argc, argv);

  status_handle =
      RegisterServiceCtrlHandler(SERVICE_NAME, service_control_handler);
  if (status_handle == nullptr) {
    return;
  }

  report_service_status(status_handle, SERVICE_RUNNING, NO_ERROR);

  dmxlitraglow::run(canceled, absl::GetFlag(FLAGS_dmx_universe),
                    absl::GetFlag(FLAGS_dmx_address_start));

  report_service_status(status_handle, SERVICE_STOPPED, NO_ERROR);
}

int _tmain(int argc, TCHAR *argv[]) {
  const SERVICE_TABLE_ENTRY table[] = {
      {SERVICE_NAME, (LPSERVICE_MAIN_FUNCTION)service_main},
      {nullptr, nullptr}};

  if (!StartServiceCtrlDispatcher(table)) {
    return GetLastError();
  }
  return 0;
}
