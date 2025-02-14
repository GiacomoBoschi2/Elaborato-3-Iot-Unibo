#include "../lib/Tasks/DoorTask.h"
#include "../lib/Scheduling/SharedData.h"

extern SharedData shared_data;

DoorTask::DoorTask(int pin){
    DoorTask::door = new Door(pin);
}

void DoorTask::init(int period){
    Task::init(period);
    status = READ_FROM_SYSTEM;
}

void DoorTask::tick(){

    status = (State)updateStatus();

    if(status==READ_FROM_SYSTEM){
        door->setAngle(0);
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
        if(shared_data.switch_mode){
            shared_data.switch_mode = 0;
            return (status==READ_FROM_SYSTEM) ? READ_FROM_POT : READ_FROM_SYSTEM;
        }
    }
    return NOT_READING;
}
