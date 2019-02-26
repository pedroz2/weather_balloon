#ifndef adxl335_h
#define adxl335_h

#include "Arduino.h"

class adxl335{
    public:
    adxl335(int X_analogPin, int Y_analogPin, int Z_analogPin);
    double readRaw();
    double readVoltage();
    double readCalibrated();

    private:
    const int X_analogPin, Y_analogPin, Z_analogPin;
}