#include "../lib/Tasks/NetworkTask.h"
#define BUF_SIZE 16

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.println(String("Message arrived on [") + topic + "] len: " + length );
}

NetworkTask::NetworkTask(char * ssid, char* password, char* mqtt_server){
    NetworkTask::ssid = ssid;
    NetworkTask::password = password;
    NetworkTask::mqtt_server = mqtt_server;
}

void NetworkTask::init(int period){
    Task::init(period);
    attempt_connect();
    NetworkTask::client = new PubSubClient(NetworkTask::espClient);
    client->setServer(mqtt_server, 1883);
    client->subscribe("frequency-topic");
    client->setCallback(callback);
}

void NetworkTask::tick(){
    if(client->connected()){
        char msg[BUF_SIZE];
        snprintf(msg, BUFSIZ+1, "%f", 15.0f);
        client->publish("temperature-topic", "sas"); 
    }
    else{
        String clientId = String("esiot-2043-client-")+String(random(0xffff), HEX);
        client->connect(clientId.c_str());
    }
}

void NetworkTask::attempt_connect(){
    delay(100);
    WiFi.mode(WIFI_STA);
    WiFi.begin(NetworkTask::ssid, NetworkTask::password);
}