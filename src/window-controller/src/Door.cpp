#include "../lib/Components/Door.h"
#include <Arduino.h>

Door::Door(int pin){
    handler.attach(pin);
    Door::pin = pin;
    pinMode(pin,OUTPUT);
}

void Door::setAngle(int angle){
    handler.write(angle);
}