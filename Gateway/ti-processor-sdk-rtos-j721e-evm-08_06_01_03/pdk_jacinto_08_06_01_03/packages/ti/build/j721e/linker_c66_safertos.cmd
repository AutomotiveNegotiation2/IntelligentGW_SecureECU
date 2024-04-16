/*=========================*/
/*     Linker Settings     */
/*=========================*/

-u InterruptVectorTable

-stack  0x2000                              /* SOFTWARE STACK SIZE           */
-heap   0x1000                              /* HEAP AREA SIZE                */

#define DDR0_CODE_START             ( 0x80000000 )
#define DEFAULT_SECTION_ALIGNMENT   ( 32 )

/*--------------------------------------------------------------------------*/
/*                               Memory Map                                 */
/*--------------------------------------------------------------------------*/
MEMORY
{
    L2SRAM                :   o = 0x00800000 l = 0x00048000   /* 288KB LOCAL L2/SRAM */
    L1PSRAM               :   o = 0x00E00000 l = 0x00008000   /* 32KB LOCAL L1P/SRAM */
    L1DSRAM               :   o = 0x00F00000 l = 0x00008000   /* 32KB LOCAL L1D/SRAM */

    /*========================J721E MCMS3 LOCATIONS ===================*/
    /*---------- J721E Reserved Memory for ARM Trusted Firmware -------*/
    MSMC3_ARM_FW   (RWIX)   : o = 0x70000000, l = 0x20000       /* 128KB */
    MSMC3 (RWIX)            : o = 0x70020000  l = 0x7D0000      /* 8MB - 192KB */
    /*------------- J721E Reserved Memory for DMSC Firmware -----------*/
    MSMC3_DMSC_FW  (RWIX)   : o = 0x707F0000, l = 0x10000       /* 64KB */

    /*======================= J721E DDR LOCATION =======================*/
    DDR0        :   o = 0x80000000 l = 0x20000000   /* 512MB DDR0 */
}

/*----------------------------------------------------------------------------*/
/* Section Configuration                                                      */
/*----------------------------------------------------------------------------*/
SECTIONS
{    
   	/* For SafeRTOS based applications the following symbols need to be exported:
	 *
	 * lnkFlashStartAddr - the start of the Flash memory section used during runtime.
	 *
	 * IMPORTANT NOTE: lnkFlashStartAddr can be relocated (e.g. when a
	 * bootloader is used), but it must be aligned according to its size
	 * (rounded up to the next power of 2), otherwise the MPU will be
	 * configured incorrectly.
	 *
	 * lnkFlashEndAddr - the end of the Flash memory section used during runtime.
	 *
	 * lnkKernelFuncStartAddr - the start address of the Flash block containing
	 * the interrupt vector table and the kernel functions.
	 * NOTE: This should be aligned according to the section size, i.e. 0x8000.
	 *
	 * lnkKernelFuncEndAddr - the end address of the Flash block containing
	 * the interrupt vector table and the kernel functions.
	 *
	 * lnkKernelDataStartAddr - the start address of the RAM block containing
	 * the system stacks and the kernel data.
	 *
	 * lnkKernelDataEndAddr - the end address of the RAM block containing
	 * the system stacks and the kernel data.
	 */

    /* hard addresses forces vecs to be allocated there */
   
    .interrupt_vectors : {. = align(32); }  > DDR0_CODE_START

    .priv_code          palign( DEFAULT_SECTION_ALIGNMENT ),
                        LOAD_START( lnkKernelFuncStartAddr ),
                        LOAD_END( lnkKernelFuncEndAddr ) :
    {
        *(.KERNEL_FUNCTION)
    } > DDR0

    .text:_c_int00      load >  DDR0 ALIGN(0x10000)
    .text:              load >  DDR0 palign( DEFAULT_SECTION_ALIGNMENT ), 
                                     LOAD_START( lnkStartFlashAddress )

    .unpriv_rodata      palign( DEFAULT_SECTION_ALIGNMENT ) :
    {
        *(.const)
        *(.switch)
    } > DDR0

    .cinit              LOAD_END( lnkEndFlashAddress )          : {} > DDR0

    GROUP               palign( DEFAULT_SECTION_ALIGNMENT ),
                        LOAD_START( lnkUnprivilegedDataStartAddr )
    {
        .rodata:  
        .bss:
        .neardata:
        .KERNEL_DATA        palign( DEFAULT_SECTION_ALIGNMENT ),
                            LOAD_START( lnkKernelDataStartAddr ),
                            LOAD_END( lnkKernelDataEndAddr )
    } > DDR0

    GROUP               palign( DEFAULT_SECTION_ALIGNMENT ),
                        LOAD_END( lnkUnprivilegedDataEndAddr )
    {
        .cio:
        .data:
        .sysmem:
        .fardata:
        .far:
    } > DDR0

    .stack              palign( DEFAULT_SECTION_ALIGNMENT ),
                        LOAD_START( lnkStacksStartAddr )        : {} > DDR0 
}

/*-------------------------------- END ---------------------------------------*/
