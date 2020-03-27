#include "IlluminatedButton.h"

void IlluminatedButton::init() {
  debouncer.attach(pinButton, INPUT_PULLUP);
  debouncer.interval(BUTTON_BOUNCE_INTERVAL);

  pinMode(pinLed0, OUTPUT);
  set(0, LED_LOW);
  if (pinLed1) {
    pinMode(pinLed1, OUTPUT);
    set(1, LED_LOW);
  }
  if (pinLed2) {
    pinMode(pinLed2, OUTPUT);
    set(2, LED_LOW);
  }
}
void IlluminatedButton::update() {
  debouncer.update();
  // Restore last LED values when releasing button
  released();
}

bool IlluminatedButton::pressed() {
  return debouncer.fell();
}
bool IlluminatedButton::pressed(int value0) {
  if (pressed()) {
    intensity(0, value0, false);
    return true;
  } else {
    return false;
  }
}
bool IlluminatedButton::pressed(int value0, int value1) {
  if (pressed(value0)){
    intensity(1, value1, false);
    return true;
  } else {
    return false;
  }
}
bool IlluminatedButton::pressed(int value0, int value1, int value2) {
  if (pressed(value1)){
    intensity(2, value2, false);
    return true;
  } else {
    return false;
  }
}
bool IlluminatedButton::released() {
  if (debouncer.rose()) {
    restoreIntensity();
    return true;
  } else {
    return false;
  }
}

// Get pin number for LED;
int IlluminatedButton::pinLed(int led) {
  switch (led) {
    case 0:  return pinLed0;
    case 1:  return pinLed1;
    default: return pinLed2;
  }
}
// Set illumination without saving state
void IlluminatedButton::intensity(int led, int value, bool save) {
  analogWrite(pinLed(led), value);
  if (save) {
    switch (led) {
      case 0:  intensityLed0 = value; break;
      case 1:  intensityLed1 = value; break;
      default: intensityLed2 = value; break;
    }
  }
}

// Restore previously set value
void IlluminatedButton::restoreIntensity() {
  intensity(pinLed0, intensityLed0, false);
  if (intensityLed1) intensity(pinLed1, intensityLed1, false);
  if (intensityLed2) intensity(pinLed2, intensityLed2, false);
}

