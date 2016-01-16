#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>
#include "LED.h"
#include "BMP180.h"
#include "MPU6050.h"
#include "HMC5883.h"
#include "HC_SR04.h"
#include "IMU.h"

#define _DEBUG_

SoftwareSerial CLI(19, 18);
sensor::barometer::BMP180 barometer;
sensor::orientation::accelerometer::MPU6050 accelerometer;
sensor::orientation::gyroscope::MPU6050 gyroscope;
sensor::orientation::magnetometer::HMC5883 magnetometer;
sensor::sonar::HC_SR04 sonar;
stabilization::IMU::Kalman IMU(accelerometer, gyroscope, magnetometer);
const uint32_t _millis = 600;
uint64_t _millis1 = 0;
uint64_t _millis2 = 0;

void setup() {
  CLI.begin(9600);
  Wire.begin();
  delay(1000);
  barometer.initialize();
  accelerometer.initialize();
  accelerometer.set_correction(0, 0, 0);
  gyroscope.initialize();
  gyroscope.calibrate();
  sensor::orientation::magnetometer::MPU6050::I2C_bypass_mode();
  magnetometer.initialize();
  sonar.initialize();
  CLI.println();
  CLI.println();
  CLI.println("Calibration...");
  magnetometer.calibrate();
  CLI.println(magnetometer.calibrate_info());
}

void loop() {
  uint64_t tm = millis();
  if (tm - _millis2 >= 1) {
    barometer.measure();
    accelerometer.measure();
    gyroscope.measure();
    magnetometer.measure();
    sonar.measure();
    IMU.iteration();
    _millis2 = tm;
  }
  if (_millis1 / _millis != tm / _millis) {
//    CLI.println(barometer.debug_info());
//    CLI.println(accelerometer.debug_info());
//    CLI.println(gyroscope.debug_info());
//    CLI.println(magnetometer.debug_info());
//    CLI.println(sonar.debug_info());
    CLI.println(IMU.debug_info());
//    String s;
//    s += "X(c): "; s += IMU.X_corrected; s += ", Y(c): "; s += IMU.Y_corrected; s += ", Z(c): "; s += IMU.Z_corrected;
//    CLI.println(s);
    _millis1 = tm;
  }
}

