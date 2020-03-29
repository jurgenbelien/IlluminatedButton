#include "Button.h"

void Button::init() {
  pinMode(pinButton, INPUT_PULLUP);
  lastState = getHardwareState();
}

void Button::update() {
  // Reset change tracking
  stateChanged = false;

  // Throttled checking of hardware state
  if (THROTTLE_INTERVAL < stateDuration()) {
    bool currentState = getHardwareState();
    stateChanged = currentState != lastState;

    if (stateChanged) {
      stateChangeTimestamp = millis();
      lastState = currentState;
    }
  }

  executeCallbacks();
}

void Button::executeCallbacks() {
  if (!!pressedCallback && pressed()) {
    pressedCallback();
  }
  if (!!releasedCallback && released()) {
    releasedCallback();
  }
}

bool Button::pressed() {
  return stateChanged && lastState;
}
}
bool Button::released() {
  return stateChanged && !lastState;
}

// Register callbacks
void Button::onPressed(void (*callback)()) {
  pressedCallback = callback;
}
void Button::onReleased(void (*callback)()) {
  releasedCallback = callback;
}
// Remove callbacks
void Button::removeOnPressed() {
  pressedCallback = NULL;
}
void Button::removeOnReleased() {
  releasedCallback = NULL;
}

bool Button::getHardwareState() {
  return !digitalRead(pinButton); // with INPUT_PULLUP, down is 1, up is 0;
}
int Button::stateDuration() {
  return millis() - stateChangeTimestamp;
}
