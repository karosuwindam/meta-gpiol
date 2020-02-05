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
    GpioL gpio_l26;
    GpioL gpio_l19;
    GpioL gpio_l13;
    int t_r=0;
    int r1=0;
    if(gpio_l26.gpioCreate(GPIO26,GPIO_DIR_OUT) >= 0){
        if(r = gpio_l19.gpioCreate(GPIO19,GPIO_DIR_IN) >= 0){
            if(r = gpio_l13.gpioCreate(GPIO13,GPIO_DIR_OUT) >= 0){
                gpio_l13.gpioChange(1);

                while(i < 2500){
                    t_r = gpio_l19.gpioRead();
                    if(t_r >= 0){
                        r1 = t_r;
                        if(r1 == 0){
                            gpio_l26.gpioChange(0);
                        }
                        usleep(2000);
                    }else{
                        usleep(2000);
                    }
                    gpio_l26.gpioChange(1);
                    usleep(2000);
                    i++;
                }
            }
        }
    }

    printf("close gpio %d\n",GPIO26);

    gpio_l13.gpioClose();
    gpio_l19.gpioClose();
    gpio_l26.gpioClose();

    return 0;
}
