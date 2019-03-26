#ifndef MPU_h
#define MPU_h
#include "Wire.h"
#include "Arduino.h"
#define MPU_ADDRESS 0x68
#define MAG_ADDRESS 0x0C

class MPU {
public:
    MPU();
    void begin();
    long* readAccelerometer();
    long* readGyroscope();
    void printAcc();
    void printGyro();
private:
    static const int PACKET_SIZE = 3;
    float RealAx, RealAy, RealAz, RealGx, RealGy, RealGz;
    long RawAx, RawAy, RawAz, RawGx, RawGy, RawGz;
    long acc[PACKET_SIZE];
    long gyro[PACKET_SIZE];
};

#endif
