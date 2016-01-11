#include "IMU.h"

namespace stabilization {
namespace IMU {

IMU::IMU(sensor::orientation::accelerometer::accelerometer& accelerometer, sensor::orientation::gyroscope::gyroscope& gyroscope, sensor::orientation::magnetometer::magnetometer& magnetometer):
  _accelerometer(accelerometer),
  _gyroscope(gyroscope),
  _magnetometer(magnetometer)
{
  _time_micros = micros();
}

double IMU::get_dt() {
  double time_micros = _time_micros;
  _time_micros = micros();
  return (_time_micros - time_micros) / (double)1000000;
}

const String IMU::debug_info() {
  String s;
  s += "X: "; s += E_X_degrees(); s += ", Y: "; s += E_Y_degrees(); s += ", Z: "; s += E_Z_degrees();
  return s;
}

Kalman::axis::axis() {
  _Q_degrees = 0.001;
  _Q_dps_bias = 0.003;
  _R = 0.03;
  _degrees = 0.0;
  _dps_bias = 0.0;
  _dps = 0.0;
  _P_0_0 = 0.0;
  _P_0_1 = 0.0;
  _P_1_0 = 0.0;
  _P_1_1 = 0.0;
}

void Kalman::axis::iteration(const double new_degrees, const double new_dps, const double dt) {
  _dps = new_dps - _dps_bias;
  _degrees += dt * (double)_dps;
  _P_0_0 += dt * (dt * _P_1_1 - _P_0_1 - _P_1_0 + _Q_degrees);
  _P_0_1 -= dt * _P_1_1;
  _P_1_0 -= dt * _P_1_1;
  _P_1_1 += _Q_dps_bias * dt;
  double S = _P_0_0 + _R;
  double K_0 = _P_0_0 / S;
  double K_1 = _P_1_0 / S;
  double d = new_degrees - _degrees;
  _degrees += K_0 * d;
  _dps_bias += K_1 * d;
  _P_0_0 -= K_0 * _P_0_0;
  _P_0_1 -= K_0 * _P_0_1;
  _P_1_0 -= K_1 * _P_0_0;
  _P_1_1 -= K_1 * _P_0_1;
}

const double Kalman::axis::E_degrees() {
  return _degrees;
}

Kalman::Kalman(sensor::orientation::accelerometer::accelerometer& accelerometer, sensor::orientation::gyroscope::gyroscope& gyroscope, sensor::orientation::magnetometer::magnetometer& magnetometer):
IMU(accelerometer, gyroscope, magnetometer)
{
}

void Kalman::iteration() {
  _accelerometer.measure();
  _gyroscope.measure();
  _magnetometer.measure();
  double dt = get_dt();
  _X.iteration(_accelerometer.X_degrees(), -_gyroscope.Y_dps(), dt);
  _Y.iteration(_accelerometer.Y_degrees(), _gyroscope.X_dps(), dt);
  _Z.iteration(atan2(_magnetometer.Y(), _magnetometer.X()) * 180 / M_PI, _gyroscope.Z_dps(), dt);
}

const double Kalman::E_X_degrees() {
  return _X.E_degrees();
}

const double Kalman::E_Y_degrees() {
  return _Y.E_degrees();
}

const double Kalman::E_Z_degrees() {
  return _Z.E_degrees();
}

}
}
