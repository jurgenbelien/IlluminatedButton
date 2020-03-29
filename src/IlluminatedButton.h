#define BOUNCE_WITH_PROMPT_DETECTION // Immediately register button press
#define BUTTON_BOUNCE_INTERVAL 15
#define BUTTON_LONG_PRESS_INTERVAL 1000

#define LED_OFF  0
#define LED_LOW  64
#define LED_MID  127
#define LED_HIGH 255

#include <core_pins.h>
#include <stddef.h>

#include "Button.h"
#include "Led.h"

class IlluminatedButton : public Button, public Led {
  public:
    IlluminatedButton(uint8_t pinButton, uint8_t pinLed0)
    : IlluminatedButton(pinButton, pinLed0, pinLed0) {}
    IlluminatedButton(uint8_t pinButton, uint8_t pinLed0, uint8_t pinLed1)
    : IlluminatedButton(pinButton, pinLed0, pinLed1, pinLed1) {}
    IlluminatedButton(uint8_t pinButton, uint8_t pinLed0, uint8_t pinLed1, uint8_t pinLed2)
    : Button(pinButton),
      Led(pinLed0, pinLed1, pinLed2) {}

    void init();
    void update();

    bool pressed(uint8_t value0);
    bool pressed(uint8_t value0, uint8_t value1);
    bool pressed(uint8_t value0, uint8_t value1, uint8_t value2);

    void set(uint8_t value0);
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
    bool setHardwareLedIntensity(uint8_t led, uint8_t value);
    void setLedIntensity(uint8_t led, uint8_t value);
    uint8_t getLedIntensity(uint8_t led);

    uint8_t led0Intensity;
    uint8_t led1Intensity;
    uint8_t led2Intensity;

    void restore();
};
