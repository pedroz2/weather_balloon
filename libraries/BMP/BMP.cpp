#include "BMP.h"

BMP::BMP(){
}

void BMP::begin() {
    groupAddresses();
}

void BMP::readAltitude() {
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
}

void BMP::readUncompPress(){
    Wire.beginTransmission(BMP_ADDRESS);
    Wire.write(0xF4);
    Wire.write(0x34 + OverSampSett << 6);
    Wire.endTransmission();
    delay(ConvTimeDel);

    UP = (readToRegisters(0xF6, 3)) >> (8-OverSampSett);

    //Calculate true readPressure
    B6 = B5 - 4000;
    X1 = (B2 *(B6 * B6 / 4092) / 2048) ; 
    X2 = AC2 * B6 / 2048; 
    X3 = X1 + X2; 
    B3 = (((AC1*4+X3) << OverSampSett) + 2) / 4 ; 
    X1 = AC3 * B6 / 8192; 
    X2 = (B1 * (B6 * B6 / 4096)) / 65536; 
    X3 = ((X1 + X2) + 2)/ 4; 
    B4 = AC4 *( (unsigned long) (X3 + 32768)) / 32768; 
    B7 = ((unsigned long) UP - B3) * (50000 >> OverSampSett); 
    if (B7 < 0x80000000)
    {
        P = (B7*2) / B4;
    } 
    else
    {
        P = (B7 / B4) * 2;
    }
    
    X1 = (P / 256) *(P / 256); 
    X1 = (X1 * 3038) / 65536; 
    X2 = (-7357 * P) / 65536; 
    P =  P + (X1 + X2 + 3791) / 16;
    P = P/100; // this gives us HPa 
}

void BMP::printAllData(){
    Serial.print(T,3);
    Serial.print(",");
    Serial.print(P,2);
    Serial.print(",");
    Serial.print(A,2);
    Serial.print(",");
    delay(20);
    groupAddresses();
    readUncompPress();
    readUncompTemp();

}
