#include "Timer.h"
#include "Arduino.h"


Timer::Timer(){
  last_tick = 0;
}

/* period in ms */
void Timer::setupPeriod(int period){
  base_period = period;
}

void Timer::waitForNextTick(){
  /* wait for timer signal */
  while((last_timestamp_tracked =millis())-last_tick<base_period) {}
  last_tick = last_timestamp_tracked;
}

unsigned long Timer::getTotalTimeElapsed(){
  return millis();
}