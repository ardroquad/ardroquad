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
    float X;
    float Y;
    float Z;
  } _values_dps;
public:
  gyroscope();
  const float Xdps();
  const float Ydps();
  const float Zdps();
  virtual String debug_info();
};

}
}
}

#endif



