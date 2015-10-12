#ifndef _sonar_h_
#define _sonar_h_

#include "sensor.h"

namespace sensors {
namespace sonar {
  
class sonar: 
public sensor {
private:
public:
  virtual int32_t get_distance() = 0;
};

}
}

#endif
