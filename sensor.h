#ifndef _sensor_h_
#define _sensor_h_

namespace sensors {
  class sensor {
  private:
  public:
    virtual void initialize() = 0;
    virtual String diagnostic_data() = 0;
  };
}

#endif



