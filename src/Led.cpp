#include "Led.h"

void Led::init() {
  pinMode(pinLed, OUTPUT);
}

void Led::set(uint8_t value) {
  analogWrite(pinLed, value);
  intensity = value;
}

uint8_t Led::get() {
  return intensity;
}
