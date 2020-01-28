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
    opengpio(GPIO21, GPIO_DIR_OUT);
    //ch_gpio(GPIO21, 1);
    printf("Hello World!\n");

    return 0;
}
