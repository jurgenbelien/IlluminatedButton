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

  if (button.pressed(LED_HIGH)) {
    Serial.println("Button pressed");
  }
}
