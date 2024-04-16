//******************************************************************************
//* MEMSET_T2.ASM  - THUMB-2 STATE -  v#####                                   *
//* Copyright (c) 1996@%%%% Texas Instruments Incorporated                     *
//******************************************************************************

//****************************************************************************
//* memset - INITIALIZE MEMORY WITH VALUE.
//*
//*     C Prototype   : void *memset(void *s, int c, size_t n)//
//*      C++ Prototype : void *std::memset(void *s, int c, std::size_t n)//
//*
//****************************************************************************
//*
//*   o DESTINATION LOCATION IS IN r0
//*   o INITIALIZATION VALUE IS IN r1
//*   o NUMBER OF BYTES TO INITIALIZE IS IN r2
//*
//*   o ORIGINAL DESTINATION LOCATION RETURNED IN r0
//****************************************************************************

	.equ __TI_memset,1
	.section .text:memset, "ax", %progbits
	.global memset
	.thumb_func
memset:
	PUSH	{R0, R4, R5, R6, LR}	// save R0 also since original dst
					// address is returned.

	TST	R0, #3			// check for word alignment
	BEQ	_word_aligned

			// set bytes until there are no more
					// to set or until address is aligned
_unaligned_loop:
	CMP	R2, #0
	ITTT	HI
	STRBHI	R1, [R0], #1
	SUBSHI	R2, R2, #1
	TSTHI	R0, #3
	BNE	_unaligned_loop

	CMP	R2, #0			// return early if no more bytes
	IT	EQ
	POPEQ	{R0, R4, R5, R6, PC}	// to set.

_word_aligned:
	ANDS	R1, R1, #255		// be safe since prototype has value as
					// as an int rather than unsigned char

	ORR	R1, R1, R1, LSL	#8	// replicate byte in 2nd byte of
					// register

	CMP	R2,#4			// are at least 4 bytes being set
	BCC	_memset3

	ORR	R1, R1, R1, LSL	#16	// replicate byte in upper 2 bytes
					// of register. note that each of
					// the bottom 2 bytes already contain
					// the byte value from above.

	CMP	R2,#8			// are at least 8 bytes being set
	BCC	_memset7

	MOV	R6,R1			// copy bits into another register so
					// 8 bytes at a time can be copied.
					// use R5 since it is already being
					// saved/restored.

	CMP	R2,#16			// are at least 16 bytes being set
	BCC	_memset15

	MOV	R4, R1			// copy bits into 2 other registers so
	MOV	R5, R1			// 16 bytes at a time can be copied

	SUBS	R3, R2, #15		// set up loop count
	ANDS	R2, R2, #15		// determine number of bytes to set
					// after setting 16 byte blocks

_memset16_loop:				// set blocks of 16 bytes
	STMIA	R0!, {R1, R4, R5, R6}
	SUBS	R3, R3, #16
	BHI	_memset16_loop

_memset15:				// may still be as many as 15 bytes to
					// set. the address in R0 is guaranteed
					// to be word aligned here.

	TST	R2, #8			// are at least 8 bytes being set
	IT	NE
	STMIANE	R0!, {R1, R6}


_memset7:				// may still be as many as 7 bytes to
					// set. the address in R0 is guaranteed
					// to be word aligned here.

	TST	R2, #4			// are at least 4 bytes being set
	IT	NE
	STRNE	R1, [R0], #4

_memset3:				// may still be as many as 3 bytes to
					// set. the address in R0 is guaranteed
					// to be word aligned here.

	TST	R2, #2			// are there at least 2 more bytes to
	IT	NE
	STRHNE	R1, [R0], #2		// set.	 the address in R0 is guaranteed
					// to be half-word aligned here.

	TST	R2, #1			// is there one remaining byte to set
	IT	NE
	STRBNE	R1, [R0]


	POP	{R0, R4, R5, R6, PC}		// restore regs and return

	.section .text:TI_memset_small, "ax", %progbits
	.global TI_memset_small
	.thumb_func
TI_memset_small:
	MOVS	r3, #0
_loop:	CMP	r2, r3
	IT	eq
	BXEQ	lr
	STRB	r1, [r0, r3]
	ADDS	r3, #1
	B	_loop
