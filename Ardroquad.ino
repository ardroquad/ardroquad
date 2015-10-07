#include <Arduino.h>
#include <Wire.h>
#include "LED.h"
#include "BMP180.h"

#define _DEBUG_

sensors::pressure::BMP180 pressure;
controls::LED LED;

void setup() {
  Serial.begin(115200);
  Wire.begin(); 
  delay(1000);
  pressure.initialize();
}

void loop() {
  Serial.println(pressure.diagnostic_data());
  pressure.get_pressure();
  delay(1000);
}

