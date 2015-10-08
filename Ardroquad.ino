#include <Arduino.h>
#include <Wire.h>
#include "LED.h"
#include "BMP180.h"
#include "MPU6050.h"

#define _DEBUG_

sensors::barometer::BMP180 barometer;
sensors::accelerometer::MPU6050 accelerometer;

void setup() {
  Serial.begin(115200);
  Wire.begin(); 
  delay(1000);
  barometer.initialize();
  accelerometer.initialize();
}

void loop() {
//  Serial.println(barometer.diagnostic_data());
//  barometer.get_pressure();
  accelerometer.update();
  Serial.print(accelerometer.X());
  Serial.print(" ");
  Serial.print(accelerometer.Y());
  Serial.print(" ");
  Serial.println(accelerometer.Z());
  delay(100);
}

