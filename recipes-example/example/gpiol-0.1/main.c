#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "gpiol.h"


int main(int argc, char **argv)
{
    //linuxgpio_export(GPIO21);
    //linuxgpio_dir(GPIO21,GPIO_DIR_OUT);
    int r;
    r = opengpio(GPIO21, GPIO_DIR_OUT);
    if(r >= 0){
        printf("open gpio %d\n",GPIO21);

        ch_gpio(GPIO21, 1);
    }else{
        printf("close gpio %d\n",GPIO21);
        closegpio(GPIO21);
    }
    printf("Hello World!\n");

    return 0;
}
