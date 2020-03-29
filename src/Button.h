#define BOUNCE_WITH_PROMPT_DETECTION // Immediately register button press
#define BUTTON_BOUNCE_INTERVAL 15
#define BUTTON_LONG_PRESS_INTERVAL 1000

#include <inttypes.h>
#include <core_pins.h>
#include <Bounce2.h>

class Button {
  public:
    Button(uint8_t pinButton)
    : pinButton(pinButton), debouncer(Bounce()) {}

    void init();
    void update();

    // Callbacks
    void onPressed(void (*callback)());
    void onLongPressed(void (*callback)());
    void onReleased(void (*callback)());
    void removeOnPressed();
    void removeOnLongPressed();
    void removeOnReleased();

    bool pressed();
    bool longPressed();
    bool released();

  protected:

  private:
    const uint8_t pinButton;

    Bounce debouncer;

    bool isPressed = false;
    bool isLongPressed = false;
    bool isReleased = false;

    void (*pressedCallback)();
    void (*longPressedCallback)();
    void (*releasedCallback)();

    unsigned long pressedTimestamp = 0;
};
