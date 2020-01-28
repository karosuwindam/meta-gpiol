#define GPIO21 21
#define GPIO_DIR_IN	0
#define GPIO_DIR_OUT	1


extern int opengpio(unsigned int gpio, unsigned int inout);
extern int closegpio(unsigned int gpio);
extern int ch_gpio(unsigned int gpio, int value);

static int linuxgpio_export(unsigned int gpio);
static int linuxgpio_unexport(unsigned int gpio);
static int linuxgpio_dir(unsigned int gpio, unsigned int dir);
static int linuxgpio_dir_out(unsigned int gpio);
static int linuxgpio_dir_in(unsigned int gpio);
static int linuxgpio_openfd(unsigned int gpio);
static int linuxgpio_setup_pin(unsigned int gpio, int value);


