#include "../lib/Tasks/LedTask.h"

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
    greenLed->switchOn();
    redLed->switchOff();
}