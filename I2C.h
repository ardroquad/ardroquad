#ifndef _I2C_h_
#define _I2C_h_

#include <Wire.h>

namespace I2C {
  
void read_buffer(const uint8_t I2C_address, const uint8_t address, uint8_t buffer[], const uint8_t size);
void read_8(const uint8_t I2C_address, const uint8_t address, uint8_t& value);
void write_8(const uint8_t I2C_address, const uint8_t address, const uint8_t value);
void read_16(const uint8_t I2C_address, const uint8_t address, int16_t& data);
void read_16(const uint8_t I2C_address, const uint8_t address, uint16_t& data);
void read_16(const uint8_t I2C_address, const uint8_t address, int32_t& data);
void read_16(const uint8_t I2C_address, const uint8_t address, uint32_t& data);
void read_24(const uint8_t I2C_address, const uint8_t address, int32_t& data);

}

#endif



