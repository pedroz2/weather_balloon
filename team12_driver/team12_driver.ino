#include <b57164.h>
#include <Arduino.h>
#include <GPS.h>
#include <tmp36.h>
#include <hih4030.h>
#include <mpx4115.h>
#include <adxl335.h>
#include <mpu9250.h>
#include <bmp280.h>



//LOGGER AND SERIAL
const long SERIALRATE = 9600;
const int LOGGERrx = 7;
const int LOGGERtx = 8;
SoftwareSerial logger(LOGGERrx, LOGGERtx);

//ANALOG READ PINS
const int TMP36_pin = A6;            //temp
const int HIH4030_pin = A7;          //humidity
const int MPX4115_pin = A4;          //pressure
const int B57164_pin = A5;           //thermister
const int ADXL335_Xpin = A1;          //X axis accelerometer
const int ADXL335_Ypin = A2;          //Y axis accelerometer
const int ADXL335_Zpin = A3;          //Z axis accelerometer

//I2C EXTRA SENSORS
const int BMP280_I2C = 0;
const int MPU9250_I2C = 0;

//GPS RX/TX
const int GPSrx = 3;            //gps recieving pin
const int GPStx = 2;            //gps transmitting pin

//SENSOR INTIALIZATION
GPS gps(GPSrx, GPStx);
TMP36 tmp36(TMP36_pin);
HIH4030 hih4030(HIH4030_pin);
MPX4115 mpx4115(MPX4115_pin);
B57164 b57164(B57164_pin);
ADXL335 adxl335(ADXL335_Xpin, ADXL335_Ypin, ADXL335_Zpin);

void setup() {
  // put your setup code here, to run once:
  gps.begin(SERIALRATE);


  logger.begin(SERIALRATE);
  logger.println("ENGR 100 -- TEAM 12 -- BEGIN DATA");
  logger.println("TIME, TMP36, HIH4030, MPX4115, B57164, ADXL335_X_axis, ADXL335_Y_axis, ADXL335_Z_axis, GPS");  

  Serial.begin(SERIALRATE);
  Serial.println("ENGR 100 -- TEAM 12 -- BEGIN DATA");
  Serial.println("TIME, TMP36, HIH4030, MPX4115, B57164, ADXL335_X_axis, ADXL335_Y_axis, ADXL335_Z_axis, GPS");  
} 

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long int currTime = second();

  logger.print(currTime);
  logger.print(",");
  logger.print(TMP36.readCalibrated());
  logger.print(",");
  logger.print(HIH4030.readCalibrated());
  logger.print(",");
  logger.print(MPX4115.readCalibrated());
  logger.print(",");
  logger.print(B57164.readCalibrated());
  logger.print(",");
  logger.print(ADXL335.readCalibratedX());
  logger.print(",");
  logger.print(ADXL335.readCalibratedY());
  logger.print(",");
  logger.print(ADXL335.readCalibratedZ());
  logger.print(",");
  logger.print(GPS.returnGPSInfo());
  logger.println(",");

  Serial.print(currTime);
  Serial.print(",");
  Serial.print(TMP36.readCalibrated());
  Serial.print(",");
  Serial.print(HIH4030.readCalibrated());
  Serial.print(",");
  Serial.print(MPX4115.readCalibrated());
  Serial.print(",");
  Serial.print(B57164.readCalibrated());
  Serial.print(",");
  Serial.print(ADXL335.readCalibratedX());
  Serial.print(",");
  Serial.print(ADXL335.readCalibratedY());
  Serial.print(",");
  Serial.print(ADXL335.readCalibratedZ());
  Serial.print(",");
  Serial.print(GPS.returnGPSInfo());
  Serial.println(",");
}


/*

Arduino: 1.8.8 (Windows 10), Board: "Arduino Nano, ATmega328P (Old Bootloader)"

team12_driver:38:1: error: 'TMP36' does not name a type

 TMP36 tmp36(TMP36_pin);

 ^

team12_driver:39:1: error: 'HIH4030' does not name a type

 HIH4030 hih4030(HIH4030_pin);

 ^

team12_driver:40:1: error: 'MPX4115' does not name a type

 MPX4115 mpx4115(MPX4115_pin);

 ^

team12_driver:41:1: error: 'B57164' does not name a type

 B57164 b57164(B57164_pin);

 ^

team12_driver:42:1: error: 'ADXL335' does not name a type

 ADXL335 adxl335(ADXL335_Xpin, ADXL335_Ypin, ADXL335_Zpin);

 ^

C:\cpp\team12-engr100\team12_driver\team12_driver.ino: In function 'void loop()':

team12_driver:60:39: error: 'second' was not declared in this scope

   unsigned long int currTime = second();

                                       ^

team12_driver:64:16: error: 'TMP36' was not declared in this scope

   logger.print(TMP36.readCalibrated());

                ^

team12_driver:66:16: error: 'HIH4030' was not declared in this scope

   logger.print(HIH4030.readCalibrated());

                ^

team12_driver:68:16: error: 'MPX4115' was not declared in this scope

   logger.print(MPX4115.readCalibrated());

                ^

team12_driver:70:16: error: 'B57164' was not declared in this scope

   logger.print(B57164.readCalibrated());

                ^

team12_driver:72:16: error: 'ADXL335' was not declared in this scope

   logger.print(ADXL335.readCalibratedX());

                ^

team12_driver:78:19: error: expected primary-expression before '.' token

   logger.print(GPS.returnGPSInfo());

                   ^

team12_driver:97:19: error: expected primary-expression before '.' token

   Serial.print(GPS.returnGPSInfo());

                   ^

exit status 1
'TMP36' does not name a type

This report would have more information with
"Show verbose output during compilation"
option enabled in File -> Preferences.

*/