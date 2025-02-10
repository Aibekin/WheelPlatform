#include "DriverPacket.h"

void DriverPacket::fillFromCommand(const std::string &command)
{
    if (command.size() >= 4)
    {
        direction = static_cast<uint8_t>(command[0]);
        speedHundreds = static_cast<uint8_t>(command[1]);
        speedTens = static_cast<uint8_t>(command[2]);
        speedOnes = static_cast<uint8_t>(command[3]);
    }
}

std::array<uint8_t, 11> DriverPacket::toByteArray()
{
    return {header1, enableRotation, header2, header3,
            direction, speedHundreds, speedTens, speedOnes,
            footer1, footer2, footer3};
}