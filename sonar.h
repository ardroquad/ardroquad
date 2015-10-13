#ifndef _sonar_h_
#define _sonar_h_

#include "sensor.h"

namespace sensor {
namespace sonar {
  
class sonar: 
public sensor {
private:
  static const char* __id;
public:
  virtual const String id() const;
  virtual double get_distance_cm() const = 0;
};

}
}

#endif
