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
public:
  gyroscope();
  const float X_dps();
  const float Y_dps();
  const float Z_dps();
  virtual String debug_info();
};

}
}
}

#endif



