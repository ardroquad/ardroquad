#include "magnetometer.h"

namespace sensor {
namespace orientation {
namespace magnetometer {

const char* magnetometer::__id = "magnetometer";

const String magnetometer::id() const {
  String s;
  s += orientation::id(); s += id_divider(); s += __id;
  return s;
}

void magnetometer::calibrate() {
  
}

}
}
}
