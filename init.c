#include <gpio.h>
#include <serial.h>
#include <clock.h>
#include <init.h>

void init(void)
{
	clock_init();
	gpio_init();
	serial_init();
}
