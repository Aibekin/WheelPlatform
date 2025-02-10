#include "src/ComPort.h"
#include "src/DriverPacket.h"
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
    LPCSTR port3 = "COM7";

    ComPort radio(port1, true);
    ComPort motor1(port2, false);
    ComPort motor2(port3, false);

    HANDLE hSerialRead = radio.returnSerial();
    HANDLE hSerialWriteL = motor1.returnSerial();
    HANDLE hSerialWriteR = motor2.returnSerial();

    char buffer[8];
    DWORD bytesRead, bytesWrittenL, bytesWrittenR;
    std::string response;

    while (true)
    {
        if (ReadFile(hSerialRead, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead > 0)
        {
            response.assign(buffer, bytesRead);
            std::vector<std::string> tokens = splitString(response, ',');

            DriverPacket packet1;
            DriverPacket packet2;
            packet1.fillFromCommand(tokens[0]);
            packet2.fillFromCommand(tokens[1]);

            std::array<uint8_t, 11> data1 = packet1.toByteArray();
            std::array<uint8_t, 11> data2 = packet2.toByteArray();

            std::thread t1([&]()
                           { WriteFile(hSerialWriteL, data1.data(), data1.size(), &bytesWrittenL, NULL); });
            std::thread t2([&]()
                           { WriteFile(hSerialWriteR, data2.data(), data2.size(), &bytesWrittenR, NULL); });
            t1.join();
            t2.join();
        }
    }

    return 0;
}