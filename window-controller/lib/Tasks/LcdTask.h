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
  char* currentMsg;

  //optimize calls
  int prev_displayed_state = -1;
  int prev_door_rot = -1;
  double prev_temp = -1;
};

#endif