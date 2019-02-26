#include "mpu9250.h"
#include "Arduino.h"

mpu9250::mpu9250(int analogPin)
: analogPin(analogPin){

}


double mpu9250::readRaw(){
    return analogRead(analogPin);
}

double mpu9250::readVoltage(){
    return readRaw()*(5.0/1024.0);
}

double mpu9250::readCalibrated(){
    
}