#include <Arduino.h>
#include <Wire.h>
#include "LED.h"
#include "BMP_085_180.h"

sensors::pressure::BMP_085_180 pressure;
controls::LED LED;

void setup() {
//  Serial.begin(115200);
  Wire.begin(); 
  delay(1000);
//  pressure.initialize();
}

void loop() {
  while (true) {
//    Serial.println(pressure.diagnostic_data());
//    pressure.get_pressure();
    LED.brightness(LED.max_brightness());
    delay(200);
    LED.on();
    delay(200);
    LED.off();
    delay(200);
    LED.on();
    delay(200);
    LED.off();
    delay(200);
    LED.brightness(0);
    LED.on();
    for (int i = 1; i <= LED.max_brightness(); ++i) {
      LED.brightness(i);
      delay(2);
    }
    for (int i = LED.max_brightness(); i >= 0; --i) {
      LED.brightness(i);
      delay(2);
    }
  }
}

