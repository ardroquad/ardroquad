#include "sonar.h"

namespace sensor {
namespace sonar {

const char* sonar::__id = "sonar";

const String sonar::id() const {
  String s;
  s += sensor::id(); s += id_divider(); s += __id;
  return s;
}

}
}

