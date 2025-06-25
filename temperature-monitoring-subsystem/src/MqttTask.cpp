#include "../lib/Tasks/MqttTask.h"
#include "../lib/Scheduling/SharedData.h"
#define BUF_SIZE 16

#define START_FREQUENCY 3000

extern SharedData share_data;
int updated_freq = START_FREQUENCY;

void callback(char* topic, byte* payload, unsigned int length) {
    String msg((char*)payload, length);
    updated_freq = (msg.toInt());
    share_data.frequency = updated_freq;
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

    reader.subscribe("frequency-topic");
    reader.loop();
}

void MqttTask::tick(){

    share_data.network_ok = (WiFi.status() == WL_CONNECTED);
    share_data.mqtt_ok = reader.connected() && writer.connected();
    //send temperature if enough ticks have passed
    MqttTask::tick_counter+=Task::myPeriod;

    int to_send= tick_counter>=MqttTask::frequency;
    if(share_data.mqtt_ok  && share_data.network_ok){
        if(share_data.send_data){
            char msg[BUF_SIZE];
            snprintf(msg, BUFSIZ+1, "%.2f", share_data.temperature);
            Serial.println(msg);
            writer.publish("temperature-topic", msg); 
            share_data.send_data = 0;
        }
    }
    else if(share_data.network_ok){
        String clientId = String("esiot-2043-client-")+String(random(0xffff), HEX);
        String clientId2 = String("esiot-2043-client-")+String(random(0xffff), HEX);
        writer.connect(clientId.c_str());
        reader.connect(clientId2.c_str());
        reader.subscribe("frequency-topic");
        reader.loop();
    }
}

