#ifndef __SERIALTASK__
#define __SERIALTASK__

#include "SerialHandler.h"
#include "Task.h"

class SerialTask: public Task{
    public:
        SerialTask();
        void init(int period);
        void tick();
    private:
        char* buffer;
        SerialHandler* handler;
};

#endif