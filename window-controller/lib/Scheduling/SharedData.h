#ifndef __SHAREDDATA__
#define __SHAREDDATA__

enum state{
    AUTO_MODE,
    MANUAL_MODE,
    SYSTEM_PANIC
};

struct SharedData
{
    int switch_mode;
    int switch_alarm;
    int current_mode = 0;
    long door_rotation;
    int auto_mode_rotation;
    double current_temp = 0.0;
};

#endif
