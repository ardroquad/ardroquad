#include "gyroscope.h"

namespace sensors {
namespace orientation {
namespace gyroscope {

gyroscope::gyroscope() {
  _dps.X = 0;
  _dps.Y = 0;
  _dps.Z = 0;
  _degrees.X = 0;
  _degrees.Y = 0;
  _degrees.Z = 0;
  _time_last_update = micros();
}

const float gyroscope::X_dps() {
  return _dps.X;
}

const float gyroscope::Y_dps() {
  return _dps.Y;
}

const float gyroscope::Z_dps() {
  return _dps.Z;
}

const float gyroscope::X_degrees() {
  return _degrees.X;
}

const float gyroscope::Y_degrees() {
  return _degrees.Y;
}

const float gyroscope::Z_degrees() {
  return _degrees.Z;
}

void gyroscope::update() {
  uint64_t time_current = micros();
}

String gyroscope::debug_info() {
  String s;
  s += orientation::debug_info();
  s += ", X(dps): "; s += _dps.X; s += ", Y(dps): "; s += _dps.Y; s += ", Z(dps): "; s += _dps.Z;
  return s;
}

}
}
}
