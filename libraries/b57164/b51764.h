#ifndef b57164_h
#define b57164_h

#include "Arduino.h"

class b57164{
    public:
    b57164(int analogPin);
    double readRaw();
    double readVoltage();
    double readCalibrated();

    private:
    const int analogPin;
}