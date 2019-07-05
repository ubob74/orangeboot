.PHONY := clean

ARM_PREFIX=arm-buildroot-linux-gnueabihf-

CC := ${ARM_PREFIX}gcc
LD := ${ARM_PREFIX}ld.bfd
OBJCOPY := ${ARM_PREFIX}objcopy

LD_SCRIPT := ./boot.lds
DEV := /dev/uc
TOOL := tools/mksunxiboot

CFLAGS := -D__KERNEL__

CFLAGS += -nostdinc -isystem $(shell (${CC} -print-file-name=include))
CFLAGS += -Iinclude
CFLAGS += -ffunction-sections -fdata-sections -fno-common
CFLAGS += -ffreestanding -fno-builtin

CFLAGS_ARM +=-marm
CFLAGS_ARM +=-march=armv7-a
CFLAGS_ARM +=-mno-unaligned-access
#CFLAGS_ARM +=-msoft-float
CFLAGS_ARM +=-mabi=aapcs-linux

SRC = main.c init.c gpio.c serial.c clock.c ns16550.c

vpath %.c
ASMS = $(SRC:.c=.s)
OBJS = $(SRC:.c=.o)
OBJS += vectors.o

all: boot-spl.bin

boot-spl.bin: boot-spl
	${OBJCOPY} -j .text -j .rodata -j .data \
		-j .dtb.init.rodata  -O binary $< $@

boot-spl: start.o built-in.o asm-build
	${LD} -T ${LD_SCRIPT} --gc-sections -Bstatic --gc-sections --no-dynamic-linker \
		-Ttext 0x60 ./start.o \
		--start-group ./built-in.o --end-group \
		-Map boot-spl.map -o $@

asm-build: ${ASMS}

built-in.o: ${OBJS}
	${LD} -r -o $@ $^

start.o: start.S
	${CC} -Wp,-MD,./.start.o.d ${CFLAGS} ${CFLAGS_ARM} \
		-g -Wa,-mimplicit-it=always -pipe -c -o $@ $<

vectors.o: vectors.S
	${CC} -Wp,-MD,./.vectors.o.d ${CFLAGS} ${CFLAGS_ARM} \
		-g -Wa,-mimplicit-it=always -mword-relocations -fno-pic -pipe -c -o $@ $<

%.o: %.c
	${CC} -Wall -Wstrict-prototypes -std=gnu11 -fshort-wchar -Os -fno-stack-protector \
		-fno-delete-null-pointer-checks -g -fstack-usage \
		${CFLAGS_ARM} -fno-pic ${CFLAGS} -c -o $@ $^

%.s: %.c
	${CC} -Wall -Wstrict-prototypes -std=gnu11 -fno-stack-protector \
		-fno-delete-null-pointer-checks -g -fstack-usage \
		${CFLAGS_ARM} ${CFLAGS} -S $^

install:
	$(shell ${TOOL} ./boot-spl.bin ./orangeboot-spl.bin)
	$(shell sudo dd if=./orangeboot-spl.bin of=${DEV} bs=1024 seek=8)

clean:
	rm -f *.o .*.o.d *.bin *.su *.map ./boot-spl *.s
