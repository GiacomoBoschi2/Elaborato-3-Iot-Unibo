#ifndef __DOOR__
#define __DOOR__
#include <Servo.h>

class Door{
public:
  Door(int pin);
  void setAngle(int angle);
private:
  int pin;
  Servo handler;
};

#endif