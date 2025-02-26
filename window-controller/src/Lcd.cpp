#include "../Components/Lcd.h"

Lcd::Lcd(int address, int cols, int rows):lcd(address,cols,rows){

}

void Lcd::init(){
    lcd.init();
    lcd.backlight();
    lcd.clear();
}

void Lcd::message(const char* msg){
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(msg);
}

void Lcd::clear(){
    lcd.clear();
}

void Lcd::close(){
    lcd.clear();
    lcd.noBacklight();
}