#ifndef __LCD__
#define __LCD__

#include <LiquidCrystal_I2c.h>
#include <Wire.h>

class Lcd{
public:
  Lcd(int address, int cols, int rows);
  void init();
  void message(const char* msg);
  void close();
  void clear();
private:
  LiquidCrystal_I2C lcd;
};

#endif
