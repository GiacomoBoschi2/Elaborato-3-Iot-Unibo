#include "../lib/Tasks/LedTask.h"
#include "../lib/Scheduling/SharedData.h"

extern SharedData share_data;

LedTask::LedTask(int greenPin,int redPin){
    LedTask::greenPin = greenPin;
    LedTask::redPin = redPin;
}

void LedTask::init(int period){
    Task::init(period);
    LedTask::greenLed = new Led(LedTask::greenPin);
    LedTask::redLed = new Led(LedTask::redPin);
}

void LedTask::tick(){
    if(share_data.network_ok & share_data.mqtt_ok){
        greenLed->switchOn();
        redLed->switchOff();
    }
    else{
        greenLed->switchOff();
        redLed->switchOn();
    }

}