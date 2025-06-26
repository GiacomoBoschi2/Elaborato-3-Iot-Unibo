#include <Arduino.h>
#include "../lib/Scheduling/Scheduler.h"
#include "../lib/Tasks/DoorTask.h"
#include "../lib/Tasks/ButtonTask.h"
#include "../lib/Tasks/LcdTask.h"
#include "../lib/Scheduling/SharedData.h"
#include "../lib/Tasks/SerialReaderTask.h"
#include "../lib/Tasks/SerialWriterTask.h"
#include "../lib/Tasks/ModeTask.h"


#define BASE_PERIOD 50

#define DOOR_PIN 9
#define BUTTON_PIN 2
#define POTENTIOMETER_PIN A0

#define LCDADDRESS 0x27
#define LCDCOLS 20
#define LCDROWS 4

Scheduler* sched;
DoorTask* doorTask;
ButtonTask* buttonTask;
LcdTask* lcdTask;
SerialWriterTask* serialTask;
SerialReaderTask* serialTaskWriter;
ModeTask* modeTask;
SharedData share_data;

void initalizeSharedData(){
  share_data.door_rotation = 0;
  share_data.switch_mode = 0;
  share_data.current_temp = 0.0;
  share_data.switch_alarm = 0;
}

void setup() {
  initalizeSharedData();
  sched = new Scheduler();
  sched->init(BASE_PERIOD);

  buttonTask = new ButtonTask(BUTTON_PIN);
  buttonTask->init(BASE_PERIOD*2);

  //create tasks
  doorTask = new DoorTask(DOOR_PIN,POTENTIOMETER_PIN);
  doorTask->init(BASE_PERIOD*4);

  lcdTask = new LcdTask(LCDADDRESS,LCDCOLS,LCDROWS);
  lcdTask->init(BASE_PERIOD*4);

  serialTask = new SerialWriterTask();
  serialTask->init(BASE_PERIOD*6);

  serialTaskWriter = new SerialReaderTask();
  serialTaskWriter->init(BASE_PERIOD*4);
  
  modeTask = new ModeTask();
  modeTask->init(BASE_PERIOD*2);

  //add tasks
  sched->addTask(buttonTask);
  sched->addTask(doorTask);
  sched->addTask(lcdTask);
  sched->addTask(serialTask);
  sched->addTask(modeTask);
  sched->addTask(serialTaskWriter);
}

void loop() {
  // put your main code here, to run repeatedly:
  sched->schedule();
}

