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

  // Handle last update() iteration
  if (isPressed) {
    pressedTimestamp = millis();
  }
  if (isLongPressed) {
    pressedTimestamp = 0;
  }
  if (isReleased) {
    pressedTimestamp = 0;
    restoreIntensity();
  }

  // Get state from hardware
  isPressed = debouncer.fell();
  isLongPressed = (0 < pressedTimestamp && millis() > pressedTimestamp + BUTTON_LONG_PRESS_INTERVAL);
  isReleased = debouncer.rose();

  // Run callbacks
  bool isPressedImmediately = isPressed && !longPressedCallback;
  bool isReleasedBeforeLongPress = isReleased && !isLongPressed;

  if (!!pressedCallback && (isPressedImmediately || isReleasedBeforeLongPress)) {
    pressedCallback();
  }
  if (!!longPressedCallback && isLongPressed) {
    longPressedCallback();
    restoreIntensity();
  }
  if (!!releasedCallback && isReleased) {
    releasedCallback();
  }
}

bool IlluminatedButton::pressed() {
  return isPressed;
}
bool IlluminatedButton::pressed(uint8_t value0) {
  return (pressed() && intensity(0, value0));
}
bool IlluminatedButton::pressed(uint8_t value0, uint8_t value1) {
  return (pressed(value0) && intensity(1, value1));
}
bool IlluminatedButton::pressed(uint8_t value0, uint8_t value1, uint8_t value2) {
  return (pressed(value1) && intensity(2, value2));
}
bool IlluminatedButton::longPressed() {
  return isLongPressed;
}
bool IlluminatedButton::released() {
  return isReleased;
}

// Register callbacks
void IlluminatedButton::onPressed(void (*callback)()) {
  pressedCallback = callback;
}
void IlluminatedButton::onLongPressed(void (*callback)()) {
  longPressedCallback = callback;
}
void IlluminatedButton::onReleased(void (*callback)()) {
  releasedCallback = callback;
}
// Remove callbacks
void IlluminatedButton::removeOnPressed() {
  pressedCallback = NULL;
}
void IlluminatedButton::removeOnLongPressed() {
  longPressedCallback = NULL;
}
void IlluminatedButton::removeOnReleased() {
  releasedCallback = NULL;
}

// Set LED
void IlluminatedButton::set(uint8_t value) {
  set(0, value);
}
void IlluminatedButton::set(uint8_t led, uint8_t value) {
  intensity(led, value, true);
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
  intensity(0, r, true);
  intensity(1, g, true);
  intensity(2, b, true);
}

// Get pin number for LED
uint8_t IlluminatedButton::pinLed(uint8_t led) {
  switch (led) {
    case 0:  return pinLed0;
    case 1:  return pinLed1;
    default: return pinLed2;
  }
}
// Set illumination
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
// Set illumnation without saving, used inside conditionals
bool IlluminatedButton::intensity(uint8_t led, uint8_t value) {
  intensity(led, value, false);
  return true;
}
// Restore button LED state
bool IlluminatedButton::restoreIntensity() {
  intensity(pinLed0, intensityLed0, false);
  if (pinLed1 != pinLed0) intensity(pinLed1, intensityLed1, false);
  if (pinLed2 != pinLed1) intensity(pinLed2, intensityLed2, false);
  return true;
}
