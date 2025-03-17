#include "TempSensor.h"
#include <Arduino.h>

#define CONVERT_FOR_V5(x) ((((double)(x) * (3.3 / 4095.0))-0.5)*100)

TempSensor::TempSensor(int pin){
    this->pin = pin;
}

double TempSensor::getTemperature() {
    // Lettura analogica e conversione in °C (per esempio con LM35)
    int analogValue = analogRead(pin);
    double temperature = CONVERT_FOR_V5(analogValue); // Conversione
    return temperature;
};