#ifndef __MODETASK__
#define __MODETASK__


#include "../Tasks/Task.h"

//just a task for managing mode logic
class ModeTask:public Task{
public:
  ModeTask();
  void tick();
  void init(int period);
private:
  enum State {AUTO_MODE,MANUAL_MODE,SYSTEM_PANIC} state;
};

#endif