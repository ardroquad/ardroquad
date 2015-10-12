#include <Arduino.h>
#include <Wire.h>
#include "LED.h"
#include "BMP180.h"
#include "MPU6050.h"
#include "HMC5883.h"
#include "IMU.h"

#define _DEBUG_

sensors::barometer::BMP180 barometer;
sensors::orientation::accelerometer::MPU6050 accelerometer;
sensors::orientation::gyroscope::MPU6050 gyroscope;
sensors::orientation::magnetometer::HMC5883 magnetometer;
IMU _IMU(accelerometer, gyroscope);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  delay(1000);
  barometer.initialize();
  accelerometer.initialize();
  accelerometer.set_correction_Z(225);
  gyroscope.initialize();
  sensors::orientation::magnetometer::MPU6050::I2C_bypass_mode();
  magnetometer.initialize();
}

void loop() {
  barometer.get_pressure();
  accelerometer.update();
  gyroscope.update();
  magnetometer.update();
//  Serial.println(barometer.debug_info());
//  Serial.println(accelerometer.debug_info());
  Serial.println(gyroscope.debug_info());
//  Serial.println(magnetometer.debug_info());
  delay(500);
}

