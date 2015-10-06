#include "c_sensor_pressure_BMP.h"

c_sensor_pressure_BMP::c_sensor_pressure_BMP() {
  _device_address = c_sensor_pressure_BMP_device_address;
};

void c_sensor_pressure_BMP::read_eeprom(const uint8_t address, const unsigned short bytes, uint8_t buffer[]) {
  Wire.beginTransmission(_device_address);
  Wire.write(address);
  Wire.endTransmission();
  
  Wire.beginTransmission(_device_address);
  Wire.requestFrom(_device_address, bytes);
  for (uint8_t i = 0; Wire.available() && i < bytes; ++i) {
    buffer[i] = Wire.read();
  }
  Wire.endTransmission();
}

void c_sensor_pressure_BMP::initialize() {
  readAllCC();
}

String c_sensor_pressure_BMP::sensor_id() {
  return c_sensor_pressure_BMP_sensor_id;
}

String c_sensor_pressure_BMP::diagnostic_data() {
  String s;
  s = "AC1: "; s += _cc.ac1; s += "\r\n";
  s += "AC2: "; s += _cc.ac2; s += "\r\n";
  s += "AC3: "; s += _cc.ac3; s += "\r\n";
  s += "AC4: "; s += _cc.ac4; s += "\r\n";
  s += "AC5: "; s += _cc.ac5; s += "\r\n";
  s += "AC6: "; s += _cc.ac6; s += "\r\n";
  return s;
}

void c_sensor_pressure_BMP::readCC(const uint8_t address, short& cc) {
  read_eeprom(address, c_sensor_pressure_BMP_bytes_CC, _buffer);
  cc = ((short)_buffer[0] << 8 | ((short)_buffer[1]));
}

void c_sensor_pressure_BMP::readCC(const uint8_t address, unsigned short& cc) {
  read_eeprom(address, c_sensor_pressure_BMP_bytes_CC, _buffer);
  cc = ((unsigned short)_buffer[0] << 8 | ((unsigned short)_buffer[1]));
}

void c_sensor_pressure_BMP::readAllCC() {
  readCC(c_sesnsor_pressure_BMP_CC_AC1, _cc.ac1);
  readCC(c_sesnsor_pressure_BMP_CC_AC2, _cc.ac2);
  readCC(c_sesnsor_pressure_BMP_CC_AC3, _cc.ac3);
  readCC(c_sesnsor_pressure_BMP_CC_AC4, _cc.ac4);
  readCC(c_sesnsor_pressure_BMP_CC_AC5, _cc.ac5);
  readCC(c_sesnsor_pressure_BMP_CC_AC6, _cc.ac6);
  readCC(c_sesnsor_pressure_BMP_CC_B1, _cc.b1);
  readCC(c_sesnsor_pressure_BMP_CC_B2, _cc.b2);
  readCC(c_sesnsor_pressure_BMP_CC_MB, _cc.mb);
  readCC(c_sesnsor_pressure_BMP_CC_MC, _cc.mc);
  readCC(c_sesnsor_pressure_BMP_CC_MD, _cc.md);
}
