#include "GPS.h"
#include "Arduino.h"
#include <SoftwareSerial.h>

GPS::GPS(int in, int out):gpsPort(in, out)
{
}

void GPS::begin(int gpsRate){
    gpsPort.begin(gpsRate);
    resetChar();
    gpsPort.listen();
}

String GPS::returnGPSInfo()
{
    currentLine = "";
    while(gpsPort.available()) {
        info[spot++] = gpsPort.read();
    }
    
    if(checkIfPrint()) resetChar();
    
    if(spot == MAX_CHARACTERS) resetChar();
    for(int i = 0; i < spot; i++) {
        currentLine+=info[i];
    }
    spot = 0;
    
    return currentLine;
}

void GPS::resetChar()
{
    for(int i = 0; i < MAX_CHARACTERS; i++)
    {
        if(info[i] == '\0')
            break;
        info[i] = '\0';
    }
    spot = 0;
}

bool GPS::checkIfPrint()
{
    for(int i = 0; i < MAX_CHARACTERS-4; i++)
    {
        if(info[i] == '\0')
            break;
        if(info[i] == 'G' && info[i+1] =='P' && info[i+2] == 'G' && info[i+3] == 'G' && info[i+4] == 'A') {
            int startSpot = i;
            int endSpot = i;
            bool endFound = false;
            
            while(endSpot < 400 && !endFound) {
                if(info[endSpot] == '\n')
                    endFound = true;
                else
                    endSpot++;
            }
            
            if (endFound) {
                for(int j = startSpot; j <= endSpot; j++) {
                    currentLine += info[j];
                }
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}
