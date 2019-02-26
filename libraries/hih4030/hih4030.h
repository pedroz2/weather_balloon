#ifndef hih4030_h
#define hih4030_h

#include "Arduino.h"

class hih4030{
    public:
    hih4030(int analogPin);
    double readRaw();
    double readVoltage();
    double readCalibrated();

    private:
    const int analogPin;
};

#endif