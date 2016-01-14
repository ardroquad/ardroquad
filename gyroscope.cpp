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

void gyroscope::calibrate() {
  int32_t sum_X = 0;
  int32_t sum_Y = 0;
  int32_t sum_Z = 0;
  for (uint16_t i = 0; i < __calibration_count; ++i) {
    measure();
    sum_X += X();
    sum_Y += Y();
    sum_Z += Z();
    delay(__calibration_delay);
  }
  set_correction(-sum_X / __calibration_count, -sum_Y / __calibration_count, -sum_Z / __calibration_count);
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
