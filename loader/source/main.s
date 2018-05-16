// Pi1 - 0x7E000000
// Pi2 - 0x3F000000
// Pi3 - 0x20000000??

.equ BCM2708_PERI_BASE, 0x3F000000
.equ GPIO_BASE, (BCM2708_PERI_BASE + 0x00200000)
.equ TIMER_BASE, (BCM2708_PERI_BASE + 0x00003000)

.equ GPFSEL0, (GPIO_BASE + 0x00000000)		// GPIO Pin 0 - 9
.equ GPFSEL1, (GPIO_BASE + 0x00000004)		// GPIO Pin 10 - 19
.equ GPFSEL2, (GPIO_BASE + 0x00000008)		// GPIO Pin 20 - 29
.equ GPFSEL3, (GPIO_BASE + 0x0000000C)		// GPIO Pin 30 - 39
.equ GPFSEL4, (GPIO_BASE + 0x00000010)		// GPIO Pin 40 - 49
.equ GPFSEL5, (GPIO_BASE + 0x00000014)		// GPIO Pin 50 - 59
.equ GPSET0, (GPIO_BASE + 0x0000001C)		// GPIO Pin Output Set 0
.equ GPSET1, (GPIO_BASE + 0x00000020)		// GPIO Pin Output Set 1
.equ GPCLR0, (GPIO_BASE + 0x00000028)		// GPIO Pin Output Clear 0
.equ GPCLR1, (GPIO_BASE + 0x0000002C)		// GPIO Pin Output Clear 1

.section .init

/**
 * _start function
 */ 
.globl _start
_start:

	bl NOS_LED_Init

	_start_loop: 
		mov r0, #1
		lsl r0, #17
		bl NOS_Timer_USleep
		bl NOS_LED_Off

		mov r0, #1
		lsl r0, #17
		bl NOS_Timer_USleep
		bl NOS_LED_On
		b _start_loop



/**
 * Microsecond sleep
 * @param r0 Microseconds
 */
.globl NOS_Timer_USleep
NOS_Timer_USleep:
	mov r1, r0
	ldr r0, =TIMER_BASE
	ldrd r2, r3, [r0, #4]
	add r1, r1, r2

	NOS_Timer_Delay_loop:
		ldrd r2, r3, [r0, #4]
		cmp r2, r1
		bls NOS_Timer_Delay_loop

	mov pc, lr

/**
 * Initialize LEDs.
 */
.globl NOS_LED_Init
NOS_LED_Init:
	// GPIO 5, GPFSEL0, 5*3 = 15
	ldr r0, =GPFSEL0
	mov r1, #1
	lsl r1, #15
	str r1, [r0]
	mov pc, lr

/**
 * Turn LED on.
 */
.globl NOS_LED_On
NOS_LED_On:
	// GPIO 5, GPSET0
	ldr r0, =GPSET0
	mov r1, #1
	lsl r1, #5
	str r1, [r0]
	mov pc, lr

/**
 * Turn LED off.
 */
.globl NOS_LED_Off
NOS_LED_Off:
	// GPIO 5, GPCLR0
	ldr r0, =GPCLR0
	mov r1, #1
	lsl r1, #5
	str r1, [r0]
	mov pc, lr
