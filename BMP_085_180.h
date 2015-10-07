#ifndef _BMP_085_180_h_
#define _BMP_085_180_h_

#include <Arduino.h>
#include <Wire.h>
#include "pressure.h"

namespace sensors {
  namespace pressure {
    class BMP_085_180: 
    public pressure {
    private:
      static const uint8_t __i2c_address = 0x77;
      static const uint8_t __buffer_size = 3;
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
      } __UT;
      static const struct {
        static const uint8_t address = 0xF6;
        static const uint8_t command_read = 0x34;
        static const uint8_t delay_ultra_low_power = 6;
        static const uint8_t delay_standard = 9;
        static const uint8_t delay_high_resolution = 15;
        static const uint8_t delay_ultra_high_resolution = 27;
      } __UP;
      static const uint8_t __UP_read_delays[4];
      enum osses {
        ultra_low_power = 0,
        standard = 1,
        high_resolution = 2,
        ultra_high_resolution = 3
      } _oss;
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
      } _cc;
      uint8_t _i2c_address;
      uint8_t _buffer[__buffer_size];
      struct {
        int32_t raw;
        int32_t celsius;
        int32_t b5;
        uint32_t last_read_millis;
      } _temperature;
      struct {
        int32_t raw;
        int32_t pascals;
        uint32_t request_millis;
      } _pressure;
      bool _initialized;
      void read_data(const uint8_t address, const uint8_t bytes, uint8_t buffer[]);
      void read_16(const uint8_t address, int32_t& data);
      void read_16(const uint8_t address, uint32_t& data);
      void read_19(const uint8_t address, int32_t& data);
      void read_cc();
      void write_8(const uint8_t address, const uint8_t data);
      void read_temperature();
      void request_pressure();
      void read_pressure();
    public:
      BMP_085_180();
      virtual void initialize();
      virtual String diagnostic_data();
      virtual int32_t get_pressure();
    };
  }
}

#endif
