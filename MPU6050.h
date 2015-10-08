#ifndef _MPU6050_h_
#define _MPU6050_h_

#include <Arduino.h>
#include "accelerometer.h"
#include "gyroscope.h"

namespace sensors {
namespace orientation {
namespace accelerometer {

class MPU6050:
public accelerometer {
private:
  static const char* __id;
  static const uint8_t __I2C_address = 0x68;
  static const uint8_t __register_accelerometer_config = 0x6B;
  static const uint8_t __value_accelerometer_config = 0x2;
  static const uint8_t __register_DLPF_config = 0x1a;
  static const uint8_t __value_DLPF_config = 0x0;
  static const uint8_t __register_X = 0x3B;
  static const uint8_t __register_Y = 0x3D;
  static const uint8_t __register_Z = 0x3F;

public:
  MPU6050();
  virtual void initialize();
  virtual const char* id() const;
  virtual void update();
};

}
namespace gyroscope {

class MPU6050: 
public gyroscope {
private:
  static const char* __id;
  static const uint8_t __I2C_address = 0x68;
  static const uint8_t __register_pwr_mgmt_1 = 0x6B;
  static const uint8_t __reset_pwr_mgmt_1 = 0x80;
  static const uint32_t __delay_reset_pwr_mgmt_1 = 50;
  static const uint8_t __init_pwr_mgmt_1 = 0x3;
  static const uint8_t __register_DLPF_config = 0x1a;
  static const uint8_t __value_DLPF_config = 0x0;
  static const uint8_t __register_gyroscope_config = 0x1b;
  static const uint8_t __value_gyroscope_config = 0x18;
  static const uint8_t __register_X = 0x43;
  static const uint8_t __register_Y = 0x45;
  static const uint8_t __register_Z = 0x47;
public:
  MPU6050();
  virtual void initialize();
  virtual const char* id() const;
  virtual void update();
};

}
}
}

#endif
