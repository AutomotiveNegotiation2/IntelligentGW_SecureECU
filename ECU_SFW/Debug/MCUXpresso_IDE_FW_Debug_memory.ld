/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright 2008-2013 Code Red Technologies Ltd,
 * Copyright 2013-2024 NXP
 * Generated linker script file for MIMXRT1176xxxxx
 * Created from memory.ldt by FMCreateLinkMemory
 * Using Freemarker v2.3.30
 * MCUXpresso IDE v11.9.1 [Build 2170] [2024-04-19] on 2024. 8. 14. 오후 4:21:00
 */

MEMORY
{
  /* Define each memory region */
  BOARD_FLASH (rx) : ORIGIN = 0x30000000, LENGTH = 0x400000 /* 4M bytes (alias Flash) */  
  SRAM_OC1 (rwx) : ORIGIN = 0x20240000, LENGTH = 0x80000 /* 512K bytes (alias RAM) */  
  SRAM_OC2 (rwx) : ORIGIN = 0x202c0000, LENGTH = 0x40000 /* 256K bytes (alias RAM2) */  
  NCACHE_REGION (rwx) : ORIGIN = 0x20300000, LENGTH = 0x40000 /* 256K bytes (alias RAM3) */  
  SRAM_OC_ECC1 (rwx) : ORIGIN = 0x20340000, LENGTH = 0x10000 /* 64K bytes (alias RAM4) */  
  SRAM_OC_ECC2 (rwx) : ORIGIN = 0x20350000, LENGTH = 0x10000 /* 64K bytes (alias RAM5) */  
  BOARD_SDRAM (rwx) : ORIGIN = 0x80000000, LENGTH = 0x4000000 /* 64M bytes (alias RAM6) */  
}

  /* Define a symbol for the top of each memory region */
  __base_BOARD_FLASH = 0x30000000  ; /* BOARD_FLASH */  
  __base_Flash = 0x30000000 ; /* Flash */  
  __top_BOARD_FLASH = 0x30000000 + 0x400000 ; /* 4M bytes */  
  __top_Flash = 0x30000000 + 0x400000 ; /* 4M bytes */  
  __base_SRAM_OC1 = 0x20240000  ; /* SRAM_OC1 */  
  __base_RAM = 0x20240000 ; /* RAM */  
  __top_SRAM_OC1 = 0x20240000 + 0x80000 ; /* 512K bytes */  
  __top_RAM = 0x20240000 + 0x80000 ; /* 512K bytes */  
  __base_SRAM_OC2 = 0x202c0000  ; /* SRAM_OC2 */  
  __base_RAM2 = 0x202c0000 ; /* RAM2 */  
  __top_SRAM_OC2 = 0x202c0000 + 0x40000 ; /* 256K bytes */  
  __top_RAM2 = 0x202c0000 + 0x40000 ; /* 256K bytes */  
  __base_NCACHE_REGION = 0x20300000  ; /* NCACHE_REGION */  
  __base_RAM3 = 0x20300000 ; /* RAM3 */  
  __top_NCACHE_REGION = 0x20300000 + 0x40000 ; /* 256K bytes */  
  __top_RAM3 = 0x20300000 + 0x40000 ; /* 256K bytes */  
  __base_SRAM_OC_ECC1 = 0x20340000  ; /* SRAM_OC_ECC1 */  
  __base_RAM4 = 0x20340000 ; /* RAM4 */  
  __top_SRAM_OC_ECC1 = 0x20340000 + 0x10000 ; /* 64K bytes */  
  __top_RAM4 = 0x20340000 + 0x10000 ; /* 64K bytes */  
  __base_SRAM_OC_ECC2 = 0x20350000  ; /* SRAM_OC_ECC2 */  
  __base_RAM5 = 0x20350000 ; /* RAM5 */  
  __top_SRAM_OC_ECC2 = 0x20350000 + 0x10000 ; /* 64K bytes */  
  __top_RAM5 = 0x20350000 + 0x10000 ; /* 64K bytes */  
  __base_BOARD_SDRAM = 0x80000000  ; /* BOARD_SDRAM */  
  __base_RAM6 = 0x80000000 ; /* RAM6 */  
  __top_BOARD_SDRAM = 0x80000000 + 0x4000000 ; /* 64M bytes */  
  __top_RAM6 = 0x80000000 + 0x4000000 ; /* 64M bytes */  
