#ifndef _CLOCK_H
#define _CLOCK_H

#define CCU_BASE				0x01C20000
#define APB2_CFG_REG_OFFSET		0x0058
#define BUS_CLK_GATING_REG3_OFFSET	0x006C
#define BUS_SOFT_RST_REG4_OFFSET	0x02D8

#define APB2_CLK_SRC_OSC24M			(0x1 << 24)
#define APB2_CLK_RATE_N_1			(0x0 << 16)
#define APB2_CLK_RATE_M(m)			((m - 1) << 0)

#define APB2_GATE_UART0_SHIFT		(16)
#define APB2_RESET_UART0_SHIFT		(16)

void clock_init(void);

#endif
