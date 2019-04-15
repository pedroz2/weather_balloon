#include "TMP36.h"
#include "Arduino.h"

TMP36::TMP36(int analogPin)
: analogPin(analogPin){

}


double TMP36::readRaw(){
    return analogRead(analogPin);
}

double TMP36::readVoltage(){
    return readRaw()*(5.0/1024.0);
}

double TMP36::readCalibrated(){
    return readVoltage(); // NEEDS CALIBRATION
}