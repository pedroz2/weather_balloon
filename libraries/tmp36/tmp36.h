#ifndef tmp36_h
#define tmp36_h

#include "Arduino.h"

class tmp36{
    public:
    tmp36(int analogPin);
    double readRaw();
    double readVoltage();
    double readCalibrated();

    private:
    const int analogPin;
}