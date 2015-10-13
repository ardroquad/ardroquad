#include "gyroscope.h"

namespace sensor {
namespace orientation {
namespace gyroscope {

const char* gyroscope::__id = "gyroscope";

gyroscope::gyroscope() {
  _dps.X = 0;
  _dps.Y = 0;
  _dps.Z = 0;
}

const String gyroscope::id() const {
  String s;
  s += orientation::id(); s += id_divider(); s += __id;
  return s;
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
