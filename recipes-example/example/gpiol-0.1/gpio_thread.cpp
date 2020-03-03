#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include "gpiol.h"
#include "gpio_class.h"
#include "gpio_thread.h"


GpioThread::GpioThread()
:tid_()
,mutex_()
{
    pthread_mutex_init(&mutex_, NULL);
}

GpioThread::~GpioThread()
{
    pthread_cancel(tid_);
    pthread_join(tid_,NULL);
    pthread_mutex_destroy(&mutex_);
}
/*
 * GPIOの新規作成
*/
int GpioThread::CreateNew(int gpio,int inout)
{
    if(gpio_tmp.gpioCreate(gpio,inout) < 0 ){
        return -1;
    }
    gpioc_f = gpioport_f_ON;
    return 0;
}

void GpioThread::Chgpio(int inout)
{
    gpio_tmp.gpioChange(inout);
    return;
}

void GpioThread::Wthread(void)
{
    while (exit!=0)
    {
        gpiopin = gpio_tmp.gpioRead();
        usleep(GPIO_LOOP_SLEEP);
    }
    stop_flag = thread_STOP;
    
    return;
}

int GpioThread::DelWhread()
{
    exit =0;
    while(stop_flag!=thread_STOP){
        usleep(1000);
    }
    gpioc_f = gpioport_f_OFF;
    gpio_tmp.gpioClose();
    return 0;
}

int GpioThread::Start()
{
    if ((stop_flag == thread_STOP)&&(gpioc_f==gpioport_f_ON)){
        stop_flag = thread_START;
        pthread_create(&tid_, NULL, GpioThread::LaunchThread,this);
        //pthread_create(&thread1,NULL,(void *)Wthread,NULL);
    }else{

    }
    return 0;
}

int GpioThread::Stop()
{
    if(stop_flag != thread_STOP){
        pthread_cancel(tid_);
        stop_flag = thread_STOP;
    }
    return 0;
}

void GpioThread::exerun()
{
    while(true){
        gpiopin = gpio_tmp.gpioRead();
        usleep(GPIO_LOOP_SLEEP);
    }
}