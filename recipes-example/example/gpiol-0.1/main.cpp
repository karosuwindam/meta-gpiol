#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <iostream>
#include "gpiol.h"
#include "gpio_class.h"


int main(int argc, char **argv)
{
    //linuxgpio_export(GPIO21);
    //linuxgpio_dir(GPIO21,GPIO_DIR_OUT);
    int r;
    int i=0;
    GpioL gpio_l;
    r = gpio_l.gpioCreate(GPIO26,GPIO_DIR_OUT);
    if(r >= 0){
        printf("open gpio %d\n",GPIO26);
        while(i < 10){
            gpio_l.gpioChange(1);
            sleep(1);
            gpio_l.gpioChange(0);
            sleep(1);
            i++;
            }
    }else{
        printf("close gpio %d\n",GPIO26);
    }
    gpio_l.gpioClose();

    return 0;
}
