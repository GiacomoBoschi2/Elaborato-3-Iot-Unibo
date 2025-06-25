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
}

void LcdTask::tick(){
    char msg[32];
    sprintf(msg, "Current rotation: %d", share_data.door_rotation);
    
    if(share_data.current_mode == MANUAL_MODE){
        lcd->message(msg,0,1);
        sprintf(msg, "Manual Mode\0");
        lcd->message(msg,1,0);
        sprintf(msg, "Temperature:%s",String(share_data.current_temp).c_str());
        lcd->message(msg,2,0);
    }
    else if(share_data.current_mode == AUTO_MODE){
        lcd->message(msg,0,1);
        sprintf(msg, "Automatic Mode\0");
        lcd->message(msg,1,0);
    }
    else{
        lcd->message(msg,0,1);
        sprintf(msg, "ALARM STATE");
        lcd->message(msg,1,0);
        sprintf(msg, "Wait for dashboard\0");
        lcd->message(msg,2,0);
    }
   
}

void LcdTask::updateMsg(const char* msg){
    currentMsg = msg;
}

