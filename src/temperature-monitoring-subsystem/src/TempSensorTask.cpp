#include "TempSensorTask.h"
#include <Arduino.h>
#include "../lib/Scheduling/SharedData.h"

extern SharedData share_data;

TempSensorTask::TempSensorTask(int pin){
    sensor = new TempSensor(pin);
    Serial.begin(9600);
}

void TempSensorTask::init(int period) {
    Task::init(period);
    check_time = 0;
    saved_period = period;
}

void TempSensorTask::tick(){
    check_time += saved_period;

    if(check_time>=share_data.frequency){
        check_time = 0;
        double measure = sensor->getTemperature();
        share_data.temperature = measure;
        share_data.send_data = 1;
    }
}