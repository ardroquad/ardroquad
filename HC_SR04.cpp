#include <Arduino.h>
#include "HC_SR04.h"

namespace sensors {
namespace sonar {

const char* HC_SR04::__id = "HC_SR04/sonar";

HC_SR04::HC_SR04() {
  _distance_cm = 0;
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

}
}
