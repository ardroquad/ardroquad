#include <Arduino.h>
#include <Wire.h>
#include "c_LED.h"
#include "c_sensor_pressure_BMP.h"

sensors::pressure::c_BMP pressure;
controls::c_LED LED;

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

