#include "../lib/Tasks/ModeTask.h"
#include "../lib/Scheduling/SharedData.h"

extern struct SharedData share_data;

ModeTask::ModeTask(){

}

void ModeTask::init(int period){
    Task::init(period);
    state = AUTO_MODE;
    share_data.current_mode = AUTO_MODE;
}

void ModeTask::tick(){

    if(share_data.switch_alarm){
        share_data.current_mode = (share_data.current_mode == SYSTEM_PANIC ? MANUAL_MODE : SYSTEM_PANIC);
        share_data.switch_alarm = 0;
    }

    //no mode switch under SYSTEM_PANIC
    if(share_data.current_mode == SYSTEM_PANIC)return;

    if(share_data.switch_mode){
        share_data.switch_mode = 0;
        if(share_data.current_mode==AUTO_MODE){
            share_data.current_mode = MANUAL_MODE;
        }
        else{
            share_data.current_mode = AUTO_MODE;
        }
    }
}