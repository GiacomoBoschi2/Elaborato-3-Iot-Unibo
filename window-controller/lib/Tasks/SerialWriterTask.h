#ifndef __SERIALWRITERTASK__
#define __SERIALWRITERTASK__

#include "SerialHandler.h"
#include "Task.h"

class SerialWriterTask: public Task{
    public:
    SerialWriterTask();
        void init(int period);
        void tick();
    private:
        void handleRotationCommand();
        void handleSwitchToManualCommand();
        char* buffer;
        SerialHandler* handler;
};

#endif