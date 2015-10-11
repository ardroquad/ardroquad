#include <Arduino.h>
#include "I2C.h"

namespace I2C {

void read_buffer(const uint8_t I2C_address, const uint8_t address, uint8_t buffer[], const uint8_t size) {
  Wire.beginTransmission(I2C_address);
  Wire.write(address);
  Wire.endTransmission();
  Wire.beginTransmission(I2C_address);
  Wire.requestFrom(I2C_address, size);
  for (uint8_t i = 0; Wire.available() && i < size; ++i) {
    buffer[i] = Wire.read();
  }
  Wire.endTransmission();
}

void read_8(const uint8_t I2C_address, const uint8_t address, uint8_t& value) {
  Wire.beginTransmission(I2C_address);
  Wire.write(address);
  Wire.write(value);
  Wire.endTransmission();
}

void write_8(const uint8_t I2C_address, const uint8_t address, const uint8_t value) {
  Wire.beginTransmission(I2C_address);
  Wire.write(address);
  Wire.write(value);
  Wire.endTransmission();
}

void read_16(const uint8_t I2C_address, const uint8_t address, int16_t& data) {
  uint8_t buffer[2];
  I2C::read_buffer(I2C_address, address, buffer, 2);
  data = (int16_t)buffer[0] << 8 | (int16_t)buffer[1];
}

void read_16(const uint8_t I2C_address, const uint8_t address, uint16_t& data) {
  uint8_t buffer[2];
  I2C::read_buffer(I2C_address, address, buffer, 2);
  data = (uint16_t)buffer[0] << 8 | (uint16_t)buffer[1];
}

void read_16(const uint8_t I2C_address, const uint8_t address, int32_t& data) {
  uint8_t buffer[2];
  I2C::read_buffer(I2C_address, address, buffer, 2);
  int16_t data_16 = (int16_t)buffer[0] << 8 | (int16_t)buffer[1];
  data = data_16;
}

void read_16(const uint8_t I2C_address, const uint8_t address, uint32_t& data) {
  uint8_t buffer[2];
  I2C::read_buffer(I2C_address, address, buffer, 2);
  uint16_t data_16 = (uint16_t)buffer[0] << 8 | (uint16_t)buffer[1];
  data = data_16;
}

void read_24(const uint8_t I2C_address, const uint8_t address, int32_t& data) {
  uint8_t buffer[3];
  I2C::read_buffer(I2C_address, address, buffer, 3);
  data = (int32_t)buffer[0] << 16 | (int32_t)buffer[1] << 8 | (int32_t)buffer[2];
}

void read_3x16(const uint8_t I2C_address, const uint8_t address, int32_t& data_1, int32_t& data_2, int32_t& data_3) {
  uint8_t buffer[6];
  I2C::read_buffer(I2C_address, address, buffer, 6);
  int16_t data_16 = (int16_t)buffer[0] << 8 | (int16_t)buffer[1];
  data_1 = data_16;
  data_16 = (int16_t)buffer[2] << 8 | (int16_t)buffer[3];
  data_2 = data_16;
  data_16 = (int16_t)buffer[4] << 8 | (int16_t)buffer[5];
  data_3 = data_16;
}

}
