#ifndef TMP36_h
#define TMP36_h

#include "Arduino.h"

class TMP36{
    public:
    TMP36(int analogPin);
    double readRaw();
    double readVoltage();
    double readCalibrated();

    private:
    const int analogPin;
};

#endif