#ifndef __TIMER__
#define __TIMER__

#include <Arduino.h>

//Code retrieved from the iot course (2024-2025) 
class Timer {
    
public:  
  Timer();
  /* period in ms */
  void setupPeriod(int period);  
  void waitForNextTick();
  unsigned long getTotalTimeElapsed(); // for debugging purpose only

private:
  unsigned long last_tick;
  unsigned long base_period;
  unsigned long last_timestamp_tracked;
};


#endif