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

  if (button.pressed()) {
    Serial.println("Button pressed");
  }
  if (button.longPressed()) {
    Serial.println("Button long-pressed");
  }
  if (button.released()) {
    Serial.println("Button released");
  }
}
