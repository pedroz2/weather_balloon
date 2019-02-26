#include "hih4030.h"
#include "Arduino.h"

hih4030::hih4030(int analogPin)
: analogPin(analogPin){

}


double hih4030::readRaw(){
    return analogRead(analogPin);
}

double hih4030::readVoltage(){
    return readRaw()*(5.0/1024.0);
}

double hih4030::readCalibrated(){
    
}