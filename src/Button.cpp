#include "Button.h"

void Button::init() {
  pinMode(pinButton, INPUT_PULLUP);
  lastState = getHardwareState();
}

void Button::update() {
  // Reset change tracking
  stateChanged = false;

  if (durationSince(stateChangeTimestamp) > THROTTLE_INTERVAL) {
    bool currentState = getHardwareState();
    stateChanged = currentState != lastState;

    if (stateChanged) {
      stateChangeTimestamp = millis();
      handledDuration = 0;
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
bool Button::held() {
  return lastState;
}
bool Button::held(int duration) {
  bool heldForDuration = lastState // Button is down
    && durationSince(stateChangeTimestamp) > duration // for longer than specified duration
    && handledDuration < duration // and previously handled duration is lower than specified duration
  ;
  if (heldForDuration) {
    handledDuration = duration;
  }
  return heldForDuration;
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
int Button::durationSince(unsigned long timestamp) {
  return (timestamp == 0) ? 0 : millis() - timestamp;
}
