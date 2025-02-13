
#ifndef __SHARABLEDATA__
#define __SHARABLEDATA__

struct SharableData{

        /*info to share to java interface*/
        double temperature = 0;
        double fillPercentage = 0;
        int doorStatus = 0;

        /*flags and commands*/
        int wError = 0;         //flag variable,checks if waste bin is full
        int tError = 0;         //flag variable,checks if there is a temperature problem
        int ignoreTempError = 0; //flag variable,checks if temperature errors should be considered,gets set to 
        int openDoor  = 0;      //flag command, if set to 1 indicates that the door should become open
        int closeDoor = 0;      //flag command, if set to 1 indicates that the door should become closed
        int emptyDoor = 0;      //flag command, if set to 1 indicates that the door should be in a -90 degree position to empty the waste bin,this flag should always take priority over open and close flags.
        int sleep_mode = 0;     //flag variable,if set to 1 indicates that the system is in sleep mode,the LCD should be turned off and the leds freezed.
    };



#endif
