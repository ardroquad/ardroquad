#ifndef _IMU_h_
#define _IMU_h_

// https://github.com/TKJElectronics/Example-Sketch-for-IMU-including-Kalman-filter/blob/master/IMU/MPU6050/Kalman.h
// http://blog.tkjelectronics.dk/2012/09/a-practical-approach-to-kalman-filter-and-how-to-implement-it/
// http://habrahabr.ru/post/255661/

#include "accelerometer.h"
#include "gyroscope.h"
#include "magnetometer.h"

namespace stabilization {
namespace IMU {

class IMU {
  private:
    double _time_micros;
  protected:
    sensor::orientation::accelerometer::accelerometer& _accelerometer;
    sensor::orientation::gyroscope::gyroscope& _gyroscope;
    sensor::orientation::magnetometer::magnetometer& _magnetometer;
    double get_dt();
  public:
  double X_corrected;
  double Y_corrected;
  IMU(sensor::orientation::accelerometer::accelerometer& accelerometer, sensor::orientation::gyroscope::gyroscope& gyroscope, sensor::orientation::magnetometer::magnetometer& magnetometer);
  virtual void iteration() = 0;
  virtual const double E_X_degrees() = 0;
  virtual const double E_Y_degrees() = 0;
  virtual const double E_Z_degrees() = 0;
  virtual const String debug_info();
};

class Kalman:
public IMU {
private:
  class axis {
  private:
    double _Q_degrees;
    double _Q_dps_bias;
    double _R;
    double _dps_bias;
    double _dps;
    double _degrees;
    double _P_0_0;
    double _P_0_1;
    double _P_1_0;
    double _P_1_1;
  public:
    axis();
    void iteration(const double new_degrees, const double new_dps, const double dt);
    void set(const double new_degrees);
    const double E_degrees();
  };
public:
  Kalman(sensor::orientation::accelerometer::accelerometer& accelerometer, sensor::orientation::gyroscope::gyroscope& gyroscope, sensor::orientation::magnetometer::magnetometer& magnetometer);
  axis _X;
  axis _Y;
  axis _Z;
  virtual void iteration();
  virtual const double E_X_degrees();
  virtual const double E_Y_degrees();
  virtual const double E_Z_degrees();
};

}
}

#endif
