#include <Arduino.h>
#include "I2C.h"
#include "MPU6050HMC5883L.h"

namespace sensors {
namespace orientation {
namespace magnetometer {

const char* MPU6050HMC5883L::__id = "MPU6050_HMC5883L/magnetometer";

MPU6050HMC5883L::MPU6050HMC5883L() {
}

void MPU6050HMC5883L::initialize() {
  I2C::write_8(__I2C_address, __register_user_control, __value_user_control);
  I2C::write_8(__I2C_address, __register_interruption_pin_config, __value_interruption_pin_config);
  I2C::write_8(__I2C_address, __register_pwr_mgmt_1, __value_pwr_mgmt_1);
  I2C::write_8(__I2C_magnetometer_address, __register_mode, __value_mode);
}

const char* MPU6050HMC5883L::id() const {
  return __id;
}

void MPU6050HMC5883L::update() {
  I2C::read_16(__I2C_magnetometer_address, __register_X, _values.X);
  I2C::read_16(__I2C_magnetometer_address, __register_Y, _values.Y);
  I2C::read_16(__I2C_magnetometer_address, __register_Z, _values.Z);
}

}
}
}
