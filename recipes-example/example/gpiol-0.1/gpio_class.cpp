#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#include "enum.h"
#include "gpio_class.h"


int GpioL::gpioCreate(int gpio,int inout)
{
    gpioPort = gpio;
    gpioInout = inout;
    return opengpio(gpioPort,gpioInout);
}
void GpioL::gpioChange(int output)
{
    if(gpioInout == GPIO_DIR_OUT){
        ch_gpio(gpioPort,output);
    }
    return;
}

void GpioL::gpioClose()
{
    closegpio(gpioPort);
    return;
}

int GpioL::gpioRead()
{
    int r;
    r = read_gpio(gpioPort);
    //r = 1;
    return r;
}