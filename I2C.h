#ifndef _I2C_h_
#define _I2C_h_

#include <Wire.h>

namespace I2C {
  void write_register(const uint8_t I2C_address, const uint8_t register_address, const uint8_t value);
}

#endif



