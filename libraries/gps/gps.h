/*
 GPS.h - Library for printing GPS data form NEO-6M sensor.
 Created by Arthur K. Zhang, November 14, 2018.
 Property of SPARK el electrical
 */

#ifndef GPS_h
#define GPS_h

#include <TinyGPS++.h>
#include <Arduino.h>
#include <SoftwareSerial.h>;

class GPS
{
public:
    GPS(int in, int out);
    void begin(int gpsRate, int serialRate);
    void smartDelay(unsigned long ms);
    void printGPSInfo();
private:
    SoftwareSerial gpsPort;
    TinyGPSPlus gps;
    void printDate();
    void printTime();
};

#endif
