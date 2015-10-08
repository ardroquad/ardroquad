#ifndef _accelerometer_h_
#define _accelerometer_h_

#include "sensor.h"

namespace sensors {
namespace accelerometer {

class accelerometer: 
public sensor {
protected:
  struct {
    int16_t X;
    int16_t Y;
    int16_t Z;
  }
  _values;
public:
  accelerometer();
  int16_t X();
  int16_t Y();
  int16_t Z();
  virtual void update() = 0;
};

}
}

#endif



