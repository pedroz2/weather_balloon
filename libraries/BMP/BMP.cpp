#include "BMP.h"

BMP::BMP(){
}

void BMP::begin() {
    groupAddresses();
}

long BMP::readAltitude() {
    A = 44330 * (1 - pow((P / p0), 0.1903));
    
}

long BMP::readToRegisters(int code, int numBytes) {
    long value = 0;
    Wire.beginTransmission(BMP_ADDRESS);
    Wire.write(code);
    Wire.endTransmission();
    Wire.requestFrom(BMP_ADDRESS, numBytes);
    if (Wire.available() >= numBytes) {
        for (int i = 0; i < numBytes; i++) {
            value = (value <<8 ) | Wire.read();
        }
    }
    return value;
}

void BMP::groupAddresses() {
    AC1 = readToRegisters(0xAA, 2);
    AC2 = readToRegisters(0xAC, 2);
    AC3 = readToRegisters(0xAE, 2);
    AC4 = readToRegisters(0xB0, 2);
    AC5 = readToRegisters(0xB2, 2);
    AC6 = readToRegisters(0xB4, 2);
    H1 = readToRegisters(0xB6, 2);
    B2 = readToRegisters(0xB8, 2);
    MB = readToRegisters(0xBA, 2);
    MC = readToRegisters(0xBC, 2);
    MD = readToRegisters(0xBE, 2);
}

void BMP::readUncompTemp() {
    Wire.beginTransmission(BMP_ADDRESS);
    Wire.write(0xF4);
    Wire.write(0x2E);
    Wire.endTransmission();
    delay(4.5);
    
    UT = readToRegisters(0xF6, 2);
    
    // calculate true temperature value
    X1 = (UT - (AC6*AC5)/pow(2,15) );
    X2 = (MC * pow(2,11))/(X1 + MD);
    B5 = X1 + X2;
    T = (B5 + 8)/pow(2,4);
    T = T/10;
    T = T * (9/5.0) + 32;
    return B5;
}

long BMP::readPressure();
long BMP::readTemperature();
void BMP::printAllData();
