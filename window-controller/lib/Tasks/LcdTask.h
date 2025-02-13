#ifndef __LCDTASK__
#define __LCDTASK__

#include "../Components/Lcd.h"
#include "../Tasks/Task.h"

class LcdTask:public Task{
public:
  LcdTask(int address, int cols, int rows);
  void updateMsg(const char* msg);
  void tick();
  void init(int period);
private:
  Lcd* lcd;
  unsigned long timerDelay;
  int timerOn;
  const char* currentMsg;
  long long previous_door_status;
};

#endif