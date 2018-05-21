.section .init

/**
 * _start function
 */ 
.globl _start
_start:
	// Setup stack pointer @ 128MB.
	mov sp, #0x08000000

	// Branch into loader main.
	bl loader_main

	// Force halt here.
	halt:
		b halt
