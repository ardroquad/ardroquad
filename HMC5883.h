#ifndef _HMC5883L_h_
#define _HMC5883L_h_

#include <Arduino.h>
#include "magnetometer.h"

namespace sensors {
namespace orientation {
namespace magnetometer {

namespace MPU6050 {
  
static const uint8_t __I2C_address = 0x68;
static const uint8_t __register_user_control = 0x6A;
static const uint8_t __value_user_control = 0x0;
static const uint8_t __register_interruption_pin_config = 0x37;
static const uint8_t __value_interruption_pin_config = 0x2;
static const uint8_t __register_pwr_mgmt_1 = 0x6B;
static const uint8_t __value_pwr_mgmt_1 = 0x0;
void bypass_init();

}

class HMC5883:
public magnetometer {
private:
  static const char* __id;
  static const uint8_t __I2C_address = 0x1E;
  static const uint8_t __register_mode = 0x2;
  static const uint8_t __value_mode = 0x0;
  static const uint8_t __register_X = 0x3;
  static const uint8_t __register_Y = 0x5;
  static const uint8_t __register_Z = 0x7;
public:
  virtual void initialize();
  virtual const char* id() const;
  virtual void update();
};

}
}
}

#endif
