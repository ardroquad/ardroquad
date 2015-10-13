#include "barometer.h"

namespace sensor {
namespace barometer {

const char* barometer::__id = "barometer";

const String barometer::id() const {
  String s;
  s += sensor::id(); s += id_divider(); s += __id;
  return s;
}


}
}

