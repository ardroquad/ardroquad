#include <Arduino.h>
#include "c_sensor_pressure_BMP.h"

using namespace sensors::pressure;

c_BMP::c_BMP() {
  _i2c_address = __i2c_address;
  _UT = 0;
  _temperature = 0;
  _b5 = 0;
  _UP = 0;
  _pressure = 0;
};

void c_BMP::initialize() {
  read_cc();
  read_temperature();
  read_pressure();
}

void c_BMP::read_data(const uint8_t address, const uint8_t bytes, uint8_t buffer[]) {
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

String c_BMP::diagnostic_data() {
  String s;
  s = "BMP085/BMP180:"; s += "\r\n";
  /*
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
  */
  s += "  Temperature: "; s += "\r\n";
  s += "    uncompensated: "; s += _UT; s += "\r\n";
  s += "    celsius: "; s += _temperature / 10; s += "."; s += _temperature % 10; s += "\r\n";
  s += "  Pressure: "; s += "\r\n";
  s += "    uncompensated: "; s += _UP; s += "\r\n";
  s += "    pascals: "; s += _pressure; s += "\r\n";
  s += "    mm Hg: "; s += (long)((float)_pressure / 133.3); s += "\r\n";
  return s;
}

void c_BMP::read_16(const uint8_t address, int32_t& data) {
  read_data(address, 2, _buffer);
  int16_t data_16 = (int16_t)_buffer[0] << 8 | (int16_t)_buffer[1];
  data = data_16;
}

void c_BMP::read_19(const uint8_t address, int32_t& data) {
  read_data(address, 3, _buffer);
  data = (int32_t)_buffer[0] << 16 | (int32_t)_buffer[1] << 8 | (int32_t)_buffer[2];
}

void c_BMP::read_16(const uint8_t address, uint32_t& data) {
  read_data(address, 2, _buffer);
  uint16_t data_16 = (uint16_t)_buffer[0] << 8 | (uint16_t)_buffer[1];
  data = data_16;
}

void c_BMP::read_cc() {
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

void c_BMP::write_8(const uint8_t address, const uint8_t data) {
  Wire.beginTransmission(_i2c_address);
  Wire.write(address);
  Wire.write(data);
  Wire.endTransmission();
}

void c_BMP::read_temperature() {
  write_8(__control_address, __command_read_UT);
  delay(__delay_read_UT);
  read_16(__address_UT, _UT);
  int32_t x1 = (_UT - _cc.ac6) * _cc.ac5 / 32768;
  int32_t x2 = _cc.mc * 2048 / (x1 + _cc.md);
  _b5 = x1 + x2;
  _temperature = (_b5 + 8) / 16;
}

void c_BMP::read_pressure() {
  write_8(__control_address, __command_read_UP);
  delay(__delay_read_UP);
  read_19(__address_UP, _UP);
  _UP >>= 8;
  int32_t b6 = _b5 - 4000;
  int32_t x1 = (_cc.b2 * (b6 * b6 / 4096)) / 2048;
  int32_t x2 = _cc.ac2 * b6 / 2048;
  int32_t x3 = x1 + x2;
  int32_t b3 = ((_cc.ac1 * 4 + x3) + 2) / 4;
  x1 = _cc.ac3 * b6 / 8192;
  x2 = (_cc.b1 * (b6 * b6 / 4096)) / 65536;
  x3 = ((x1 + x2) + 2) / 4;
  uint32_t b4 = _cc.ac4 * (uint32_t)(x3 + 32768) / 32768;
  uint32_t b7 = ((uint32_t)_UP - b3) * 50000;
  _pressure = b7 < 0x80000000 ? (b7 * 2) / b4 : (b7 / b4) * 2;
  x1 = (_pressure / 256) * (_pressure / 256);
  x1 = (x1 * 3038) / 65536;
  x2 = (-7357 * _pressure) / 65536;
  _pressure = _pressure + (x1 + x2 + 3791) / 16;
}

void c_BMP::force_temperature_update() {
  read_temperature();
  read_pressure();
}

int32_t c_BMP::get_temperature() {
  return _temperature;
}
