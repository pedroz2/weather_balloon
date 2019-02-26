#include "gps.h"
#include "Arduino.h"
#include <SoftwareSerial.h>

GPS::GPS(int in, int out):gpsPort(in, out)
{
    TinyGPSPlus gps;
}

void GPS::begin(int gpsRate, int serialRate){
    gpsPort.begin(gpsRate);
    Serial.begin(serialRate);
}

void GPS::printGPSInfo()
{
    unsigned long chars;
    unsigned short sentences, failed;
    while (gpsPort.available()){
        // get the byte data from the GPS
        int c = gpsPort.read();
        gps.encode(c);
    }
    long lat, lon;
    Serial.print("Lat: "); Serial.println(gps.location.lat(), 6);
    Serial.print("Long: "); Serial.println(gps.location.lng(), 6);
    Serial.print("Alt: "); Serial.println(gps.altitude.feet());
    Serial.print("Course: "); Serial.println(gps.course.deg());
    Serial.print("Speed: "); Serial.println(gps.speed.mph());
    Serial.print("Date: "); printDate();
    Serial.print("Time: "); printTime();
    Serial.print("Sats: "); Serial.println(gps.satellites.value());
    Serial.println();
}

void GPS::smartDelay(unsigned long ms)
{
    unsigned long start = millis();
    do
    {
        // If data has come in from the GPS module
        while (gpsPort.available())
            gps.encode(gpsPort.read()); // Send it to the encode function
        // tinyGPS.encode(char) continues to "load" the tinGPS object with new
        // data coming in from the GPS module. As full NMEA strings begin to come in
        // the tinyGPS library will be able to start parsing them for pertinent info
    } while (millis() - start < ms);
    
}

void GPS::printDate()
{
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.println(gps.date.year());
    
}

void GPS::printTime()
{
    Serial.print(gps.time.hour());
    Serial.print(":");
    if (gps.time.minute() < 10) Serial.print('0');
    Serial.print(gps.time.minute());
    Serial.print(":");
    if (gps.time.second() < 10) Serial.print('0');
    Serial.println(gps.time.second());
    
}

