#include "../lib/Tasks/LcdTask.h"
#include "../lib/Scheduling/SharedData.h"

extern struct SharedData share_data;

LcdTask::LcdTask(int address, int cols, int rows){
    this->lcd = new Lcd(address, cols, rows);
    this->currentMsg = "";
}

void LcdTask::init(int period){
    Task::init(period);
}

void LcdTask::tick(){
    String door_rotation = "Current rotation (in degrees):"+share_data.door_rotation;
    char* msg = (char*)malloc(128);
    door_rotation.toCharArray(msg,128,0);
    updateMsg(msg);
    lcd->message(currentMsg);

}

void LcdTask::updateMsg(const char* msg){
    currentMsg = msg;
}

