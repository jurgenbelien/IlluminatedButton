#include <IlluminatedButton.h>

#define PIN_BUTTON 3
#define PIN_LED 1

IlluminatedButton button(PIN_BUTTON, PIN_LED);

void logPress() {
  Serial.println("Button pressed");
}
void logHeld() {
  Serial.println("Button held");
  button.removeOnHeld(logHeld);
}
void logRelease() {
  Serial.println("Button released");
}

void setup() {
  Serial.begin(9600);
  button.init();

  button.onPressed(logPress);
  button.onHeld(500, logHeld);
  button.onReleased(logRelease);
}

void loop() {
  button.update();
}
