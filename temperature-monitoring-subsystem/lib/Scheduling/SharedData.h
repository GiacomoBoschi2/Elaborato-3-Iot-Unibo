#ifndef __SHAREDDATA__
#define __SHAREDDATA__

struct SharedData
{
    long frequency = 1000;
    double temperature = 0;
    int network_ok = 1;
    int send_data = 1;
    int receive_data = 1;
};

#endif
