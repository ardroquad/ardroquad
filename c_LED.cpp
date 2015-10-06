#include "c_LED.h"

using namespace controls;

c_LED::c_LED(const uint8_t pin, const bool state, const uint8_t brightness): 
_pin(pin), _state(state), _brightness(brightness) {
  initialize();
};

c_LED::c_LED(const uint8_t pin, const bool state):
_pin(pin), _state(state), _brightness(__max_brightness) {
  initialize();
};

c_LED::c_LED(const uint8_t pin):
_pin(pin), _state(__state_on), _brightness(__max_brightness) {
  initialize();
};

c_LED::c_LED():
_pin(__pin), _state(__state_on), _brightness(__max_brightness) {
  initialize();
};

void c_LED::initialize() {
  pinMode(_pin, OUTPUT);
};

const void c_LED::update_pin() {
  if (__state_on == _state) {
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
  _state = __state_on;
  update_pin();
};

void c_LED::off() {
  _state = __state_off;
  update_pin();
};
