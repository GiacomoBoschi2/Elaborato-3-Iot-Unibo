#include "../lib/Tasks/MqttTask.h"
#include "../lib/Scheduling/SharedData.h"
#define BUF_SIZE 16

#define START_FREQUENCY 3000

extern SharedData share_data;
int updated_freq = START_FREQUENCY;

void callback(char* topic, byte* payload, unsigned int length) {
    String msg((char*)payload, length);
    updated_freq = (msg.toInt());
}

MqttTask::MqttTask(char* mqtt_server){
    this->mqtt_server = mqtt_server; // Initialize MQTT client with WiFiClient
}

void MqttTask::init(int period){
    Task::init(period);
    MqttTask::frequency = START_FREQUENCY;

    //setup writer
    writer.setClient(espClientWriter);  
    writer.setServer(mqtt_server, 1883);

    //setup reader
    reader.setClient(espClientReader);  
    reader.setServer(mqtt_server, 1883);
    reader.setCallback(callback);
}

void MqttTask::tick(){
    share_data.send_data = writer.connected();
    share_data.network_ok = (WiFi.status() == WL_CONNECTED);
    share_data.receive_data = reader.connected();



    //send temperature if enough ticks have passed
    MqttTask::tick_counter+=Task::myPeriod;

    int to_send= tick_counter>=MqttTask::frequency;
    if(to_send){
        tick_counter = 0;
        if(share_data.send_data && share_data.network_ok){
            char msg[BUF_SIZE];
            snprintf(msg, BUFSIZ+1, "%.2f", share_data.temperature);
            Serial.println(msg);
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

