#ifndef __NETWORKTASK__
#define __NETWORKTASK__

#include "Task.h"
#include <Ethernet.h>   
#include <PubSubClient.h>
#include <WiFi.h>

class NetworkTask: public Task{
    public:
        NetworkTask(IPAddress* address, byte mac_address[]);
        void init(int period);
        void tick();
    private:
        void init_wifi(char * ssid, char* password);
        IPAddress* address;
        byte* mac;
        PubSubClient* client;

};

#endif