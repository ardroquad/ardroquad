#ifndef _gyroscope_h_
#define _gyroscope_h_

#include "orientation.h"

namespace sensors {
namespace orientation {
namespace gyroscope {

class gyroscope: 
public orientation {
protected:
  struct {
    double X;
    double Y;
    double Z;
  } _dps;
  struct {
    double X;
    double Y;
    double Z;
  } _degrees;
  uint64_t _time_last_update;
public:
  gyroscope();
  const float X_dps();
  const float Y_dps();
  const float Z_dps();
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



