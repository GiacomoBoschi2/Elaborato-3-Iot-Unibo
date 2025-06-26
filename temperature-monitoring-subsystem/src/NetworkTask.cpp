#include "../lib/Tasks/NetworkTask.h"
#include "../lib/Scheduling/SharedData.h"
#include "lwip/dns.h" 

extern SharedData share_data;



NetworkTask::NetworkTask(char * ssid, char* password){
    this->ssid = ssid;
    this->password = password;
}

void NetworkTask::init(int period){
    Task::init(period);
}

void NetworkTask::tick(){
    share_data.network_ok = (WiFi.status() == WL_CONNECTED);
    if(!share_data.network_ok){
        attempt_connect();
        share_data.network_ok = (WiFi.status() == WL_CONNECTED);
    }
}

void NetworkTask::attempt_connect(){
    WiFi.mode(WIFI_STA);
    WiFi.begin(NetworkTask::ssid, NetworkTask::password);
    int i = 0;
    while (WiFi.status() != WL_CONNECTED && i<20) {
        delay(1);
        i+=1;
    }

    if(WiFi.status()==WL_CONNECTED){
        ip_addr_t dns1, dns2;
        IP_ADDR4(&dns1, 8, 8, 8, 8);
        IP_ADDR4(&dns2, 8, 8, 4, 4);
    
        dns_setserver(0, &dns1);  // Primary DNS
        dns_setserver(1, &dns2);  // Secondary DNS
    }
    else{
        Serial.println("Connection failed");
         WiFi.printDiag(Serial);
    }
}

