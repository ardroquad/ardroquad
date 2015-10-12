#include "gyroscope.h"

namespace sensors {
namespace orientation {
namespace gyroscope {

gyroscope::gyroscope() {
  _dps.X = 0;
  _dps.Y = 0;
  _dps.Z = 0;
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

String gyroscope::debug_info() {
  String s;
  s += orientation::debug_info();
  s += ", X(dps): "; s += _dps.X; s += ", Y(dps): "; s += _dps.Y; s += ", Z(dps): "; s += _dps.Z;
  return s;
}

}
}
}
