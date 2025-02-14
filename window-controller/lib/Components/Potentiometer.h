#ifndef __POTENTIOMETER__
#define __POTENTIOMETER__

class Potentiometer{
    public:
    Potentiometer(int pin);
    int read(bool convert_to_angles = true);
    private:
    int voltage_to_angles(int volt);
    int pin;
};
#endif