#include <Arduino.h>
#include "I2C.h"
#include "MPU6050.h"

namespace sensors {
namespace orientation {
namespace accelerometer {

const char* MPU6050::__id = "MPU6050/accelerometer";
const MPU6050::__full_scale_range_struct MPU6050::__full_scale_ranges[] = {
  {0x0, 2},
  {0x8, 4},
  {0x10, 8},
  {0x18, 16}
};

void MPU6050::initialize() {
  I2C::write_8(__I2C_address, __register_accelerometer_config, __full_scale_ranges[__full_scale_range].value_accelerometer_config);
  I2C::write_8(__I2C_address, __register_DLPF_config, __value_DLPF_config);
  I2C::write_8(__I2C_address, __register_pwr_mgmt_1, __value_pwr_mgmt_1);
}

const char* MPU6050::id() const {
  return __id;
}

String MPU6050::debug_info() {
  String s;
  s += accelerometer::debug_info();
  s += ", Xg: "; s += _valuesG.X; s += ", Yg: "; s += _valuesG.Y; s += ", Zg: "; s += _valuesG.Z;
  return s;
}

void MPU6050::update() {
  I2C::read_16(__I2C_address, __register_X, _values.X);
  I2C::read_16(__I2C_address, __register_Y, _values.Y);
  I2C::read_16(__I2C_address, __register_Z, _values.Z);
  correct();
  _valuesG.X = (float)_values.X / (float)32767 * __full_scale_ranges[__full_scale_range].max_g;
  _valuesG.Y = (float)_values.Y / (float)32767 * __full_scale_ranges[__full_scale_range].max_g;
  _valuesG.Z = (float)_values.Z / (float)32767 * __full_scale_ranges[__full_scale_range].max_g;
}

}
namespace gyroscope {

const char* MPU6050::__id = "MPU6050/gyroscope";

MPU6050::MPU6050() {
}

void MPU6050::initialize() {
  I2C::write_8(__I2C_address, __register_gyroscope_config, __value_gyroscope_config);
  I2C::write_8(__I2C_address, __register_DLPF_config, __value_DLPF_config);
  I2C::write_8(__I2C_address, __register_pwr_mgmt_1, __value_pwr_mgmt_1);
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
