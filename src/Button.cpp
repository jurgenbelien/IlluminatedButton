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
      callbackHandledDuration = 0;
      lastState = currentState;
    }
  }

  executeCallbacks();
}

void Button::executeCallbacks() {
  if (!!onPressedCallback && pressed()) {
    onPressedCallback();
  }
  if (!!onReleasedCallback && released()) {
    onReleasedCallback();
  }
  if (onHeldCallbacks.size() > 0 && held()) {
    for (std::pair<int, function> entry : onHeldCallbacks) {
      int duration = entry.first;
      if (
        callbackHandledDuration < duration // previously handled duration is lower than specified callback duration
        && held(duration, false) // held duration is met
      ) {
        function callback = entry.second;
        callbackHandledDuration = duration;
        callback();
      }
    }
  }
}

bool Button::pressed() {
  return stateChanged && lastState;
}
bool Button::held() {
  return lastState;
}
bool Button::held(int duration, bool updateHandledDuration) {
  bool heldForDuration = lastState // Button is down
    && durationSince(stateChangeTimestamp) > duration // for longer than specified
    && handledDuration < duration // and previously handled duration is lower than specified duration
  ;
  if (heldForDuration && updateHandledDuration) {
    handledDuration = duration;
  }
  return heldForDuration;
}
bool Button::released() {
  return stateChanged && !lastState;
}

// Register callbacks
void Button::onPressed(function callback) {
  onPressedCallback = callback;
}
void Button::onReleased(function callback) {
  onReleasedCallback = callback;
}
void Button::onHeld(int duration, function callback) {
  onHeldCallbacks.insert(std::make_pair(duration, callback));
}
// Remove callbacks
void Button::removeOnPressed() {
  onPressedCallback = NULL;
}
void Button::removeOnReleased() {
  onReleasedCallback = NULL;
}
void Button::removeOnHeld(int duration){
  onHeldCallbacks.erase(duration);
}
void Button::removeOnHeld(function callback){
  for (std::pair<int, function> entry : onHeldCallbacks) {
    if (entry.second == callback) {
      onHeldCallbacks.erase(entry.first);
    }
  }
}

bool Button::getHardwareState() {
  return !digitalRead(pinButton); // with INPUT_PULLUP, down is 1, up is 0;
}
int Button::durationSince(unsigned long timestamp) {
  return (timestamp == 0) ? 0 : millis() - timestamp;
}
