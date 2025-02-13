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
    lcd.setCursor(0,0);
    for(int i = 0;i<strlen(msg);i++){
        lcd.write(msg[i]);
    }
}

void Lcd::close(){
    
}