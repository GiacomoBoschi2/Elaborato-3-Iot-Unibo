#include "../lib/Tasks/DoorTask.h"

DoorTask::DoorTask(int pin){
    DoorTask::door = new Door(pin);
}

void DoorTask::init(int period){
    Task::init(period);
    status = READ_FROM_SYSTEM;
}

void DoorTask::tick(){
    if(status==READ_FROM_SYSTEM){
        door->setAngle(120);
    }
    else if(status==READ_FROM_POT){
        door->setAngle(60);
    }
    else{
        door->setAngle(90);
    }
}

