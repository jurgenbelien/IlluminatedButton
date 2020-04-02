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

  if (button.held(500, { LED_MID })) {
    Serial.println("Only executes when button is released after being held for 500ms");
  } else {
    if (button.pressed({ LED_HIGH })) {
      Serial.println("Only executes when button is released before button.held() condition is met");
    }
  }
}
