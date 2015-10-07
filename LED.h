#ifndef _LED_h_
#define _LED_h_

#include <Arduino.h>
#include "control.h"

namespace controls {
  class LED:
  public control {
  private:
    static const bool __state_on = true;
    static const bool __state_off = false;
    static const uint8_t __pin = 13;
    static const bool __state = __state_off;
    static const uint8_t __max_brightness = 255;
    uint8_t _pin;
    bool _state;
    uint8_t _brightness;
    void initialize();
    const void update_pin();
  public:
    LED(const uint8_t pin, const bool state, const uint8_t brightness);
    LED(const uint8_t pin, const bool state);
    LED(const uint8_t pin);
    LED();
    void brightness(const uint8_t brightness);
    void on();
    void off();
  };
}

#endif







