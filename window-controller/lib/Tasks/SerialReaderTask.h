#ifndef __SERIALWRITERTASK__
#define __SERIALWRITERTASK__

#include "SerialHandler.h"
#include "Task.h"

class SerialReaderTask: public Task{
    public:
    SerialReaderTask();
        void init(int period);
        void tick();
    private:
        void handleRotationCommand();
        void handleSwitchToManualCommand();
        void handleAlarmModeCommand();
        void undoAlarmMode();
        char* buffer;
        SerialHandler* handler;
};

#endif