#ifndef _accelerometer_h_
#define _accelerometer_h_

#include "orientation.h"

namespace sensors {
namespace orientation {
namespace accelerometer {

class accelerometer: 
public orientation {
protected:
  struct {
    float X;
    float Y;
    float Z;
  } _values_g;
  struct {
    float X;
    float Y;
    float Z;
  } _values_radians;
public:
  accelerometer();
  const float Xg();
  const float Yg();
  const float Zg();
  virtual String debug_info();
  virtual void update();
};

}
}
}

#endif



