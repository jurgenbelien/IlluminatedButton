#include "IlluminatedButton.h"

void IlluminatedButton::init() {
  Button::init();
  for (uint8_t i = 0; i < leds.size(); i++) {
    Led& led = leds[i];
    led.init();
    set(i, LED_OFF);
  }
}

void IlluminatedButton::update() {
  Button::update();
  if (Button::released()) {
    restore();
  }
}

bool IlluminatedButton::pressed(const vector<uint8_t>& values, bool leading) {
  return IlluminatedButton::held(0, values, leading);
}
bool IlluminatedButton::held(unsigned int duration, const vector<uint8_t>& values, bool leading) {
    bool heldLeading = Button::held(duration, true);
  if (heldLeading) {
    setVolatile(values);
  }
  return leading ? heldLeading : Button::held(duration, leading);
}

int IlluminatedButton::held() {
  return Button::held();
}

void IlluminatedButton::set(const vector<uint8_t>& values) {
  setLedIntensities(values, true);
}
void IlluminatedButton::set(uint8_t ledIndex, uint8_t value) {
  setLedIntensity(ledIndex, value, true);
}

void IlluminatedButton::setVolatile(const vector<uint8_t>& values) {
  setLedIntensities(values, false);
}
void IlluminatedButton::setVolatile(uint8_t ledIndex, uint8_t value) {
  setLedIntensity(ledIndex, value, false);
}

void IlluminatedButton::restore() {
  IlluminatedButton::setLedIntensities(intensities, false);
}

// Private methods
void IlluminatedButton::setLedIntensities(const vector<uint8_t>& values, bool save) {
  for (uint8_t i = 0; i < values.size() && i < leds.size(); i++) {
    setLedIntensity(i, values[i], save);
  }
}

void IlluminatedButton::setLedIntensity(uint8_t ledIndex, uint8_t value, bool save) {
  leds[ledIndex].set(value);
  if (save) {
    intensities[ledIndex] = value;
  }
}

