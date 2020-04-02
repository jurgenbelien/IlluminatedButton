#define LED_OFF  0
#define LED_LOW  64
#define LED_MID  127
#define LED_HIGH 255

#include <core_pins.h>

class Led {
  public:
    Led(uint8_t pinLed)
    : pinLed(pinLed) {}

    void init();

    void set(uint8_t value);
    uint8_t get();

  private:
    const uint8_t pinLed;
    uint8_t intensity = 0;
};
