#ifndef bmp280_h
#define bmp280_h

#include "Arduino.h"
#include "Wire.h"
#define BMP_ADDRESS = 0x77

class BMP{
public:
    BMP();
    void begin();
    long readAltitude();
    long readPressure();
    void readUncompTemp();
    long readTemperature();
    void printAllData();
private:
    long AC1, AC2, AC3, H1, B2, MB, MC, MD;
    unsigned long AC4, AC5, AC6; //unsigned vars from datasheet
    
    unsigned long X1, X2, X3, B3, B5, B6, UP, UT, p;
    const int OverSampSett = 3; // set oversample rate
    const int ConvTimeDel = 26; // set conversion time
    const long p0 = 256.0;
    
    float T, P, A;
    
    long readToRegisters(int code, int numBytes);
    void groupAddresses();
};

#endif
