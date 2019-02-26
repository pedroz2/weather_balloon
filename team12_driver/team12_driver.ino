#include <Arduino.h>
#include <GPS.h>
const int RXgps = 3;
const int TXgps = 2;
const int RXlog = 7;
const int TXlog = 8;
const long SERIALRATE = 9600;

GPS gps(RXgps, TXgps);
SoftwareSerial logger(RXlog, TXlog);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIALRATE);
  gps.begin(SERIALRATE);
  logger.begin(SERIALRATE);
  Serial.println("beginning");
} 

void loop() {
  // put your main code here, to run repeatedly:
  
}
