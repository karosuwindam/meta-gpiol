#define OFF 0
#define ON 1

/*GPIOポート入力*/
#define GPIO_PATH "/sys/class/gpio"
#define GPIO_EXPORT GPIO_PATH "/export"
#define GPIO_UNEXPORT GPIO_PATH "/unexport"
// #define GPIO_A GPIO_PATH+"/export"

enum GPIO_PIN{
    GPIO1=1,
    GPIO2,
    GPIO3,
    GPIO4,
    GPIO5,
    GPIO6,
    GPIO7,
    GPIO8,
    GPIO9,
    GPIO10,
    GPIO11,
    GPIO12,
    GPIO13,
    GPIO14,
    GPIO15,
    GPIO16,
    GPIO17,
    GPIO18,
    GPIO19,
    GPIO20,
    GPIO21,
    GPIO22,
    GPIO23,
    GPIO24,
    GPIO25,
    GPIO26,
    GPIO_MAX
};

enum GPIO_DIR{
    GPIO_DIR_IN=0,
    GPIO_DIR_OUT
};