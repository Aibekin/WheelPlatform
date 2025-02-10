#include <iomanip>
#include <array>
#include <cstdint>

struct DriverPacket
{
    uint8_t header1 = 0x21;
    uint8_t enableRotation = 0x4D;
    uint8_t header2 = 0x20;
    uint8_t header3 = 0x20;
    uint8_t direction = 0x00; // Направление вращения
    uint8_t speedHundreds = 0x00;
    uint8_t speedTens = 0x00;
    uint8_t speedOnes = 0x00;
    uint8_t footer1 = 0x20;
    uint8_t footer2 = 0x30;
    uint8_t footer3 = 0x0D;

    void fillFromCommand(const std::string &command);

    // Метод получения пакета в виде массива байтов
    std::array<uint8_t, 11> toByteArray();
};