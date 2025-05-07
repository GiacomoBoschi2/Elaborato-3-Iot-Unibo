#include "../lib/Tasks/NetworkTask.h"
#include "../lib/Scheduling/SharedData.h"
#define BUF_SIZE 16

#define START_FREQUENCY 3000

extern SharedData share_data;
int updated_freq = START_FREQUENCY;

void callback(char* topic, byte* payload, unsigned int length) {
    String msg((char*)payload, length);
    updated_freq = (msg.toInt());
}

NetworkTask::NetworkTask(char * ssid, char* password, char* mqtt_server){
    this->ssid = ssid;
    this->password = password;
    this->mqtt_server = mqtt_server; // Initialize MQTT client with WiFiClient
}

void NetworkTask::init(int period){
    Task::init(period);
    attempt_connect();
    NetworkTask::frequency = START_FREQUENCY;

    //setup writer
    writer.setClient(espClientWriter);  
    writer.setServer(mqtt_server, 1883);

    //setup reader
    reader.setClient(espClientReader);  
    reader.setServer(mqtt_server, 1883);
    reader.setCallback(callback);
}

void NetworkTask::tick(){
    share_data.send_data = writer.connected();
    share_data.network_ok = (WiFi.status() == WL_CONNECTED);
    share_data.receive_data = reader.connected();

    //send temperature if enough ticks have passed
    NetworkTask::tick_counter+=Task::myPeriod;

    int to_send= tick_counter>=NetworkTask::frequency;
    if(to_send){
        tick_counter = 0;
        if(share_data.send_data && share_data.network_ok){
            writer.subscribe("temperature-topic");
            char msg[BUF_SIZE];
            snprintf(msg, BUFSIZ+1, "%.2f", share_data.temperature);
            writer.publish("temperature-topic", msg); 
        }
        else{
            String clientId = String("esiot-2043-client-")+String(random(0xffff), HEX);
            writer.connect(clientId.c_str());
        }
    }
    //check if frequency reader is connected
    if(!share_data.receive_data){
        String clientId = String("esiot-2043-client-")+String(random(0xffff), HEX);
        reader.connect(clientId.c_str());
    }

    reader.subscribe("frequency-topic");
    reader.loop();
    frequency = updated_freq;
}

void NetworkTask::attempt_connect(){
    WiFi.mode(WIFI_STA);
    WiFi.begin(NetworkTask::ssid, NetworkTask::password);
    int i = 0;
    while (WiFi.status() != WL_CONNECTED && i<25) {
        delay(500);
        i+=1;
    }
}