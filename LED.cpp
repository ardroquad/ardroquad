#include "LED.h"

using namespace controls;

LED::LED(const uint8_t pin, const bool state, const uint8_t brightness): 
_pin(pin), _state(state), _brightness(brightness) {
  initialize();
};

LED::LED(const uint8_t pin, const bool state):
_pin(pin), _state(state), _brightness(__max_brightness) {
  initialize();
};

LED::LED(const uint8_t pin):
_pin(pin), _state(__state_on), _brightness(__max_brightness) {
  initialize();
};

LED::LED():
_pin(__pin), _state(__state_on), _brightness(__max_brightness) {
  initialize();
};

void LED::initialize() {
  pinMode(_pin, OUTPUT);
};

const void LED::update_pin() {
  if (__state_on == _state) {
    analogWrite(_pin, _brightness);
  } 
  else {
    digitalWrite(_pin, LOW);
  }
};

void LED::brightness(const unsigned char brightness) {
  _brightness = brightness;
  update_pin();
};

uint8_t LED::max_brightness() {
  return __max_brightness;
}

void LED::on() {
  _state = __state_on;
  update_pin();
};

void LED::off() {
  _state = __state_off;
  update_pin();
};
