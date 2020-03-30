#include "IlluminatedButton.h"

void IlluminatedButton::init() {
  Button::init();
  Led::init();
  // Set initial state
  for (uint8_t i = 0; i < pinCount; i++) {
    set(i, 0);
  }
}

void IlluminatedButton::update() {
  Button::update();
  if (Button::released()) {
    restore();
  }
}

bool IlluminatedButton::pressed() {
  return Button::pressed();
}
bool IlluminatedButton::pressed(uint8_t value0) {
  return IlluminatedButton::pressed()
    && setHardwareLedIntensity(0, value0);
}
bool IlluminatedButton::pressed(uint8_t value0, uint8_t value1) {
  return pressed(value0)
    && setHardwareLedIntensity(1, value1);
}
bool IlluminatedButton::pressed(uint8_t value0, uint8_t value1, uint8_t value2) {
  return pressed(value0, value1)
    && setHardwareLedIntensity(2, value2);
}

// Set LED and save state
void IlluminatedButton::set(uint8_t value) {
  set(0, value);
}
void IlluminatedButton::set(uint8_t led, uint8_t value) {
  setLedIntensity(led, value);
}

// Convienence methods
void IlluminatedButton::on() {
  on(0);
}
void IlluminatedButton::on(uint8_t led) {
  set(led, LED_HIGH);
}
void IlluminatedButton::off() {
  off(0);
}
void IlluminatedButton::off(uint8_t led) {
  set(led, LED_OFF);
}
void IlluminatedButton::dim() {
  dim(0);
}
void IlluminatedButton::dim(uint8_t led) {
  set(led, LED_MID);
}
void IlluminatedButton::rgb(uint8_t r, uint8_t g, uint8_t b) {
  set(0, r);
  set(1, g);
  set(2, b);
}

void IlluminatedButton::setLedIntensity(uint8_t led, uint8_t value) {
  if (setHardwareLedIntensity(led, value)) {
    switch (led) {
      case 0:
        led0Intensity = value;
        break;
      case 1:
        led1Intensity = value;
        break;
      case 2:
        led2Intensity = value;
        break;
    }
  }
}
bool IlluminatedButton::setHardwareLedIntensity(uint8_t led, uint8_t value) {
  return Led::set(led, value); // Return boolean in order to add execution to conditional
}

void IlluminatedButton::restore() {
  setHardwareLedIntensity(0, led0Intensity);
  if (Led::pinCount > 1) {
    setHardwareLedIntensity(1, led1Intensity);
  }
  if (Led::pinCount > 2) {
    setHardwareLedIntensity(2, led2Intensity);
  }
}

