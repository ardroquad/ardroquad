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
    double X;
    double Y;
    double Z;
  } _g;
  struct {
    float X;
    float Y;
    float Z;
  } _degrees;
public:
  accelerometer();
  const float X_g();
  const float Y_g();
  const float Z_g();
  const float X_degrees();
  const float Y_degrees();
  const float Z_degrees();
  virtual String debug_info();
  virtual void update();
};

}
}
}

#endif



