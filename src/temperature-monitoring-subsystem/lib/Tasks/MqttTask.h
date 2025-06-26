#ifndef __MQTTTASK__
#define __MQTTTASK__

#include "Task.h"
#include <Ethernet.h>   
#include <PubSubClient.h>
#include <WiFi.h>

class MqttTask: public Task{
    public:
        MqttTask(char* mqtt_server);
        void init(int period);
        void tick();
    private:
        char* mqtt_server;
        int frequency = 0;
        int tick_counter = 0;
        WiFiClient espClientWriter;
        WiFiClient espClientReader;
        PubSubClient writer;
        PubSubClient reader;

};

#endif