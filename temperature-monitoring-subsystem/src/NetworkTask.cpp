#include "../lib/Tasks/NetworkTask.h"

NetworkTask::NetworkTask(char * ssid, char* password, char* mqtt_server){
    NetworkTask::ssid = ssid;
    NetworkTask::password = password;
    NetworkTask::mqtt_server = mqtt_server;
}

void NetworkTask::init(int period){
    Task::init(period);
    attempt_connect();
    client.setServer(mqtt_server, 1883);
}

void NetworkTask::tick(){
    
    
}

void NetworkTask::attempt_connect(){
    delay(100);
    WiFi.mode(WIFI_STA);
    WiFi.begin(NetworkTask::ssid, NetworkTask::password);
}