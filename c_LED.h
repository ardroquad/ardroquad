#ifndef _c_LED_h_
#define _c_LED_h_

#include <Arduino.h>

#define C_LED_STATE_ON true
#define C_LED_STATE_OFF false

#define C_LED_PIN 13
#define C_LED_STATE C_LED_STATE_OFF
#define C_LED_BRIGHTNESS_MAX 255

class c_LED {
private:
  unsigned char _pin;
  bool _state;
  unsigned char _brightness;
  void initialize();
  const void update_pin();
public:
  c_LED(const unsigned char pin, const bool state, const unsigned char brightness);
  c_LED(const unsigned char pin, const bool state);
  c_LED(const unsigned char pin);
  c_LED();
  void brightness(const unsigned char brightness);
  void on();
  void off();
};

#endif







