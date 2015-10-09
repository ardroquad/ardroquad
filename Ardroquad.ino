#include <Arduino.h>
#include <Wire.h>
#include "LED.h"
#include "BMP180.h"
#include "MPU6050.h"
#include "MPU6050HMC5883L.h"

#define _DEBUG_

sensors::barometer::BMP180 barometer;
sensors::orientation::accelerometer::MPU6050 accelerometer;
sensors::orientation::gyroscope::MPU6050 gyroscope;
sensors::orientation::magnetometer::MPU6050HMC5883L magnetometer;

void setup() {
  Serial.begin(115200);
  Wire.begin(); 
  delay(1000);
  barometer.initialize();
  accelerometer.initialize();
  gyroscope.initialize();
  magnetometer.initialize();
}

void loop() {
  barometer.get_pressure();
  accelerometer.update();
  gyroscope.update();
  magnetometer.update();
//  Serial.println(barometer.debug_info());
//  Serial.println(accelerometer.debug_info());
//  Serial.println(gyroscope.debug_info());
  Serial.println(magnetometer.debug_info());
  delay(500);
}

