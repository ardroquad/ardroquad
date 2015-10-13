#include <Arduino.h>
#include "HC_SR04.h"

namespace sensors {
namespace sonar {

const char* HC_SR04::__id = "HC_SR04/sonar";
uint64_t HC_SR04::_echo_micros = 0;
HC_SR04::interruption HC_SR04::_interruption = released;
double HC_SR04::_distance_cm = 0;

void HC_SR04::echo() {
  switch (_interruption) {
  case waiting_HIGH:
    _echo_micros = micros();
    _interruption = waiting_LOW;
    attachInterrupt(__interrupt_echo, echo, FALLING);
    break;
  case waiting_LOW:
    _distance_cm = micros() - _echo_micros;
    _distance_cm = _distance_cm / 1000 > 26 ? -1 : _distance_cm /= 58;
    _echo_micros = 0;
    _interruption = released;
    detachInterrupt(__interrupt_echo);
  break;
  case released:
  break;
  }
}

void HC_SR04::initialize() {
  pinMode(__pin_trigger, OUTPUT);
  pinMode(__pin_echo, INPUT);
}

const char* HC_SR04::id() const {
  return __id;
}

String HC_SR04::debug_info() const {
  String s;
  s += __id; s += ": distance(cm): "; s += _distance_cm;
  return s;
}

double HC_SR04::get_distance_cm() const {
  return _distance_cm;
}

bool HC_SR04::measure() {
  if (_interruption != released) {
    return false;
  }
  _interruption = waiting_HIGH;
  attachInterrupt(__interrupt_echo, echo, RISING);
  digitalWrite(__pin_trigger, LOW);
  delayMicroseconds(__trigger_delay_LOW);
  digitalWrite(__pin_trigger, HIGH);
  delayMicroseconds(__trigger_delay_HIGH);
  digitalWrite(__pin_trigger, LOW);
}

}
}
