#define LED_OFF  0
#define LED_LOW  64
#define LED_MID  127
#define LED_HIGH 255

#include <core_pins.h>

class Led {
  public:
    Led(uint8_t pinLed0)
    : Led(pinLed0 ,pinLed0, pinLed0, 1) {}
    Led(uint8_t pinLed0 ,uint8_t pinLed1)
    : Led(pinLed0 ,pinLed1, pinLed1, 2) {}
    Led(uint8_t pinLed0 ,uint8_t pinLed1, uint8_t pinLed2)
    : Led(pinLed0 ,pinLed1, pinLed2, 3) {}
    Led(uint8_t pinLed0 ,uint8_t pinLed1, uint8_t pinLed2, uint8_t pinCount)
    : pinCount(pinCount), pinLed0(pinLed0), pinLed1(pinLed1), pinLed2(pinLed2) {}


    void init();

    void set(uint8_t value);
    bool set(uint8_t led, uint8_t value);

    // Convienence methods
    void on();
    void on(uint8_t led);
    void off();
    void off(uint8_t led);
    void dim();
    void dim(uint8_t led);
    void rgb(uint8_t r, uint8_t g, uint8_t b);

  protected:
    const uint8_t pinCount;
    uint8_t pinLed(uint8_t led);

  private:
    const uint8_t pinLed0;
    const uint8_t pinLed1;
    const uint8_t pinLed2;

};
