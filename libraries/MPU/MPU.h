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
    double* readAccelerometer();
    double* readGyroscope();
    void printAcc();
    void printGyro();
private:
    static const int PACKET_SIZE = 3;
    double RealAx, RealAy, RealAz, RealGx, RealGy, RealGz;
    double RawAx, RawAy, RawAz, RawGx, RawGy, RawGz;
    double acc[PACKET_SIZE];
    double gyro[PACKET_SIZE];
};

#endif
