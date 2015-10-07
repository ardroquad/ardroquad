#ifndef _pressure_h_
#define _pressure_h_

#include "sensor.h"

namespace sensors {
  namespace pressure {
    class pressure: 
    public sensor {
    private:
    public:
      virtual int32_t get_pressure() = 0;
    };
  }
}

#endif



