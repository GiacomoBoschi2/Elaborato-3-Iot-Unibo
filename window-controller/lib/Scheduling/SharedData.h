#ifndef __SHAREDDATA__
#define __SHAREDDATA__

struct SharedData
{
    int switch_mode;
    int manual_mode_on;
    long door_rotation;
    int auto_mode_rotation;
    double current_temp = 0.0;
};

#endif
