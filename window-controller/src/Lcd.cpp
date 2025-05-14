#include "../Components/Lcd.h"


Lcd::Lcd(int address, int cols, int rows):lcd(address,cols,rows){

}

void Lcd::init(){
    lcd.init();
    lcd.backlight();
    lcd.clear();
}

void Lcd::message(const char* msg,int line = 0,int clear = 0){
    if(clear){
        lcd.backlight();
        lcd.clear();
    }
    lcd.setCursor(0,line);
    lcd.print(msg);
}

void Lcd::clear(){
    lcd.clear();
}

void Lcd::close(){
    lcd.clear();
    lcd.noBacklight();
}