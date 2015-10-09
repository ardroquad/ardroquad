#include <Arduino.h>
#include "I2C.h"
#include "MPU6050HMC5883L.h"

namespace sensors {
namespace orientation {
namespace magnetometer {

const char* MPU6050HMC5883L::__id = "MPU6050HMC5883L/magnetometer";

MPU6050HMC5883L::MPU6050HMC5883L() {
}

void MPU6050HMC5883L::initialize() {
  I2C::write_8(__I2C_address, __register_user_control, __value_user_control);
  I2C::write_8(__I2C_address, __register_interruption_pin_config, __value_interruption_pin_config);
  I2C::write_8(__I2C_address, __register_I2C_master_control, __value_I2C_master_control);
  I2C::write_8(__I2C_address, __register_I2C_slave0_address, __value_I2C_slave0_address);
  I2C::write_8(__I2C_address, __register_I2C_slave0_register, __value_I2C_slave0_register);
  I2C::write_8(__I2C_address, __register_I2C_slave0_control, __value_I2C_slave0_control);
}

const char* MPU6050HMC5883L::id() const {
  return __id;
}

void MPU6050HMC5883L::update() {
  I2C::read_16(__I2C_address, __register_X, _values.X);
  I2C::read_16(__I2C_address, __register_Y, _values.Y);
  I2C::read_16(__I2C_address, __register_Z, _values.Z);
}

}
}
}
