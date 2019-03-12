#ifndef ADXL335_h
#define ADXL335_h

#include "Arduino.h"

class ADXL335{
    public:
    ADXL335(int X_analogPin, int Y_analogPin, int Z_analogPin);
    double readRawX();
    double readRawY();
    double readRawZ();
    double readVoltageX();
    double readVoltageY();
    double readVoltageZ();
    double readCalibratedX();
    double readCalibratedY();
    double readCalibratedZ();

    private:
    const int X_analogPin, Y_analogPin, Z_analogPin;
};

#endif