#include <Arduino.h>
#include "I2C.h"
#include "HMC5883.h"

namespace sensor {
namespace orientation {
namespace magnetometer {
namespace MPU6050 {

void I2C_bypass_mode() {
  I2C::write_8(__I2C_address, __register_user_control, __value_user_control);
  I2C::write_8(__I2C_address, __register_interruption_pin_config, __value_interruption_pin_config);
  I2C::write_8(__I2C_address, __register_pwr_mgmt_1, __value_pwr_mgmt_1);
}

}

const char* HMC5883::__id = "MPU6050_HMC5883L/magnetometer";

void HMC5883::initialize() {
  I2C::write_8(__I2C_address, __register_configuration_a, __value_configuration_a);
  I2C::write_8(__I2C_address, __register_mode, __value_mode);
}

const String HMC5883::id() const {
  String s;

  s += magnetometer::id(); s += sensor::id_divider(); s += __id;
  return s;
}

void HMC5883::measure() {
  I2C::read_3x16(__I2C_address, __register_XYZ, _values.X, _values.Z, _values.Y);
}

}
}
}
