#include <Arduino.h>
#include "I2C.h"
#include "MPU6050.h"

namespace sensors {
namespace accelerometer {

MPU6050::MPU6050() {
}

void MPU6050::initialize() {
  I2C::write_8(__I2C_address, __register_accelerometer_config, __value_accelerometer_config);
}

String MPU6050::debug_info() {
  return "none";
}

void MPU6050::update() {
  I2C::read_16(__I2C_address, __register_X, _values.X);
  I2C::read_16(__I2C_address, __register_Y, _values.Y);
  I2C::read_16(__I2C_address, __register_Z, _values.Z);
}

}
}
