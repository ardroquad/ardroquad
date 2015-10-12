#ifndef _barometer_h_
#define _barometer_h_

#include "sensor.h"

namespace sensors {
namespace barometer {
  
class barometer: 
public sensor {
private:
public:
  virtual int32_t get_pressure() = 0;
};

}
}

#endif
