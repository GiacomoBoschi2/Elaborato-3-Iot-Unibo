#include "../lib/Tasks/NetworkTask.h"


NetworkTask::NetworkTask(IPAddress* address, byte* mac_address){
    NetworkTask::address = address;
    NetworkTask::mac = mac_address;
    client = new PubSubClient();
}

void NetworkTask::init(int period){
    Task::init(period);
    client->setServer(*address,59999);
}

void NetworkTask::tick(){

}