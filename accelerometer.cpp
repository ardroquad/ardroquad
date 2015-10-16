#include "accelerometer.h"

namespace sensor {
namespace orientation {
namespace accelerometer {

const char* accelerometer::__id = "accelerometer";

accelerometer::accelerometer() {
  _g.X = 0;
  _g.Y = 0;
  _g.Z = 0;
  _degrees.X = 0;
  _degrees.Y = 0;
  _degrees.Z = 0;
}

const String accelerometer::id() const {
  String s;
  s += orientation::id(); s += id_divider(); s += __id;
  return s;
}

const float accelerometer::X_g() {
  return _g.X;
}

const float accelerometer::Y_g() {
  return _g.Y;
}

const float accelerometer::Z_g() {
  return _g.Z;
}

const float accelerometer::X_degrees() {
  return _degrees.X;
}

const float accelerometer::Y_degrees() {
  return _degrees.Y;
}

const float accelerometer::Z_degrees() {
  return _degrees.Z;
}

const String accelerometer::debug_info() const {
  String s;
  s += orientation::debug_info();
  s += ", X(g): "; s += _g.X; s += ", Y(g): "; s += _g.Y; s += ", Z(g): "; s += _g.Z; s += ", X(d): "; s += _degrees.X; s += ", Y(d): "; s += _degrees.Y; s += ", Z(d): "; s += _degrees.Z;
  return s;
}

void accelerometer::measure() {
  double R = sqrt(_g.X * _g.X + _g.Y * _g.Y + _g.Z * _g.Z);
  _degrees.X = acos(_g.X / R) * 180 / M_PI;
  _degrees.Y = acos(_g.Y / R) * 180 / M_PI;
  _degrees.Z = acos(_g.Z / R) * 180 / M_PI;
}

}
}
}
