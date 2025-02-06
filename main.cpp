#include <windows.h>
#include <iostream>
#include <string>
#include "src/ComPort.h"

int main()
{
    HANDLE hSerialRead = CreateFile("COM3", GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    HANDLE hSerialWrite = CreateFile("COM6", GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);

    if (hSerialRead == INVALID_HANDLE_VALUE || hSerialWrite == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Port opening error" << std::endl;
        return 1;
    }

    ComPort com1(hSerialRead, true);
    ComPort com2(hSerialWrite, true);

    char buffer[1024];
    DWORD bytesRead, bytesWritten;
    std::string response;

    while (true)
    {
        if (ReadFile(hSerialRead, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead > 0)
        {
            response.assign(buffer, bytesRead);
            std::cout << "Transmitted" << response << std::endl;
            WriteFile(hSerialWrite, buffer, bytesRead, &bytesWritten, NULL);
            std::cout << "Recieved: " << bytesWritten << std::endl;
        }
    }

    CloseHandle(hSerialRead);
    CloseHandle(hSerialWrite);
    return 0;
}

// #include <iostream>
// #include <windows.h>

// using namespace std;

// string portName = "COM3"; // Specify the correct COM port
// DWORD baudRate = 115200;  // Transmission speed

// HANDLE openSerialPort(const string &port)
// {
//     HANDLE hSerial = CreateFile(port.c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);

//     if (hSerial == INVALID_HANDLE_VALUE)
//     {
//         cerr << "Error: Failed to open port " << port << endl;
//         return nullptr;
//     }

//     DCB dcbSerialParams = {0};
//     dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

//     if (!GetCommState(hSerial, &dcbSerialParams))
//     {
//         cerr << "Error: Unable to get port state" << endl;
//         CloseHandle(hSerial);
//         return nullptr;
//     }

//     dcbSerialParams.BaudRate = baudRate;
//     dcbSerialParams.ByteSize = 8;
//     dcbSerialParams.Parity = NOPARITY;
//     dcbSerialParams.StopBits = ONESTOPBIT;

//     if (!SetCommState(hSerial, &dcbSerialParams))
//     {
//         cerr << "Error: Unable to configure port" << endl;
//         CloseHandle(hSerial);
//         return nullptr;
//     }

//     return hSerial;
// }

// bool sendCommand(HANDLE hSerial, const string &command)
// {
//     DWORD bytesWritten;
//     string fullCommand = command + "\r"; // Add carriage return
//     return WriteFile(hSerial, fullCommand.c_str(), fullCommand.size(), &bytesWritten, nullptr);
// }

// string readResponse(HANDLE hSerial)
// {
//     char buffer[256];
//     DWORD bytesRead;
//     string response;

//     if (ReadFile(hSerial, buffer, sizeof(buffer), &bytesRead, nullptr) && bytesRead > 0)
//     {
//         response.assign(buffer, bytesRead);
//     }

//     return response;
// }

// int main()
// {
//     HANDLE hSerial = openSerialPort("\\\\.\\COM3"); // Open port

//     if (!hSerial)
//     {
//         return 1;
//     }

//     string command;
//     while (true)
//     {
//         cout << "Enter command: ";
//         cin >> command;

//         if (command == "Q")
//             break;

//         if (sendCommand(hSerial, command))
//         {
//             cout << "Command sent: " << command << endl;
//             Sleep(100); // Wait for response
//             string response = readResponse(hSerial);
//             cout << "Response: " << response << endl;
//         }
//         else
//         {
//             cout << "Error sending command!" << endl;
//         }
//     }

//     CloseHandle(hSerial);
//     return 0;
// }

// #include <windows.h>
// #include <iostream>

// int main()
// {
//     HANDLE hSerial;
//     hSerial = CreateFile("COM5", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

//     if (hSerial == INVALID_HANDLE_VALUE)
//     {
//         std::cerr << "Error opening COM port!" << std::endl;
//         return 1;
//     }

//     DCB dcbSerialParams = {0};
//     dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

//     if (!GetCommState(hSerial, &dcbSerialParams))
//     {
//         std::cerr << "Error getting COM port parameters!" << std::endl;
//         CloseHandle(hSerial);
//         return 1;
//     }

//     dcbSerialParams.BaudRate = CBR_9600;
//     dcbSerialParams.ByteSize = 8;
//     dcbSerialParams.StopBits = ONESTOPBIT;
//     dcbSerialParams.Parity = NOPARITY;

//     if (!SetCommState(hSerial, &dcbSerialParams))
//     {
//         std::cerr << "Error setting COM port parameters!" << std::endl;
//         CloseHandle(hSerial);
//         return 1;
//     }

//     unsigned char data[] = {0x21, 0x4D, 0x20, 0x20, 0x1D, 0x35, 0x30, 0x30, 0x20, 0x30, 0x0D};
//     DWORD bytesWritten;

//     if (!WriteFile(hSerial, data, sizeof(data), &bytesWritten, NULL))
//     {
//         std::cerr << "Error sending data!" << std::endl;
//         CloseHandle(hSerial);
//         return 1;
//     }

//     std::cout << "Data successfully sent!" << std::endl;

//     // Reading response
//     char buffer[256];
//     DWORD bytesRead;

//     if (ReadFile(hSerial, buffer, sizeof(buffer) - 1, &bytesRead, NULL))
//     {
//         buffer[bytesRead] = '\0';
//         std::cout << "Response: " << buffer << std::endl;
//     }
//     else
//     {
//         std::cerr << "Error reading data!" << std::endl;
//     }

//     CloseHandle(hSerial);
//     return 0;
// }
