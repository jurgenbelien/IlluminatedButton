#include <IlluminatedButton.h>

#define PIN_BUTTON 3
#define PIN_LED 1

IlluminatedButton button(PIN_BUTTON, PIN_LED);

void setup() {
  Serial.begin(9600);
  button.init();
}

void loop() {
  button.update();

  Serial.println("All conditionals will only be true once per button interaction.");
  if (button.pressed()) {
    Serial.println("Button is pressed.");
  }
  if (button.held(500)) {
    Serial.println("Button is held for 500ms.");
  }
  if (button.released()) {
    Serial.println("Button is released.");
  }
}
