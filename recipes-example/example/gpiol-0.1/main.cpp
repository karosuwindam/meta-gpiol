#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <iostream>
#include "gpiol.h"
#include "gpio_class.h"
#include "gpio_thread.h"
#include <signal.h>

static int g_hoge = 0;

/* シグナルハンドラ */
void sig_handler(int signo)
{
    if (signo == SIGUSR1) {
        printf("received SIGUSR1¥n");
    } else if (signo == SIGKILL) {
        printf("received SIGKILL¥n");
    } else if (signo == SIGSTOP) {
        printf("received SIGSTOP¥n");
    } else if (signo == SIGINT){       //ctrl+c
        printf("received SIGQUIT\n");
    } else if (signo == SIGTERM){       //15
        printf("received SIGTERM\n");
    }
    g_hoge = 1;
}


int main(int argc, char **argv)
{
    /* シグナルハンドラの設定 */
    if (signal(SIGUSR1, sig_handler) == SIG_ERR) {
        printf("¥ncan't catch SIGUSR1¥n");
    }
 
    /* シグナルハンドラの設定 */
    if (signal(SIGKILL, sig_handler) == SIG_ERR) {
        printf("¥ncan't catch SIGKILL¥n");
    }
 
    /* シグナルハンドラの設定 */
    if (signal(SIGSTOP, sig_handler) == SIG_ERR) {
        printf("¥ncan't catch SIGSTOP¥n");
    }
    /* シグナルハンドラの設定 */
    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        printf("¥ncan't catch SIGINT");
    }
    /* シグナルハンドラの設定 */
    if (signal(SIGTERM, sig_handler) == SIG_ERR) {
        printf("¥ncan't catch SIGTERM");
    }

    GpioThread gpiolist[3];
    int num = 0;
    int gpiopn[3]={GPIO13,GPIO19,GPIO26};
    int gpiopnout[3]={GPIO_DIR_IN,GPIO_DIR_OUT,GPIO_DIR_OUT};
    for(int i=0;i<3;i++){
        gpiolist[i].CreateNew(gpiopn[i],gpiopnout[i]);
        gpiolist[i].Start();
    }
    gpiolist[2].Chgpio(ON);
    gpiolist[1].Chgpio(ON);
    while(g_hoge==0){
        if(num%2000==0){
            gpiolist[2].Chgpio(gpiolist[2].gpiopin == OFF);
            // printf("%i,%i\n",num,gpiolist[2].gpiopin);
        }
        usleep(1000);
        num++;
    }
    for(int i=0;i<3;i++){
        gpiolist[i].Stop();
        gpiolist[i].DelWhread();
    }
    return 0;
}
