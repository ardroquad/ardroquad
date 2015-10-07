#include <Arduino.h>
#include <Wire.h>
#include "LED.h"
#include "BMP_085_180.h"

sensors::pressure::BMP_085_180 pressure;
controls::LED LED;

void setup() {
  Serial.begin(115200);
  Wire.begin(); 
  delay(5000);
  pressure.initialize();
}

void loop() {
  while (true) {
    Serial.println(pressure.diagnostic_data());
    pressure.force_temperature_update();
    LED.on();
    delay(500);
    LED.off();
    delay(500);
  }
}

