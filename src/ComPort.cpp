#include "ComPort.h"

ComPort::ComPort(LPCSTR port, bool r)
{
    read = r;
    hSerial = CreateFile(port, read ? GENERIC_READ : (GENERIC_READ | GENERIC_WRITE), 0, NULL, OPEN_EXISTING, 0, NULL);

    if (hSerial == INVALID_HANDLE_VALUE)
        throw "Port opening error";

    configureComPort(hSerial);
}

ComPort::~ComPort()
{
    CloseHandle(hSerial);
}

void ComPort::configureComPort(HANDLE &Serial)
{
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(Serial, &dcbSerialParams))
        throw "Com port get status error";

    dcbSerialParams.BaudRate = read ? CBR_57600 : CBR_115200;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.Parity = NOPARITY;
    dcbSerialParams.StopBits = ONESTOPBIT;

    if (!SetCommState(Serial, &dcbSerialParams))
        throw "Com port set status error";
}

HANDLE ComPort::returnSerial()
{
    return hSerial;
}