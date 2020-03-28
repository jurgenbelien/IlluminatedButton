#define BOUNCE_WITH_PROMPT_DETECTION // Immediately register button press
#define BUTTON_BOUNCE_INTERVAL 15
#define BUTTON_LONG_PRESS_INTERVAL 1000

#define LED_OFF  0
#define LED_LOW  64
#define LED_MID  127
#define LED_HIGH 255

#include <core_pins.h>
#include <Bounce2.h>

class IlluminatedButton {
  public:
    IlluminatedButton(uint8_t pinButton, uint8_t pinLed0)
    : IlluminatedButton(pinButton, pinLed0, pinLed0) {}
    IlluminatedButton(uint8_t pinButton, uint8_t pinLed0, uint8_t pinLed1)
    : IlluminatedButton(pinButton, pinLed0, pinLed1, pinLed1) {}
    IlluminatedButton(uint8_t pinButton, uint8_t pinLed0, uint8_t pinLed1, uint8_t pinLed2)
    : pinButton(pinButton),
      pinLed0(pinLed0),
      pinLed1(pinLed1), // Additional LED pins, when not specified in constructor
      pinLed2(pinLed2), // they will be the same as the preceding LED pin
      debouncer(Bounce()) {}

    void init();
    void update();

    bool pressed();
    bool pressed(uint8_t value0);
    bool pressed(uint8_t value0, uint8_t value1);
    bool pressed(uint8_t value0, uint8_t value1, uint8_t value2);
    bool longPressed();
    bool released();

    // Register callbacks
    void onPressed(void (*callback)()) {
      pressedCallback = callback;
    }
    void onLongPressed(void (*callback)()) {
      longPressedCallback = callback;
    }
    void onReleased(void (*callback)()) {
      releasedCallback = callback;
    }
    // Remove callbacks
    void removeOnPressed() {
      pressedCallback = NULL;
    }
    void removeOnLongPressed() {
      longPressedCallback = NULL;
    }
    void removeOnReleased() {
      releasedCallback = NULL;
    }

    void set(uint8_t value) {
      set(0, value);
    }
    void set(uint8_t led, uint8_t value) {
      intensity(led, value, true);
    }

    // Convienence methods
    void on() {
      on(0);
    }
    void on(uint8_t led) {
      set(led, LED_HIGH);
    }

    void off() {
      off(0);
    }
    void off(uint8_t led) {
      set(led, LED_OFF);
    }

    void dim() {
      dim(0);
    }
    void dim(uint8_t led) {
      set(led, LED_MID);
    }

    void rgb(uint8_t r, uint8_t g, uint8_t b) {
      intensity(0, r, true);
      intensity(1, g, true);
      intensity(2, b, true);
    }

  private:
    const uint8_t pinButton;

    const uint8_t pinLed0;
    const uint8_t pinLed1;
    const uint8_t pinLed2;

    uint8_t pinLed(uint8_t led);

    uint8_t intensityLed0 = LED_LOW;
    uint8_t intensityLed1 = LED_LOW;
    uint8_t intensityLed2 = LED_LOW;

    unsigned long pressedMillis = 0;

    void intensity(uint8_t led, uint8_t value, bool save = false);

    void (*pressedCallback)();
    void (*longPressedCallback)();
    void (*releasedCallback)();

    void restoreIntensity();

    Bounce debouncer;
};
