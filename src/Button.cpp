#include "Button.h"

void Button::init() {
  pinMode(pinButton, INPUT_PULLUP);
  state = getHardwareState();
}

void Button::update() {
  stateChanged = false;   // Reset change tracking
  if (durationSince(stateChangeTimestamp) > THROTTLE_INTERVAL) {
    stateChanged = getHardwareState() != state;
    if (stateChanged) {
      previousStateChangeTimestamp = stateChangeTimestamp;
      stateChangeTimestamp = millis();
      handledDuration = -1;
      handledTimeout = -1;
      state = !state;
    }
  }

  executeCallbacks();
}

bool Button::pressed(bool leading) {
  return (leading) ? stateChanged && state : Button::released();
}
int Button::held() {
  return state ? durationSince(stateChangeTimestamp) : 0;
}
bool Button::held(unsigned int duration, bool leading) {
  // Test for leading side held
  if (leading && heldLeading(duration)) {
    if (handledDuration < (int) duration) {
      handledDuration = duration; // only return true once for this duration
      return true;
    }
    return false;
  }
  // Otherwise test for trailing side
  return (!leading && heldTrailing(duration));
}
bool Button::released() {
  return stateChanged && !state;
}

void Button::addCallback(function callback, unsigned int timeout, bool leading) {
  callbackPair entry = std::make_pair(timeout, callback);
  if (leading) {
    leadingCallbacks.insert(entry);
  } else {
    trailingCallbacks.insert(entry);
  }
}
void Button::removeCallback(function callback) {
  removeCallback(callback, true);
  removeCallback(callback, false);
}
void Button::removeCallback(function callback, bool leading) {
  callbacksMap callbacks = (leading)
    ? leadingCallbacks
    : trailingCallbacks;
  for (callbackPair entry : callbacks) {
    if (entry.second == callback) {
      callbacks.erase(entry.first);
    }
  }
}

// Private methods
void Button::executeCallbacks() {
  if (state && leadingCallbacks.size()) {
    for (callbackPair entry : leadingCallbacks) {
      int timeout = entry.first;
      if (heldLeading(timeout)) {
        if (handledTimeout < (int) timeout) {
          handledTimeout = timeout; // Only fire once for this timeout
          function callback = entry.second;
          callback();
        }
        break;
      }
    }
  } else if (released() && trailingCallbacks.size()) {
    for (callbackPair entry : trailingCallbacks) {
      int timeout = entry.first;
      if (heldTrailing(timeout)) {
        function callback = entry.second;
        callback();
        break;
      }
    }

  }
}

bool Button::heldLeading(unsigned int duration) {
  return (state // Button is down
    && durationSince(stateChangeTimestamp) > duration // for longer than `duration`
  );
}
bool Button::heldTrailing(unsigned int duration) {
  return (stateChanged // Button moved
    && !state // Button is up
    && duration < durationSince(previousStateChangeTimestamp) // and previous state was longer than `duration`
  );
}

bool Button::getHardwareState() {
  return !digitalRead(pinButton); // with INPUT_PULLUP, down is 1, up is 0;
}
unsigned int Button::durationSince(unsigned long timestamp) {
  return (timestamp == 0) ? 0 : millis() - timestamp;
}

