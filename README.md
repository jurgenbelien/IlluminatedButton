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
  button.init();
  delay(250);
  button.off();
}

void loop() {
  button.update();
  if (button.pressed()) {
    button.on();
  }
  if (button.released()) {
    button.off();
  }
}
```
