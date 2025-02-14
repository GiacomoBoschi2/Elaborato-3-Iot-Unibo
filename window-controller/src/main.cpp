#include <Arduino.h>
#include "../lib/Scheduling/Scheduler.h"
#include "../lib/Tasks/DoorTask.h"
#include "../lib/Tasks/ButtonTask.h"
#include "../lib/Scheduling/SharedData.h"

#define BASE_PERIOD 50

#define DOOR_PIN 9
#define BUTTON_PIN 2
#define POTENTIOMETER_PIN A0

Scheduler* sched;
DoorTask* doorTask;
ButtonTask* buttonTask;
SharedData share_data;

void setup() {
  sched = new Scheduler();
  sched->init(BASE_PERIOD);

  //create tasks
  doorTask = new DoorTask(DOOR_PIN,POTENTIOMETER_PIN);
  doorTask->init(BASE_PERIOD*2);
  buttonTask = new ButtonTask(BUTTON_PIN);
  buttonTask->init(BASE_PERIOD*3);

  //add tasks
  sched->addTask(doorTask);
  sched->addTask(buttonTask);
}

void loop() {
  // put your main code here, to run repeatedly:
  sched->schedule();
}

