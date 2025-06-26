#ifndef __SERIALTASK__
#define __SERIALTASK__

#include "SerialHandler.h"
#include "Task.h"

class SerialWriterTask: public Task{
    public:
        SerialWriterTask();
        void init(int period);
        void tick();
    private:
        char* buffer;
        SerialHandler* handler;
};

#endif