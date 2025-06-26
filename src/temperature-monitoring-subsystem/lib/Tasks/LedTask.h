#ifndef __LEDTASK__
#define __LEDTASK__

#include "Task.h"
#include "../Components/Led.h"

class LedTask: public Task{
    public:
        LedTask(int greenPin,int redPin);
        void init(int period);
        void tick();
    private:
        int redPin,greenPin;
        Led* greenLed;
        Led* redLed;
};

#endif