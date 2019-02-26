#ifndef mpx4115_h
#define mpx4115_h

#include "Arduino.h"

class mpx4115{
    public:
    mpx4115(int analogPin);
    double readRaw();
    double readVoltage();
    double readCalibrated();

    private:
    const int analogPin;
}