#include <Arduino.h>
#include "../lib/Components/Potentiometer.h"

Potentiometer::Potentiometer(int pin){
    Potentiometer::pin = pin;
}

int Potentiometer::read(bool convert_to_angles=true){
    int read_value = analogRead(pin);

    if(convert_to_angles){
        return Potentiometer::voltage_to_angles(read_value);
    }

    return read_value;
}

long Potentiometer::voltage_to_angles(int voltage){
    return map(voltage, 0, 1023, 0, 90);
}