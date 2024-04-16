/*=========================*/
/*     Linker Settings     */
/*=========================*/

--ram_model
--args 0x1000
--diag_suppress=10068 /* "no matching section" */
--cinit_compression=off
-e _c_int00_secure

-heap  0x20000      /* HEAP AREA SIZE                */
-stack 0x20000      /* SOFTWARE STACK SIZE           */

#define DDR0_ALLOCATED_START  0xA0000000
#define C7X_ALLOCATED_START DDR0_ALLOCATED_START + 0x08000000

#define C7X_EXT_DATA_BASE   (C7X_ALLOCATED_START + 0x00100000)
#define C7X_MEM_TEXT_BASE   (C7X_ALLOCATED_START + 0x00200000)
#define C7X_MEM_DATA_BASE   (C7X_ALLOCATED_START + 0x00300000)
#define C7X_DDR_SPACE_BASE  (C7X_ALLOCATED_START + 0x00400000)

/*--------------------------------------------------------------------------*/
/*                               Memory Map                                 */
/*--------------------------------------------------------------------------*/
MEMORY
{
    L2SRAM (RWX):  org = 0x64800000,          len = 0x00070000
    DDR0_RESERVED: org = 0x80000000,          len = 0x20000000   /* 512MB Reserved for A72 OS */
    C7X_IPC_D:     org = C7X_ALLOCATED_START, len = 0x00100000   /*  1MB DDR */
    C7X_EXT_D:     org = C7X_EXT_DATA_BASE,   len = 0x00100000   /*  1MB DDR */
    C7X_TEXT:      org = C7X_MEM_TEXT_BASE,   len = 0x00100000   /*  1MB DDR */
    C7X_DATA:      org = C7X_MEM_DATA_BASE,   len = 0x00100000   /*  1MB DDR */
    C7X_DDR_SPACE: org = C7X_DDR_SPACE_BASE,  len = 0x00C00000   /* 12MB DDR */
}

/*----------------------------------------------------------------------------*/
/* Section Configuration                                                      */
/*----------------------------------------------------------------------------*/
SECTIONS
{
    boot:
    {
      boot.*<boot.oe71>(.text)
    } load > C7X_TEXT ALIGN(0x200000)
    
/* Code sections. */
    GROUP LOAD_START( lnkStartFlashAddress ),
          LOAD_END( lnkEndFlashAddress )
    {
        .vecs                   : {} ALIGN(0x400000)
        .secure_vecs            : {} ALIGN(0x200000)
        .text:_c_int00_secure   : {} ALIGN(0x200000)
        .text                   : {} ALIGN(0x200000)

        .cinit                  : {}  /* could be part of const */
        .const                  : {}
        .KERNEL_FUNCTION LOAD_START( lnkKernelFuncStartAddr ),
                         LOAD_END( lnkKernelFuncEndAddr )
                                : {} palign( 0x10000 )
    } > C7X_DDR_SPACE

/* Data sections. */
    GROUP  palign( 0x10000 ), LOAD_START( lnkRamStartAddr ), LOAD_END( lnkRamEndAddr )
    {
        .bss                    : {}  /* Zero-initialized data */
        .data                   : {}  /* Initialized data */

        .init_array             : {}  /* C++ initializations */
        .stack                  : {} ALIGN(0x10000)
        .args                   : {}
        .cio                    : {}
        .switch                 : {} /* For exception handling. */
        .sysmem      /* heap */
        .KERNEL_DATA LOAD_START( lnkKernelDataStartAddr ),
                     LOAD_END( lnkKernelDataEndAddr )
                                : {} palign( 0x800 )
    } > C7X_DDR_SPACE_BASE

    GROUP:              >  C7X_DDR_SPACE
    {
        .data.Mmu_tableArray          : type=NOINIT
        .data.Mmu_tableArraySlot      : type=NOINIT
        .data.Mmu_level1Table         : type=NOINIT
        .data.Mmu_tableArray_NS       : type=NOINIT
        .data.Mmu_tableArraySlot_NS   : type=NOINIT
        .data.Mmu_level1Table_NS      : type=NOINIT
    }

    ipc_data_buffer:       > C7X_DDR_SPACE
    .benchmark_buffer:     > C7X_DDR_SPACE ALIGN (32)

    .resource_table: { __RESOURCE_TABLE = .;} > C7X_EXT_D

/* Additional sections settings. */
}

/*-------------------------------- END ---------------------------------------*/
