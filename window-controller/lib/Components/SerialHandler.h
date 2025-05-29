#ifndef __SERIALHANDLER__
#define __SERIALHANDLER__

#include <Arduino.h>

class SerialHandler
{
private:
public:
    SerialHandler();
    int tryRead(char* reader);
    int tryReadline(char* reader);
    int tryWrite(char* message);
    int tryWrite(double message);
    int tryWrite(int message);
    int tryWriteLine(char* message);
    int tryWriteLine(int message);
    int tryWriteLine(double message);
};



#endif