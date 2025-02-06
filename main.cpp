#include "src/ComPort.h"
#include <thread>
#include <sstream>
#include <vector>

std::vector<std::string> splitString(const std::string &str, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(str);

    while (std::getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }

    return tokens;
}

int main()
{
    LPCSTR port1 = "COM3";
    LPCSTR port2 = "COM6";

    ComPort radio(port1, true);
    ComPort motor1(port2, false);

    HANDLE hSerialRead = radio.returnSerial();
    HANDLE hSerialWrite = motor1.returnSerial();

    char buffer[256];
    DWORD bytesRead, bytesWritten, bytesReturn;
    std::string response;
    std::cout << "\033[?25l" << "Motor\n\n";

    while (true)
    {
        if (ReadFile(hSerialRead, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead > 0)
        {
            response.assign(buffer, bytesRead);
            std::cout << "\r" << response << std::flush;
            std::vector<std::string> tokens = splitString(response, ',');
            std::thread t1([&]()
                           { WriteFile(hSerialWrite, tokens[0].c_str(), tokens[0].size(), &bytesWritten, NULL); });
            t1.join();
        }
    }

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
//         for (DWORD i = 0; i < bytesRead; ++i)
//             printf("%02X ", static_cast<unsigned char>(buffer[i]));
//         cout << endl;
//         response.assign(buffer, bytesRead);
//     }

//     return response;
// }

// int main()
// {
//     HANDLE hSerial = openSerialPort("\\\\.\\COM6"); // Open port

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