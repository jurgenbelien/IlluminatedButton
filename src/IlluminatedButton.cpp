#include "IlluminatedButton.h"

void IlluminatedButton::init() {
  Button::init();
  for (uint8_t i = 0; i < leds.size(); i++) {
    Led& led = leds[i];
    led.init();
    setLedIntensity(i, LED_OFF);
  }
}

void IlluminatedButton::update() {
  Button::update();
  if (Button::released()) {
    restore();
  }
}

bool IlluminatedButton::pressed(bool leading) {
  return IlluminatedButton::held(0, leading);
}
bool IlluminatedButton::held(unsigned int duration, bool leading) {
  return Button::held(duration, leading);
}
bool IlluminatedButton::released() {
  return Button::released();
}

int IlluminatedButton::held() {
  return Button::held();
}

bool IlluminatedButton::pressedIlluminate(const vector<uint8_t>& values) {
  return IlluminatedButton::pressedIlluminate(values, false);
}
bool IlluminatedButton::pressedIlluminate(const vector<uint8_t>& values, bool leading) {
  return IlluminatedButton::heldIlluminate(values, 0, leading);
}
bool IlluminatedButton::heldIlluminate(const vector<uint8_t>& values, unsigned int duration) {
  return IlluminatedButton::heldIlluminate(values, duration, false);
}
bool IlluminatedButton::heldIlluminate(const vector<uint8_t>& values, unsigned int duration, bool leading) {
  bool heldLeading = Button::held(duration, true);
  if (heldLeading) {
    setLedIntensity(values, false);
  }
  return leading ? heldLeading : IlluminatedButton::held(duration, leading);
}

// Set LED and save state
void IlluminatedButton::set(const vector<uint8_t>& values) {
  setLedIntensity(values);
}
void IlluminatedButton::set(uint8_t ledIndex, uint8_t value) {
  setLedIntensity(ledIndex, value);
}

// Private methods
void IlluminatedButton::setLedIntensity(const vector<uint8_t>& values, bool save) {
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
void IlluminatedButton::restore() {
  for (uint8_t i = 0; i < leds.size() && i < intensities.size(); i++) {
    Led& led = leds[i];
    uint8_t intensity = intensities[i];
    led.set(intensity);
  }
}
