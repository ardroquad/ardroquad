#ifndef _sensor_h_
#define _sensor_h_

#include <Arduino.h>

namespace sensor {
  
class sensor {
private:
  static const char* __id;
  static const char* __id_divider;
public:
  virtual void initialize() = 0;
  virtual const String id() const;
  const String id_divider() const;
  virtual const String debug_info() const = 0;
  virtual void measure() = 0;
};

}

#endif



