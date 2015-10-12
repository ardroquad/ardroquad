#ifndef _HC_SR04_h_
#define _HC_SR04_h_

#include <Arduino.h>
#include "sonar.h"

namespace sensors {
namespace sonar {

class HC_SR04: 
public sonar
{
private:
  static const char* __id;
  const uint8_t __pin_trigger = 0;
  const uint8_t __pin_echo = 0;
  double _distance_cm;
public:
  HC_SR04();
  virtual void initialize();
  virtual const char* id() const;
  virtual String debug_info() const;
  virtual double get_distance_cm() const;
};

}
}

#endif
