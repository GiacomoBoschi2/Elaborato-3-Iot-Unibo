#ifndef __NETWORKTASK__
#define __NETWORKTASK__

#include "Task.h"
#include <Ethernet.h>   
#include <PubSubClient.h>
#include <WiFi.h>

class NetworkTask: public Task{
    public:
        NetworkTask(char * ssid, char* password, char* mqtt_server);
        void init(int period);
        void tick();
    private:
        void attempt_connect();
        char* ssid;
        char* password;
        char* mqtt_server;
        WiFiClient espClient;
        PubSubClient client;

};

#endif