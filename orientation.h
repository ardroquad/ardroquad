#ifndef _orientation_h_
#define _orientation_h_

#include "sensor.h"

namespace sensors {
namespace orientation {

class orientation: 
public sensor {
protected:
  struct {
    int16_t X;
    int16_t Y;
    int16_t Z;
  }
  _values;
public:
  orientation();
  virtual String debug_info() const;
  virtual void update() = 0;
  int16_t X() const;
  int16_t Y() const;
  int16_t Z() const;
};

}
}

#endif
