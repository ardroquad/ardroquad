#include <Arduino.h>
#include <Wire.h>
#include "LED.h"
#include "BMP180.h"
#include "MPU6050.h"
#include "HMC5883.h"
#include "HC_SR04.h"
#include "IMU.h"

#define _DEBUG_

const uint32_t _millis = 500;

sensor::barometer::BMP180 barometer;
sensor::orientation::accelerometer::MPU6050 accelerometer;
sensor::orientation::gyroscope::MPU6050 gyroscope;
sensor::orientation::magnetometer::HMC5883 magnetometer;
sensor::sonar::HC_SR04 sonar;
stabilization::IMU::Kalman IMU(accelerometer, gyroscope, magnetometer);
uint64_t m = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  delay(1000);
  barometer.initialize();
  accelerometer.initialize();
  accelerometer.set_correction(0, 0, 225);
  gyroscope.initialize();
  gyroscope.set_correction(17, -34, 16);
  sensor::orientation::magnetometer::MPU6050::I2C_bypass_mode();
  magnetometer.initialize();
  sonar.initialize();
}

void loop() {
  uint64_t tm = millis();
  if (m != tm) {
    barometer.measure();
    sonar.measure();
    IMU.iteration();
  }
  if (tm / _millis != millis() / _millis) {
//    Serial.println(barometer.debug_info());
//    Serial.println(accelerometer.debug_info());
//    Serial.println(gyroscope.debug_info());
//    Serial.println(magnetometer.debug_info());
//    Serial.println(sonar.debug_info());
    Serial.println(IMU.debug_info());
  }
  m = tm;
}

