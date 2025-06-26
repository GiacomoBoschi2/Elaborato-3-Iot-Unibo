#include "../lib/Tasks/SerialWriterTask.h"
#include "../lib/Scheduling/SharedData.h"

extern struct SharedData share_data;
#define MAX_BUFFER_SIZE 32

SerialWriterTask::SerialWriterTask(){
    handler = new SerialHandler();
}

void SerialWriterTask::init(int period){
    Task::init(period);
}

void SerialWriterTask::tick(){
    handler->tryWriteLine(share_data.window_rot);
}