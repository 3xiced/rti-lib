#include <Windows.h>
#include <rti_export.h>

#include <iostream>

namespace rti {
RTI_EXPORT BOOL ExecuteCommand(std::wstring& appName, std::wstring& cmdArgs);
}
