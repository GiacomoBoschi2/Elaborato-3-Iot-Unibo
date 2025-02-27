#ifndef __LED__
#define __LED__

#include <Arduino.h>

class Led{
    public:
        Led(int pin);
        void switchOn();
        void switchOff();
    private:
        int pin;
        int isOn;
};

#endif