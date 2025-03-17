#ifndef __SHAREDDATA__
#define __SHAREDDATA__

struct SharedData
{
    long frequency = 1000;
    double temperature = 0;
    int network_ok = 0;
    int server_ok = 1;
};

#endif
