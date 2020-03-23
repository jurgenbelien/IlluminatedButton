#define BOUNCE_LOCK_OUT // Immediately register button press
#define BUTTON_BOUNCE_INTERVAL 25

#define ANALOG_LOW  0
#define ANALOG_MID  96
#define ANALOG_HIGH 255

#include <core_pins.h>
#include <Bounce2.h>

class IlluminatedButton {
  public:
    IlluminatedButton(int pinButton, int pinLed0) :
      pinButton(pinButton), pinLed0(pinLed0), debouncer(Bounce()) {}
    IlluminatedButton(int pinButton, int pinLed0, int pinLed1) :
      pinButton(pinButton), pinLed0(pinLed0), pinLed1(pinLed1), debouncer(Bounce()) {}
    IlluminatedButton(int pinButton, int pinLed0, int pinLed1, int pinLed2) :
      pinButton(pinButton), pinLed0(pinLed0), pinLed1(pinLed1), pinLed2(pinLed2), debouncer(Bounce()) {}

    void init();

    void on();
    void on(int led);
    void onAll();

    void off();
    void off(int led);
    void offAll();

    void dim();
    void dim(int led);

    void intensity(int intensity);
    void intensity(int led, int level);
    void intensityAll(int level);

    void rgb(int r, int g, int b);

    void update();
    bool pressed();
    bool released();
  private:
    int pinButton;
    int pinLed0;
    int pinLed1;
    int pinLed2;
    Bounce debouncer;
};
