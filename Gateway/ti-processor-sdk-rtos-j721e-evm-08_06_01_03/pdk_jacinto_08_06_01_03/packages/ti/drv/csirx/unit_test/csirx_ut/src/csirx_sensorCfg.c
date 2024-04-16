/*
 *  Copyright (c) Texas Instruments Incorporated 2019
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file csirx_sensorCfg.c
 *
 *  \brief Memory allocator API.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "csirx_test.h"
#include "imx390.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 * @{
 * Macros to control Fusion board and Camera Sensor version for the capture
 */
/**< Fusion Board Revision.
     '0': for Rev B or older boards.
     '1': for Rev C board. */
#define FUSION_BOARD_VER                     (1U)
/**< D3 IMX390 sensor version.
     '0': for D3_IMX390_CM module.
     '1': for D3_IMX390_RCM module. */
#define D3IMX390_MODULE_VER                  (0U)
/** @} */


#define SENSOR_CFG_SIZE  (3075)

/**
 * @{
 * I2C Addresses for serialisers/Sensors attached to the UB960
 */
#define UB960_SERIALISER_ADDR                (0x18)
#if (D3IMX390_MODULE_VER == 0)
#define D3IMX390_SENSOR_ADDR                 (0x21)
#endif
#if (D3IMX390_MODULE_VER == 1)
#define D3IMX390_SENSOR_ADDR                 (0x1A)
#endif
/** @} */

/**
 * @{
 * Generic Alias Addresses for serialisers attached to the UB960
 */
#define D3IMX390_UB960_PORT_0_SER_ADDR       (0x74U)
#define D3IMX390_UB960_PORT_1_SER_ADDR       (0x76U)
#define D3IMX390_UB960_PORT_2_SER_ADDR       (0x78U)
#define D3IMX390_UB960_PORT_3_SER_ADDR       (0x7AU)
/** @} */

/**
 * @{
 * Generic Alias Addresses for sensors attached to the UB960
 */
#define D3IMX390_UB960_PORT_0_SENSOR_ADDR    (0x40U)
#define D3IMX390_UB960_PORT_1_SENSOR_ADDR    (0x42U)
#define D3IMX390_UB960_PORT_2_SENSOR_ADDR    (0x44U)
#define D3IMX390_UB960_PORT_3_SENSOR_ADDR    (0x46U)
/** @} */

#define  D3IMX390_UB960_DATALANES_4           (0x0U)
#define  D3IMX390_UB960_DATALANES_3           (0x1U)
#define  D3IMX390_UB960_DATALANES_2           (0x2U)
#define  D3IMX390_UB960_DATALANES_1           (0x3U)
#define  D3IMX390_UB960_DATALANE_SHIFT        (0x4U)

/**< Number of channels */
#define APP_CAPT_CH_MAX                           ((uint32_t)4U)

/**< I2C transaction timeout */
#define APP_I2C_TRANSACTION_TIMEOUT               ((uint32_t)2000U)
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
int32_t App_sensorConfig(CsirxSensorCfg *senCfg);
extern void App_wait(uint32_t wait_in_ms);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
extern I2C_Handle gI2cHandle;
uint16_t gSensorCfg[SENSOR_CFG_SIZE][3] = IMX390_LINEAR_1920X1080_CONFIG;
uint16_t gUb960SensorCfg[][3] = {
    {0x01, 0x02, 0x100},
    {0x1f, 0x05, 0x1},

    {0xB0, 0x1C,0x1},
    {0xB1, 0x16,0x1},
    {0xB2, 0x00,0x1},
    {0xB1, 0x17,0x1},
    {0xB2, 0x00,0x1},
    {0xB1, 0x18,0x1},
    {0xB2, 0x00,0x1},
    {0xB1, 0x19,0x1},
    {0xB2, 0x00,0x1},
    {0xB0, 0x1C,0x1},
    {0xB1, 0x15,0x1},
    {0xB2, 0x0A,0x1},
    {0xB2, 0x00,0x10},

    {0x0D, 0x90, 0x1}, /*I/O to 3V3 - Options not valid with datashee*/
    {0x0C, 0x0F, 0x1}, /*Enable All ports*/

    /*Select Channel 0*/
    {0x4C, 0x01, 0x1},
    {0x58, 0x5E, 0x1},
    {0x72, 0x00, 0x1}, /*VC map*/

    /*Select Channel 1*/
    {0x4C, 0x12, 0x1},
    {0x58, 0x5D, 0x1},/*Enable Back channel, set to 50Mbs*/

    /*Select Channel 2*/
    {0x4C, 0x24, 0x1},
    {0x58, 0x5D, 0x1},/*Enable Back channel, set to 50Mbs*/

    /*Select Channel 3*/
    {0x4C, 0x38, 0x1},
    {0x58, 0x5D, 0x1},/*Enable Back channel, set to 50Mbs*/

    /*Select Channel 0*/
    {0x4C, 0x01, 0x1},
    {0xB0, 0x04, 0x1},
    {0xB1, 0x03, 0x1},
    {0xB2, 0x20, 0x1},
    {0xB1, 0x13, 0x1},
    {0xB2, 0x20, 0x1},
    {0xB0, 0x04, 0x1},
    {0xB1, 0x04, 0x1},
    {0xB2, 0x3F, 0x1},
    {0xB1, 0x14, 0x1},
    {0xB2, 0x3F, 0x1},
    {0x42, 0x71, 0x1}, /*Unknown*/
    {0x41, 0xF0, 0x1}, /*Unknown*/
    {0xB9, 0x18, 0x1},

    /*Select Channel 1*/
    {0x4C, 0x12, 0x1},
    {0xB0, 0x08, 0x1},
    {0xB1, 0x03, 0x1},
    {0xB2, 0x20, 0x1},
    {0xB1, 0x13, 0x1},
    {0xB2, 0x20, 0x1},
    {0xB0, 0x08, 0x1},
    {0xB1, 0x04, 0x1},
    {0xB2, 0x3F, 0x1},
    {0xB1, 0x14, 0x1},
    {0xB2, 0x3F, 0x1},
    {0xB0, 0x08, 0x1},
    {0x42, 0x71, 0x1}, /*Unknown*/
    {0x41, 0xF0, 0x1}, /*Unknown*/
    {0xB9, 0x18, 0x1},

    /*Select Channel 2*/
    {0x4C, 0x24, 0x1},
    {0xB0, 0x0C, 0x1},
    {0xB1, 0x03, 0x1},
    {0xB2, 0x20, 0x1},
    {0xB1, 0x13, 0x1},
    {0xB2, 0x20, 0x1},
    {0xB0, 0x0C, 0x1},
    {0xB1, 0x04, 0x1},
    {0xB2, 0x3F, 0x1},
    {0xB1, 0x14, 0x1},
    {0xB2, 0x3F, 0x1},
    {0x42, 0x71, 0x1},/*Unknown*/
    {0x41, 0xF0, 0x1},/*Unknown*/
    {0xB9, 0x18, 0x1},

    /*Select Channel 3*/
    {0x4C, 0x38, 0x1},
    {0xB0, 0x10, 0x1},
    {0xB1, 0x03, 0x1},
    {0xB2, 0x20, 0x1},
    {0xB1, 0x13, 0x1},
    {0xB2, 0x20, 0x1},
    {0xB0, 0x10, 0x1},
    {0xB1, 0x04, 0x1},
    {0xB2, 0x3F, 0x1},
    {0xB1, 0x14, 0x1},
    {0xB2, 0x3F, 0x1},
    {0x42, 0x71, 0x1},/*Unknown*/
    {0x41, 0xF0, 0x1},/*Unknown*/
    {0xB9, 0x18, 0x1},

    {0x32, 0x01, 0x1}, /*Enable TX port 0*/
    {0x20, 0x00, 0x1}, /*Forwarding and using CSIport 0 */

    /*Sets GPIOS*/
    {0x10, 0x83, 0x1},
    {0x11, 0xA3, 0x1},
    {0x12, 0xC3, 0x1},
    {0x13, 0xE3, 0x1},

    {0x4C, 0x01, 0x1}, /* 0x01 */
    {0x32, 0x01, 0x1}, /*Enable TX port 0*/
    {0x33, 0x02, 0x1}, /*Enable Continuous clock mode and CSI output*/
    {0xBC, 0x00, 0x1}, /*Unknown*/
    {0x5D, (UB960_SERIALISER_ADDR << 1U), 0x1}, /*Serializer I2C Address*/
    {0x65, (D3IMX390_UB960_PORT_0_SER_ADDR << 1U), 0x1},
    {0x5E, (D3IMX390_SENSOR_ADDR << 1U), 0x1}, /*Sensor I2C Address*/
    {0x66, (D3IMX390_UB960_PORT_0_SENSOR_ADDR << 1U), 0x1},
    {0x6D, 0x6C,0x1}, /*CSI Mode*/
    {0x72, 0x00,0x1}, /*VC Map - All to 0 */
    {0x7C, 0x20, 0x10}, /*Line Valid active high, Frame Valid active high*/
    {0xD5, 0xF3, 0x10}, /*Auto Attenuation*/
    {0xB0,0x1C, 0x1},
    {0xB1,0x15, 0x1},
    {0xB2,0x0A, 0x1},
    {0xB2,0x00, 0x1},

    {0x4C, 0x12, 0x1}, /* 0x12 */
    {0x32, 0x01, 0x1}, /*Enable TX port 0*/
    {0x33, 0x02, 0x1}, /*Enable Continuous clock mode and CSI output*/
    {0xBC, 0x00, 0x1}, /*Unknown*/
    {0x5D, (UB960_SERIALISER_ADDR << 1U), 0x1}, /*Serializer I2C Address*/
    {0x65, (D3IMX390_UB960_PORT_1_SER_ADDR << 1U), 0x1},
    {0x5E, (D3IMX390_SENSOR_ADDR << 1U), 0x1}, /*Sensor I2C Address*/
    {0x66, (D3IMX390_UB960_PORT_1_SENSOR_ADDR << 1U), 0x1},
    {0x6D, 0x6C,0x1}, /*CSI Mode*/
    {0x72, 0x55,0x1}, /*VC Map - All to 1 */
    {0x7C, 0x20, 0x10}, /*Line Valid active high, Frame Valid active high*/
    {0xD5, 0xF3, 0x10}, /*Auto Attenuation*/
    {0xB0,0x1C, 0x1},
    {0xB1,0x15, 0x1},
    {0xB2,0x0A, 0x1},
    {0xB2,0x00, 0x1},

    {0x4C, 0x24, 0x1}, /* 0x24 */
    {0x32, 0x01, 0x1}, /*Enable TX port 0*/
    {0x33, 0x02, 0x1}, /*Enable Continuous clock mode and CSI output*/
    {0xBC, 0x00, 0x1}, /*Unknown*/
    {0x5D, (UB960_SERIALISER_ADDR << 1U), 0x1}, /*Serializer I2C Address*/
    {0x65, (D3IMX390_UB960_PORT_2_SER_ADDR << 1U), 0x1},
    {0x5E, (D3IMX390_SENSOR_ADDR << 1U), 0x1}, /*Sensor I2C Address*/
    {0x66, (D3IMX390_UB960_PORT_2_SENSOR_ADDR << 1U), 0x1},
    {0x6D, 0x6C,0x1}, /*CSI Mode*/
    {0x72, 0xaa,0x1}, /*VC Map - All to 2 */
    {0x7C, 0x20, 0x10}, /*Line Valid active high, Frame Valid active high*/
    {0xD5, 0xF3, 0x10}, /*Auto Attenuation*/
    {0xB0,0x1C, 0x1},
    {0xB1,0x15, 0x1},
    {0xB2,0x0A, 0x1},
    {0xB2,0x00, 0x1},

    {0x4C, 0x38, 0x1}, /* 0x38 */
    {0x32, 0x01, 0x1}, /*Enable TX port 0*/
    {0x33, 0x02, 0x1}, /*Enable Continuous clock mode and CSI output*/
    {0xBC, 0x00, 0x1}, /*Unknown*/
    {0x5D, (UB960_SERIALISER_ADDR << 1U), 0x1}, /*Serializer I2C Address*/
    {0x65, (D3IMX390_UB960_PORT_3_SER_ADDR << 1U), 0x1},
    {0x5E, (D3IMX390_SENSOR_ADDR << 1U), 0x1}, /*Sensor I2C Address*/
    {0x66, (D3IMX390_UB960_PORT_3_SENSOR_ADDR << 1U), 0x1},
    {0x6D, 0x6C,0x1}, /*CSI Mode*/
    {0x72, 0xFF,0x1}, /*VC Map - All to 3 */
    {0x7C, 0x20, 0x10}, /*Line Valid active high, Frame Valid active high*/
    {0xD5, 0xF3, 0x10}, /*Auto Attenuation*/
    {0xB0,0x1C, 0x1},
    {0xB1,0x15, 0x1},
    {0xB2,0x0A, 0x1},
    {0xB2,0x00, 0x100},
};

uint16_t gUb953SensorCfg[][3] = {
    {0x01, 0x01, 0x80},
    {0x02, 0x72, 0x10},

#if (FUSION_BOARD_VER == 0)
    {0x06, 0x21, 0x1F},
#elif (FUSION_BOARD_VER == 1)
    {0x06, 0x41, 0x1F},
#else
/* Unsupported version */
#endif

#if (D3IMX390_MODULE_VER == 0)
    {0x07, 0x28, 0x1F},
    {0x0D, 0x01, 0x10},
#elif (D3IMX390_MODULE_VER == 1)
    {0x07, 0x15, 0x80},
    {0x0D, 0x03, 0x10},
#else
/* Unsupported version */
#endif
    {0x0E, 0xF0, 0x10},
    {0xB0, 0x04, 0x10},
    {0xB1, 0x08, 0x10},
    {0xB2, 0x07, 0x80},
};

uint32_t gUb953I2CAddr[APP_CAPT_CH_MAX] =
{
    D3IMX390_UB960_PORT_0_SER_ADDR,
    D3IMX390_UB960_PORT_1_SER_ADDR,
    D3IMX390_UB960_PORT_2_SER_ADDR,
    D3IMX390_UB960_PORT_3_SER_ADDR
};

uint32_t gSensorI2CAddr[APP_CAPT_CH_MAX] =
{
    D3IMX390_UB960_PORT_0_SENSOR_ADDR,
    D3IMX390_UB960_PORT_1_SENSOR_ADDR,
    D3IMX390_UB960_PORT_2_SENSOR_ADDR,
    D3IMX390_UB960_PORT_3_SENSOR_ADDR
};

/** \brief Log enable for CSIRX Unit Test  application */
extern uint32_t gAppTrace;
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t App_sensorConfig(CsirxSensorCfg *senCfg)
{
    int32_t retVal = FVID2_SOK;
    int32_t status;
    uint32_t cnt, sensorIdx;
    uint8_t i2cInst = 0U, i2cAddr = 0U, regAddr8, regVal;
    uint16_t regAddr;
    Board_STATUS ret = BOARD_SOK;

    Board_fpdU960GetI2CAddr(&i2cInst, &i2cAddr, BOARD_CSI_INST_0);
    for (cnt = 0;
         cnt < sizeof(gUb960SensorCfg)/(sizeof(gUb960SensorCfg[0]));
         cnt ++)
    {
        regAddr8 = gUb960SensorCfg[cnt][0] & 0xFF;
        regVal = gUb960SensorCfg[cnt][1] & 0xFF;
        status = Board_i2c8BitRegWr(gI2cHandle, i2cAddr, regAddr8, &regVal, 1,
                                    APP_I2C_TRANSACTION_TIMEOUT);
        if (0 != status)
        {
            GT_2trace(gAppTrace,
                      GT_INFO,
                      APP_NAME ": Failed to Set UB960 register %x: Value:%x\n",
                      gUb960SensorCfg[cnt][0],
                      gUb960SensorCfg[cnt][1]);
            break;
        }
        else
        {
            App_wait(gUb960SensorCfg[cnt][2]);
        }
    }

    for (sensorIdx = 0U ; sensorIdx < senCfg->chNum ; sensorIdx++)
    {
        if (0 == status)
        {
            /* UB960 Port configuration */
            i2cAddr = gUb953I2CAddr[sensorIdx];
            for (cnt = 0;
                 cnt < sizeof(gUb953SensorCfg)/(sizeof(gUb953SensorCfg[0]));
                 cnt ++)
            {
                regAddr8 = gUb953SensorCfg[cnt][0] & 0xFF;
                regVal = gUb953SensorCfg[cnt][1] & 0xFF;
                status = Board_i2c8BitRegWr(gI2cHandle,
                                            i2cAddr,
                                            regAddr8,
                                            &regVal,
                                            1,
                                            APP_I2C_TRANSACTION_TIMEOUT);
                if (0 != status)
                {
                    GT_2trace(gAppTrace, GT_INFO,
                              APP_NAME
                              ": Failed to Set UB953 register %x: Value:%x\n",
                              gUb953SensorCfg[cnt][0],
                              gUb953SensorCfg[cnt][1]);
                    break;
                }
                else
                {
                    App_wait(gUb953SensorCfg[cnt][2]);
                }
            }
        }
        else
        {
            break;
        }
    }

    for (sensorIdx = 0U ; sensorIdx < senCfg->chNum ; sensorIdx++)
    {
        if (0 == status)
        {
            /* Sensor 0 configuration */
            i2cAddr = gSensorI2CAddr[sensorIdx];
            for (cnt = 0; cnt < SENSOR_CFG_SIZE; cnt ++)
            {
                regAddr = gSensorCfg[cnt][0];
                regVal = gSensorCfg[cnt][1];

                status = Board_i2c16BitRegWr(gI2cHandle,
                                             i2cAddr,
                                             regAddr,
                                             &regVal,
                                             1,
                                             BOARD_I2C_REG_ADDR_MSB_FIRST,
                                             APP_I2C_TRANSACTION_TIMEOUT);
                if (0 != status)
                {
                    GT_2trace(gAppTrace, GT_INFO,
                              APP_NAME
                              ": Failed to Set Sensor register %x: Value:0x%x\n",
                              regAddr,
                              regVal);
                    break;
                }
            }
        }
        else
        {
            break;
        }
    }

    if (0 == status)
    {
        Board_fpdU960GetI2CAddr(&i2cInst, &i2cAddr, BOARD_CSI_INST_0);
        regAddr8 = 0x33;
        regVal = 0x3;
        if (senCfg->numDataLanes == 4)
        {
            regVal |= (D3IMX390_UB960_DATALANES_4 << D3IMX390_UB960_DATALANE_SHIFT);
        }
        else if (senCfg->numDataLanes == 3)
        {
            regVal |= (D3IMX390_UB960_DATALANES_3 << D3IMX390_UB960_DATALANE_SHIFT);
        }
        else if (senCfg->numDataLanes == 2)
        {
            regVal |= (D3IMX390_UB960_DATALANES_2 << D3IMX390_UB960_DATALANE_SHIFT);
        }
        else if (senCfg->numDataLanes == 1)
        {
            regVal |= (D3IMX390_UB960_DATALANES_1 << D3IMX390_UB960_DATALANE_SHIFT);
        }
        status = Board_i2c8BitRegWr(gI2cHandle,
                                    i2cAddr,
                                    regAddr8,
                                    &regVal,
                                    1,
                                    APP_I2C_TRANSACTION_TIMEOUT);
        if (0 != status)
        {
            GT_0trace(gAppTrace, GT_INFO,
                      APP_NAME ": Failed to enable CSI port\n");
        }

        if (ret != BOARD_SOK)
        {
            GT_0trace(gAppTrace, GT_INFO,
                      APP_NAME ": ERROR in Sensor Configuration!!!\r\n");
        }

    }
    else
    {
        GT_0trace(gAppTrace, GT_INFO,
                  APP_NAME ": Sensor Configuration Failed!!!\r\n");
    }

    return (retVal);
}
