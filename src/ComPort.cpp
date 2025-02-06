#include "ComPort.h"

ComPort::ComPort(HANDLE Serial, bool read)
{
    hSerial = Serial;
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams))
        throw "Com port get status error";

    dcbSerialParams.BaudRate = read ? CBR_57600 : CBR_115200;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.Parity = NOPARITY;
    dcbSerialParams.StopBits = ONESTOPBIT;

    if (!SetCommState(hSerial, &dcbSerialParams))
        throw "Com port set status error";
}

ComPort::~ComPort()
{
    CloseHandle(hSerial);
}