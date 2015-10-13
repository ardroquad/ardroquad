#ifndef _barometer_h_
#define _barometer_h_

#include <Arduino.h>
#include "sensor.h"

namespace sensor {
namespace barometer {
  
class barometer: 
public sensor {
private:
  static const char* __id;
public:
  virtual const String id() const;
  virtual int32_t get_pascals() = 0;
};

}
}

#endif
