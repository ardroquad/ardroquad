#include <Arduino.h>
#include "BMP180.h"
#include "I2C.h"

namespace sensor {
namespace barometer {

const char* BMP180::__id = "BMP180";

const uint8_t BMP180::__UP_delays_read[4] = {
  __UP.delay_ultra_low_power,
  __UP.delay_standard,
  __UP.delay_high_resolution,
  __UP.delay_ultra_high_resolution
};

BMP180::BMP180() {
  _temperature.raw = 0;
  _temperature.celsius = 0;
  _temperature.b5 = 0;
  _temperature.request_millis = 0;
  _pressure.raw = 0;
  _pressure.pascals = 0;
  _pressure.request_millis = 0;
  _oss = __oss;
  _initialized = false;
  _reading_parameter = none;
};

void BMP180::initialize() {
  read_cc();
  request_temperature();
  delay(__UT.delay_read);
  read_temperature();
  request_pressure();
  delay(__UP_delays_read[_oss]);
  read_pressure();
  _initialized = true;
}

const String BMP180::id() const {
  String s;
  s+= barometer::id(); s += sensor::id_divider(); s += __id;
  return s;
}

String const BMP180::debug_info() const {
  String s;
  s += id(); s += ": t(C): "; s += _temperature.celsius / 10; s += "."; s += _temperature.celsius % 10; s += ",  p(Pa): "; s += _pressure.pascals; s += ", p(mmHg): "; s += (long)((float)_pressure.pascals / 133.3);
  return s;
}

void BMP180::read_cc() {
  I2C::read_16(__I2C_address, __cca_ac1, _cc.ac1);
  I2C::read_16(__I2C_address, __cca_ac2, _cc.ac2);
  I2C::read_16(__I2C_address, __cca_ac3, _cc.ac3);
  I2C::read_16(__I2C_address, __cca_ac4, _cc.ac4);
  I2C::read_16(__I2C_address, __cca_ac5, _cc.ac5);
  I2C::read_16(__I2C_address, __cca_ac6, _cc.ac6);
  I2C::read_16(__I2C_address, __cca_b1, _cc.b1);
  I2C::read_16(__I2C_address, __cca_b2, _cc.b2);
  I2C::read_16(__I2C_address, __cca_mb, _cc.mb);
  I2C::read_16(__I2C_address, __cca_mc, _cc.mc);
  I2C::read_16(__I2C_address, __cca_md, _cc.md);
}

void BMP180::request_temperature() {
  I2C::write_8(__I2C_address, __control_address, __UT.command_read);
  _temperature.request_millis = millis();
  _reading_parameter = temperature;
}

void BMP180::read_temperature() {
  I2C::read_16(__I2C_address, __UT.address, _temperature.raw);
  int32_t x1 = (_temperature.raw - _cc.ac6) * _cc.ac5 / 32768;
  int32_t x2 = _cc.mc * 2048 / (x1 + _cc.md);
  _temperature.b5 = x1 + x2;
  _temperature.celsius = (_temperature.b5 + 8) / 16;
  _reading_parameter = none;
}

void BMP180::request_pressure() {
  I2C::write_8(__I2C_address, __control_address, __UP.command_read + (_oss << 6));
  _pressure.request_millis = millis();
  _reading_parameter = pressure;
}

void BMP180::read_pressure() {
  I2C::read_24(__I2C_address, __UP.address, _pressure.raw);
  _pressure.raw >>= 8 - _oss;
  int32_t b6 = _temperature.b5 - 4000;
  int32_t x1 = (_cc.b2 * (b6 * b6 / 4096)) / 2048;
  int32_t x2 = _cc.ac2 * b6 / 2048;
  int32_t x3 = x1 + x2;
  int32_t b3 = (((_cc.ac1 * 4 + x3) << _oss) + 2) / 4;
  x1 = _cc.ac3 * b6 / 8192;
  x2 = (_cc.b1 * (b6 * b6 / 4096)) / 65536;
  x3 = ((x1 + x2) + 2) / 4;
  uint32_t b4 = _cc.ac4 * (uint32_t)(x3 + 32768) / 32768;
  uint32_t b7 = ((uint32_t)_pressure.raw - b3) * (50000 >> _oss);
  _pressure.pascals = b7 < 0x80000000 ? (b7 * 2) / b4 : (b7 / b4) * 2;
  x1 = (_pressure.pascals / 256) * (_pressure.pascals / 256);
  x1 = (x1 * 3038) / 65536;
  x2 = (-7357 * _pressure.pascals) / 65536;
  _pressure.pascals = _pressure.pascals + (x1 + x2 + 3791) / 16;
  _reading_parameter = none;
}

int32_t BMP180::get_pressure() {
  if (_initialized) {
    switch (_reading_parameter) {
    case temperature:
      if (millis() >= _temperature.request_millis + __UT.delay_read) {
        read_temperature();
        request_pressure();
      }
      break;
    case pressure:
      if (millis() >= _pressure.request_millis + __UP_delays_read[_oss]) {
        read_pressure();
      }
      break;
    case none:
      break;
    }
    if (none == _reading_parameter) {
      if (millis() >= _temperature.request_millis + __UT.delay_refresh) {
        request_temperature();
      }
      else {
        request_pressure();
      }
    }
  }
  return _pressure.pascals;
}

}
}
