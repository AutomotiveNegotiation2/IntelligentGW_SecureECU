/*
 * Ring Accelerator
 *
 * Ring accelerator SoC-specific configuration definitions
 *
 * Data version: 210812_211103
 *
 * Copyright (C) 2018-2023 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef RA_CFG_H
#define RA_CFG_H

/**
 * NAVSS0_RINGACC_0 total number of rings
 */
#define RA_NAVSS0_RINGACC_0_MAX_INDEX (974U)
/**
 * Ring accelerator ring event index.
 */
#define RA_NAVSS0_RINGACC_0_RING_OES_EVT_INDEX_OFFSET (0x0U)
/**
 * NAVSS0_RINGACC_0 total number of ring monitors
 */
#define RA_NAVSS0_RINGACC_0_MONITOR_MAX_INDEX (32U)
/**
 * MCU_NAVSS0_RINGACC0 total number of rings
 */
#define RA_MCU_NAVSS0_RINGACC0_MAX_INDEX (256U)
/**
 * Ring accelerator ring event index.
 */
#define RA_MCU_NAVSS0_RINGACC0_RING_OES_EVT_INDEX_OFFSET (0x0U)
/**
 * MCU_NAVSS0_RINGACC0 total number of ring monitors
 */
#define RA_MCU_NAVSS0_RINGACC0_MONITOR_MAX_INDEX (32U)
/**
 * Ring accelerator ring monitor event index.  Must be greater than the max of
 * all SoC RAs max ring index to avoid event indexing conflicts.
 */
#define RA_MON_OES_EVT_INDEX_OFFSET (0x400U)
/**
 * Ring accelerator global control error event index.  Must be greater than
 * the max of all SoC RAs max ring index to avoid event indexing conflicts.
 */
#define RA_GCFG_ERROR_EVT_INDEX (0x800U)

#endif /* RA_CFG_H */
