#define THROTTLE_INTERVAL 25

#include <inttypes.h>
#include <core_pins.h>
#include <stddef.h>

class Button {
  public:
    Button(uint8_t pinButton)
    : pinButton(pinButton) {}

    void init();
    void update();

    bool pressed();
    bool held();
    bool held(int duration);
    bool released();

    // Callbacks
    void onPressed(void (*callback)());
    void onReleased(void (*callback)());
    void removeOnPressed();
    void removeOnReleased();

  private:
    const uint8_t pinButton;

    bool lastState = 0;
    bool stateChanged = false;
    bool getHardwareState();
    unsigned long int stateChangeTimestamp = 0;
    unsigned long int handledStateChangeTimestamp = 0;
    int stateDuration();

    void executeCallbacks();
    void (*pressedCallback)();
    void (*longPressedCallback)();
    void (*releasedCallback)();

};
