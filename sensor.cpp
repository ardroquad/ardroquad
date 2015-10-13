#include "sensor.h"

namespace sensor {

const char* sensor::__id = "sensor";
const char* sensor::__id_divider = "::";

const String sensor::id() const {
  return __id;
}

const String sensor::id_divider() const {
  return __id_divider;
}

}

