#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "enum.h"
#include "gpiol.h"
// #include <cstring>

static int linuxgpio_export(unsigned int gpio)
{
  int fd, len, r;
  char buf[11];

  fd = open(GPIO_EXPORT, O_WRONLY);
  if (fd < 0) {
    perror("Can't open /sys/class/gpio/export");
    return fd;
  }

  len = snprintf(buf, sizeof(buf), "%u", gpio);
  r = write(fd, buf, len);
  close(fd);

  return r;
}

static int linuxgpio_unexport(unsigned int gpio)
{
  int fd, len, r;
  char buf[11];

  fd = open(GPIO_UNEXPORT, O_WRONLY);
  if (fd < 0) {
    perror("Can't open /sys/class/gpio/unexport");
    return fd;
  }

  len = snprintf(buf, sizeof(buf), "%u", gpio);
  r = write(fd, buf, len);
  close(fd);

  return r;
}

static int linuxgpio_dir(unsigned int gpio, unsigned int dir)
{
  int fd, r;
  char buf[60];

  snprintf(buf, sizeof(buf), "%s/gpio%u/direction",GPIO_PATH, gpio);

  fd = open(buf, O_WRONLY);
  if (fd < 0) {
    perror("Can't open gpioX/direction");
    return fd;
  }

  if (dir == GPIO_DIR_OUT)
    r = write(fd, "out", 4);
  else
    r = write(fd, "in", 3);

  close(fd);

  return r;
}

static int linuxgpio_dir_out(unsigned int gpio)
{
  return linuxgpio_dir(gpio, GPIO_DIR_OUT);
}

static int linuxgpio_dir_in(unsigned int gpio)
{
  return linuxgpio_dir(gpio, GPIO_DIR_IN);
}

static int linuxgpio_openfd(unsigned int gpio)
{
  char filepath[60];

  snprintf(filepath, sizeof(filepath), "%s/gpio%u/value",GPIO_PATH, gpio);
  return (open(filepath, O_RDWR));
}

int opengpio(unsigned int gpio, unsigned int inout)
{
  int rf;
  if (gpio >= GPIO_MAX){
    return -1;
  }
  rf = linuxgpio_export(gpio);
  if(rf >= 0){
    if(inout == GPIO_DIR_OUT){
      return linuxgpio_dir_out(gpio);
    }else{
      return linuxgpio_dir_in(gpio);
    }
  }else{
    return -1;
  }
}

int ch_gpio(unsigned int gpio, int value)
{
  return linuxgpio_setup_pin(gpio, value);
}

int closegpio(unsigned int gpio)
{
  return linuxgpio_unexport(gpio);
}

int read_gpio(unsigned int gpio)
{
  return linuxgpio_read_pin(gpio);
}

static int linuxgpio_setup_pin(unsigned int gpio, int value)
{
  int gpio_pin;
  int r;
  gpio_pin = linuxgpio_openfd(gpio);
  if (gpio_pin < 0){
    return -1;
  }
  if(value){
    r = write(gpio_pin, "1",1);
  }else{
    r = write(gpio_pin, "0",1);
  }
  if(r!=1){
    return -1;
  }
  close(gpio_pin);
  return 0;
}

static int linuxgpio_read_pin(unsigned int gpio)
{
  int gpio_pin;
  int r = -1;
  char buf;
  gpio_pin = linuxgpio_openfd(gpio);
  if (gpio_pin < 0){
    return r;
  }
  if (lseek(gpio_pin, 0, SEEK_SET)<0){
    close(gpio_pin);
    return -1;
  }
  if(read(gpio_pin, &buf,1) != 1){
    close(gpio_pin);
    return -1;
  }
  if (buf == '1'){
    r = 1;
  }else if(buf == '0'){
    r = 0;
  }
  close(gpio_pin);
  return r;
}
