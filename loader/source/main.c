#include "regs.h"

void usleep(u32 us)
{
	const u32 end = *REG32(TIMER_BASE + 4) + us;
	while(end > *REG32(TIMER_BASE + 4));
}

#define GPIO_FN_INPUT (0x0)
#define GPIO_FN_OUTPUT (0x1)
#define GPIO_FN_ALT0 (0x4)
#define GPIO_FN_ALT1 (0x5)
#define GPIO_FN_ALT2 (0x6)
#define GPIO_FN_ALT3 (0x7)
#define GPIO_FN_ALT4 (0x3)
#define GPIO_FN_ALT5 (0x2)

static u32 s_gpiosel[6];

void gpio_init()
{
	// Initialize gpiosel to whatever is already there.
	for(u32 i = 0; i < 6; ++i)
	{
		s_gpiosel[i] = *REG32(GPFSEL0 + (i * 4));
	}
}

void gpio_setup(u32 i, u32 fn)
{
	const u32 l = i % 10;
	const u32 s = i / 10;
	const u32 m = 7 << (3 * l);

	s_gpiosel[s] = (s_gpiosel[s] & ~m) | (fn << (3 * l));
	*REG32(GPFSEL0 + (s * 4)) = s_gpiosel[s];
}

void gpio_write(u32 i, u32 v)
{
	const u32 l = i % 32;
	const u32 s = i / 32;
	if(v)
		*REG32(GPSET0 + (s * 4)) = 1 << l;
	else
		*REG32(GPCLR0 + (s * 4)) = 1 << l;
}

#define DBGIO_RCLK 4
#define DBGIO_SRCLK 5
#define DBGIO_SER 6

void dbgio_init()
{
	gpio_setup(DBGIO_RCLK, GPIO_FN_OUTPUT);
	gpio_setup(DBGIO_SRCLK, GPIO_FN_OUTPUT);
	gpio_setup(DBGIO_SER, GPIO_FN_OUTPUT);
	gpio_write(DBGIO_RCLK, 0);
	gpio_write(DBGIO_SRCLK, 0);
	gpio_write(DBGIO_SER, 0);
}

void dbgio_write(u8 v)
{
	const u32 wait_us = 1;
	gpio_write(DBGIO_RCLK, 0);
	for(i32 i = 7; i >= 0; --i)
	{
		gpio_write(DBGIO_SER, (v & (1 << i)) ? 1 : 0);
		gpio_write(DBGIO_SRCLK, 1);
		usleep(wait_us);
		gpio_write(DBGIO_SRCLK, 0);
		usleep(wait_us);
	}
	gpio_write(DBGIO_RCLK, 1);
	usleep(wait_us);
}

void loader_main()
{
	gpio_init();
	dbgio_init();

	u8 i = 0;

	for(;;)
	{
		dbgio_write(i++);
		usleep(1 << 17);

		//gpio_write(6, 0);
		
		//gpio_write(6, 1);
		//usleep(1 << 17);
	}
}

