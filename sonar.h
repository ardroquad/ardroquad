#ifndef _sonar_h_
#define _sonar_h_

#include "sensor.h"

namespace sensors {
namespace sonar {
  
class sonar: 
public sensor {
private:
public:
  virtual double get_distance_cm() const = 0;
};

}
}

#endif
