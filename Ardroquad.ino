#include <Arduino.h>
#include <Wire.h>
#include "LED.h"
#include "BMP180.h"

#define _DEBUG_

sensors::barometer::BMP180 barometer;
controls::LED LED;

void setup() {
  Serial.begin(115200);
  Wire.begin(); 
  delay(1000);
  barometer.initialize();
}

void loop() {
  Serial.println(barometer.diagnostic_data());
  barometer.get_pressure();
  delay(1000);
}

