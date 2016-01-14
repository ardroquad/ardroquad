#ifndef _orientation_h_
#define _orientation_h_

#include <Arduino.h>
#include "sensor.h"

namespace sensor {
namespace orientation {

class orientation:
public sensor {
private:
  static const char* __id;
protected:
  struct {
    int32_t X;
    int32_t Y;
    int32_t Z;
  }
  _values;
  struct {
    int32_t X;
    int32_t Y;
    int32_t Z;
  }
  _correction;
public:
  orientation();
  virtual const String id() const;
  virtual const String debug_info() const;
  virtual void calibrate() = 0;
  void set_correction(const int32_t X, const int32_t Y, const int32_t Z);
  void correct();
  int32_t X() const;
  int32_t Y() const;
  int32_t Z() const;
};

}
}

#endif
