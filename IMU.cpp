#include "IMU.h"

namespace IMU {

IMU::IMU(sensor::orientation::accelerometer::accelerometer& accelerometer, sensor::orientation::gyroscope::gyroscope& gyroscope):
  _accelerometer(accelerometer),
  _gyroscope(gyroscope)
{
  _time_micros = micros();
}

double IMU::get_dt() {
  double time_micros = _time_micros;
  _time_micros = micros();
  return _time_micros - time_micros;
}

Kalman::axis::axis() {
  _Q_angle = 0;
  _Q_bias = 0;
  _R = 0;
  _angle = 0;
  _bias = 0;
  _P[0][0] = 0;
  _P[0][1] = 0;
  _P[1][0] = 0;
  _P[1][1] = 0;
}

Kalman::Kalman(sensor::orientation::accelerometer::accelerometer& accelerometer, sensor::orientation::gyroscope::gyroscope& gyroscope):
IMU(accelerometer, gyroscope)
{
}

void Kalman::iteration() {
}

}
