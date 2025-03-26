#include "../lib/Components/SerialHandler.h"

#define MAX_BUFFER_SIZE 64


SerialHandler::SerialHandler(){
    Serial.begin(9600);
}

//integer returns success of operation (success=1 and failure=0),if operation is successful,reader will contain the values
int SerialHandler::tryRead(char* reader){
    if(Serial.available()>0){
        int read_len = Serial.readBytes(reader, MAX_BUFFER_SIZE);
        reader[min(read_len,63)] = 0;
        return read_len>0;
    }
    return 0;
}

int SerialHandler::tryWrite(char* message){
    Serial.print(message);
    return 1;
}

int SerialHandler::tryWrite(double message){
    Serial.print(message);
    return 1;
}

int SerialHandler::tryWrite(int message){
    Serial.print(message);
    return 1;
}

int SerialHandler::tryWriteLine(char* message){
    Serial.println(message);
    return 1;
}

int SerialHandler::tryWriteLine(int message){
    Serial.println(message);
    return 1;
}

int SerialHandler::tryWriteLine(double message){
    Serial.println(message);
    return 1;
}