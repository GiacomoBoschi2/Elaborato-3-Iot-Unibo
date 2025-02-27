#include <Arduino.h>
#include "../lib/Scheduling/Scheduler.h"
#include "../lib/Tasks/LedTask.h"
#include "../lib/Scheduling/Timer.h"

#define RED_PIN 12
#define GREEN_PIN 14

#define BASE_PERIOD 100

Scheduler* sched;
LedTask* ledTask;

void setup() {
  sched = new Scheduler();
  sched->init(BASE_PERIOD);

  ledTask = new LedTask(GREEN_PIN,RED_PIN);
  ledTask -> init(BASE_PERIOD*2);
  sched->addTask(ledTask);
}

void loop() {
  sched->schedule();
}

