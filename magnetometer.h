#ifndef _magnetometer_h_
#define _magnetometer_h_

#include "orientation.h"

namespace sensor {
namespace orientation {
namespace magnetometer {

class magnetometer: 
public orientation {
private:
  static const char* __id;
public:
  virtual const String id() const;
  virtual void calibrate();
};

}
}
}

#endif
