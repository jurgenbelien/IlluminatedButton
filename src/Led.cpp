#include "Led.h"

void Led::init() {
  pinMode(pinLed0, OUTPUT);
  if (pinCount > 1) {
    pinMode(pinLed1, OUTPUT);
  }
  if (pinCount > 2) {
    pinMode(pinLed2, OUTPUT);
  }
}

// Set LED
void Led::set(uint8_t value) {
  set(0, value);
}
bool Led::set(uint8_t led, uint8_t value) {
  if (led < pinCount) {
    analogWrite(pinLed(led), value);
    return true;
  } else {
    return false;
  }
}

// Convienence methods
void Led::on() {
  on(0);
}
void Led::on(uint8_t led) {
  set(led, LED_HIGH);
}
void Led::off() {
  off(0);
}
void Led::off(uint8_t led) {
  set(led, LED_OFF);
}
void Led::dim() {
  dim(0);
}
void Led::dim(uint8_t led) {
  set(led, LED_MID);
}
void Led::rgb(uint8_t r, uint8_t g, uint8_t b) {
  set(0, r);
  set(1, g);
  set(2, b);
}

// Get pin number for LED
uint8_t Led::pinLed(uint8_t led) {
  switch (led) {
    case 0:  return pinLed0;
    case 1:  return pinLed1;
    default: return pinLed2;
  }
}

