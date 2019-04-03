#include <Arduino.h>
#include <GPS.h>
#include <B57164.h>
#include <TMP36.h>
#include <HIH4030.h>
#include <MPX4115.h>
#include <ADXL335.h>
#include <MPU.h>
#include<Adafruit_BMP280.h>

//LOGGER AND SERIAL 
const long SERIALRATE = 9600;
const int OPENLOG_TXPIN = 10;
const int OPENLOG_RXPIN = 9;
SoftwareSerial logger(OPENLOG_TXPIN, OPENLOG_RXPIN);

//ANALOG READ PINS
const int HIH4030_pin = A7;          //humidity
const int MPX4115_pin = A6;          //pressure
const int B57164_pin = A3;           //thermister
const int ADXL335_Xpin = A0;          //X axis accelerometer
const int ADXL335_Ypin = A1;          //Y axis accelerometer
const int ADXL335_Zpin = A2;          //Z axis accelerometer

//I2C EXTRA SENSORS -- MUST USE PINS A4/A5
const int I2C_SDA = A4;
const int I2C_SCL = A5;

//GPS RX/TX
const int GPSrx = 11;            //gps recieving pin
const int GPStx = 12;            //gps transmitting pin

//SENSOR INTIALIZATION
//TMP36 tmp36(TMP36_pin); NOT USED
HIH4030 hih4030(HIH4030_pin);
MPX4115 mpx4115(MPX4115_pin);
B57164 b57164(B57164_pin);
ADXL335 adxl335(ADXL335_Xpin, ADXL335_Ypin, ADXL335_Zpin);
GPS gps(GPSrx, GPStx);
MPU mpu;
Adafruit_BMP280 bmp;

// Global Variable initialization
double humidity = 0;
double pressure = 0;
double temperature = 0;
double* mpu_acc;
double* mpu_gyro;
double* mpu_mag;
double *adxl_acc = new double[3];
String gps_data = "";
double bmp_temperature=0;
double bmp_pressure=0;
double bmp_altitude=0;
volatile bool isWindBad = false;
volatile uint8_t count = 0;
int acc_threshold = 3;
unsigned long currTime;

void setup() {
  logger.begin(SERIALRATE);
  logger.println("Time, x, y, z, temperature, BMP_altitude, BMP_temperature, BMP_pressure, Humidity, MPU_acc_x, MPU_acc_y, MPU_acc_z, GYRO_x, GYRO_y, GYRO_z, MPX_pressure, GPS");
  Serial.begin(SERIALRATE);
  Serial.println("ENGR 100 -- TEAM 12 -- BEGIN DATA");
  Serial.println("Time, x, y, z, temperature, BMP_altitude, BMP_temperature, BMP_pressure, Humidity, MPU_acc_x, MPU_acc_y, MPU_acc_z, GYRO_x, GYRO_y, GYRO_z, MPX_pressure, GPS"); 

  // i2c sensors
  //note gps should always be initialized last

  //initializes interrupts
  initInterrupts();
  mpu.begin();
  bmp.begin();
  gps.begin(SERIALRATE);
} 

void loop() {
  currTime = millis();
  if (count > 1) {
    // update sensors at default 1Hz
    updateSensors();
    // prints sensor data
    printSensorData();
    // log sensor data
    logSensorData();
    count = 0; // resets counter for interrupts
    
    // updates isWindBad
  //  if (mpu_acc[0] > acc_threshold || mpu_acc[0] < -acc_threshold ||
  //    mpu_acc[1] > acc_threshold || mpu_acc[1] < -acc_threshold ||
  //    mpu_acc[2] > acc_threshold || mpu_acc[2] < -acc_threshold) {
  //    isWindBad = true;
  //  } else {
  //    isWindBad = false;
  //  }
  }
}

void logSensorData() {
  logger.print(currTime);
  logger.print(",");
  logger.print(adxl_acc[0]);
  logger.print(",");
  logger.print(adxl_acc[1]);
  logger.print(",");
  logger.print(adxl_acc[2]);
  logger.print(",");
  logger.print(temperature);
  logger.print(",");
  logger.print(bmp_altitude);
  logger.print(",");
  logger.print(bmp_temperature);
  logger.print(",");
  logger.print(bmp_pressure);
  logger.print(",");
  logger.print(humidity);
  logger.print(",");
  logger.print(mpu_acc[0]);
  logger.print(",");
  logger.print(mpu_acc[1]);
  logger.print(",");
  logger.print(mpu_acc[2]);
  logger.print(",");
  logger.print(mpu_gyro[0]);
  logger.print(",");
  logger.print(mpu_gyro[1]);
  logger.print(",");
  logger.print(mpu_gyro[2]);
  logger.print(",");
  logger.print(pressure);
  logger.print(",");
  logger.print(gps_data);
  logger.println();
}

void printSensorData() {
  Serial.print(currTime);
  Serial.print(",");
  Serial.print(adxl_acc[0]);
  Serial.print(",");
  Serial.print(adxl_acc[1]);
  Serial.print(",");
  Serial.print(adxl_acc[2]);
  Serial.print(",");
  Serial.print(temperature);
  Serial.print(",");
  Serial.print(bmp_altitude);
  Serial.print(",");
  Serial.print(bmp_temperature);
  Serial.print(",");
  Serial.print(bmp_pressure);
  Serial.print(",");
  Serial.print(humidity);
  Serial.print(",");
  Serial.print(mpu_acc[0]);
  Serial.print(",");
  Serial.print(mpu_acc[1]);
  Serial.print(",");
  Serial.print(mpu_acc[2]);
  Serial.print(",");
  Serial.print(mpu_gyro[0]);
  Serial.print(",");
  Serial.print(mpu_gyro[1]);
  Serial.print(",");
  Serial.print(mpu_gyro[2]);
  Serial.print(",");
  Serial.print(pressure);
  Serial.print(",");
  Serial.print(gps_data);
  Serial.println();
//  Serial.print(mpu_mag[0]);
//  Serial.print(",");
//  Serial.print(mpu_mag[1]);
//  Serial.print(",");
//  Serial.print(mpu_mag[2]);
//  Serial.println(",");
}

void updateSensors() {
  // if winds aren't bad update all sensors
// if (!isWindBad) {
     humidity = hih4030.readCalibrated();
     pressure = mpx4115.readCalibrated();
     temperature = b57164.readCalibrated();
     bmp_temperature = bmp.readTemperature();
     bmp_pressure = bmp.readPressure();
     bmp_altitude = bmp.readAltitude(1025);
     gps_data = gps.readGPSInfo();
 //}
   mpu_acc = mpu.readAccelerometer();
   mpu_gyro = mpu.readGyroscope();
   mpu_mag = mpu.readMagnetometer();
   adxl_acc[0] = adxl335.readCalibratedX();
   adxl_acc[1] = adxl335.readCalibratedY();
   adxl_acc[2] = adxl335.readCalibratedZ();
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
