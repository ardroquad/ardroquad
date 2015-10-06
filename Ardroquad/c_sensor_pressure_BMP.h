#ifndef _c_sensor_presssure_BMP_h_
#define _c_sensor_presssure_BMP_h_

#include <Wire.h>
#include "c_sensor_pressure.h"

#define c_sensor_pressure_BMP_sensor_id "BMP085/BMP180"

#define c_sensor_pressure_BMP_device_address 0x77
#define c_sensor_pressure_BMP_buffer_size 3
#define c_sensor_pressure_BMP_bytes_CC 2

#define c_sesnsor_pressure_BMP_CC_AC1 0xAA
#define c_sesnsor_pressure_BMP_CC_AC2 0xAC
#define c_sesnsor_pressure_BMP_CC_AC3 0xAE
#define c_sesnsor_pressure_BMP_CC_AC4 0xB0
#define c_sesnsor_pressure_BMP_CC_AC5 0xB2
#define c_sesnsor_pressure_BMP_CC_AC6 0xB4
#define c_sesnsor_pressure_BMP_CC_B1  0xB6
#define c_sesnsor_pressure_BMP_CC_B2  0xB8
#define c_sesnsor_pressure_BMP_CC_MB  0xBA
#define c_sesnsor_pressure_BMP_CC_MC  0xBC
#define c_sesnsor_pressure_BMP_CC_MD  0xBE

class c_sensor_pressure_BMP: 
public c_sensor_pressure {
public:
  struct {
    short ac1;
    short ac2;
    short ac3;
    unsigned short ac4;
    unsigned short ac5;
    unsigned short ac6;
    short b1;
    short b2;
    short mb;
    short mc;
    short md;
  } _cc;
  unsigned char _device_address;
  uint8_t _buffer[c_sensor_pressure_BMP_buffer_size];
  void read_eeprom(const uint8_t address, const unsigned short bytes, uint8_t buffer[]);
  void readCC(const uint8_t address, short& cc);
  void readCC(const uint8_t address, unsigned short& cc);
  void readAllCC();
public:
  c_sensor_pressure_BMP();
  virtual void initialize();
  virtual String sensor_id();
  virtual String diagnostic_data();
};

#endif


