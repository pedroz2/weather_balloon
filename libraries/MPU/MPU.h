#ifndef MPU_h
#define MPU_h
#include "Wire.h"
#include "Arduino.h"

class MPU {
public:
    MPU();
    void begin();
    long* readAccelerometer();
    long* readGyroscope();
    void printAcc();
    void printGyro();
private:
    const int MPU_ADDRESS = 0x68;
    static const int PACKET_SIZE = 3;
    float RealAx, RealAy, RealAz, RealGx, RealGy, RealGz;
    long RawAx, RawAy, RawAz, RawGx, RawGy, RawGz;
    long acc[PACKET_SIZE];
    long gyro[PACKET_SIZE];
};

#endif
