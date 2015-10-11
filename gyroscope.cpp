#include "gyroscope.h"

namespace sensors {
namespace orientation {
namespace gyroscope {

gyroscope::gyroscope() {
  _values_dps.X = 0;
  _values_dps.Y = 0;
  _values_dps.Z = 0;
}

const float gyroscope::Xdps() {
  return _values_dps.X;
}

const float gyroscope::Ydps() {
  return _values_dps.Y;
}

const float gyroscope::Zdps() {
  return _values_dps.Z;
}

String gyroscope::debug_info() {
  String s;
  s += orientation::debug_info();
  s += ", X(dps): "; s += _values_dps.X; s += ", Y(dps): "; s += _values_dps.Y; s += ", Z(dps): "; s += _values_dps.Z;
  return s;
}

}
}
}
