#ifndef bmp280_h
#define bmp280_h

#include "Arduino.h"

class bmp280{
    public:
    bmp280(int analogPin);
    double readRaw();
    double readVoltage();
    double readCalibrated();

    private:
    const int analogPin;
}