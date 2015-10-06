#ifndef _c_sensor_h_
#define _c_sensor_h_

class c_sensor {
private:
public:
  virtual void initialize() = 0;
  virtual String sensor_id() = 0;
  virtual String diagnostic_data() = 0;
};

#endif

