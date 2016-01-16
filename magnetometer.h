#ifndef _magnetometer_h_
#define _magnetometer_h_

#include <EEPROM.h>
#include "orientation.h"

namespace sensor {
namespace orientation {
namespace magnetometer {

class magnetometer: 
public orientation {
private:
  static const uint16_t __calibration_seconds = 30;
  static const uint8_t __calibration_delay = 1;
  static const uint16_t __EEPROM_address = 0;
  static const char* __id;
protected:
  struct {
    struct {
      int32_t X = 0;
      int32_t Y = 0;
      int32_t Z = 0;
    } hard;
    struct {
      double X = 1.0;
      double Y = 1.0;
      double Z = 1.0;
    } soft;
  } _calibration;
public:
  magnetometer();
  virtual const String id() const;
  virtual void calibrate();
  virtual const String calibrate_info() const;
};

}
}
}

#endif
