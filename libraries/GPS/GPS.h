/*
 GPS.h - Library for printing GPS data form NEO-6M sensor.
 Created by Arthur K. Zhang, November 14, 2018.
 Property of 
 */

#ifndef GPS_h
#define GPS_h

#include <Arduino.h>
#include <SoftwareSerial.h>

class GPS
{
public:
    GPS(int in, int out);
    void begin(int gpsRate);
    String readGPSInfo();
private:
    SoftwareSerial gpsPort;
    void printDate();
    void printTime();
    void resetChar();
    bool checkIfPrint();
    int spot = 0;
    static const int MAX_CHARACTERS = 400;
    char info[MAX_CHARACTERS];
    String currentLine = "";
};

#endif
