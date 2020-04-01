#define BOUNCE_WITH_PROMPT_DETECTION // Immediately register button press
#define BUTTON_BOUNCE_INTERVAL 15
#define BUTTON_LONG_PRESS_INTERVAL 1000

#define LED_OFF  0
#define LED_LOW  64
#define LED_MID  127
#define LED_HIGH 255

#include <core_pins.h>
#include <stddef.h>
#include <vector>

using std::vector;

#include "Button.h"
#include "Led.h"

class IlluminatedButton : public Button {
  public:
    IlluminatedButton(uint8_t pinButton, uint8_t pinLed0)
    : Button(pinButton),
      leds({ Led(pinLed0) }),
      intensities(1) {}
    IlluminatedButton(uint8_t pinButton, uint8_t pinLed0, uint8_t pinLed1)
    : Button(pinButton),
      leds({ Led(pinLed0), Led(pinLed1) }),
      intensities(2) {}
    IlluminatedButton(uint8_t pinButton, uint8_t pinLed0, uint8_t pinLed1, uint8_t pinLed2)
    : Button(pinButton),
      leds({ Led(pinLed0), Led(pinLed1), Led(pinLed2) }),
      intensities(3) {}

    void init();
    void update();

    bool pressed(bool leading = false);
    bool held(unsigned int duration, bool leading = false);
    bool released();

    int held();

    bool pressedIlluminate(const vector<uint8_t>& values);
    bool pressedIlluminate(const vector<uint8_t>& values, bool leading);
    bool heldIlluminate(const vector<uint8_t>& values, unsigned int duration);
    bool heldIlluminate(const vector<uint8_t>& values, unsigned int duration, bool leading);

    void set(const vector<uint8_t>& values);
    void set(uint8_t ledIndex, uint8_t value);

  private:
    vector<Led> leds;
    vector<uint8_t> intensities;

    void setLedIntensity(const vector<uint8_t>& values, bool save = true);
    void setLedIntensity(uint8_t ledIndex, uint8_t value, bool save = true);
    uint8_t getLedIntensity(uint8_t ledIndex);

    void restore();
};
