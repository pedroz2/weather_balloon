#ifndef HIH4030_h
#define HIH4030_h

#include "Arduino.h"

class HIH4030{
    public:
    HIH4030(int analogPin);
    double readRaw();
    double readVoltage();
    double readCalibrated();

    private:
    const int analogPin;
};

#endif