#include "IlluminatedButton.h"

void IlluminatedButton::init() {
  pinMode(pinLed0, OUTPUT);
  dim(0);
  if (pinLed1) {
    pinMode(pinLed1, OUTPUT);
    dim(1);
  }
  if (pinLed2) {
    pinMode(pinLed2, OUTPUT);
    dim(2);
  }
  debouncer.attach(pinButton, INPUT_PULLUP);
  debouncer.interval(BUTTON_BOUNCE_INTERVAL);
}

void IlluminatedButton::update() {
  debouncer.update();
}

bool IlluminatedButton::pressed() {
  return debouncer.fell();
}

bool IlluminatedButton::released() {
  return debouncer.rose();
}

void IlluminatedButton::on() {
  on(0);
}

void IlluminatedButton::on(int led) {
  intensity(led, ANALOG_HIGH);
}
void IlluminatedButton::onAll() {
  intensityAll(ANALOG_HIGH);
}

void IlluminatedButton::off() {
  off(0);
}

void IlluminatedButton::off(int led) {
  intensity(led, ANALOG_LOW);
}

void IlluminatedButton::offAll() {
  intensityAll(ANALOG_LOW);
}

void IlluminatedButton::dim() {
  dim(0);
}

void IlluminatedButton::dim(int led) {
  intensity(led, ANALOG_MID);
}

void IlluminatedButton::intensity(int level) {
  intensity(0, level);
}

void IlluminatedButton::intensity(int led, int level) {
  switch (led) {
    case 0:
      analogWrite(pinLed0, level);
      break;
    case 1:
      analogWrite(pinLed1, level);
      break;
    case 2:
      analogWrite(pinLed2, level);
      break;
  }
}

void IlluminatedButton::intensityAll(int level) {
  analogWrite(pinLed0, level);
  if (pinLed1) analogWrite(pinLed1, level);
  if (pinLed2) analogWrite(pinLed2, level);
}

void IlluminatedButton::rgb(int r, int g, int b) {
  analogWrite(pinLed0, r);
  analogWrite(pinLed1, g);
  analogWrite(pinLed2, b);
}
