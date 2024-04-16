//******************************************************************************
//* BOOT  v#####                                                               *
//* Copyright (c) 1996@%%%% Texas Instruments Incorporated                     *
//******************************************************************************

//****************************************************************************
//* BOOT.S
//*
//* THIS IS THE INITAL BOOT ROUTINE FOR TMS470 C++ PROGRAMS.
//* IT MUST BE LINKED AND LOADED WITH ALL C++ PROGRAMS.
//*
//* THIS MODULE PERFORMS THE FOLLOWING ACTIONS:
//*   1) ALLOCATES THE STACK AND INITIALIZES THE STACK POINTER
//*   2) CALLS AUTO-INITIALIZATION ROUTINE
//*   3) CALLS THE FUNCTION MAIN TO START THE C++ PROGRAM
//*   4) CALLS THE STANDARD EXIT ROUTINE
//*
//* THIS MODULE DEFINES THE FOLLOWING GLOBAL SYMBOLS:
//*   1) __stack     STACK MEMORY AREA
//*   2) _c_int00    BOOT ROUTINE
//*
//****************************************************************************


//****************************************************************************
//*  32 BIT STATE BOOT ROUTINE                                               *
//****************************************************************************

        .global __stack
//***************************************************************
//* DEFINE THE USER MODE STACK (DEFAULT SIZE IS 512)
//***************************************************************
        .section ".stack","aw",%nobits
__stack: .zero 4

         .text
        .global _c_int00
        .type   _c_int00,%function
        .arm
//***************************************************************
//* FUNCTION DEF: _c_int00
//***************************************************************
_c_int00:

        #ifdef __ARM_FP
        //*------------------------------------------------------
        //* SETUP PRIVILEGED AND USER MODE ACCESS TO COPROCESSORS
        //* 10 AND 11, REQUIRED TO ENABLE NEON/VFP
        //* COPROCESSOR ACCESS CONTROL REG
        //* BITS [23:22] - CP11, [21:20] - CP10
        //* SET TO 0b11 TO ENABLE USER AND PRIV MODE ACCESS
        //*------------------------------------------------------
        MRC      p15,#0x0,r0,c1,c0,#2
        MOV      r3,#0xf00000
        ORR      r0,r0,r3
        MCR      p15,#0x0,r0,c1,c0,#2

        //*------------------------------------------------------
        // SET THE EN BIT, FPEXC[30] TO ENABLE NEON AND VFP
        //*------------------------------------------------------
        MOV      r0,#0x40000000
        FMXR     FPEXC,r0
        #endif

        //*------------------------------------------------------
        //* SET TO USER MODE
        //*------------------------------------------------------
        MRS     r0, cpsr
        BIC     r0, r0, #0x1F  // CLEAR MODES
        ORR     r0, r0, #0x10  // SET USER MODE
        MSR     cpsr_cf, r0

        //*------------------------------------------------------
        //* INITIALIZE THE USER MODE STACK
        //*------------------------------------------------------
        #if __TI_AVOID_EMBEDDED_CONSTANTS
        MOVW    sp, :lower16:__STACK_END
        MOVT    sp, :upper16:__STACK_END
        #else
        LDR     sp, c_STACK_END
        #endif

        //*------------------------------------------------------
	//* Call the __mpu_init hook function.
        //*------------------------------------------------------
        BL      __mpu_init

        //*------------------------------------------------------
        //* Perform all the required initializations when
        //* _system_pre_init() returns non-zero:
        //*   - Process BINIT Table
        //*   - Perform C auto initialization
        //*   - Call global constructors
        //*------------------------------------------------------
        BL      _system_pre_init
        CMP     R0, #0
        BEQ     bypass_auto_init
        BL      __TI_auto_init
bypass_auto_init:

        //*------------------------------------------------------
        //* CALL APPLICATION
        //*------------------------------------------------------
        BL      _args_main

        //*------------------------------------------------------
        //* IF APPLICATION DIDN'T CALL EXIT, CALL EXIT(1)
        //*------------------------------------------------------
        MOV     R0, #1
        BL      exit

        //*------------------------------------------------------
        //* DONE, LOOP FOREVER
        //*------------------------------------------------------
L1:     B       L1


//***************************************************************
//* CONSTANTS USED BY THIS MODULE
//***************************************************************
        #if !__TI_AVOID_EMBEDDED_CONSTANTS
c_STACK_END: .long __STACK_END
        #endif

//******************************************************
//* UNDEFINED REFERENCES                               *
//******************************************************
	.global	__STACK_END
        .global _system_pre_init
        .global __TI_auto_init
	.global _args_main
	.global	exit
	.global	__mpu_init

	.end
