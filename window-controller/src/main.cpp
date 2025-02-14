#include <Arduino.h>
#include "../lib/Scheduling/Scheduler.h"
#include "../lib/Tasks/DoorTask.h"

#define DOOR_PIN 9

Scheduler* sched;
DoorTask* doorTask;

void setup() {
  // put your setup code here, to run once:
  sched = new Scheduler();
  doorTask = new DoorTask(DOOR_PIN);

  //add tasks
  sched->addTask(doorTask);
}

void loop() {
  // put your main code here, to run repeatedly:
  sched->schedule();
}

