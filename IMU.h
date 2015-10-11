#ifndef _IMU_h_
#define _IMU_h_

#include "accelerometer.h"
#include "gyroscope.h"

class IMU {
private:
  sensors::orientation::accelerometer::accelerometer& _accelerometer;
  sensors::orientation::gyroscope::gyroscope& _gyroscope;
  struct {
    int32_t X;
    int32_t Y;
    int32_t Z;
  } _estimate[2];
public:
  IMU(sensors::orientation::accelerometer::accelerometer& accelerometer, sensors::orientation::gyroscope::gyroscope& gyroscope);
  void calculate();
};

#endif
