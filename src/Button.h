
#define THROTTLE_INTERVAL 5

#include <inttypes.h>
#include <core_pins.h>
#include <stddef.h>
#include <map>

typedef   void (*function)();

class Button {
  public:
    Button(uint8_t pinButton)
    : pinButton(pinButton) {}

    void init();
    void update();

    bool pressed();
    bool held();
    bool held(int duration, bool lead = false);
    bool released();

    // Callbacks
    void onPressed(function callback);
    void onReleased(function callback);
    void onHeld(int duration, function callback);
    void removeOnPressed();
    void removeOnReleased();
    void removeOnHeld(int duration);
    void removeOnHeld(function callback);

  private:
    const uint8_t pinButton;

    bool leading(int duration);
    bool trailing(int duration);

    bool state = 0;
    bool stateChanged = false;
    bool getHardwareState();
    unsigned long int stateChangeTimestamp = millis();
    unsigned long int previousStateChangeTimestamp = millis();
    int handledDuration = 0;
    int durationSince(unsigned long int timestamp);

    void executeCallbacks();
    void (*onPressedCallback)();
    void (*onReleasedCallback)();
    std::map<int, function, std::greater<int>> onHeldCallbacks; // sort highest to lowest

};
