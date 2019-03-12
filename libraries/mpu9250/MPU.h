#ifndef MPU_h
#define MPU_h

#include "Arduino.h"

class MPU{
public:
    MPU();
    void begin(int serialRate);
    double readRaw();
    double readVoltage();
    double readCalibrated();
private:
    int AccAddress = 0x53;
    int GyroAddress = 0x69;
    int MagAddress = 0x1E;
};

#endif
