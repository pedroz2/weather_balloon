#include <Arduino.h>
#include <GPS.h>
#include <B57164.h>
#include <TMP36.h>
#include <HIH4030.h>
#include <MPX4115.h>
#include <ADXL335.h>
#include <mpu9250.h>
#include <bmp280.h>



//LOGGER AND SERIAL
const long SERIALRATE = 9600;
const int LOGGERrx = 7;
const int LOGGERtx = 8;
SoftwareSerial logger(LOGGERrx, LOGGERtx);

//ANALOG READ PINS
const int TMP36_pin = A0;            //temp -- NOT USED
const int HIH4030_pin = A0;          //humidity
const int MPX4115_pin = A7;          //pressure
const int B57164_pin = A6;           //thermister
const int ADXL335_Xpin = A1;          //X axis accelerometer
const int ADXL335_Ypin = A2;          //Y axis accelerometer
const int ADXL335_Zpin = A3;          //Z axis accelerometer

//I2C EXTRA SENSORS -- MUST USE PINS A4/A5
const int I2C_SDA = A4;
const int I2C_SCL = A5;

//GPS RX/TX
const int GPSrx = 3;            //gps recieving pin
const int GPStx = 2;            //gps transmitting pin

//SENSOR INTIALIZATION
//TMP36 tmp36(TMP36_pin); NOT USED
//GPS gps(GPSrx, GPStx);
HIH4030 hih4030(HIH4030_pin);
MPX4115 mpx4115(MPX4115_pin);
B57164 b57164(B57164_pin);
ADXL335 adxl335(ADXL335_Xpin, ADXL335_Ypin, ADXL335_Zpin);

void setup() {
  Serial.begin(SERIALRATE);
  Serial.println("ENGR 100 -- TEAM 12 -- BEGIN DATA");
  Serial.println("TIME, HIH4030, MPX4115, B57164, ADXL335_X_axis, ADXL335_Y_axis, ADXL335_Z_axis, GPS");  

  //note gps should always be initialized last
  //gps.begin(SERIALRATE);
} 

void loop() {
  unsigned long int currTime = millis()/1000;

  Serial.print(currTime);
  Serial.print(",");
  Serial.print(hih4030.readCalibrated());
  Serial.print(",");
  Serial.print(mpx4115.readCalibrated());
  Serial.print(",");
  Serial.print(b57164.readCalibrated());
  Serial.print(",");
  Serial.print(adxl335.readCalibratedX());
  Serial.print(",");
  Serial.print(adxl335.readCalibratedY());
  Serial.print(",");
  Serial.print(adxl335.readCalibratedZ());
  Serial.print(",");
  //Serial.print(gps.readGPSInfo());
  //Serial.print(",");
  Serial.println();

  delay(1000);
}
