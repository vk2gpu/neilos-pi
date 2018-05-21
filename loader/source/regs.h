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

// Pi1 - 0x7E000000
// Pi2 (Pi3 32-bit too?) - 0x3F000000
#define BCM2708_PERI_BASE 0x3F000000

#define GPIO_BASE (BCM2708_PERI_BASE + 0x00200000)
#define TIMER_BASE (BCM2708_PERI_BASE + 0x00003000)

#define GPFSEL0 (GPIO_BASE + 0x00000000)		// GPIO Pin 0 - 9
#define GPFSEL1 (GPIO_BASE + 0x00000004)		// GPIO Pin 10 - 19
#define GPFSEL2 (GPIO_BASE + 0x00000008)		// GPIO Pin 20 - 29
#define GPFSEL3 (GPIO_BASE + 0x0000000C)		// GPIO Pin 30 - 39
#define GPFSEL4 (GPIO_BASE + 0x00000010)		// GPIO Pin 40 - 49
#define GPFSEL5 (GPIO_BASE + 0x00000014)		// GPIO Pin 50 - 59
#define GPSET0 (GPIO_BASE + 0x0000001C)			// GPIO Pin Output Set 0
#define GPSET1 (GPIO_BASE + 0x00000020)			// GPIO Pin Output Set 1
#define GPCLR0 (GPIO_BASE + 0x00000028)			// GPIO Pin Output Clear 0
#define GPCLR1 (GPIO_BASE + 0x0000002C)			// GPIO Pin Output Clear 1

#endif // REGS_H
