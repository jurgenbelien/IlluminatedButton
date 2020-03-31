
#define THROTTLE_INTERVAL 5

#include <inttypes.h>
#include <core_pins.h>
#include <stddef.h>
#include <map>

typedef void (*function)();
typedef std::pair<int, function> callbackPair;
typedef std::map<unsigned int, function, std::greater<int>> callbacksMap; // sort descending for trailing callbacks

class Button {
  public:
    Button(uint8_t pinButton)
    : pinButton(pinButton) {}

    void init();
    void update();

    bool pressed();
    int held();
    bool held(unsigned int duration, bool leading = false);
    bool released();

    // Callbacks
    void addCallback(function callback, unsigned int timeout = 0, bool leading = false);
    void removeCallback(function callback);
    void removeCallback(function callback, bool leading);

  private:
    const uint8_t pinButton;

    void executeCallbacks();

    bool heldLeading(unsigned int duration);
    bool heldTrailing(unsigned int duration);

    bool state = 0;
    bool stateChanged = false;
    bool getHardwareState();
    unsigned long int stateChangeTimestamp = millis();
    unsigned long int previousStateChangeTimestamp = millis();
    int handledDuration = -1; // hold duration can be 0
    int handledTimeout = -1;  // callback timeout can be 0
    unsigned int durationSince(unsigned long int timestamp);


    callbacksMap leadingCallbacks;
    callbacksMap trailingCallbacks;

};
