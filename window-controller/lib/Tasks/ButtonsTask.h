#ifndef __BUTTONSTASK__
#define __BUTTONSTASK__

#include "Task.h"
#include "Button.h"

class ButtonsTask: public Task{
    public:
        ButtonsTask(int buttonPin);
        void init(int period);
        void tick();
    private:
        int button_pin;
        Button* button_handler;
        int ticks_elapsed;
        enum {PRESSED,NOT_PRESSED} status;
};
#endif