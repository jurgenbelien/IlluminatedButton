#include "Button.h"

void Button::init() {
  pinMode(pinButton, INPUT_PULLUP);
  state = getHardwareState();
}

void Button::update() {
  // Reset change tracking
  stateChanged = false;

  if (durationSince(stateChangeTimestamp) > THROTTLE_INTERVAL) {
    stateChanged = getHardwareState() != state;
    if (stateChanged) {
      previousStateChangeTimestamp = stateChangeTimestamp;
      stateChangeTimestamp = millis();
      handledDuration = 0;
      state = !state;
    }
  }

  executeCallbacks();
}

void Button::executeCallbacks() {
  bool hasOnHeldCallbacks = onHeldCallbacks.size() > 0;
  if (!!onPressedCallback && !hasOnHeldCallbacks && pressed()) {
    onPressedCallback();
  }
  if (hasOnHeldCallbacks && released()) {
    function callback = onPressedCallback;
    for (std::pair<int, function> entry : onHeldCallbacks) {
      int duration = entry.first;
      // Highest registered duration lower than state duration is executed
      if (duration < durationSince(previousStateChangeTimestamp)) {
        callback = entry.second;
        break;
      }
    }
    if (callback != NULL) {
      callback();
    }
  }
  if (!!onReleasedCallback && released()) {
    onReleasedCallback();
  }
}

bool Button::pressed() {
  return stateChanged && state;
}
bool Button::held() {
  return state;
}
bool Button::held(int duration, bool lead) {
  // Test for leading side held
  if (lead && leading(duration)) {
    if (handledDuration < duration) {
      handledDuration = duration; // return true once for this duration
      return true;
    }
  }
  // Otherwise test for trailing side
  return (!lead && trailing(duration));
}
bool Button::released() {
  return stateChanged && !state;
}

// Register callbacks
void Button::onPressed(function callback) {
  onPressedCallback = callback;
}
void Button::onReleased(function callback) {
  onReleasedCallback = callback;
}
void Button::onHeld(function callback, int duration) {
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

bool Button::leading(int duration) {
  return (state // Button is down
    && durationSince(stateChangeTimestamp) > duration // for longer than `duration`
  );
}

bool Button::trailing(int duration) {
  return (stateChanged // Button moved
    && !state // Button is up
    && duration < durationSince(previousStateChangeTimestamp) // and previous state was longer than `duration`
  );
}

bool Button::getHardwareState() {
  return !digitalRead(pinButton); // with INPUT_PULLUP, down is 1, up is 0;
}
int Button::durationSince(unsigned long timestamp) {
  return (timestamp == 0) ? 0 : millis() - timestamp;
}
