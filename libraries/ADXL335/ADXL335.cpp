#include "ADXL335.h"
#include "Arduino.h"

ADXL335::ADXL335(int X_analogPin, int Y_analogPin, int Z_analogPin)
: X_analogPin(X_analogPin), Y_analogPin(Y_analogPin), Z_analogPin(Z_analogPin){

}

//NEEDS CALIBRATION

//X AXIS
double ADXL335::readRawX(){
    return analogRead(X_analogPin);
}

double ADXL335::readVoltageX(){
    return readRawX()*(5.0/1024.0);
}

double ADXL335::readCalibratedX(){
    return readVoltageX();
}

//Y AXIS
double ADXL335::readRawY(){
    return analogRead(Y_analogPin);
}

double ADXL335::readVoltageY(){
    return readRawY()*(5.0/1024.0);
}

double ADXL335::readCalibratedY(){
    return readVoltageY();
}

//Z AXIS
double ADXL335::readRawZ(){
    return analogRead(Z_analogPin);
}

double ADXL335::readVoltageZ(){
    return readRawZ()*(5.0/1024.0);
}

double ADXL335::readCalibratedZ(){
    return readVoltageZ();
}