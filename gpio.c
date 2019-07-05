#include <common.h>
#include <gpio.h>
#include <io.h>
#include <asm/types.h>

void gpio_init(void)
{
	gpio_set_mode(PA, 4, GPIO_MODE2);
	gpio_set_mode(PA, 5, GPIO_MODE2);
	gpio_set_pull(PA, 5, GPIO_PULL_UP);
}

void gpio_set_mode(int id, u32 pin, u32 val)
{
	u32 bank = 0;
	struct sunxi_gpio *pio = BANK_TO_GPIO(bank);
	u32 index = GPIO_CFG_INDEX(pin);
	u32 offset = GPIO_CFG_OFFSET(pin);

	clrsetbits_le32(&pio->cfg[0] + index, 0xf << offset, val << offset);
}

int gpio_set_pull(int id, u32 pin, u32 val)
{
	u32 bank = 0;
	u32 index = GPIO_PULL_INDEX(pin);
	u32 offset = GPIO_PULL_OFFSET(pin);
	struct sunxi_gpio *pio = BANK_TO_GPIO(bank);

	clrsetbits_le32(&pio->pull[0] + index, 0x3 << offset, val << offset);
	return 0;
}

void gpio_set_value(int bank, u32 pin, u32 val)
{
	struct sunxi_gpio *pio = BANK_TO_GPIO(bank);

	setbits_le32(&pio->dat, (1 << pin));
}
