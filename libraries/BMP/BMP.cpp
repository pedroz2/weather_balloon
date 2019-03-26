#include "BMP.h"

BMP::BMP(){
}

void BMP::begin() {
    Wire.begin();
    groupAddresses();
}

float BMP::readAltitude() {
    float altitude;

    float pressure = readPressure();
    pressure /= 100;
    
    altitude = 44330 * (1.0 - pow(pressure/p0, 0.1903));

    return altitude; 
}

float BMP::readPressure(){
    int64_t var1, var2, p;

    // Must be done first to get the t_fine variable set up
    readTemperature();

    int32_t adc_P = readToRegister(0xF7, 2);
    adc_P >>= 4;

    var1 = ((int64_t)t_fine) - 128000;
    var2 = var1 * var1 * (int64_t)_bmp280_calib.dig_P6;
    var2 = var2 + ((var1*(int64_t)_bmp280_calib.dig_P5)<<17);
    var2 = var2 + (((int64_t)_bmp280_calib.dig_P4)<<35);
    var1 = ((var1 * var1 * (int64_t)_bmp280_calib.dig_P3)>>8) +
        ((var1 * (int64_t)_bmp280_calib.dig_P2)<<12);
    var1 = (((((int64_t)1)<<47)+var1))*((int64_t)_bmp280_calib.dig_P1)>>33;

    if (var1 == 0) {
        return 0;  // avoid exception caused by division by zero
    }
    p = 1048576 - adc_P;
    p = (((p<<31) - var2)*3125) / var1;
    var1 = (((int64_t)_bmp280_calib.dig_P9) * (p>>13) * (p>>13)) >> 25;
    var2 = (((int64_t)_bmp280_calib.dig_P8) * p) >> 19;

    p = ((p + var1 + var2) >> 8) + (((int64_t)_bmp280_calib.dig_P7)<<4);
    return (float)p/256;
}

float BMP::readTemperature(){
  int32_t var1, var2;

  int32_t adc_T = read24(BMP280_REGISTER_TEMPDATA);
  adc_T >>= 4;

  var1  = ((((adc_T>>3) - ((int32_t)_bmp280_calib.dig_T1 <<1))) *
	   ((int32_t)_bmp280_calib.dig_T2)) >> 11;

  var2  = (((((adc_T>>4) - ((int32_t)_bmp280_calib.dig_T1)) *
	     ((adc_T>>4) - ((int32_t)_bmp280_calib.dig_T1))) >> 12) *
	   ((int32_t)_bmp280_calib.dig_T3)) >> 14;

  t_fine = var1 + var2;

  float T  = (t_fine * 5 + 128) >> 8;
  return T/100;
}

void BMP::readToRegisters(int code, int numBytes) {
    long value = 0;
    Wire.beginTransmission(BMP_ADDRESS);
    Wire.write(code);
    Wire.endTransmission();
    Wire.requestFrom(BMP_ADDRESS, numBytes);
    if (Wire.available() >= numBytes) {
        for (int i = 0; i < numBytes; i++) {
            value = (value <<8 ) | Wire.read();
        }
    }
    return value;
}

void BMP::groupAddresses() {
    dig_T1 = readToRegisters(0x88, 2);
    dig_T2 = readToRegisters(0x8A, 2);
    dig_T3 = readToRegisters(0x8C, 2);
    dig_P1 = readToRegisters(0x8E, 2);
    dig_P2 = readToRegisters(0x90, 2);
    dig_P3 = readToRegisters(0x92, 2);
    dig_P4 = readToRegisters(0x94, 2);
    dig_P5 = readToRegisters(0x96, 2);
    dig_P6 = readToRegisters(0x98, 2);
    dig_P7 = readToRegisters(0x9A, 2);
    dig_P8 = readToRegisters(0x9C, 2);
    dig_P9 = readToRegisters(0x9E, 2);
}


