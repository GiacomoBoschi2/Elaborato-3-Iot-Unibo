#include "../lib/Tasks/ButtonTask.h"
#include "../lib/Scheduling/SharedData.h"

extern struct SharedData shared_data;

ButtonTask::ButtonTask(int pin){
    ButtonTask::button_handler = new Button(pin);
    ButtonTask::button_pin = pin;
}

void ButtonTask::init(int period){
    Task::init(period);
    status = NOT_PRESSED;
}

void ButtonTask::tick(){
    int press = button_handler->isPressed();
    if(press){
        status = PRESSED;
    }
    else if(!press && status==PRESSED)
    {
        shared_data.switch_mode = 1;
        status = NOT_PRESSED;
    }
}


