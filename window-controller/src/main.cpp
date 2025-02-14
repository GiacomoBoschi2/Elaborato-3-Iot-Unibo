#include <Arduino.h>
#include "../lib/Scheduling/Scheduler.h"
#include "../lib/Tasks/DoorTask.h"

#define BASE_PERIOD 50

#define DOOR_PIN 9

Scheduler* sched;
DoorTask* doorTask;

void setup() {
  sched = new Scheduler();
  sched->init(BASE_PERIOD);

  //create tasks
  doorTask = new DoorTask(DOOR_PIN);
  doorTask->init(BASE_PERIOD*2);

  //add tasks
  sched->addTask(doorTask);
}

void loop() {
  // put your main code here, to run repeatedly:
  sched->schedule();
}

