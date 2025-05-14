#include "../lib/Tasks/SerialTask.h"
#include "../lib/Scheduling/SharedData.h"

extern struct SharedData share_data;
#define MAX_BUFFER_SIZE 64

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
    if(success){
        String read_bytes = buffer;
        share_data.auto_mode_rotation = read_bytes.toInt();
        handler->tryWriteLine(share_data.auto_mode_rotation);
    }
}