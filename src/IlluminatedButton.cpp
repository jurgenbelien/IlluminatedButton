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

bool IlluminatedButton::pressed(const vector<uint8_t>& values, bool leading) {
  return IlluminatedButton::held(0, values, leading);
}
bool IlluminatedButton::held(unsigned int duration, const vector<uint8_t>& values, bool leading) {
    bool heldLeading = Button::held(duration, true);
  if (heldLeading) {
    setLedIntensity(values, false);
  }
  return leading ? heldLeading : Button::held(duration, leading);
}

int IlluminatedButton::held() {
  return Button::held();
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
