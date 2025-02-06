#include <windows.h>
#include <iostream>
#include <string>
#include "src/ComPort.h"

int main()
{
    LPCSTR port1 = "COM3";
    LPCSTR port2 = "COM6";

    ComPort com1(port1, true);
    ComPort com2(port2, false);

    HANDLE hSerialRead = com1.returnSerial();
    HANDLE hSerialWrite = com2.returnSerial();

    char buffer[256];
    DWORD bytesRead, bytesWritten, bytesReturn;
    std::string response;
    std::cout << "\033[?25l" << "Motor\n\n";

    while (true)
    {
        if (ReadFile(hSerialRead, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead > 0)
        {
            // response.assign(buffer, bytesRead);
            // std::cout << "Transmitted" << response << std::endl;
            WriteFile(hSerialWrite, buffer, bytesRead, &bytesWritten, NULL);
            if (ReadFile(hSerialWrite, buffer, sizeof(buffer), &bytesReturn, NULL) && bytesReturn > 0)
            {
                response.assign(buffer, bytesReturn);
                std::cout << "\r" << response << std::flush;
            }
        }
    }

    return 0;
}