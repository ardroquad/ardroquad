#include <Arduino.h>
#include "orientation.h"

namespace sensor {
namespace orientation {

const char* orientation::__id = "orientation";
  
orientation::orientation() {
  _values.X = 0;
  _values.Y = 0;
  _values.Z = 0;
  _correction.X = 0;
  _correction.Y = 0;
  _correction.Z = 0;
}

const String orientation::id() const {
  String s;
  s += sensor::id(); s += id_divider(); s += __id;
  return s;
}

const String orientation::debug_info() const {
  String s;
  s += id(); s += ": X: "; s += X(); s += ", Y: "; s += Y(); s += ", Z: "; s += Z(); s += ", R: "; s += sqrt(X() * X() + Y() * Y() + Z() * Z());
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

void orientation::set_correction(const int32_t X, const int32_t Y, const int32_t Z) {
  _correction.X = X;
  _correction.Y = Y;
  _correction.Z = Z;
}

void orientation::correct() {
  _values.X += _correction.X;
  _values.Y += _correction.Y;
  _values.Z += _correction.Z;
}

}
}
