#include "MPX4115.h"
#include "Arduino.h"

MPX4115::MPX4115(int analogPin)
: analogPin(analogPin){

}


double MPX4115::readRaw(){
    return analogRead(analogPin);
}

double MPX4115::readVoltage(){
    return readRaw()*(5.0/1024.0);
}

double MPX4115::readCalibrated(){
    return readVoltage() * pressure_slope;
}
