#ifndef REGS_H
#define REGS_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef signed char i8;
typedef signed short i16;
typedef signed int i32;

#define REG8(a) ((volatile u8*)(a))
#define REG16(a) ((volatile u16*)(a))
#define REG32(a) ((volatile u32*)(a))

// TODO: Query.
#define SYSTEM_CLOCK_HZ 250000000

// See BCM2835 docs for details about registers defined.

// Pi1 - 0x7E000000
// Pi2 (Pi3 32-bit too?) - 0x3F000000
#define BCM2708_PERI_BASE 0x3F000000

#define GPIO_BASE (BCM2708_PERI_BASE + 0x00200000)
#define TIMER_BASE (BCM2708_PERI_BASE + 0x00003000)
#define AUX_BASE (BCM2708_PERI_BASE + 0x00215000)

// GPIO registers.
#define GPFSEL0 (GPIO_BASE + 0x00)
#define GPFSEL1 (GPIO_BASE + 0x04)
#define GPFSEL2 (GPIO_BASE + 0x08)
#define GPFSEL3 (GPIO_BASE + 0x0C)
#define GPFSEL4 (GPIO_BASE + 0x10)
#define GPFSEL5 (GPIO_BASE + 0x14)
#define GPSET0 (GPIO_BASE + 0x1C)
#define GPSET1 (GPIO_BASE + 0x20)
#define GPCLR0 (GPIO_BASE + 0x28)
#define GPCLR1 (GPIO_BASE + 0x2C)

#define GPPUD (GPIO_BASE + 0x94)
#define GPPUDCLK0 (GPIO_BASE + 0x98)
#define GPPUDCLK1 (GPIO_BASE + 0x9C)

// GPIO selection parameters.
#define GPIO_FN_INPUT (0x0)
#define GPIO_FN_OUTPUT (0x1)
#define GPIO_FN_ALT0 (0x4)
#define GPIO_FN_ALT1 (0x5)
#define GPIO_FN_ALT2 (0x6)
#define GPIO_FN_ALT3 (0x7)
#define GPIO_FN_ALT4 (0x3)
#define GPIO_FN_ALT5 (0x2)

// Aux peripherals.
#define AUX_IRQ (AUX_BASE + 0x00)
#define AUX_ENABLES (AUX_BASE + 0x04)
#define AUX_MU_IO_REG (AUX_BASE + 0x40)
#define AUX_MU_IER_REG (AUX_BASE + 0x44)
#define AUX_MU_IIR_REG (AUX_BASE + 0x48)
#define AUX_MU_LCR_REG (AUX_BASE + 0x4C)
#define AUX_MU_MCR_REG (AUX_BASE + 0x50)
#define AUX_MU_LSR_REG (AUX_BASE + 0x54)
#define AUX_MU_MSR_REG (AUX_BASE + 0x58)
#define AUX_MU_SCRATCH (AUX_BASE + 0x5C)
#define AUX_MU_CNTL_REG (AUX_BASE + 0x60)
#define AUX_MU_STAT_REG (AUX_BASE + 0x64)
#define AUX_MU_BAUD_REG (AUX_BASE + 0x68)

// Aux IRQ parameters.
#define AUX_IRQ_MU_PENDING (1)
#define AUX_IRQ_SPI1_PENDING (2)
#define AUX_IRQ_SPI2_PENDING (4)

// Aux enables.
#define AUX_ENABLES_MU (1)
#define AUX_ENABLES_SPI1 (2)
#define AUX_ENABLES_SPI2 (4)



#endif // REGS_H
