#ifndef bmp280_h
#define bmp280_h

#include "Arduino.h"
#include "Wire.h"
#define BMP_ADDRESS 0x10

class BMP{
public:
    BMP();
    void begin();
    void readAltitude();
    void readUncompTemp();
    void readUncompPress();
    void printAllData();
private:
    unsigned short dig_T1;
    short dig_T2, dig_T3; 
    unsigned short dig_P1;
    short dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;

    signed long UT, UP;
    
    const int OverSampSett = 3; // set oversample rate
    const int ConvTimeDel = 26; // set conversion time
    const long p0 = 256.0;
    
    float T, P, A;
    
    long readToRegisters(int code, int numBytes);
    void groupAddresses();
};

#endif
