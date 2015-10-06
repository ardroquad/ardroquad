#include <Arduino.h>
#include <Wire.h>
#include "c_LED.h"
#include "c_sensor_pressure_BMP.h"

c_LED LED;
c_sensor_pressure_BMP BMP;

void setup() {
  Serial.begin(115200);
  Wire.begin(); 
  delay(1000);
  BMP.initialize();
}

void loop() {
  Serial.println(BMP.sensor_id());
  Serial.println(BMP.diagnostic_data());

  while (true) {
    LED.on();
    delay(200);
    LED.off();
    delay(200);
  }
}

