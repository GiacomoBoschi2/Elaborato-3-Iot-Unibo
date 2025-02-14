#ifndef __DOORTASK__
#define __DOORTASK__

#include "Task.h"
#include "Door.h"
#include "Potentiometer.h"


class DoorTask:public Task {
public:
  DoorTask(int doorPin,int potPin);
  void init(int period);
  void tick();
private:
  int pin;
  Door* door;
  Potentiometer* pot;
  enum State {READ_FROM_SYSTEM,READ_FROM_POT,NOT_READING} status;
  int updateStatus();
};

#endif