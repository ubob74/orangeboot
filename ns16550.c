#include <common.h>
#include <gpio.h>
#include <ns16550.h>
#include <io.h>

const struct ns16550 *com_port = (struct ns16550 *)UART0_BASE;

static int ns16550_calc_divisor(void)
{
	return DIV_ROUND_CLOSEST(SUNXI_NS16550_CLK, 16 * DEFAULT_BAUD_RATE);
}

static void ns16550_setbrg(int baud_divisor)
{
	serial_out(UART_LCR_DLAB | UART_LCRVAL, &com_port->lcr);
	serial_out(baud_divisor & 0xff, &com_port->dll);
	serial_out((baud_divisor >> 8) & 0xff, &com_port->dlm);
	serial_out(UART_LCRVAL, &com_port->lcr);
}

void ns16550_init(void)
{
	int baud_divisor;

	baud_divisor = ns16550_calc_divisor();

	while (!(readb(&com_port->lsr) & UART_LSR_TEMT));

	serial_out(0x0, &com_port->ier);
	serial_out(0x0, &com_port->fcr);

	ns16550_setbrg(baud_divisor);
}

void ns16550_putc(char c)
{
	while (!(serial_in(&com_port->lsr) & UART_LSR_THRE));
	serial_out(c, (ulong)&com_port->thr);
}
