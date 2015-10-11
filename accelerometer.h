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
  } _g;
  struct {
    float X;
    float Y;
    float Z;
  } _normalized;
public:
  accelerometer();
  const float X_g();
  const float Y_g();
  const float Z_g();
  const float X_normalized();
  const float Y_normalized();
  const float Z_normalized();
  virtual String debug_info();
  virtual void update();
};

}
}
}

#endif



