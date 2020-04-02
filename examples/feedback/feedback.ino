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

  if (button.pressed({ LED_HIGH })) {
    Serial.println("Led is high as soon as button is pressed, ");
    Serial.println("  but this only fires after button is released.");
  }

  if (button.held(500, { LED_MID })) {
    Serial.println("Led is medium as soon as button is held for 500ms, ");
    Serial.println("  but this only fires after button is released.");
  }

  if (button.held(1000, { LED_LOW }, true)) {
    Serial.println("Led is low as soon as button is held for 1000ms, ");
    Serial.println("  and this fires immediately, due to leading being true.");
  }
}

