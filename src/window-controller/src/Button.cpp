#include "../lib/Components/Button.h"
#include <Arduino.h>

Button::Button(int pin){
    Button::pin = pin;
}

bool Button::isPressed(){
    return  digitalRead(Button::pin);
}