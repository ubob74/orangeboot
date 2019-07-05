#include <common.h>

.globl reset

reset:
	/* disable interrupts (FIQ and IRQ), set the cpu to SVC32 mode */
	mrs r0, cpsr
	and r1, r0, #0x1f	@ mask mode bits
	bic r0, r0, #0x1f	@ clear all mode bits
	orr r0, r0, #0x13	@ set SVC mode
	orr r0, r0, #0xc0	@ disable FIQ and IRQ
	msr cpsr, r0

	/* Setup stack */
	ldr sp, =BOOT_STACK
	bic sp, sp, #0x7 /* 8-byte alignment for ABI compliance */

	bl init
	bl _main

.L1:
	b .L1
