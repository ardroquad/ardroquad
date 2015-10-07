#include <Arduino.h>
#include "BMP180.h"

using namespace sensors::pressure;

const uint8_t BMP180::__UP_delays_read[4] = {
  __UP.delay_ultra_low_power,
  __UP.delay_standard,
  __UP.delay_high_resolution,
  __UP.delay_ultra_high_resolution
};

BMP180::BMP180() {
  _i2c_address = __i2c_address;
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

String BMP180::diagnostic_data() {
  String s;
  s = "BMP085/BMP180:"; s += "\r\n";
#ifdef _DEBUG_
  s += "  Calibrating coefficients:"; s += "\r\n";
  s += "    ac1: "; s += _cc.ac1; s += "\r\n";
  s += "    ac2: "; s += _cc.ac2; s += "\r\n";
  s += "    ac3: "; s += _cc.ac3; s += "\r\n";
  s += "    ac4: "; s += _cc.ac4; s += "\r\n";
  s += "    ac5: "; s += _cc.ac5; s += "\r\n";
  s += "    ac6: "; s += _cc.ac6; s += "\r\n";
  s += "    b1:  "; s += _cc.b1; s += "\r\n";
  s += "    b2:  "; s += _cc.b2; s += "\r\n";
  s += "    mb:  "; s += _cc.mb; s += "\r\n";
  s += "    mc:  "; s += _cc.mc; s += "\r\n";
  s += "    md:  "; s += _cc.md; s += "\r\n";
#endif
  s += "  Temperature: "; s += "\r\n";
#ifdef _DEBUG_
  s += "    raw: "; s += _temperature.raw; s += "\r\n";
#endif
  s += "    celsius: "; s += _temperature.celsius / 10; s += "."; s += _temperature.celsius % 10; s += "\r\n";
  s += "  Pressure: "; s += "\r\n";
#ifdef _DEBUG_
  s += "    raw: "; s += _pressure.raw; s += "\r\n";
#endif
  s += "    pascals: "; s += _pressure.pascals; s += "\r\n";
  s += "    mm Hg: "; s += (long)((float)_pressure.pascals / 133.3); s += "\r\n";
  return s;
}

void BMP180::read_data(const uint8_t address, const uint8_t bytes, uint8_t buffer[]) {
  Wire.beginTransmission(_i2c_address);
  Wire.write(address);
  Wire.endTransmission();
  
  Wire.beginTransmission(_i2c_address);
  Wire.requestFrom(_i2c_address, bytes);
  for (uint8_t i = 0; Wire.available() && i < bytes; ++i) {
    buffer[i] = Wire.read();
  }
  Wire.endTransmission();
}

void BMP180::read_16(const uint8_t address, int32_t& data) {
  read_data(address, 2, _buffer);
  int16_t data_16 = (int16_t)_buffer[0] << 8 | (int16_t)_buffer[1];
  data = data_16;
}

void BMP180::read_16(const uint8_t address, uint32_t& data) {
  read_data(address, 2, _buffer);
  uint16_t data_16 = (uint16_t)_buffer[0] << 8 | (uint16_t)_buffer[1];
  data = data_16;
}

void BMP180::read_19(const uint8_t address, int32_t& data) {
  read_data(address, 3, _buffer);
  data = (int32_t)_buffer[0] << 16 | (int32_t)_buffer[1] << 8 | (int32_t)_buffer[2];
}

void BMP180::read_cc() {
  read_16(__cca_ac1, _cc.ac1);
  read_16(__cca_ac2, _cc.ac2);
  read_16(__cca_ac3, _cc.ac3);
  read_16(__cca_ac4, _cc.ac4);
  read_16(__cca_ac5, _cc.ac5);
  read_16(__cca_ac6, _cc.ac6);
  read_16(__cca_b1, _cc.b1);
  read_16(__cca_b2, _cc.b2);
  read_16(__cca_mb, _cc.mb);
  read_16(__cca_mc, _cc.mc);
  read_16(__cca_md, _cc.md);
}

void BMP180::write_8(const uint8_t address, const uint8_t data) {
  Wire.beginTransmission(_i2c_address);
  Wire.write(address);
  Wire.write(data);
  Wire.endTransmission();
}

void BMP180::request_temperature() {
  write_8(__control_address, __UT.command_read);
  _temperature.request_millis = millis();
  _reading_parameter = temperature;
}

void BMP180::read_temperature() {
  read_16(__UT.address, _temperature.raw);
  int32_t x1 = (_temperature.raw - _cc.ac6) * _cc.ac5 / 32768;
  int32_t x2 = _cc.mc * 2048 / (x1 + _cc.md);
  _temperature.b5 = x1 + x2;
  _temperature.celsius = (_temperature.b5 + 8) / 16;
  _reading_parameter = none;
}

void BMP180::request_pressure() {
  write_8(__control_address, __UP.command_read + (_oss << 6));
  _pressure.request_millis = millis();
  _reading_parameter = pressure;
}

void BMP180::read_pressure() {
  read_19(__UP.address, _pressure.raw);
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
