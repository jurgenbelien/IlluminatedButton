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
    IlluminatedButton(int pinButton, int pinLed0)
    : IlluminatedButton(pinButton, pinLed0, pinLed0) {}
    IlluminatedButton(int pinButton, int pinLed0, int pinLed1)
    : IlluminatedButton(pinButton, pinLed0, pinLed1, pinLed1) {}
    IlluminatedButton(int pinButton, int pinLed0, int pinLed1, int pinLed2)
    : pinButton(pinButton),
      pinLed0(pinLed0),
      pinLed1(pinLed1),
      pinLed2(pinLed2),
      debouncer(Bounce()) {}

    void init();
    void update();

    bool pressed();
    bool pressed(int value0);
    bool pressed(int value0, int value1);
    bool pressed(int value0, int value1, int value2);
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

    void set(int value) {
      set(0, value);
    }
    void set(int led, int value) {
      intensity(led, value, true);
    }

    // Convienence methods
    void on() {
      on(0);
    }
    void on(int led) {
      set(led, LED_HIGH);
    }

    void off() {
      off(0);
    }
    void off(int led) {
      set(led, LED_OFF);
    }

    void dim() {
      dim(0);
    }
    void dim(int led) {
      set(led, LED_MID);
    }

    void rgb(int r, int g, int b) {
      intensity(0, r, true);
      intensity(1, g, true);
      intensity(2, b, true);
    }

  private:
    int pinButton;

    int pinLed(int led);
    int pinLed0;
    int pinLed1;
    int pinLed2;

    int intensityLed0;
    int intensityLed1;
    int intensityLed2;

    unsigned long pressedMillis = 0;

    void intensity(int led, int value, bool save = false);

    void (*pressedCallback)();
    void (*longPressedCallback)();
    void (*releasedCallback)();

    void restoreIntensity();

    Bounce debouncer;
};
