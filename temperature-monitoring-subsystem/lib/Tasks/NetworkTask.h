#ifndef __NETWORKTASK__
#define __NETWORKTASK__

#include "Task.h"
#include <Ethernet.h>   


class NetworkTask: public Task{
    public:
        NetworkTask(IPAddress address);
        void init(int period);
        void tick();
    private:
        IPAddress address;
};

#endif