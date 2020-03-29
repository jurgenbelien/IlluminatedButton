#include "Button.h"

void Button::init() {
  debouncer.attach(pinButton, INPUT_PULLUP);
  debouncer.interval(BUTTON_BOUNCE_INTERVAL);
}

void Button::update() {
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
  }
  if (!!releasedCallback && isReleased) {
    releasedCallback();
  }
}

bool Button::pressed() {
  return isPressed;
}
bool Button::longPressed() {
  return isLongPressed;
}
bool Button::released() {
  return isReleased;
}

// Register callbacks
void Button::onPressed(void (*callback)()) {
  pressedCallback = callback;
}
void Button::onLongPressed(void (*callback)()) {
  longPressedCallback = callback;
}
void Button::onReleased(void (*callback)()) {
  releasedCallback = callback;
}
// Remove callbacks
void Button::removeOnPressed() {
  pressedCallback = NULL;
}
void Button::removeOnLongPressed() {
  longPressedCallback = NULL;
}
void Button::removeOnReleased() {
  releasedCallback = NULL;
}
