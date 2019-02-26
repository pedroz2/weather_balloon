#include "mpx4115.h"
#include "Arduino.h"

mpx4115::mpx4115(int analogPin)
: analogPin(analogPin){

}


double mpx4115::readRaw(){
    return analogRead(analogPin);
}

double mpx4115::readVoltage(){
    return readRaw()*(5.0/1024.0);
}

double mpx4115::readCalibrated(){
    
}