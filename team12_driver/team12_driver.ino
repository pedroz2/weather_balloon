<<<<<<< HEAD
#include <Arduino.h>
#include <GPS.h>
#include <B57164.h>
#include <TMP36.h>
#include <HIH4030.h>
#include <MPX4115.h>
#include <ADXL335.h>
#include <MPU.h>
#include <BMP.h>



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
GPS gps(GPSrx, GPStx);
HIH4030 hih4030(HIH4030_pin);
MPX4115 mpx4115(MPX4115_pin);
B57164 b57164(B57164_pin);
ADXL335 adxl335(ADXL335_Xpin, ADXL335_Ypin, ADXL335_Zpin);
MPU mpu;
BMP bmp;

void setup() {
  Serial.begin(SERIALRATE);
  Serial.println("ENGR 100 -- TEAM 12 -- BEGIN DATA");
  Serial.println("TIME, HIH4030, MPX4115, B57164, ADXL335_X_axis, ADXL335_Y_axis, ADXL335_Z_axis, GPS, MPU, BMP");  

  // i2c sensors
  mpu.begin();
  bmp.begin();
  //note gps should always be initialized last
  //gps.begin(SERIALRATE);
} 

void loop() {
  unsigned long int currTime = millis()/1000;

  Serial.print(currTime);
  Serial.print(",");
  // Serial.print(hih4030.readCalibrated());
  // Serial.print(",");
  // Serial.print(mpx4115.readCalibrated());
  // Serial.print(",");
  // Serial.print(b57164.readCalibrated());
  // Serial.print(",");
  // Serial.print(adxl335.readCalibratedX());
  // Serial.print(",");
  // Serial.print(adxl335.readCalibratedY());
  // Serial.print(",");
  // Serial.print(adxl335.readCalibratedZ());
  // Serial.print(",");
  // Serial.print(gps.readGPSInfo());
  // Serial.print(",");
  // mpu.printAcc();
  // Serial.print(",");
  // mpu.printGyro();
  // Serial.print(",");
  bmp.printAllData();
  Serial.print(",");
  Serial.println();

  delay(1000);
}
=======
#include <Arduino.h>
#include <GPS.h>
#include <B57164.h>
#include <TMP36.h>
#include <HIH4030.h>
#include <MPX4115.h>
#include <ADXL335.h>
#include <MPU.h>
#include <BMP.h>

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
GPS gps(GPSrx, GPStx);
HIH4030 hih4030(HIH4030_pin);
MPX4115 mpx4115(MPX4115_pin);
B57164 b57164(B57164_pin);
ADXL335 adxl335(ADXL335_Xpin, ADXL335_Ypin, ADXL335_Zpin);
MPU mpu;
BMP bmp;

// Global Variable initialization
uint16_t humidity;
uint16_t pressure;
uint16_t temperature;
uint16_t mpu_acc[3];
uint16_t mpu_gyro[3];
uint16_t adxl_acc[3];
String gps;
uint16_t bmp_temperature;
uint16_t bmp_pressure;
uint16_t bmp_altitude;
bool isWindBad = false;
uint8_t count = 0;
uint16_t acc_threshold = 3;

void setup() {
  Serial.begin(SERIALRATE);
  Serial.println("ENGR 100 -- TEAM 12 -- BEGIN DATA");
  Serial.println("TIME, HIH4030, MPX4115, B57164, ADXL335_X_axis, ADXL335_Y_axis, ADXL335_Z_axis, GPS, MPU, BMP");  

  // i2c sensors
  mpu.begin();
  //note gps should always be initialized last
  //gps.begin(SERIALRATE);

  //initializes interrupts
  initInterrupts();
} 

void loop() {
  if (count > 1) {
    // update sensors at default 1Hz
    updateSensors();
    // prints sensor data
    printSensorData();
    count = 0; // resets counter for interrupts
    
    // updates isWindBad
    if (mpu_acc[0] > acc_threshold || mpu_acc[0] < -acc_threshold ||
    mpu_acc[1] > acc_threshold || mpu_acc[1] < -acc_threshold ||
    mpu_acc[2] > acc_threshold || mpu_acc[2] < -acc_threshold) {
      isWindBad = true;
    } else {
      isWindBad = false;
    }
  }
}

void printSensorData() {
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
  Serial.print(gps.readGPSInfo());
  Serial.print(",");
  mpu.printAcc();
  Serial.print(",");
  mpu.printGyro();
  Serial.print(",");
  bmp.printAllData();
  Serial.print(",");
  Serial.println();
}

void updateSensors() {
  // if winds aren't bad update all sensors
  if (!isWindBad) {
    humidity = hih4030.readCalibrated();
    pressure = mpx4115.readCalibrated();
    temperature = b57164.readCalibrated();
    bmp_temperature = bmp.readUncompTemp();
    bmp_pressure = bmp.readUncompPress();
    bmp_altitude = bmp.readAltitude();
  }
  mpu_acc = mpu.readAccelerometer();
  mpu_gyro = mpu.readGyroscope();
  adxl_acc[0] = adxl335.readCalibratedX();
  adxl_acc[1] = adxl335.readCalibratedY();
  adxl_acc[2] = adxl335.readCalibratedZ();
  gps = gps.readGPSInfo();
}

void initInterrupts() {
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  // set prescaler to ctc mode
  TCCR1B |= (1<<CS12);
  TCCR1B |= (1<<WGM12); // ensures we're in ctc mode
  TIMSK1 = 0;
  // enables comparison between timer and comparison register OCR1A
  TIMSK1 |= (1<<OCIE1A); 
  OCR1A = 31250;
  interrupts(); // renables interrupt
}

ISR(TIMER1_COMPA_vect) {
  if(isWindBad) {
    count+=2;
  } else {
    ++count;
  }
}
>>>>>>> 3ad5d66ab426cf8dae62909c98dc0aa67617b761
