#ifndef __NETWORKTASK__
#define __NETWORKTASK__

#include "Task.h"
#include <Ethernet.h>   
#include <WiFi.h>

class NetworkTask: public Task{
    public:
        NetworkTask(char * ssid, char* password);
        void init(int period);
        void tick();
    private:
        void attempt_connect();
        char* ssid;
        char* password;
};

#endif