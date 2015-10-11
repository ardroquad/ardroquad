#include "accelerometer.h"

namespace sensors {
namespace orientation {
namespace accelerometer {

accelerometer::accelerometer() {
  _g.X = 0;
  _g.Y = 0;
  _g.Z = 0;
  _normalized.X = 0;
  _normalized.Y = 0;
  _normalized.Z = 0;
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

const float accelerometer::X_normalized() {
  return _normalized.X;
}

const float accelerometer::Y_normalized() {
  return _normalized.Y;
}

const float accelerometer::Z_normalized() {
  return _normalized.Z;
}

String accelerometer::debug_info() {
  String s;
  s += orientation::debug_info();
  s += ", X(g): "; s += _g.X; s += ", Y(g): "; s += _g.Y; s += ", Z(g): "; s += _g.Z; s += ", X(normalized): "; s += _normalized.X; s += ", Y(normalized): "; s += _normalized.Y; s += ", Z(normalized): "; s += _normalized.Z;
  return s;
}

void accelerometer::update() {
  float R = sqrt(_g.X * _g.X + _g.Y * _g.Y + _g.Z * _g.Z);
  _normalized.X = _g.X / R;
  _normalized.Y = _g.Y / R;
  _normalized.Z = _g.Z / R;
}

}
}
}
