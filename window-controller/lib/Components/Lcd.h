#ifndef __LCD__
#define __LCD__

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

class Lcd{
public:
  Lcd(int address, int cols, int rows);
  void init();
  void message(const char* msg,int line = 0, int clear=0);
  void close();
  void clear();
private:
  LiquidCrystal_I2C lcd;
};

#endif
