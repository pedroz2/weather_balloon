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
    const double x_slope = 3.4483;
    const double y_slope = 3.2258;
    const double z_slope = 3.7037;
    const double x_intercept = -4.8276;
    const double y_intercept = -4.4839;
    const double z_intercept = -5.6667;
};

#endif
