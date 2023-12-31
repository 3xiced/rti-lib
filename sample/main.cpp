#include <iostream>
#include <string>

#include "rti.h"

int main() {
    rti::ExecuteCommand(std::wstring{L"C:\\Windows\\system32\\cmd.exe"}, std::wstring{L""});
    return 0;
}