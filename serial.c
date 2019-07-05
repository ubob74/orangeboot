#include <serial.h>
#include <ns16550.h>

void serial_putc(char c)
{
	if (c == '\n')
		ns16550_putc('\r');
	ns16550_putc(c);
}

void serial_puts(const char *s)
{
	while (*s)
		serial_putc(*s++);
}

void serial_init(void)
{
	ns16550_init();
}
