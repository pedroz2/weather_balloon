#ifndef mpu9250_h
#define mpu9250_h

#include "Arduino.h"

class mpu9250{
    public:
    mpu9250(int analogPin);
    double readRaw();
    double readVoltage();
    double readCalibrated();

    private:
    const int analogPin;
};

#endif