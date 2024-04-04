// SPDX-License-Identifier: GPL-2.0+
/*
 * j784s4 Quality of Service (QoS) Configuration Data
 * Auto generated from K3 Resource Partitioning tool
 * 
 * Copyright (C) 2022 Texas Instruments Incorporated - https://www.ti.com/
 */
#include <common.h>
#include <asm/arch/hardware.h>
#include "common.h"

struct k3_qos_data j784s4_qos_data[] = {
	/* modules_qosConfig0 - 2 endpoints, 10 channels */
	{
		.reg = K3_DSS_MAIN_0_DSS_INST0_VBUSM_DMA + 0x100 + 0x4 * 0,
		.val = ATYPE_3 | ORDERID_15,
	},
	{
		.reg = K3_DSS_MAIN_0_DSS_INST0_VBUSM_DMA + 0x100 + 0x4 * 1,
		.val = ATYPE_3 | ORDERID_15,
	},
	{
		.reg = K3_DSS_MAIN_0_DSS_INST0_VBUSM_DMA + 0x100 + 0x4 * 2,
		.val = ATYPE_3 | ORDERID_15,
	},
	{
		.reg = K3_DSS_MAIN_0_DSS_INST0_VBUSM_DMA + 0x100 + 0x4 * 3,
		.val = ATYPE_3 | ORDERID_15,
	},
	{
		.reg = K3_DSS_MAIN_0_DSS_INST0_VBUSM_DMA + 0x100 + 0x4 * 4,
		.val = ATYPE_3 | ORDERID_15,
	},
	{
		.reg = K3_DSS_MAIN_0_DSS_INST0_VBUSM_DMA + 0x100 + 0x4 * 5,
		.val = ATYPE_3 | ORDERID_15,
	},
	{
		.reg = K3_DSS_MAIN_0_DSS_INST0_VBUSM_DMA + 0x100 + 0x4 * 6,
		.val = ATYPE_3 | ORDERID_15,
	},
	{
		.reg = K3_DSS_MAIN_0_DSS_INST0_VBUSM_DMA + 0x100 + 0x4 * 7,
		.val = ATYPE_3 | ORDERID_15,
	},
	{
		.reg = K3_DSS_MAIN_0_DSS_INST0_VBUSM_DMA + 0x100 + 0x4 * 8,
		.val = ATYPE_3 | ORDERID_15,
	},
	{
		.reg = K3_DSS_MAIN_0_DSS_INST0_VBUSM_DMA + 0x100 + 0x4 * 9,
		.val = ATYPE_3 | ORDERID_15,
	},
	{
		.reg = K3_DSS_MAIN_0_DSS_INST0_VBUSM_FBDC + 0x100 + 0x4 * 0,
		.val = ATYPE_3 | ORDERID_15,
	},
	{
		.reg = K3_DSS_MAIN_0_DSS_INST0_VBUSM_FBDC + 0x100 + 0x4 * 1,
		.val = ATYPE_3 | ORDERID_15,
	},
	{
		.reg = K3_DSS_MAIN_0_DSS_INST0_VBUSM_FBDC + 0x100 + 0x4 * 2,
		.val = ATYPE_3 | ORDERID_15,
	},
	{
		.reg = K3_DSS_MAIN_0_DSS_INST0_VBUSM_FBDC + 0x100 + 0x4 * 3,
		.val = ATYPE_3 | ORDERID_15,
	},
	{
		.reg = K3_DSS_MAIN_0_DSS_INST0_VBUSM_FBDC + 0x100 + 0x4 * 4,
		.val = ATYPE_3 | ORDERID_15,
	},
	{
		.reg = K3_DSS_MAIN_0_DSS_INST0_VBUSM_FBDC + 0x100 + 0x4 * 5,
		.val = ATYPE_3 | ORDERID_15,
	},
	{
		.reg = K3_DSS_MAIN_0_DSS_INST0_VBUSM_FBDC + 0x100 + 0x4 * 6,
		.val = ATYPE_3 | ORDERID_15,
	},
	{
		.reg = K3_DSS_MAIN_0_DSS_INST0_VBUSM_FBDC + 0x100 + 0x4 * 7,
		.val = ATYPE_3 | ORDERID_15,
	},
	{
		.reg = K3_DSS_MAIN_0_DSS_INST0_VBUSM_FBDC + 0x100 + 0x4 * 8,
		.val = ATYPE_3 | ORDERID_15,
	},
	{
		.reg = K3_DSS_MAIN_0_DSS_INST0_VBUSM_FBDC + 0x100 + 0x4 * 9,
		.val = ATYPE_3 | ORDERID_15,
	},


	/* Following registers set 1:1 mapping for orderID MAP1/MAP2
	 * remap registers. orderID x is remapped to orderID x again
	 * This is to ensure orderID from MAP register is unchanged
	 */

	/* K3_DSS_MAIN_0_DSS_INST0_VBUSM_DMA - 1 groups */
	{
		.reg = K3_DSS_MAIN_0_DSS_INST0_VBUSM_DMA + 0,
		.val = 0x76543210,
	},
	{
		.reg = K3_DSS_MAIN_0_DSS_INST0_VBUSM_DMA + 4,
		.val = 0xfedcba98,
	},

	/* K3_DSS_MAIN_0_DSS_INST0_VBUSM_FBDC - 1 groups */
	{
		.reg = K3_DSS_MAIN_0_DSS_INST0_VBUSM_FBDC + 0,
		.val = 0x76543210,
	},
	{
		.reg = K3_DSS_MAIN_0_DSS_INST0_VBUSM_FBDC + 4,
		.val = 0xfedcba98,
	},

	/* The following registers map the VBUSM source interfaces to 
	 * VBUSM.C threads. Each bit is for each VBUSM source.
	 * A bit of 0 maps to VBUSM.C Thread0 (NRT)
	 * A bit of 1 maps to VBUSM.C Thread2 (RT)
	 */

	/* NAVSS0_NORTH_0_NBSS_NB0_CFG_MMRS VBUSM source to VBUSM.C thread mapping */
	{
		.reg = NAVSS0_NORTH_0_NBSS_NB0_CFG_MMRS + 0x10,
		.val = NB_THREADMAP_2,
	},
	/* NAVSS0_NORTH_1_NBSS_NB1_CFG_MMRS VBUSM source to VBUSM.C thread mapping */
	{
		.reg = NAVSS0_NORTH_1_NBSS_NB1_CFG_MMRS + 0x10,
		.val = NB_THREADMAP_4,
	},
};

uint32_t j784s4_qos_count = sizeof(j784s4_qos_data) / sizeof(j784s4_qos_data[0]);
