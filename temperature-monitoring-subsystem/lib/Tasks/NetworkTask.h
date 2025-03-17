#ifndef __NETWORKTASK__
#define __NETWORKTASK__

#include "Task.h"
#include <Ethernet.h>   
#include <PubSubClient.h>

class NetworkTask: public Task{
    public:
        NetworkTask(IPAddress* address, byte mac_address[]);
        void init(int period);
        void tick();
    private:
        IPAddress* address;
        byte* mac;
        PubSubClient* client;

};

#endif