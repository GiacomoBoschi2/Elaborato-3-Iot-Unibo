#include "../lib/Tasks/NetworkTask.h"
#include "../lib/Scheduling/SharedData.h"
#define BUF_SIZE 16

extern SharedData share_data;

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.println(String("Message arrived on [") + topic + "] len: " + length );
}

NetworkTask::NetworkTask(char * ssid, char* password, char* mqtt_server){
    this->ssid = ssid;
    this->password = password;
    this->mqtt_server = mqtt_server; // Initialize MQTT client with WiFiClient
}

void NetworkTask::init(int period){
    Task::init(period);
    attempt_connect();

    client.setClient(espClient);  
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
}

void NetworkTask::tick(){
    share_data.server_ok = client.connected();
    share_data.network_ok = (WiFi.status() == WL_CONNECTED);

    if(share_data.server_ok){
        client.subscribe("temperature-topic");
        char msg[BUF_SIZE];
        snprintf(msg, BUFSIZ+1, "%.2f", share_data.temperature);
        client.publish("temperature-topic", msg); 
    }
    else{
        Serial.println(client.state());  // Prints the error code
        String clientId = String("esiot-2043-client-")+String(random(0xffff), HEX);
        client.connect(clientId.c_str());
    }
}

void NetworkTask::attempt_connect(){
    WiFi.mode(WIFI_STA);
    WiFi.begin(NetworkTask::ssid, NetworkTask::password);
    int i = 0;
    while (WiFi.status() != WL_CONNECTED && i<25) {
        delay(500);
        Serial.print(".");
        i+=1;
    }

    if(i<25){
        Serial.println("Success");
        Serial.println(WiFi.localIP());
    }
}