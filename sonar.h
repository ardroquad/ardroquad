#ifndef _sonar_h_
#define _sonar_h_

#include "sensor.h"

namespace sensor {
namespace sonar {
  
class sonar: 
public sensor {
private:
  static const char* __id;
protected:
  static double _cm;
public:
  sonar();
  virtual const String id() const;
  const double get_cm() const;
};

}
}

#endif
