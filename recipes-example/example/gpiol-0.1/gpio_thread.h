#include <pthread.h>
#include "enum.h"

#define STOP 0
#define START 1
enum thread_f{
    thread_STOP=0,
    thread_START,
    Dummy_thread_f = 0xFFFFFF
};
enum gpioport_f{
    gpioport_f_OFF=0,
    gpioport_f_ON,
    Dummy_gpioport_f=0xFFFFFF
};

#define GPIO_LOOP_SLEEP 1000*20

class GpioThread
{

public:
    GpioThread();
    virtual ~GpioThread();
    int gpiopin=OFF;
    int CreateNew(int gpio, int inout);
    int Start();
    int Stop();
    void Chgpio(int inout);
    int DelWhread();
private: 
    void Wthread(void);
    void Gpioread();
    int exit=0;
    
    GpioL gpio_tmp;
    gpioport_f gpioc_f=gpioport_f_OFF;
    //pthread_t thread1;
    thread_f stop_flag=thread_STOP;

    static void* LaunchThread(void *pParam){
       reinterpret_cast<GpioThread*>(pParam)->exerun();
        pthread_exit(NULL);
    }
    void exerun();

    pthread_t tid_;
    pthread_mutex_t mutex_;
    
};