#ifndef __LCDTASK__
#define __LCDTASK__

#include "../Components/Lcd.h"
#include "../Tasks/Task.h"

class LcdTask:public Task{
public:
  LcdTask(int address, int cols, int rows);
  void tick();
  void init(int period);
private:
  void updateMsg(const char* msg);
  Lcd* lcd;
  const char* currentMsg;
  enum State {DISPLAY_MANUAL_MODE,DO_NOT_DISPLAY_MANUAL_MODE} state;
};

#endif