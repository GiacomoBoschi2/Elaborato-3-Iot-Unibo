#include <Arduino.h>
#include "../lib/Scheduling/Scheduler.h"

Scheduler* sched;

void setup() {
  // put your setup code here, to run once:
  sched = new Scheduler();
}

void loop() {
  // put your main code here, to run repeatedly:
  sched->schedule();
}

