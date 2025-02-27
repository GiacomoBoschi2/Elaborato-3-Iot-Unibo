#include "../lib/Components/Led.h"


Led::Led(int pin){
    Led::isOn = 0;
    Led::pin = pin;
    pinMode(pin,OUTPUT);
    digitalWrite(Led::pin,LOW);
}

void Led::switchOn(){
    isOn = 1;
    digitalWrite(Led::pin,isOn);
}

void Led::switchOff(){
    isOn = 0;
    digitalWrite(Led::pin,isOn);
}