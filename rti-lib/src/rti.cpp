#include "rti.h"

#include <iostream>

#include "utils.h"

namespace rti {
BOOL ExecuteCommand(std::wstring& appName, std::wstring& cmdArgs) {
    BOOL success = FALSE;

    if (!rti::impl::ImpersonateAsSystem()) {
        return FALSE;
    }

    DWORD dwPID = rti::impl::StartTIServiceAndGetPID();
    if (dwPID == 0) {
        return FALSE;
    }

    HANDLE hToken = rti::impl::CreateAccessTokenFromPID(dwPID);
    if (hToken != INVALID_HANDLE_VALUE) {
        STARTUPINFO si;
        PROCESS_INFORMATION pi;

        GetStartupInfo(&si);
        success = CreateProcessWithTokenW(hToken, LOGON_WITH_PROFILE, (LPWSTR)appName.c_str(),
                                          (LPWSTR)cmdArgs.c_str(), CREATE_UNICODE_ENVIRONMENT,
                                          NULL, NULL, &si, &pi);
        if (!success) {
            std::cout << "CreateProcessWithTokenW: "
                      << std::system_category().message(GetLastError()) << std::endl;
        }
    }
    CloseHandle(hToken);

    return success;
}
}  // namespace rti