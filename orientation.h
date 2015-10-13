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
  virtual void update() = 0;
  void set_correction_X(const int32_t correction);
  void set_correction_Y(const int32_t correction);
  void set_correction_Z(const int32_t correction);
  void correct();
  int32_t X() const;
  int32_t Y() const;
  int32_t Z() const;
};

}
}

#endif
