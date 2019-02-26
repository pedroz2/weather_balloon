#include "adxl335.h"
#include "Arduino.h"

adxl335::adxl335(int X_analogPin, int Y_analogPin, int Z_analogPin)
: X_analogPin(X_analogPin), Y_analogPin(Y_analogPin), Z_analogPin(Z_analogPin){

}

//X AXIS
double adxl335::readRawX(){
    return analogRead(X_analogPin);
}

double adxl335::readVoltageX(){
    return readRawX()*(5.0/1024.0);
}

double adxl335::readCalibratedX(){
    return readVoltageX();
}

//Y AXIS
double adxl335::readRawY(){
    return analogRead(Y_analogPin);
}

double adxl335::readVoltageY(){
    return readRawY()*(5.0/1024.0);
}

double adxl335::readCalibratedY(){
    return readVoltageY();
}

//Z AXIS
double adxl335::readRawZ(){
    return analogRead(Z_analogPin);
}

double adxl335::readVoltageZ(){
    return readRawZ()*(5.0/1024.0);
}

double adxl335::readCalibratedZ(){
    return readVoltageZ();
}