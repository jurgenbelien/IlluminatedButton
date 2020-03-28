#define BOUNCE_WITH_PROMPT_DETECTION // Immediately register button press
#define BUTTON_BOUNCE_INTERVAL 15
#define BUTTON_LONG_PRESS_INTERVAL 1000

#define LED_OFF  0
#define LED_LOW  64
#define LED_MID  127
#define LED_HIGH 255

#include <core_pins.h>
#include <stddef.h>
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


    // Callbacks
    void onPressed(void (*callback)());
    void onLongPressed(void (*callback)());
    void onReleased(void (*callback)());
    void removeOnPressed();
    void removeOnLongPressed();
    void removeOnReleased();

    void set(uint8_t value);
    void set(uint8_t led, uint8_t value);

    // Convienence methods
    void on();
    void on(uint8_t led);
    void off();
    void off(uint8_t led);
    void dim();
    void dim(uint8_t led);
    void rgb(uint8_t r, uint8_t g, uint8_t b);

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

    void intensity(uint8_t led, uint8_t value, bool save);
    bool intensity(uint8_t led, uint8_t value);

    void (*pressedCallback)();
    void (*longPressedCallback)();
    void (*releasedCallback)();

    void restoreIntensity();

    Bounce debouncer;
};
