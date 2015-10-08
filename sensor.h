#ifndef _sensor_h_
#define _sensor_h_

namespace sensors {
  
class sensor {
private:
public:
  virtual void initialize() = 0;
  virtual const char* id() const = 0;
  virtual String debug_info() const = 0;
};

}

#endif



