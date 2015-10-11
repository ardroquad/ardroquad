#include <Arduino.h>
#include "orientation.h"

namespace sensors {
namespace orientation {
  
orientation::orientation() {
  _values.X = 0;
  _values.Y = 0;
  _values.Z = 0;
  _correction.X = 0;
  _correction.Y = 0;
  _correction.Z = 0;
}

String orientation::debug_info() const {
  String s;
  s += id(); s += ": X: "; s += X(); s += ", Y: "; s += Y(); s += ", Z: "; s += Z();
  return s;
}

int32_t orientation::X() const {
  return _values.X;
}

int32_t orientation::Y() const {
  return _values.Y;
}

int32_t orientation::Z() const {
  return _values.Z;
}

void orientation::set_correction_X(const int32_t correction) {
  _correction.X = correction;
}

void orientation::set_correction_Y(const int32_t correction) {
  _correction.Y = correction;
}

void orientation::set_correction_Z(const int32_t correction) {
  _correction.Z = correction;
}

void orientation::correct() {
  _values.X += _correction.X;
  _values.Y += _correction.Y;
  _values.Z += _correction.Z;
}

}
}
