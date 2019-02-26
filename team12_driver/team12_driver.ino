#include <Arduino.h>
#include <GPS.h>

//LOGGER AND SERIAL
const long SERIALRATE = 9600;
const int LOGGERrx = 7;
const int LOGGERtx = 8;
SoftwareSerial logger(LOGGERrx, LOGGERtx);

//ANALOG READ PINS
const int TMP36_pin = 0;            //temp
const int HIH4030_pin = 0;          //humidity
const int MPX4115_pin = 0;          //pressure
const int B57164_pin = 0;           //thermister
const int ADXL335_pin = 0;          //3axis accelerometer

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
ADXL335 adxl335(ADXL335_pin);

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
