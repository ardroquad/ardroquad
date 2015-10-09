#ifndef _MPU6050HMC5883L_h_
#define _MPU6050HMC5883L_h_

#include <Arduino.h>
#include "magnetometer.h"

namespace sensors {
namespace orientation {
namespace magnetometer {

class MPU6050HMC5883L:
public magnetometer {
private:
  static const char* __id;
  static const uint8_t __I2C_address = 0x68;
  static const uint8_t __I2C_magnetometer_address = 0x1E;
  static const uint8_t __register_user_control = 0x6A;
  static const uint8_t __value_user_control = 0x20;
  static const uint8_t __register_interruption_pin_config = 0x37;
  static const uint8_t __value_interruption_pin_config = 0x00;
  static const uint8_t __register_I2C_master_control = 0x24;
  static const uint8_t __value_I2C_master_control = 0x0D;
  static const uint8_t __register_I2C_slave0_address = 0x25;
  static const uint8_t __value_I2C_slave0_address = 0x80 | __I2C_magnetometer_address;
  static const uint8_t __register_I2C_slave0_register = 0x26;
  static const uint8_t __value_I2C_slave0_register = 0x03;
  static const uint8_t __register_I2C_slave0_control = 0x27;
  static const uint8_t __value_I2C_slave0_control = 0x86;
  static const uint8_t __register_X = 0x49;
  static const uint8_t __register_Y = 0x4B;
  static const uint8_t __register_Z = 0x4D;
public:
  MPU6050HMC5883L();
  virtual void initialize();
  virtual const char* id() const;
  virtual void update();
};

}
}
}

#endif
