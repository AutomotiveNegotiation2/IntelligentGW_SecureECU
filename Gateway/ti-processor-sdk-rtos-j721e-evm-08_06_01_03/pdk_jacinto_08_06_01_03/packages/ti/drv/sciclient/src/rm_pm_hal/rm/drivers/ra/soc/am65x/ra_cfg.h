/*
 * Ring Accelerator SoC configuration
 *
 * Defines the SoC-specific configuration of the Ring Accelerator architecture
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef RA_CFG_H
#define RA_CFG_H

/**
 * AM6 Main Navigator Subsystem total number of rings and max ring index
 */
#define AM6_MAIN_NAVSS_RING_MAX_INDEX   (768u)

/**
 * Ring accelerator ring event index.
 */
#define RA_NAVSS0_RINGACC0_RING_OES_EVT_INDEX_OFFSET (0x0U)
/**
 * AM6 Main Navigator Subsystem total number of ring monitors
 */
#define AM6_MAIN_NAVSS_RING_MONITOR_MAX_INDEX   (32U)

/**
 * AM6 MCU Navigator Subsystem total number of rings and max ring index
 */
#define AM6_MCU_NAVSS_RING_MAX_INDEX    (256u)

/**
 * Ring accelerator ring event index.
 */
#define RA_MCU_NAVSS0_RINGACC0_RING_OES_EVT_INDEX_OFFSET (0x0U)
/**
 * AM6 MCU Navigator Subsystem total number of ring monitors
 */
#define AM6_MCU_NAVSS_RING_MONITOR_MAX_INDEX    (32U)

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
