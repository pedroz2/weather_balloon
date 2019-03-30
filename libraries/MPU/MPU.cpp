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
    
    // magnetometer setup
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(0x37); // turn on int bypass mux
    Wire.write(0x02);
    Wire.endTransmission();
    
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(0x0A); // write to control 1 address
    Wire.write(0x0F); // set to single measurement mode and FUSE ROM access mode
    Wire.endTransmission();
    delay(100);
    // get calibration values
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(0x10); // address of first calibration value
    Wire.endTransmission();
    Wire.requestFrom(MPU_ADDRESS, 3);
    ASAX = (Wire.read()-128.0)*0.5/128+1;
    ASAY = (Wire.read()-128.0)*0.5/128+1;
    ASAZ = (Wire.read()-128.0)*0.5/128+1;
    
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(0x0A);
    Wire.write(0x00); // power down MAG
    Wire.endTransmission();
    
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(0x0A);
    Wire.write(0x16); // 0001 0110 sets to continuous100 Hz and 16 bit
    Wire.endTransmission();
    delay(100);
}

double* MPU::readAccelerometer() {
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

double* MPU::readGyroscope() {
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

double* MPU::readMagnetometer() {
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(0x03); // address of first x val
    Wire.endTransmission();
    Wire.requestFrom(MPU_ADDRESS, 6);
    
    RawMx = Wire.read()<<8|Wire.read();
    RawMy = Wire.read()<<8|Wire.read();
    RawMz = Wire.read()<<8|Wire.read();
    
    RealMx = RawMx * ASAX;
    RealMy = RawMy * ASAY;
    RealMz = RawMz * ASAZ;
    mag[0] = RealMx;
    mag[1] = RealMy;
    mag[2] = RealMz;
    // readings are ouputted in units g
    return mag;
}

void MPU::printAcc() {
    double*temp = readAccelerometer();
    Serial.println("Accelerometer: x, y, z");
    for (int i = 0; i < PACKET_SIZE; i++) {
        Serial.print(acc[i]);
        Serial.print(",");
    }
    Serial.println();
}

void MPU::printGyro() {
    double*temp = readGyroscope();
    Serial.println("Gyroscope: x, y, z");
    for (int i = 0; i < PACKET_SIZE; i++) {
        Serial.print(gyro[i]);
        Serial.print(",");
    }
    Serial.println();
}
