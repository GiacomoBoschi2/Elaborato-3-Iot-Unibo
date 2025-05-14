#include "../lib/Tasks/DoorTask.h"
#include "../lib/Scheduling/SharedData.h"
#include <Arduino.h>

extern struct SharedData share_data;

DoorTask::DoorTask(int doorPin,int potPin){
    DoorTask::door = new Door(doorPin);
    DoorTask:pot = new Potentiometer(potPin);
}

void DoorTask::init(int period){
    Task::init(period);
    status = READ_FROM_SYSTEM;
}

void DoorTask::tick(){

    status = updateStatus();
    long door_rot = prev_door_rot;

    if(status==READ_FROM_SYSTEM){
        share_data.manual_mode_on = 0;
        door_rot=share_data.auto_mode_rotation;
    }
    else if(status==READ_FROM_POT){
        share_data.manual_mode_on = 1;
        door_rot=pot->read();
    }
    else{
        door_rot=90;
    }

    //invoke door device only if necessary
    if(door_rot!=prev_door_rot){
        door->setAngle(door_rot);
        share_data.door_rotation = door_rot;
        prev_door_rot = door_rot;
    }

}

int DoorTask::updateStatus(){
    if(status!=NOT_READING){
        if(share_data.switch_mode){
            share_data.switch_mode = 0;
            return (status==READ_FROM_SYSTEM) ? READ_FROM_POT : READ_FROM_SYSTEM;
        }
        return status;
    }
    return NOT_READING;
}
