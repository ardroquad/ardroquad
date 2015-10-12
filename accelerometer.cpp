#include "accelerometer.h"

namespace sensors {
namespace orientation {
namespace accelerometer {

accelerometer::accelerometer() {
  _g.X = 0;
  _g.Y = 0;
  _g.Z = 0;
  _degrees.X = 0;
  _degrees.Y = 0;
  _degrees.Z = 0;
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

String accelerometer::debug_info() {
  String s;
  s += orientation::debug_info();
  s += ", X(g): "; s += _g.X; s += ", Y(g): "; s += _g.Y; s += ", Z(g): "; s += _g.Z; s += ", X(degrees): "; s += _degrees.X; s += ", Y(degrees): "; s += _degrees.Y; s += ", Z(degrees): "; s += _degrees.Z;
  return s;
}

void accelerometer::update() {
  double R = sqrt(_g.X * _g.X + _g.Y * _g.Y + _g.Z * _g.Z);
  _degrees.X = _g.X / R;
  _degrees.Y = _g.Y / R;
  _degrees.Z = _g.Z / R;
}

}
}
}
