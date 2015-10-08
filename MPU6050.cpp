#include <Arduino.h>
#include "I2C.h"
#include "MPU6050.h"

namespace sensors {
namespace orientation {
namespace accelerometer {

const char* MPU6050::__id = "MPU6050/accelerometer";

MPU6050::MPU6050() {
}

void MPU6050::initialize() {
  I2C::write_8(__I2C_address, __register_accelerometer_config, __value_accelerometer_config);
  I2C::write_8(__I2C_address, __register_DLPF_config, __value_DLPF_config);
}

const char* MPU6050::id() const {
  return __id;
}

void MPU6050::update() {
  I2C::read_16(__I2C_address, __register_X, _values.X);
  I2C::read_16(__I2C_address, __register_Y, _values.Y);
  I2C::read_16(__I2C_address, __register_Z, _values.Z);
}

}
namespace gyroscope {

const char* MPU6050::__id = "MPU6050/gyroscope";

MPU6050::MPU6050() {
}

void MPU6050::initialize() {
  I2C::write_8(__I2C_address, __register_pwr_mgmt_1, __reset_pwr_mgmt_1);
  delay(__delay_reset_pwr_mgmt_1);
  I2C::write_8(__I2C_address, __register_pwr_mgmt_1, __init_pwr_mgmt_1);
  I2C::write_8(__I2C_address, __register_DLPF_config, __value_DLPF_config);
  I2C::write_8(__I2C_address, __register_gyroscope_config, __value_gyroscope_config);
}

const char* MPU6050::id() const {
  return __id;
}

void MPU6050::update() {
  I2C::read_16(__I2C_address, __register_X, _values.X);
  I2C::read_16(__I2C_address, __register_Y, _values.Y);
  I2C::read_16(__I2C_address, __register_Z, _values.Z);
}

}
}
}
