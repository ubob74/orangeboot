#include <clock.h>
#include <io.h>
#include <asm/types.h>

void clock_init_uart(void)
{
	void *ccu_base = (void *)CCU_BASE;
	void *apb2_div = ccu_base + APB2_CFG_REG_OFFSET;
	void *apb2_gate = ccu_base + BUS_CLK_GATING_REG3_OFFSET;
	void *apb2_reset = ccu_base + BUS_SOFT_RST_REG4_OFFSET;

	writel(APB2_CLK_SRC_OSC24M | APB2_CLK_RATE_N_1 | \
			APB2_CLK_RATE_M(1), apb2_div);
	setbits_le32(apb2_gate, (1 << APB2_GATE_UART0_SHIFT));
	setbits_le32(apb2_reset, (1 << APB2_RESET_UART0_SHIFT));
}

void clock_init(void)
{
	clock_init_uart();
}
