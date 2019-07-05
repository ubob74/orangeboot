#ifndef _GPIO_H
#define _GPIO_H

#include <asm/types.h>

#define PIO_BASE	0x01C20800
#define PA_CFG0		(PIO_BASE + 0x00)
#define PA_DAT0		(PIO_BASE + 0x10)

/* GPIO mode */
#define GPIO_IN		0
#define GPIO_OUT	1
#define GPIO_MODE2	2

/* GPIO Pull Up/Down */
#define GPIO_PULL_UP	1
#define GPIO_PULL_DOWN	2

#define PA	0
#define PB	1
#define PC	2
#define PD	3
#define PE	4
#define PF	5
#define PG	6

#define SUNXI_PIO_BASE	PIO_BASE
#define SUNXI_GPIO_BANKS 9

struct sunxi_gpio {
	u32 cfg[4];
	u32 dat;
	u32 drv[2];
	u32 pull[2];
};

struct sunxi_gpio_reg {
	struct sunxi_gpio gpio_bank[SUNXI_GPIO_BANKS];
};

#define CFG_INDEX(pin)	(((pin) & 0x1f) >> 3)
#define CFG_PIN_OFFSET(pin)	((((pin) & 0x1f) & 0x7) << 2)
#define CFG_MASK	0xF

#define PULL_INDEX(pin)	(((pin) & 0x1f) >> 4)
#define PULL_PIN_OFFSET(pin)	((((pin) & 0x1f) & 0xf) << 1)
#define PULL_MASK	0x3
#define PULL_OFFSET	0x1C

#define PIO_DAT_OFFSET	0x10

#define BANK_TO_GPIO(bank) &((struct sunxi_gpio_reg *)SUNXI_PIO_BASE)->gpio_bank[bank]

#define GPIO_BANK(pin)      ((pin) >> 5)
#define GPIO_NUM(pin)       ((pin) & 0x1f)

#define GPIO_CFG_INDEX(pin) (((pin) & 0x1f) >> 3)
#define GPIO_CFG_OFFSET(pin)    ((((pin) & 0x1f) & 0x7) << 2)

#define GPIO_PULL_INDEX(pin)    (((pin) & 0x1f) >> 4)
#define GPIO_PULL_OFFSET(pin)   ((((pin) & 0x1f) & 0xf) << 1)

void gpio_init(void);
void gpio_set_mode(int id, u32 pin, u32 mode);
int gpio_set_pull(int id, u32 pin, u32 pull);
void gpio_set_value(int id, u32 pin, u32 val);
void gpio_test(void);

#endif
