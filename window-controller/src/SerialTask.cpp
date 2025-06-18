#include "../lib/Tasks/SerialTask.h"
#include "../lib/Scheduling/SharedData.h"

extern struct SharedData share_data;
#define MAX_BUFFER_SIZE 32

SerialTask::SerialTask(){
    handler = new SerialHandler();
}

void SerialTask::init(int period){
    Task::init(period);
    buffer = (char*)(malloc(MAX_BUFFER_SIZE));
}

void SerialTask::tick(){
    //read possible commands from Python API
    int success = handler->tryRead(buffer);
    Serial.println(success);
    if(success){
        String read_bytes = buffer;
        char delimiter [] = "|";
        char * data = strtok(buffer,delimiter);
        
        //update data 
        if(data!=NULL){
            share_data.auto_mode_rotation = atoi(data);
            data = strtok(nullptr,delimiter);
            if(data!=NULL){
                double s = atof(data);
                share_data.current_temp = s;
            }
        }
        
    }
}