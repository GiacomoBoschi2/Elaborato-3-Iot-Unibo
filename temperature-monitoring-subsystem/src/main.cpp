#include <Arduino.h>
#include "../lib/Scheduling/Scheduler.h"
#include "../lib/Scheduling/SharedData.h"
#include "../lib/Tasks/LedTask.h"
#include "../lib/Scheduling/Timer.h"
#include "../lib/Tasks/TempSensorTask.h"


#define RED_PIN 27
#define GREEN_PIN 26
#define TEMP_PIN 34
#define BASE_PERIOD 100

Scheduler* sched;
LedTask* ledTask;
TempSensorTask* tempTask;
SharedData share_data;

void setup() {
  sched = new Scheduler();
  sched->init(BASE_PERIOD);

  ledTask = new LedTask(GREEN_PIN,RED_PIN);
  ledTask -> init(BASE_PERIOD*2);
  sched->addTask(ledTask);

  tempTask = new TempSensorTask(TEMP_PIN);
  tempTask->init(BASE_PERIOD*4);
  sched->addTask(tempTask);
}

void loop() {
  sched->schedule();
}

