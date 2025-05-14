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
    char msg[32];
    sprintf(msg, "Current rotation: %d", share_data.door_rotation);
    lcd->message(msg,0,1);
    if(share_data.manual_mode_on){
        sprintf(msg, "Manual Mode\0");
        lcd->message(msg,1,0);
        sprintf(msg, "Temperature:%d \0",share_data.current_temp);
        lcd->message(msg,2,0);
    }
    else{
        sprintf(msg, "Automatic Mode\0");
        lcd->message(msg,1,0);
    }
   
}

void LcdTask::updateMsg(const char* msg){
    currentMsg = msg;
}

