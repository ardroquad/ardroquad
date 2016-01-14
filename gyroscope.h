#ifndef _gyroscope_h_
#define _gyroscope_h_

#include "orientation.h"

namespace sensor {
namespace orientation {
namespace gyroscope {

class gyroscope: 
public orientation {
private:
  static const uint8_t __calibration_count = 1000;
  static const uint8_t __calibration_delay = 1;
  static const char* __id;
protected:
  struct {
    double X;
    double Y;
    double Z;
  } _dps;
public:
  gyroscope();
  virtual const String id() const;
  virtual void calibrate();
  const float X_dps();
  const float Y_dps();
  const float Z_dps();
  virtual String debug_info();
};

}
}
}

#endif



