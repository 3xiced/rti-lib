#pragma once

#include <windows.h>

namespace rti::impl {
HANDLE CreateAccessTokenFromPID(DWORD dwProcessId);
DWORD GetPIDFromProcessName(LPCWSTR lpProcessName);
BOOL ImpersonateAsSystem();
DWORD StartTIServiceAndGetPID();
}  // namespace rti::impl
