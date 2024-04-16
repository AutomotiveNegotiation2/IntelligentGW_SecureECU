/*=========================*/
/*     Linker Settings     */
/*=========================*/

--retain="*(.bootCode)"
--retain="*(.startupCode)"
--retain="*(.startupData)"
--retain="*(.irqStack)"
--retain="*(.fiqStack)"
--retain="*(.abortStack)"
--retain="*(.undStack)"
--retain="*(.svcStack)"

--fill_value=0
--stack_size=0x4000
--heap_size=0x8000
--entry_point=_freertosresetvectors

-stack  0x4000  /* SOFTWARE STACK SIZE */
-heap   0x8000  /* HEAP AREA SIZE      */

/*-------------------------------------------*/
/*       Stack Sizes for various modes       */
/*-------------------------------------------*/
__IRQ_STACK_SIZE   = 0x00001000;
__FIQ_STACK_SIZE   = 0x0100;
__ABORT_STACK_SIZE = 0x0100;
__UND_STACK_SIZE   = 0x0100;
__SVC_STACK_SIZE   = 0x0100;

/*----------------------------*/
/*      DDR MEMORY MAP        */
/*----------------------------*/

#define DDR0_RESERVED_START     0x80000000
#define DDR0_RESERVED_SIZE      0x20000000 /* 512MB */

#define DDR0_ALLOCATED_START    0xA0000000 /* DDR0_RESERVED_START + DDR0_RESERVED_SIZE */

#define SHARED_DDR_SPACE_START  0xA4000000
#define SHARED_DDR_SPACE_SIZE   0x00800000  /*  8MB */

/*------------------------------------------------*/
/* Size of various Memory Locations for each core */ 
/*------------------------------------------------*/
#define IPC_DATA_SIZE   0x00100000 /*  1MB */
#define EXT_DATA_SIZE   0x00100000 /*  1MB */
#define MEM_TEXT_SIZE   0x00100000 /*  1MB */
#define MEM_DATA_SIZE   0x00100000 /*  1MB */
#define DDR_SPACE_SIZE  0x00C00000 /* 12MB */

#define CORE_TOTAL_SIZE 0x01000000 /* 16MB (IPC_DATA_SIZE + R5F_MEM_TEXT_SIZE + R5F_MEM_DATA_SIZE + DDR_SPACE_SIZE) */

/*-----------------------------*/
/* Start address for each core */ 
/*-----------------------------*/

#define MCU1_0_ALLOCATED_START   (DDR0_ALLOCATED_START)
#define MCU1_1_ALLOCATED_START   (MCU1_0_ALLOCATED_START + CORE_TOTAL_SIZE)
#define MCU2_0_ALLOCATED_START   (MCU1_1_ALLOCATED_START + CORE_TOTAL_SIZE)
#define MCU2_1_ALLOCATED_START   (MCU2_0_ALLOCATED_START + CORE_TOTAL_SIZE)

/*--------------------------- MCU R5FSS0 CORE0 --------------------------*/
#define MCU1_0_IPC_DATA_BASE     (MCU1_0_ALLOCATED_START)
#define MCU1_0_EXT_DATA_BASE     (MCU1_0_IPC_DATA_BASE     + IPC_DATA_SIZE)
#define MCU1_0_MEM_TEXT_BASE     (MCU1_0_EXT_DATA_BASE     + EXT_DATA_SIZE)
#define MCU1_0_MEM_DATA_BASE     (MCU1_0_MEM_TEXT_BASE     + MEM_TEXT_SIZE)
#define MCU1_0_DDR_SPACE_BASE    (MCU1_0_MEM_DATA_BASE     + MEM_DATA_SIZE)
/*--------------------------- MCU R5FSS0 CORE1 --------------------------*/
#define MCU1_1_IPC_DATA_BASE     (MCU1_1_ALLOCATED_START)
#define MCU1_1_EXT_DATA_BASE     (MCU1_1_IPC_DATA_BASE     + IPC_DATA_SIZE)
#define MCU1_1_MEM_TEXT_BASE     (MCU1_1_EXT_DATA_BASE     + EXT_DATA_SIZE)
#define MCU1_1_MEM_DATA_BASE     (MCU1_1_MEM_TEXT_BASE     + MEM_TEXT_SIZE)
#define MCU1_1_DDR_SPACE_BASE    (MCU1_1_MEM_DATA_BASE     + MEM_DATA_SIZE)
/*--------------------------- MAIN R5FSS0 CORE0 -------------------------*/
#define MCU2_0_IPC_DATA_BASE     (MCU2_0_ALLOCATED_START)
#define MCU2_0_EXT_DATA_BASE     (MCU2_0_IPC_DATA_BASE     + IPC_DATA_SIZE)
#define MCU2_0_MEM_TEXT_BASE     (MCU2_0_EXT_DATA_BASE     + EXT_DATA_SIZE)
#define MCU2_0_MEM_DATA_BASE     (MCU2_0_MEM_TEXT_BASE     + MEM_TEXT_SIZE)
#define MCU2_0_DDR_SPACE_BASE    (MCU2_0_MEM_DATA_BASE     + MEM_DATA_SIZE)
/*--------------------------- MAIN R5FSS0 CORE1 -------------------------*/
#define MCU2_1_IPC_DATA_BASE     (MCU2_1_ALLOCATED_START)
#define MCU2_1_EXT_DATA_BASE     (MCU2_1_IPC_DATA_BASE     + IPC_DATA_SIZE)
#define MCU2_1_MEM_TEXT_BASE     (MCU2_1_EXT_DATA_BASE     + EXT_DATA_SIZE)
#define MCU2_1_MEM_DATA_BASE     (MCU2_1_MEM_TEXT_BASE     + MEM_TEXT_SIZE)
#define MCU2_1_DDR_SPACE_BASE    (MCU2_1_MEM_DATA_BASE     + MEM_DATA_SIZE)


/*--------------------------------------------------------------------------*/
/*                               Memory Map                                 */
/*--------------------------------------------------------------------------*/
MEMORY
{
    /*=================== MCU R5F TCM Local View ======================*/
    MCU_R5F_TCMA_VECS       (X) : ORIGIN = 0x00000000 LENGTH = 0x00000040
    MCU_R5F_TCMA            (X) : ORIGIN = 0x00000040 LENGTH = 0x00007FC0
    MCU_R5F_TCMB_VECS       (X) : ORIGIN = 0x41010000 LENGTH = 0x00000040
    MCU_R5F_TCMB            (X) : ORIGIN = 0x41010040 LENGTH = 0x00007FC0

    /*==================== MCU R5F TCM SOC View =======================*/
    /*---------------------- MAIN R5FSS0 CORE1 ------------------------*/
    MCU2_R5F1_ATCM_RSVD  (RWIX) : ORIGIN = 0x05D00000 LENGTH = 0x00000040
    MCU2_R5F1_ATCM       (RWIX) : ORIGIN = 0x05D00040 LENGTH = 0x00007FC0
    MCU2_R5F1_BTCM_RSVD  (RWIX) : ORIGIN = 0x05D10000 LENGTH = 0x00000040
    MCU2_R5F1_BTCM       (RWIX) : ORIGIN = 0x05D10040 LENGTH = 0x00007FC0

    /*===================== MCU MSRAM Locations =======================*/
    OCMRAM_MCU1_0_0      (RWIX) : ORIGIN = 0x41C00000 LENGTH = 0x00001000
    OCMRAM_MCU1_0_1      (RWIX) : ORIGIN = 0x41C01000 LENGTH = 0x00001000
    OCMRAM_MCU1_1_0      (RWIX) : ORIGIN = 0x41C02000 LENGTH = 0x00001000
    OCMRAM_MCU1_1_1      (RWIX) : ORIGIN = 0x41C03000 LENGTH = 0x00001000
    OCMRAM_MCU2_0_0      (RWIX) : ORIGIN = 0x41C04000 LENGTH = 0x00001000
    OCMRAM_MCU2_0_1      (RWIX) : ORIGIN = 0x41C05000 LENGTH = 0x00001000
    OCMRAM_MCU2_1_0      (RWIX) : ORIGIN = 0x41C06000 LENGTH = 0x00001000
    OCMRAM_MCU2_1_1      (RWIX) : ORIGIN = 0x41C07000 LENGTH = 0x00001000
    OCMC_RAM_BOARD_CFG   (RWIX) : ORIGIN = 0x41C80000 LENGTH = 0x00002000
    OCMC_RAM             (RWIX) : ORIGIN = 0x41C82000 LENGTH = 0x0007DB00
    OCMC_RAM_X509_HEADER (RWIX) : ORIGIN = 0x41CFFB00 LENGTH = 0x00000500   

    /*=================== COMPUTE_CLUSTER0_MSMC_SRAM ==================*/
    /*---------- J7200 Reserved Memory for ARM Trusted Firmware -------*/
    MSMC3_ARM_FW         (RWIX) : ORIGIN = 0x70000000 LENGTH = 0x00040000   /* 256KB       */
    /*-----------------------------------------------------------------*/
    MSMC3                (RWIX) : ORIGIN = 0x70040000 LENGTH = 0x001B0000   /* 2MB - 320KB */
    /*------------- J7200 Reserved Memory for DMSC Firmware -----------*/
    MSMC3_DMSC_FW        (RWIX) : ORIGIN = 0x701F0000 LENGTH = 0x00010000   /* 64KB        */

    /*================================= J721E DDR Locations ==================================*/
    DDR0_RESERVED       (RWIX)  : ORIGIN = DDR0_RESERVED_START      LENGTH = DDR0_RESERVED_SIZE 
    /*---------------------------------- MCU R5FSS0 CORE0 ------------------------------*/
    MCU1_0_IPC_DATA     (RWIX)	: ORIGIN = MCU1_0_IPC_DATA_BASE     LENGTH = IPC_DATA_SIZE
    MCU1_0_EXT_DATA     (RWIX)	: ORIGIN = MCU1_0_EXT_DATA_BASE     LENGTH = EXT_DATA_SIZE
    MCU1_0_R5F_MEM_TEXT (RWIX)	: ORIGIN = MCU1_0_MEM_TEXT_BASE     LENGTH = MEM_TEXT_SIZE
    MCU1_0_R5F_MEM_DATA (RWIX)	: ORIGIN = MCU1_0_MEM_DATA_BASE     LENGTH = MEM_DATA_SIZE
    MCU1_0_DDR_SPACE    (RWIX)	: ORIGIN = MCU1_0_DDR_SPACE_BASE    LENGTH = DDR_SPACE_SIZE
    /*---------------------------------- MCU R5FSS0 CORE1 ------------------------------*/
    MCU1_1_IPC_DATA     (RWIX)	: ORIGIN = MCU1_1_IPC_DATA_BASE     LENGTH = IPC_DATA_SIZE
    MCU1_1_EXT_DATA     (RWIX)	: ORIGIN = MCU1_1_EXT_DATA_BASE     LENGTH = EXT_DATA_SIZE
    MCU1_1_R5F_MEM_TEXT (RWIX)	: ORIGIN = MCU1_1_MEM_TEXT_BASE     LENGTH = MEM_TEXT_SIZE
    MCU1_1_R5F_MEM_DATA (RWIX)	: ORIGIN = MCU1_1_MEM_DATA_BASE     LENGTH = MEM_DATA_SIZE
    MCU1_1_DDR_SPACE    (RWIX)	: ORIGIN = MCU1_1_DDR_SPACE_BASE    LENGTH = DDR_SPACE_SIZE
    /*---------------------------------- MAIN R5FSS0 CORE0 ------------------------------*/
    MCU2_0_IPC_DATA     (RWIX)	: ORIGIN = MCU2_0_IPC_DATA_BASE     LENGTH = IPC_DATA_SIZE
    MCU2_0_EXT_DATA     (RWIX)	: ORIGIN = MCU2_0_EXT_DATA_BASE     LENGTH = EXT_DATA_SIZE
    MCU2_0_R5F_MEM_TEXT (RWIX)	: ORIGIN = MCU2_0_MEM_TEXT_BASE     LENGTH = MEM_TEXT_SIZE
    MCU2_0_R5F_MEM_DATA (RWIX)	: ORIGIN = MCU2_0_MEM_DATA_BASE     LENGTH = MEM_DATA_SIZE
    MCU2_0_DDR_SPACE    (RWIX)	: ORIGIN = MCU2_0_DDR_SPACE_BASE    LENGTH = DDR_SPACE_SIZE
    /*---------------------------------- MAIN R5FSS0 CORE0 -----------------------------*/
    MCU2_1_IPC_DATA     (RWIX)	: ORIGIN = MCU2_1_IPC_DATA_BASE     LENGTH = IPC_DATA_SIZE
    MCU2_1_EXT_DATA     (RWIX)	: ORIGIN = MCU2_1_EXT_DATA_BASE     LENGTH = EXT_DATA_SIZE
    MCU2_1_R5F_MEM_TEXT (RWIX)	: ORIGIN = MCU2_1_MEM_TEXT_BASE     LENGTH = MEM_TEXT_SIZE
    MCU2_1_R5F_MEM_DATA (RWIX)	: ORIGIN = MCU2_1_MEM_DATA_BASE     LENGTH = MEM_DATA_SIZE
    MCU2_1_DDR_SPACE    (RWIX)	: ORIGIN = MCU2_1_DDR_SPACE_BASE    LENGTH = DDR_SPACE_SIZE
    /*---------------------------------- Shared Region ----------------------------------------*/
    SHARED_DDR_SPACE    (RWIX)	: ORIGIN = SHARED_DDR_SPACE_START  LENGTH = SHARED_DDR_SPACE_SIZE 
}

/*--------------------------------------------------------------*/
/*                     Section Configuration                    */
/*--------------------------------------------------------------*/
SECTIONS
{
    .freertosrstvectors : {} palign(8)      > MCU_R5F_TCMA_VECS
    
    .bootCode           : {} palign(8)      > MCU_R5F_TCMB
    .startupCode        : {} palign(8)      > MCU_R5F_TCMB
    .startupData        : {} palign(8)      > MCU_R5F_TCMB, type = NOINIT
    GROUP 
    {
        .text.hwi       : palign(8)
        .text.cache     : palign(8)
        .text.mpu       : palign(8)
        .text.boot      : palign(8)
    }                                       > MCU_R5F_TCMB

    .text               : {} palign(8)      > MCU2_0_DDR_SPACE
    .const              : {} palign(8)      > MCU2_0_DDR_SPACE
    .rodata             : {} palign(8)      > MCU2_0_DDR_SPACE
    .cinit              : {} palign(8)      > MCU2_0_DDR_SPACE
    .bss                : {} align(4)       > MCU2_0_DDR_SPACE
    .far                : {} align(4)       > MCU2_0_DDR_SPACE
    .data               : {} palign(128)    > MCU2_0_DDR_SPACE
    .sysmem             : {}                > MCU2_0_DDR_SPACE
    .data_buffer        : {} palign(128)    > MCU2_0_DDR_SPACE
    .bss.devgroup*      : {} align(4)       > MCU2_0_DDR_SPACE
    .const.devgroup*    : {} align(4)       > MCU2_0_DDR_SPACE
    .boardcfg_data      : {} align(4)       > MCU2_0_DDR_SPACE

    /* USB or any other LLD buffer for benchmarking */
    .benchmark_buffer (NOLOAD) {} align (8)     > MCU2_0_DDR_SPACE
    ipc_data_buffer (NOINIT) : {} palign(128)	> MCU2_0_DDR_SPACE
    .resource_table          : 
    {
        __RESOURCE_TABLE = .;
    }                                           > MCU2_0_EXT_DATA

    .tracebuf                : {} align(1024)   > MCU2_0_EXT_DATA

    .stack                   : {} align(4)      > MCU2_0_DDR_SPACE  (HIGH)

    .irqStack   : {. = . + __IRQ_STACK_SIZE;} align(4)      > MCU2_0_DDR_SPACE  (HIGH)
    RUN_START(__IRQ_STACK_START)
    RUN_END(__IRQ_STACK_END)

    .fiqStack   : {. = . + __FIQ_STACK_SIZE;} align(4)      > MCU2_0_DDR_SPACE  (HIGH)
    RUN_START(__FIQ_STACK_START)
    RUN_END(__FIQ_STACK_END)

    .abortStack : {. = . + __ABORT_STACK_SIZE;} align(4)    > MCU2_0_DDR_SPACE  (HIGH)
    RUN_START(__ABORT_STACK_START)
    RUN_END(__ABORT_STACK_END)

    .undStack   : {. = . + __UND_STACK_SIZE;} align(4)      > MCU2_0_DDR_SPACE  (HIGH)
    RUN_START(__UND_STACK_START)
    RUN_END(__UND_STACK_END)

    .svcStack   : {. = . + __SVC_STACK_SIZE;} align(4)      > MCU2_0_DDR_SPACE  (HIGH)
    RUN_START(__SVC_STACK_START)
    RUN_END(__SVC_STACK_END)
}



/*-------------------------------- END -----------------------------------------------*/