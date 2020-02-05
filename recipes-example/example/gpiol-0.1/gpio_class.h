#include "gpiol.h"

class GpioL
{

    int gpioPort=0;
    int gpioInout=0;
public:
    int gpioCreate(int gpio,int inout);
    void gpioChange(int output);
    int gpioRead();
    void gpioClose();
};