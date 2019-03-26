#ifndef bmp280_h
#define bmp280_h

#include "Arduino.h"
#include "Wire.h"
#define BMP_ADDRESS 0x10

class BMP{
public:
    BMP();
    void begin();
    float readAltitude();
    float readTemperature();
    float readPressure();
private:
    uint16_t dig_T1;
    int16_t dig_T2, dig_T3; 
    uint16_t dig_P1;
    int16_t dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
    int32_t   t_fine;
    
    const long p0 = 1025.0;
    
    long readToRegisters(int code, int numBytes);
    void groupAddresses();
};

#endif
