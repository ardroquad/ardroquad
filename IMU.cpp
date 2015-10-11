#include "IMU.h"

IMU::IMU(sensors::orientation::accelerometer::accelerometer& accelerometer, sensors::orientation::gyroscope::gyroscope& gyroscope):
  _accelerometer(accelerometer),
  _gyroscope(gyroscope)
{
  _estimate[0].X = _accelerometer.X_normalized();;
  _estimate[0].Y = _accelerometer.Y_normalized();;
  _estimate[0].Z = _accelerometer.Z_normalized();;
  _estimate[1].X = 0;
  _estimate[1].Y = 0;
  _estimate[1].Z = 0;
}

void IMU::calculate() {
  _estimate[1] = _estimate[0];
  double AXZ1 = atan2(_estimate[1].X, _estimate[1].Z);
}

