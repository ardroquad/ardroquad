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
IMU::Kalman _IMU(accelerometer, gyroscope);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  delay(1000);
  barometer.initialize();
  accelerometer.initialize();
  accelerometer.set_correction_Z(225);
  gyroscope.initialize();
  gyroscope.set_correction_X(17);
  gyroscope.set_correction_Y(-34);
  gyroscope.set_correction_Z(16);
  sensor::orientation::magnetometer::MPU6050::I2C_bypass_mode();
  magnetometer.initialize();
  sonar.initialize();
}

void loop() {
  uint64_t m = millis() / _millis;
  while (true) {
    if (m != millis() / _millis) {
      m = millis() / _millis;
      barometer.get_pressure();
      accelerometer.update();
      gyroscope.update();
      magnetometer.update();
      sonar.measure();
//      Serial.println(barometer.debug_info());
      Serial.println(accelerometer.debug_info());
//      Serial.println(gyroscope.debug_info());
//      Serial.println(magnetometer.debug_info());
//      Serial.println(sonar.debug_info());
    }
  }
}

