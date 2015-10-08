#ifndef _BMP180_h_
#define _BMP180_h_

#include <Arduino.h>
#include "barometer.h"

namespace sensors {
namespace barometer {

class BMP180: 
public barometer {
private:
  static const char* __id;
  static const uint8_t __I2C_address = 0x77;
  static const uint8_t __cca_ac1 = 0xAA;
  static const uint8_t __cca_ac2 = 0xAC;
  static const uint8_t __cca_ac3 = 0xAE;
  static const uint8_t __cca_ac4 = 0xB0;
  static const uint8_t __cca_ac5 = 0xB2;
  static const uint8_t __cca_ac6 = 0xB4;
  static const uint8_t __cca_b1 = 0xB6;
  static const uint8_t __cca_b2 = 0xB8;
  static const uint8_t __cca_mb = 0xBA;
  static const uint8_t __cca_mc = 0xBC;
  static const uint8_t __cca_md = 0xBE;
  static const uint8_t __control_address = 0xF4;
  static const struct {
    static const uint8_t address = 0xF6;
    static const uint8_t command_read = 0x2E;
    static const uint8_t delay_read = 5;
    static const uint16_t delay_refresh = 1000;
  } 
  __UT;
  static const struct {
    static const uint8_t address = 0xF6;
    static const uint8_t command_read = 0x34;
    static const uint8_t delay_ultra_low_power = 6;
    static const uint8_t delay_standard = 9;
    static const uint8_t delay_high_resolution = 15;
    static const uint8_t delay_ultra_high_resolution = 27;
  } 
  __UP;
  static const uint8_t __UP_delays_read[4];
  enum osses {
    ultra_low_power = 0,
    standard = 1,
    high_resolution = 2,
    ultra_high_resolution = 3
  } 
  _oss;
  static const osses __oss = ultra_high_resolution;
  struct {
    int32_t ac1;
    int32_t ac2;
    int32_t ac3;
    uint32_t ac4;
    uint32_t ac5;
    uint32_t ac6;
    int32_t b1;
    int32_t b2;
    int32_t mb;
    int32_t mc;
    int32_t md;
  } 
  _cc;
  struct {
    int32_t raw;
    int32_t celsius;
    int32_t b5;
    uint32_t request_millis;
  } 
  _temperature;
  struct {
    int32_t raw;
    int32_t pascals;
    uint32_t request_millis;
  } 
  _pressure;
  bool _initialized;
  enum {
    none,
    temperature,
    pressure
  } 
  _reading_parameter;
  void read_cc();
  void request_temperature();
  void read_temperature();
  void request_pressure();
  void read_pressure();
public:
  BMP180();
  virtual void initialize();
  virtual const char* id() const;
  virtual String debug_info() const;
  virtual int32_t get_pressure();
};

}
}

#endif
