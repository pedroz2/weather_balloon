#ifndef adxl335_h
#define adxl335_h

#include "Arduino.h"

class adxl335{
    public:
    adxl335(int X_analogPin, int Y_analogPin, int Z_analogPin);
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