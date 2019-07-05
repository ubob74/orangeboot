.macro ARM_VECTORS
	b reset
	ldr pc, _undef_instr
	ldr pc, _soft_int
	ldr pc, _prefetch_abrt
	ldr pc, _data_abrt
	ldr pc, _not_used
	ldr pc, _irq
	ldr pc, _fiq
.endm

.globl _start

	.section ".vectors", "ax"

_start:
	ARM_VECTORS

.globl _undef_instr
.globl _soft_int
.globl _prefetch_abrt
.globl _data_abrt
.globl _not_used
.globl _irq
.globl _fiq

_undef_instr:	.word undef_instr
_soft_int:		.word soft_int
_prefetch_abrt:	.word prefetch_abrt
_data_abrt:		.word data_abrt
_not_used:		.word not_used
_irq:			.word irq
_fiq:			.word fiq

.balignl 16,0xdeadbeef

/* Interrupt handling - just hang */

.align 5
undef_instr:
soft_int:
prefetch_abrt:
data_abrt:
not_used:
irq:
fiq:
1:
	b 1b

