#include "../lib/Components/Door.h"
#include <Arduino.h>

Door::Door(int pin){
    handler.attach(pin);
}

void Door::setAngle(int angle){
    handler.write(angle);
}