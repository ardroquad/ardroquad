#ifndef _IMU_h_
#define _IMU_h_

// https://github.com/TKJElectronics/Example-Sketch-for-IMU-including-Kalman-filter/blob/master/IMU/MPU6050/Kalman.h
// http://blog.tkjelectronics.dk/2012/09/a-practical-approach-to-kalman-filter-and-how-to-implement-it/
// http://habrahabr.ru/post/255661/

#include "accelerometer.h"
#include "gyroscope.h"

namespace IMU {

class IMU {
  private:
    double _time_micros;
    sensor::orientation::accelerometer::accelerometer& _accelerometer;
    sensor::orientation::gyroscope::gyroscope& _gyroscope;
  protected:
    double get_dt();
  public:
  IMU(sensor::orientation::accelerometer::accelerometer& accelerometer, sensor::orientation::gyroscope::gyroscope& gyroscope);
  virtual void iteration() = 0;
};

class Kalman:
public IMU {
private:
  class axis {
  private:
    double _Q_angle;
    double _Q_bias;
    double _R;
    double _angle;
    double _bias;
    double _P[2][2];
  public:
    axis();
  };
  axis _X;
  axis _Y;
  axis _Z;
public:
  Kalman(sensor::orientation::accelerometer::accelerometer& accelerometer, sensor::orientation::gyroscope::gyroscope& gyroscope);
  virtual void iteration();
};

}

#endif
