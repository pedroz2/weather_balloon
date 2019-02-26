#include "bmp280.h"
#include "Arduino.h"

bmp280::bmp280(int analogPin)
: analogPin(analogPin){

}


double bmp280::readRaw(){
    return analogRead(analogPin);
}

double bmp280::readVoltage(){
    return readRaw()*(5.0/1024.0);
}

double bmp280::readCalibrated(){
    
}