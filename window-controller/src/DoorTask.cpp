#include "../lib/Tasks/DoorTask.h"
#include "../lib/Scheduling/SharedData.h"
#include <Arduino.h>

extern struct SharedData share_data;

DoorTask::DoorTask(int pin){
    DoorTask::door = new Door(pin);
    Serial.begin(9600);
}

void DoorTask::init(int period){
    Task::init(period);
    status = READ_FROM_SYSTEM;
}

void DoorTask::tick(){

    status = updateStatus();

    if(status==READ_FROM_SYSTEM){
        door->setAngle(150);
    }
    else if(status==READ_FROM_POT){
        door->setAngle(60);
    }
    else{
        door->setAngle(90);
    }
}

int DoorTask::updateStatus(){
    if(status!=NOT_READING){
        Serial.println(share_data.switch_mode);
        if(share_data.switch_mode){
            share_data.switch_mode = 0;
            return (status==READ_FROM_SYSTEM) ? READ_FROM_POT : READ_FROM_SYSTEM;
        }
        return status;
    }
    return NOT_READING;
}
