#ifndef _NS16550_H_
#define _NS16550_H_

#define UART0_BASE	0x01C28000

#define SUNXI_NS16550_CLK	24000000
#define DEFAULT_BAUD_RATE	115200

#include <io.h>
#include <asm/types.h>

struct ns16550 {
	u32 rbr;
	u32 ier;
	u32 fcr;
	u32 lcr;
	u32 mcr;
	u32 lsr;
	u32 msr;
	u32 spr;
	u32 mdr1;
};

#define thr rbr
#define iir fcr
#define dll rbr
#define dlm ier

#define UART_MCR_DTR    0x01        /* DTR   */
#define UART_MCR_RTS    0x02        /* RTS   */

#define UART_LCR_WLS_MSK 0x03       /* character length select mask */
#define UART_LCR_WLS_5  0x00        /* 5 bit character length */
#define UART_LCR_WLS_6  0x01        /* 6 bit character length */
#define UART_LCR_WLS_7  0x02        /* 7 bit character length */
#define UART_LCR_WLS_8  0x03        /* 8 bit character length */
#define UART_LCR_STB    0x04        /* # stop Bits, off=1, on=1.5 or 2) */
#define UART_LCR_PEN    0x08        /* Parity enable */
#define UART_LCR_EPS    0x10        /* Even Parity Select */
#define UART_LCR_STKP   0x20        /* Stick Parity */
#define UART_LCR_SBRK   0x40        /* Set Break */
#define UART_LCR_DLAB   0x80        /* Divisor latch access bit */

#define UART_LSR_THRE   0x20        /* Xmit holding register empty */
#define UART_LSR_TEMT   0x40        /* Xmitter empty */
#define UART_LSR_ERR    0x80        /* Error */

#define UART_USR_BSY	0x00		/* Busy bit */
#define UART_LCR_8N1    0x03

//#define UART_LCRVAL (UART_LCR_8N1 | UART_LCR_PEN)	/* 8 data, 1 stop, odd parity */
#define UART_LCRVAL UART_LCR_8N1
#define UART_MCRVAL (UART_MCR_DTR | UART_MCR_RTS)   /* RTS/DTR */

#define serial_out(x, y)    writeb(x, y)
#define serial_in(y)        readb(y)

void ns16550_init(void);
void ns16550_putc(char c);

#endif
