#include "../lib/Tasks/LcdTask.h"
#include "../lib/Scheduling/SharedData.h"

extern struct SharedData share_data;

LcdTask::LcdTask(int address, int cols, int rows){
    this->lcd = new Lcd(address, cols, rows);
    this->currentMsg = "Current rotation (in angles):";
}

void LcdTask::init(int period){
    Task::init(period);
    lcd->init();
    state = DO_NOT_DISPLAY_MANUAL_MODE;
}

void LcdTask::tick(){
    char msg[64];
    sprintf(msg, "Current rotation (in degrees): %d", share_data.door_rotation);
    updateMsg(msg);
    lcd->message(currentMsg);
}

void LcdTask::updateMsg(const char* msg){
    currentMsg = msg;
}

