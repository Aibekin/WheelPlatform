#ifndef COMPORT_H
#define COMPORT_H

#include <windows.h>
#include <string>
#include <iostream>

class ComPort
{
private:
    bool read;
    HANDLE hSerial;

    void configureComPort(HANDLE &Serial);

public:
    ComPort(LPCSTR p, bool r);
    ~ComPort();

    HANDLE returnSerial();
};

#endif