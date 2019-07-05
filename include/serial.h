#ifndef _SERIAL_H
#define _SERIAL_H

void serial_init(void);
void serial_putc(char c);
void serial_puts(const char *);

#define puts(x) serial_puts(x)
#define putc(x) serial_putc(x)

#endif
