#ifndef __SHAREDDATA__
#define __SHAREDDATA__

struct SharedData
{
    long frequency = 1000;
    double temperature = 0;
    int network_ok = 1;
    int mqtt_ok = 1;
    int send_data = 0;
};

#endif
