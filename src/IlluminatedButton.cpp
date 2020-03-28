#include "IlluminatedButton.h"


void IlluminatedButton::init() {
  debouncer.attach(pinButton, INPUT_PULLUP);
  debouncer.interval(BUTTON_BOUNCE_INTERVAL);

  pinMode(pinLed0, OUTPUT);
  set(0, LED_LOW);
  if (pinLed1 != pinLed0) {
    pinMode(pinLed1, OUTPUT);
    set(1, LED_LOW);
  }
  if (pinLed2 != pinLed1) {
    pinMode(pinLed2, OUTPUT);
    set(2, LED_LOW);
  }
}
void IlluminatedButton::update() {
  debouncer.update();
  unsigned long now = millis();

  bool isPressedImmediately = false;
  bool isReleased = false;
  bool isReleasedBeforeLongPress = false;
  bool isLongPressed = 0 < pressedMillis
    && now > pressedMillis + BUTTON_LONG_PRESS_INTERVAL;

  // Handle button state
  if (pressed()) {
    isPressedImmediately = !longPressedCallback;
    pressedMillis = now;
  }
  if (released()) {
    isReleased = true;
    isReleasedBeforeLongPress = !isLongPressed;
    pressedMillis = 0;
    restoreIntensity();
  }

  // Handle callbacks
  if (!!pressedCallback && (isPressedImmediately || isReleasedBeforeLongPress)) {
    pressedCallback();
  }
  if (!!longPressedCallback && isLongPressed) {
    longPressedCallback();
    pressedMillis = 0;
    restoreIntensity();
  }
  if (!!releasedCallback && isReleased) {
    releasedCallback();
  }
}

bool IlluminatedButton::pressed() {
  return debouncer.fell();
}
bool IlluminatedButton::pressed(uint8_t value0) {
  if (pressed()) {
    intensity(0, value0, false);
    return true;
  } else {
    return false;
  }
}
bool IlluminatedButton::pressed(uint8_t value0, uint8_t value1) {
  if (pressed(value0)){
    intensity(1, value1, false);
    return true;
  } else {
    return false;
  }
}
bool IlluminatedButton::pressed(uint8_t value0, uint8_t value1, uint8_t value2) {
  if (pressed(value1)){
    intensity(2, value2, false);
    return true;
  } else {
    return false;
  }
}
bool IlluminatedButton::longPressed() {
  unsigned long now = millis();
  if (
    0 < pressedMillis
    && now > pressedMillis + BUTTON_LONG_PRESS_INTERVAL
  ) {
    restoreIntensity();
    return true;
  } else {
    return false;
  }

}
bool IlluminatedButton::released() {
  return debouncer.rose();
}

// Get pin number for LED
uint8_t IlluminatedButton::pinLed(uint8_t led) {
  switch (led) {
    case 0:  return pinLed0;
    case 1:  return pinLed1;
    default: return pinLed2;
  }
}
// Set illumination without saving state
void IlluminatedButton::intensity(uint8_t led, uint8_t value, bool save) {
  analogWrite(pinLed(led), value);
  if (save) {
    switch (led) {
      case 0:  intensityLed0 = value; break;
      case 1:  intensityLed1 = value; break;
      default: intensityLed2 = value; break;
    }
  }
}
// Restore button state
void IlluminatedButton::restoreIntensity() {
  intensity(pinLed0, intensityLed0, false);
  if (pinLed1 != pinLed0) intensity(pinLed1, intensityLed1, false);
  if (pinLed2 != pinLed1) intensity(pinLed2, intensityLed2, false);
}

