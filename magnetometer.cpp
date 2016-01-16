#include "magnetometer.h"

namespace sensor {
namespace orientation {
namespace magnetometer {

const char* magnetometer::__id = "magnetometer";

magnetometer::magnetometer() {
  EEPROM.get(__EEPROM_address, _calibration);
}

const String magnetometer::id() const {
  String s;
  s += orientation::id(); s += id_divider(); s += __id;
  return s;
}

void magnetometer::calibrate() {
  int32_t X_min = 0;
  int32_t X_max = 0;
  int32_t Y_min = 0;
  int32_t Y_max = 0;
  int32_t Z_min = 0;
  int32_t Z_max = 0;
  int64_t t = millis();
  while ((millis() - t) / 1000 < __calibration_seconds) {
    measure(false);
    X_min = X() < X_min ? X() : X_min;
    X_max = X() > X_max ? X() : X_max;
    Y_min = Y() < Y_min ? Y() : Y_min;
    Y_max = Y() > Y_max ? Y() : Y_max;
    Z_min = Z() < Z_min ? Z() : Z_min;
    Z_max = Z() > Z_max ? Z() : Z_max;
    delay(__calibration_delay);
  }
  _calibration.hard.X = (X_min - X_max) / 2 - X_min;
  _calibration.hard.Y = (Y_min - Y_max) / 2 - Y_min;
  _calibration.hard.Z = (Z_min - Z_max) / 2 - Z_min;
  int32_t length_max = X_max - X_min;
  length_max = length_max < Y_max - Y_min ? Y_max - Y_min : length_max;
  length_max = length_max < Z_max - Z_min ? Z_max - Z_min : length_max;
  _calibration.soft.X = (double)length_max / (double)(X_max - X_min);
  _calibration.soft.Y = (double)length_max / (double)(Y_max - Y_min);
  _calibration.soft.Z = (double)length_max / (double)(Z_max - Z_min);
  EEPROM.put(__EEPROM_address, _calibration);
}

const String magnetometer::calibrate_info() const {
  String s;
  s += id(); s += ": X_hard: "; s += _calibration.hard.X; s += ", Y_hard: "; s += _calibration.hard.Y; s += ", Z_hard: "; s += _calibration.hard.Z;  s += ", X_soft: "; s += _calibration.soft.X; s += ", Y_soft: "; s += _calibration.soft.Y; s += ", Z_soft: "; s += _calibration.soft.Z;
  return s;
}

}
}
}
