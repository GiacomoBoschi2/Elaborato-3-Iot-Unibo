#include "../lib/Tasks/SerialReaderTask.h"
#include "../lib/Scheduling/SharedData.h"

extern struct SharedData share_data;
#define MAX_BUFFER_SIZE 32

SerialReaderTask::SerialReaderTask(){
    handler = new SerialHandler();
}

void SerialReaderTask::init(int period){
    Task::init(period);
}

void SerialReaderTask::tick(){
    handler->tryWriteLine(share_data.auto_mode_rotation);
}