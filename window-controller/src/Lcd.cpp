#include "../lib/Components/Lcd.h"
#include <Arduino.h>

Lcd::Lcd(int address, int cols, int rows) : lcd(address, cols, rows) {

}

void Lcd::init(){
    lcd.init();
    lcd.backlight();
}

void Lcd::clear(){
    lcd.clear();
}

void Lcd::message(const char* msg){
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(msg);
}

void Lcd::close(){
    
}