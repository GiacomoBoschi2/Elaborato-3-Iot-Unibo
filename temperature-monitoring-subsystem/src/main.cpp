#include <Arduino.h>
#include "../lib/Scheduling/Scheduler.h"
#include "../lib/Tasks/LedTask.h"
#include "../lib/Scheduling/Timer.h"
#include "../lib/Tasks/TempSensorTask.h"
#include "../lib/Scheduling/SharedData.h"

#define RED_PIN 27
#define GREEN_PIN 26

#define BASE_PERIOD 100

Scheduler* sched;
LedTask* ledTask;
SharedData share_data;

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

