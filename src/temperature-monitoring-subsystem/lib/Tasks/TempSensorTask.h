#ifndef __TEMPSENSORTASK__
#define __TEMPSENSORTASK__

#include "Task.h"
#include "../Components/TempSensor.h"

class TempSensorTask: public Task{
    public:
        TempSensorTask(int pin);
        void init(int period);
        void tick();
    private:
        int pin;
        long check_time;
        int saved_period;
        TempSensor* sensor;

};

#endif