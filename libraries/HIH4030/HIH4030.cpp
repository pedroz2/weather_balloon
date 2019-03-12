#include "HIH4030.h"
#include "Arduino.h"

HIH4030::HIH4030(int analogPin)
: analogPin(analogPin){

}


double HIH4030::readRaw(){
    return analogRead(analogPin);
}

double HIH4030::readVoltage(){
    return readRaw()*(5.0/1024.0);
}

double HIH4030::readCalibrated(){
    return readVoltage(); // NEEDS CALIBRATION
}