#include <Arduino.h>
#include "I2C.h"

namespace I2C {
  void write_register(const uint8_t I2C_address, const uint8_t register_address, const uint8_t value) {
    Wire.beginTransmission(I2C_address);
    Wire.write(register_address);
    Wire.write(value);
    Wire.endTransmission();
  }
}
