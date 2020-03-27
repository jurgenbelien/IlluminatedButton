# IlluminatedButton
Class for working with buttons with leds inside. This class is dependent on
[Bounce2](https://github.com/thomasfredericks/Bounce2) class.

**Note: multi-LED functionality is untested**

## Example usage

```cpp
#include "./src/IlluminatedButton.h"

#define PIN_BUTTON 3
#define PIN_LED 1

IlluminatedButton button(PIN_BUTTON, PIN_LED);

void logPressed() {
  Serial.println("Button pressed"):
}
void logLongPressed() {
  Serial.println("Button long-pressed"):
}

void setup() {
  Serial.begin(9600);

  button.init();
  delay(250);
  button.off();

  // Add functionality with callbacks...
  button.onPressed(logPressed);
  button.onLongPressed(logLongPressed)
}

void loop() {
  button.update();

  // ...or use conditionals inside loop()
  if(button.released()) {
    Serial.println("Button released");
  }
}
```
