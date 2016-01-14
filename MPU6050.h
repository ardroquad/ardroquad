#ifndef _MPU6050_h_
#define _MPU6050_h_

#include <Arduino.h>
#include "accelerometer.h"
#include "gyroscope.h"

namespace sensor {
namespace orientation {
namespace accelerometer {

class MPU6050:
public accelerometer {
private:
  static const struct __full_scale_range_struct {
    uint8_t value_accelerometer_config;
    uint8_t max_g;
  } __full_scale_ranges[];
  static const char* __id;
  static const uint8_t __I2C_address = 0x68;
  static const uint8_t __full_scale_range = 2;
  static const uint8_t __register_accelerometer_config = 0x1c;
  static const uint8_t __register_DLPF_config = 0x1a;
  static const uint8_t __value_DLPF_config = 0x0;
  static const uint8_t __register_pwr_mgmt_1 = 0x6B;
  static const uint8_t __value_pwr_mgmt_1 = 0x0;
  static const uint8_t __register_XYZ = 0x3B;
public:
  virtual void initialize();
  virtual const String id() const;
  virtual void measure();
};

}
namespace gyroscope {

class MPU6050: 
public gyroscope {
private:
  static const struct __full_scale_range_struct {
    uint8_t value_gyroscope_config;
    uint16_t max_degrees_per_second;
  } __full_scale_ranges[];
  static const char* __id;
  static const uint8_t __I2C_address = 0x68;
  static const uint8_t __full_scale_range = 3;
  static const uint8_t __register_gyroscope_config = 0x1b;
  static const uint8_t __register_DLPF_config = 0x1a;
  static const uint8_t __value_DLPF_config = 0x0;
  static const uint8_t __register_pwr_mgmt_1 = 0x6B;
  static const uint8_t __value_pwr_mgmt_1 = 0x0;
  static const uint8_t __register_XYZ = 0x43;
public:
  MPU6050();
  virtual void initialize();
  virtual const String id() const;
  virtual void measure();
};

}
}
}

#endif
