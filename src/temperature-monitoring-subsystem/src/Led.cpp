#include "../lib/Components/Led.h"


Led::Led(int pin){
    Led::isOn = LOW;
    Led::pin = pin;
    pinMode(pin,OUTPUT);
    digitalWrite(Led::pin,LOW);
}

void Led::switchOn(){
    isOn = HIGH;
    digitalWrite(Led::pin,isOn);
}

void Led::switchOff(){
    isOn = LOW;
    digitalWrite(Led::pin,isOn);
}