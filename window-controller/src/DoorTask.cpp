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
}

void DoorTask::tick(){

    long door_rot = prev_door_rot;

    if(share_data.current_mode==AUTO_MODE){
        door_rot=share_data.auto_mode_rotation;
    }
    else if(share_data.current_mode==MANUAL_MODE){
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

