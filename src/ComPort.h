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

public:
    ComPort(HANDLE Serial, bool r);
    ~ComPort();
};

#endif