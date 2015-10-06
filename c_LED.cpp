#include "c_LED.h"

c_LED::c_LED(const unsigned char pin, const bool state, const unsigned char brightness): 
_pin(pin), _state(state), _brightness(brightness) {
  initialize();
};

c_LED::c_LED(const unsigned char pin, const bool state):
_pin(pin), _state(state), _brightness(C_LED_BRIGHTNESS_MAX) {
  initialize();
};

c_LED::c_LED(const unsigned char pin):
_pin(pin), _state(C_LED_STATE_ON), _brightness(C_LED_BRIGHTNESS_MAX) {
  initialize();
};

c_LED::c_LED():
_pin(C_LED_PIN), _state(C_LED_STATE_ON), _brightness(C_LED_BRIGHTNESS_MAX) {
  initialize();
};
void c_LED::initialize() {
  pinMode(_pin, OUTPUT);
};

const void c_LED::update_pin() {
  if (C_LED_STATE_ON == _state) {
    analogWrite(_pin, _brightness);
  } 
  else {
    digitalWrite(_pin, LOW);
  }
};

void c_LED::brightness(const unsigned char brightness) {
  _brightness = brightness;
  update_pin();
};

void c_LED::on() {
  _state = C_LED_STATE_ON;
  update_pin();
};

void c_LED::off() {
  _state = C_LED_STATE_OFF;
  update_pin();
};
