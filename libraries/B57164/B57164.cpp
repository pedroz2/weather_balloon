#include "B57164.h"
#include "Arduino.h"

B57164::B57164(int analogPin)
: analogPin(analogPin){

}


double B57164::readRaw(){
    return analogRead(analogPin);
}

double B57164::readVoltage(){
    return readRaw()*(5.0/1024.0);
}

double B57164::readCalibrated(){
    return readVoltage(); // NEEDS CALIBRATIONS
}