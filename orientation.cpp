#include <Arduino.h>
#include "orientation.h"

namespace sensors {
namespace orientation {
  
orientation::orientation() {
  _values.X = 0;
  _values.Y = 0;
  _values.Z = 0;
}

String orientation::debug_info() const {
  String s;
  s += id(); s += ": X: "; s += X(); s += ", Y: "; s += Y(); s += ", Z: "; s += Z();
  return s;
}

int16_t orientation::X() const {
  return _values.X;
}

int16_t orientation::Y() const {
  return _values.Y;
}

int16_t orientation::Z() const {
  return _values.Z;
}

}
}
