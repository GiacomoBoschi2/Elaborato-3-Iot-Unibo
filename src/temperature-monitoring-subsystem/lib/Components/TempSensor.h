#ifndef __TEMPSENSOR__
#define __TEMPSENSOR__

#include <Arduino.h>

class TempSensor{
    public:
        TempSensor(int pin);
        double getTemperature();      // Rileva la temperatura attuale 
    private:
        int pin;

};

#endif