#ifndef B57164_h
#define B57164_h

#include "Arduino.h"

class B57164{
    public:
    B57164(int analogPin);
    double readRaw();
    double readVoltage();
    double readCalibrated();

    private:
    const int analogPin;
};

#endif