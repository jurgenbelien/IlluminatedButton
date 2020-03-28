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

void setup() {
  Serial.begin(9600);
  button.init();
}

void loop() {
  button.update();

  if (button.pressed()) {
    Serial.println("Button pressed");
  }
}
```

Take a look at the [examples](./examples) to see how to add callbacks and add momentary button press feedback.
