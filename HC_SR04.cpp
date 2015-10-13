#include <Arduino.h>
#include "HC_SR04.h"

namespace sensor {
namespace sonar {

const char* HC_SR04::__id = "HC_SR04";
uint64_t HC_SR04::_echo_micros = 0;
HC_SR04::interruption HC_SR04::_interruption = released;

void HC_SR04::echo() {
  switch (_interruption) {
  case waiting_HIGH:
    _echo_micros = micros();
    _interruption = waiting_LOW;
    attachInterrupt(__interrupt_echo, echo, FALLING);
    break;
  case waiting_LOW:
    _cm = micros() - _echo_micros;
    _cm = _cm / 1000 > 26 ? -1 : _cm /= 58;
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

const String HC_SR04::id() const {
  String s;
  s += sonar::id(); s += id_divider(); s += __id;
  return s;
}

const String HC_SR04::debug_info() const {
  String s;
  s += id(); s += ": distance(cm): "; s += _cm;
  return s;
}

void HC_SR04::measure() {
  if (_interruption != released) {
    return;
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
