#ifndef _HC_SR04_h_
#define _HC_SR04_h_

#include <Arduino.h>
#include "sonar.h"

namespace sensor {
namespace sonar {

class HC_SR04: 
public sonar
{
private:
  static const char* __id;
  static const uint8_t __pin_trigger = 22;
  static const uint8_t __pin_echo = 2;
  static const uint8_t __interrupt_echo = 0;
  static const uint8_t __trigger_delay_LOW = 10;
  static const uint8_t __trigger_delay_HIGH = 20;
  static void echo();
public:
  static uint64_t _echo_micros;
  static enum interruption {
    released,
    waiting_HIGH,
    waiting_LOW
  } _interruption;
  virtual void initialize();
  virtual const String id() const;
  virtual const String debug_info() const;
  virtual void measure();
};

}
}

#endif
