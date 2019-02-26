#include "tmp36.h"
#include "Arduino.h"

tmp36::tmp36(int analogPin)
: analogPin(analogPin){

}


double tmp36::readRaw(){
    return analogRead(analogPin);
}

double tmp36::readVoltage(){
    return readRaw()*(5.0/1024.0);
}

double tmp36::readCalibrated(){
    
}