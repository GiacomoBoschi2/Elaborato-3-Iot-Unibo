#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Timer.h"
#include "Task.h"
#include <Arduino.h>

#define MAX_TASKS 10
//Code retrieved from the iot course (2024-2025)
class Scheduler {

  int basePeriod;
  int nTasks;
  Task* taskList[MAX_TASKS];
  Timer timer;

public:
  void init(int basePeriod);
  virtual bool addTask(Task* task);
  virtual void schedule();
};

#endif