#include "../lib/Tasks/ButtonTask.h"
#include "../lib/Scheduling/SharedData.h"

extern struct SharedData share_data;

ButtonTask::ButtonTask(int pin){
    ButtonTask::button_handler = new Button(pin);
    ButtonTask::button_pin = pin;
}

void ButtonTask::init(int period){
    Task::init(period);
    status = NOT_PRESSED;
    prev_status = status;
}

void ButtonTask::tick(){
    //no commands taken under alarm
    if(share_data.current_mode == SYSTEM_PANIC)return;

    int press = button_handler->isPressed();
    if(!share_data.switch_mode){
        if(press){
            status = PRESSED;
        }
        else if(!press && status==PRESSED)
        {
            share_data.switch_mode = 1;
            status = NOT_PRESSED;
        }   
    }
}


