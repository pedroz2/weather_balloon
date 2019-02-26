#include "adxl335.h"
#include "Arduino.h"

adxl335::adxl335(int X_analogPin, int Y_analogPin, int Z_analogPin)
: X_analogPin(X_analogPin), Y_analogPin(Y_analogPin), Z_analogPin(Z_analogPin){

}


double adxl335::readRaw(){
    return analogRead(analogPin);
}

double adxl335::readVoltage(){
    return readRaw()*(5.0/1024.0);
}

double adxl335::readCalibrated(){
    
}