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
    const double humidity_intercept = 82.885;
    const double humidity_slope = 2.866;
};

#endif
