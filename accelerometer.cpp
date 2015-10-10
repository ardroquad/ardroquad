#include "accelerometer.h"

namespace sensors {
namespace orientation {
namespace accelerometer {

accelerometer::accelerometer() {
  _values_g.X = 0;
  _values_g.Y = 0;
  _values_g.Z = 0;
  _values_degree.X = 0;
  _values_degree.Y = 0;
  _values_degree.Z = 0;
}

const float accelerometer::Xg() {
  return _values_g.X;
}

const float accelerometer::Yg() {
  return _values_g.Y;
}

const float accelerometer::Zg() {
  return _values_g.Z;
}

String accelerometer::debug_info() {
  String s;
  s += orientation::debug_info();
  s += ", X(g): "; s += _values_g.X; s += ", Y(g): "; s += _values_g.Y; s += ", Z(g): "; s += _values_g.Z;  s += ", X(degree): "; s += _values_degree.X; s += ", Y(degree): "; s += _values_degree.Y; s += ", Z(degree): "; s += _values_degree.Z;
  return s;
}

void accelerometer::update() {
  float R = sqrt(_values_g.X * _values_g.X + _values_g.Y * _values_g.Y + _values_g.Z * _values_g.Z);
  _values_degree.X = acos(_values_g.X / R);
  _values_degree.Y = acos(_values_g.Y / R);
  _values_degree.Z = acos(_values_g.Z / R);
}

}
}
}
