#include <Arduino.h>
#include "I2C.h"
#include "MPU6050.h"

namespace sensors { namespace accelerometer {

MPU6050::MPU6050() {
}

void MPU6050::initialize() {
  I2C::write_8(__I2C_address, __register_accelerometer_config, __value_accelerometer_config);
}

}}


