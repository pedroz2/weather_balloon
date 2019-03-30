#ifndef MPX4115_h
#define MPX4115_h

#include "Arduino.h"

class MPX4115{
    public:
    MPX4115(int analogPin);
    double readRaw();
    double readVoltage();
    double readCalibrated();

    private:
    const int analogPin;
    const double pressure_slope = 7.928;
};

#endif
