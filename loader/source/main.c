#include "regs.h"

void usleep(u32 us)
{
	const u32 end = *REG32(TIMER_BASE + 4) + us;
	while(end > *REG32(TIMER_BASE + 4));
}

void csleep(u32 c)
{
	while(c-- != 0)
		asm("nop");
}

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

void dbgio_write(u8 v);

void dbgio_init()
{
	gpio_setup(DBGIO_RCLK, GPIO_FN_OUTPUT);
	gpio_setup(DBGIO_SRCLK, GPIO_FN_OUTPUT);
	gpio_setup(DBGIO_SER, GPIO_FN_OUTPUT);
	gpio_write(DBGIO_RCLK, 0);
	gpio_write(DBGIO_SRCLK, 0);
	gpio_write(DBGIO_SER, 0);

	// Run a sequence to signify that initialization is complete.
	dbgio_write(0xff);
	usleep(1 << 15);
	for(u8 i = 0; i < 8; ++i)
	{
		dbgio_write(1 << i);
		usleep(1 << 17);
	}
	dbgio_write(0);
}

void dbgio_write(u8 v)
{
	// Bit-bang the 8 bits to the shift register.
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



void uart_init(u32 baudrate)
{
	// Configure alt function 0 for pins 14 + 15.
	// ALT0 = UART0.
	// ALT5 = UART1.
	gpio_setup(14, GPIO_FN_ALT5);
	gpio_setup(15, GPIO_FN_ALT5);

	// Pull down pins and wait at least 150 cycles.
	*REG32(GPPUD) = 0;
	csleep(150);
	*REG32(GPPUDCLK0) = (1 << 14) | (1 << 15);
	csleep(150);
	*REG32(GPPUDCLK0) = 0;

	// Enable mini UART and setup.
	*REG32(AUX_ENABLES) = AUX_ENABLES_MU;
	*REG32(AUX_MU_IER_REG) = 0b00000000;
	*REG32(AUX_MU_IIR_REG) = 0b11000110; // 0b11000000 (enable both fifos.) | 0b00000100 (always read zero) | 0b00000010 (clear the receive FIFO)
	*REG32(AUX_MU_LCR_REG) = 0b00000011; // Should just be 1 for 8-bit mode, but doesn't work?
	*REG32(AUX_MU_MCR_REG) = 0b00000000;
	*REG32(AUX_MU_LSR_REG) = 0b00000000;
	*REG32(AUX_MU_MSR_REG) = 0b00000000;
	*REG32(AUX_MU_CNTL_REG) = 0b00000011;	// Enable tx + rx.
	*REG32(AUX_MU_BAUD_REG) = ((SYSTEM_CLOCK_HZ / baudrate) / 8) - 1;
}

u32 uart_recv_blocking()
{
	for(;;)
		if(*REG32(AUX_MU_LSR_REG) & 0b00000001) // Data ready?
			break;

	return *REG32(AUX_MU_IO_REG) & 0xff;
}

void uart_send_blocking(u8 c)
{
	for(;;)
		if(*REG32(AUX_MU_LSR_REG) & 0b00100000) // Is transmitter idle?
			break;
	*REG32(AUX_MU_IO_REG) = c;
}

u32 uart_recv(u8* o)
{
	if(*REG32(AUX_MU_LSR_REG) & 0b00000001) // Data ready?
	{
		*o = *REG32(AUX_MU_IO_REG);
		return 1;
	}
	return 0;
}

void kprint(const char* s)
{
	while(*s != '\0')
		uart_send_blocking(*s++);
}

void loader_main()
{
	gpio_init();
	dbgio_init();
	uart_init(115200);

	u8 i = 0;

	// TODO: VT-100 lib.
	uart_send_blocking(27);
	kprint("[2J");
	uart_send_blocking(27);
	kprint("[;H");
	kprint("Welcome to NeilOS-Pi!\r\n\r\n>");

	for(;;)
	{
		dbgio_write(i);

		u8 c;
		if(uart_recv(&c))
		{
			uart_send_blocking(c);
			++i;
		}
	}
}

