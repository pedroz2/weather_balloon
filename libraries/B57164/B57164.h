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
    const double B = 78.7229;
    const double R = 0.7344;
};

#endif
