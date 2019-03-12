#include "MPU.h"
#include "Arduino.h"

MPU::MPU(){
    
}

void MPU::begin(int serialRate) {
    
}

double MPU::readRaw(){
    return analogRead(analogPin);
}

double MPU::readVoltage(){
    return readRaw()*(5.0/1024.0);
}

double MPU::readCalibrated(){
    
}
