#ifndef MPU_h
#define MPU_h
#include "Wire.h"
#include "Arduino.h"

class MPU{
public:
    MPU();
    void begin(int serialRate);
    double readRaw();
    double readVoltage();
    double readCalibrated();
private:
    const int ADDRESS = 0x68;
    const int
};

#endif
