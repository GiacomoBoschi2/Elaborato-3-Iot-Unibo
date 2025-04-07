#include "../lib/Tasks/NetworkTask.h"


NetworkTask::NetworkTask(IPAddress* address, byte* mac_address){
    NetworkTask::address = address;
    NetworkTask::mac = mac_address;
    client = new PubSubClient();
}

void init_wifi(char * ssid, char* password){
    delay(10);
    Serial.println(String("Connecting to ") + ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

}

void NetworkTask::init(int period){
    Task::init(period);
    client->setServer(*address,59999);
}

void NetworkTask::tick(){

}