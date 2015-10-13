#include "sonar.h"

namespace sensor {
namespace sonar {

const char* sonar::__id = "sonar";
double sonar::_cm = 0;

sonar::sonar() {
}

const String sonar::id() const {
  String s;
  s += sensor::id(); s += id_divider(); s += __id;
  return s;
}

const double sonar::get_cm() const {
  return _cm;
}

}
}

