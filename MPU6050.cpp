#include <Arduino.h>
#include "I2C.h"
#include "MPU6050.h"

namespace sensor {
namespace orientation {
namespace accelerometer {

const char* MPU6050::__id = "MPU6050";
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

const String MPU6050::id() const {
  String s;
  s += accelerometer::id(); s += id_divider(); s += __id;
  return s;
}

void MPU6050::update() {
  I2C::read_3x16(__I2C_address, __register_XYZ, _values.X, _values.Y, _values.Z);
  correct();
  _g.X = (float)_values.X / (float)32767 * (float)__full_scale_ranges[__full_scale_range].max_g;
  _g.Y = (float)_values.Y / (float)32767 * (float)__full_scale_ranges[__full_scale_range].max_g;
  _g.Z = (float)_values.Z / (float)32767 * (float)__full_scale_ranges[__full_scale_range].max_g;
  accelerometer::update();
}

}
namespace gyroscope {

const char* MPU6050::__id = "MPU6050";
const MPU6050::__full_scale_range_struct MPU6050::__full_scale_ranges[] = {
  {0x0, 250},
  {0x8, 500},
  {0x10, 1000},
  {0x18, 2000}
};

MPU6050::MPU6050() {
}

void MPU6050::initialize() {
  I2C::write_8(__I2C_address, __register_gyroscope_config, __value_gyroscope_config);
  I2C::write_8(__I2C_address, __register_DLPF_config, __value_DLPF_config);
  I2C::write_8(__I2C_address, __register_pwr_mgmt_1, __value_pwr_mgmt_1);
}

const String MPU6050::id() const {
  String s;
  s += gyroscope::id(); s += id_divider(); s += __id;
  return s;
}

void MPU6050::update() {
  I2C::read_3x16(__I2C_address, __register_XYZ, _values.X, _values.Y, _values.Z);
  correct();
  _dps.X = (float)_values.X / (float)32767 * (float)__full_scale_ranges[__full_scale_range].max_degrees_per_second;
  _dps.Y = (float)_values.Y / (float)32767 * (float)__full_scale_ranges[__full_scale_range].max_degrees_per_second;
  _dps.Z = (float)_values.Z / (float)32767 * (float)__full_scale_ranges[__full_scale_range].max_degrees_per_second;
}

}
}
}
