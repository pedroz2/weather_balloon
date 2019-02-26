#include "b57164.h"
#include "Arduino.h"

b57164::b57164(int analogPin)
: analogPin(analogPin){

}


double b57164::readRaw(){
    return analogRead(analogPin);
}

double b57164::readVoltage(){
    return readRaw()*(5.0/1024.0);
}

double b57164::readCalibrated(){
    
}