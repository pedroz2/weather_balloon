#include "MPU.h"

MPU::MPU(){
}

void MPU::begin() {
    // sensor intialization
    Wire.begin();
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission();

    // gyroscope calibration
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(0x1B);
    Wire.write(0b00011000);
    Wire.endTransmission();
    
    // accelerometer setup
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(0x1c);
    Wire.write(0b00011000);
    Wire.endTransmission();
}

long* MPU::readAccelerometer() {
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(0x3B);
    Wire.endTransmission();
    Wire.requestFrom(MPU_ADDRESS, 6);
    
    RawAx = Wire.read()<<8|Wire.read(); // 2 bytes are stored for each
    RawAy = Wire.read()<<8|Wire.read();
    RawAz = Wire.read()<<8|Wire.read();
    
    RealAx = RawAx / 2048.0;
    RealAy = RawAy / 2048.0;
    RealAz = RawAz / 2048.0;
    acc[0] = RealAx;
    acc[1] = RealAy;
    acc[2] = RealAz;
    // readings are ouputted in (degrees/sec)
    return acc;
}

long* MPU::readGyroscope() {
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(0x43);
    Wire.endTransmission();
    Wire.requestFrom(MPU_ADDRESS, 6);
    
    RawGx = Wire.read()<<8|Wire.read(); // 2 bytes are stored for each
    RawGy = Wire.read()<<8|Wire.read();
    RawGz = Wire.read()<<8|Wire.read();
    
    RealGx = RawGx / 16.4;
    RealGy = RawGy / 16.4;
    RealGz = RawGz / 16.4;
    gyro[0] = RealGx;
    gyro[1] = RealGy;
    gyro[2] = RealGz;
    // readings are ouputted in units g
    return gyro;
}

void MPU::printAcc() {
    long*temp = readAccelerometer();
    Serial.println("Accelerometer: x, y, z");
    for (int i = 0; i < PACKET_SIZE; i++) {
        Serial.print(acc[i]);
        Serial.print(" ");
    }
    Serial.println();
}

void MPU::printGyro() {
    long*temp = readGyroscope();
    Serial.println("Gyroscope: x, y, z");
    for (int i = 0; i < PACKET_SIZE; i++) {
        Serial.print(gyro[i]);
        Serial.print(" ");
    }
    Serial.println();
}