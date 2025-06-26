#include "../lib/Tasks/SerialReaderTask.h"
#include "../lib/Scheduling/SharedData.h"

extern struct SharedData share_data;
#define MAX_BUFFER_SIZE 32
#define MAX_READS_IN_A_TICK 5

SerialReaderTask::SerialReaderTask(){
    handler = new SerialHandler();
}

void SerialReaderTask::init(int period){
    Task::init(period);
    buffer = (char*)(malloc(MAX_BUFFER_SIZE));
}

void SerialReaderTask::handleSwitchToManualCommand(){
    if(share_data.current_mode==AUTO_MODE){
        share_data.switch_mode = 1;
    }
}

void SerialReaderTask::handleAlarmModeCommand(){
    share_data.switch_alarm = 1;
}

void SerialReaderTask::handleRotationCommand(){
    String read_bytes = buffer;
    char delimiter [] = "|";
    char * data = strtok(buffer,delimiter);
    
    //update data 
    if(data!=NULL){

        if(share_data.current_mode == AUTO_MODE){
            share_data.window_rot = atoi(data);
        }
        
        data = strtok(nullptr,delimiter);
        if(data!=NULL){
            double s = atof(data);
            share_data.current_temp = s;
        }
    } 
}

void SerialReaderTask::tick(){
    //read possible commands from Python API
    int i =0;
    int success = 1;
    while(i<MAX_READS_IN_A_TICK && (success = handler->tryReadline(buffer))>0){
        handler->tryWriteLine(buffer);
        if(buffer[0]=='X'){
            handleSwitchToManualCommand();
        }
        else if(buffer[0]=='P'){
            handleAlarmModeCommand();
        }
        else{
            handleRotationCommand();
        }
    }  
}