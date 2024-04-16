/*
 * Copyright (c) 2020, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <ti/drv/spi/SPI.h>
#include <ti/drv/spi/soc/SPI_soc.h>
#include <ti/board/src/flash/nor/nor.h>
#if defined (j7200_evm) || defined (am64x_evm) || defined(j721s2_evm) || defined(j784s4_evm)
#include <ti/board/src/flash/nor/ospi/nor_xspi.h>
#else
#include <ti/board/src/flash/nor/ospi/nor_ospi.h>
#endif
#include <ti/board/src/flash/nor/ospi/nor_spi_patterns.h>
#include <ti/board/src/flash/nor/ospi/nor_spi_phy_tune.h>
/* UART Header files */
#include <ti/drv/uart/UART.h>
#include <ti/drv/uart/UART_stdio.h>

extern void UART_printf(const char *pcString, ...);

#undef NOR_SPI_TUNE_DEBUG
#undef NOR_SPI_TUNE_PROFILE
#undef NOR_DISABLE_TXDLL_WINDOW

#ifdef NOR_SPI_TUNE_DEBUG
#define NOR_log UART_printf
uint32_t norSpiTuneCnt = 0;
#endif

#ifdef NOR_SPI_TUNE_PROFILE
#define NOR_log UART_printf
#endif

static NOR_PhyConfig ddrTuningPoint = {0, };
static NOR_PhyConfig sdrTuningPoint = {0, };

static void NOR_spiRdDelayConfig(OSPI_Handle handle, uint32_t rdDelay)
{
    uint32_t data;

    data = rdDelay;
    OSPI_control(handle, OSPI_V0_CMD_CFG_RD_DELAY, (void *)(&data));
}

static void NOR_spiTxRxDllConfig(OSPI_Handle handle, uint32_t txDLL, uint32_t rxDLL)
{
    uint32_t data[3];

    data[0] = TRUE;
    data[1] = txDLL;
    data[2] = rxDLL;
    OSPI_control(handle, OSPI_V0_CMD_CFG_PHY, (void *)data);
}

static void NOR_spiPhyConfig(OSPI_Handle handle, NOR_PhyConfig phyConfig)
{
    NOR_spiRdDelayConfig(handle, phyConfig.rdDelay);
    NOR_spiTxRxDllConfig(handle, phyConfig.txDLL, phyConfig.rxDLL);
}

static uint32_t rdBuf[NOR_ATTACK_VECTOR_SIZE/sizeof(uint32_t)];
static NOR_STATUS NOR_spiPhyRdAttack(uintptr_t flashVectorAddr)
{
    NOR_STATUS        status = NOR_PASS;
    uint32_t          i;
    volatile uint8_t *pByte = (volatile uint8_t *)rdBuf;

    for (i = 0; i < NOR_ATTACK_VECTOR_SIZE/sizeof(uint32_t); i++)
    {
        rdBuf[i] = CSL_REG32_RD(flashVectorAddr + i * 4);
    }

    for (i = 0; i < NOR_ATTACK_VECTOR_SIZE; i++)
    {
        if (pByte[i] != nor_attack_vector[i])
        {
            status = NOR_FAIL;
            break;
        }
    }
    return (status);
}

/*
 * Searches txDLL down from start until the tuning basis passes.
 * Does not look at the next rdDelay setting.  Returns txDLL=128 if fail.
 */
NOR_PhyConfig NOR_spiPhyFindTxHigh(OSPI_Handle handle, NOR_PhyConfig start, uint32_t offset)
{
    OSPI_v0_HwAttrs const *hwAttrs= (OSPI_v0_HwAttrs const *)handle->hwAttrs;
    NOR_STATUS             status;

    NOR_spiPhyConfig(handle, start);
    status = NOR_spiPhyRdAttack(hwAttrs->dataAddr + offset);
#ifdef NOR_SPI_TUNE_DEBUG
    norSpiTuneCnt++;
#endif
    while(status == NOR_FAIL)
    {
        start.txDLL--;
        if(start.txDLL < 48U)
        {
            start.txDLL = 128U;
            break;
        }
        NOR_spiPhyConfig(handle, start);
        status = NOR_spiPhyRdAttack(hwAttrs->dataAddr + offset);
#ifdef NOR_SPI_TUNE_DEBUG
        norSpiTuneCnt++;
#endif
    }
    return start;
}

/*
 * Searches txDLL up from start until the tuning basis passes.
 * Does not look at the next rdDelay setting.  Returns txDLL=128 if fail.
 */
NOR_PhyConfig NOR_spiPhyFindTxLow(OSPI_Handle handle, NOR_PhyConfig start, uint32_t offset)
{
    OSPI_v0_HwAttrs const *hwAttrs= (OSPI_v0_HwAttrs const *)handle->hwAttrs;
    NOR_STATUS             status;


    NOR_spiPhyConfig(handle, start);
    status = NOR_spiPhyRdAttack(hwAttrs->dataAddr + (uintptr_t)offset);
#ifdef NOR_SPI_TUNE_DEBUG
    norSpiTuneCnt++;
#endif
    while(status == NOR_FAIL)
    {
        start.txDLL++;
        if (start.txDLL > 32U)
        {
            start.txDLL = 128U;
            break;
        }
        NOR_spiPhyConfig(handle, start);
        status = NOR_spiPhyRdAttack(hwAttrs->dataAddr + offset);
#ifdef NOR_SPI_TUNE_DEBUG
        norSpiTuneCnt++;
#endif
    }
    return start;
}

/*
 * Searches rxDLL down from start until the tuning basis passes.
 * Does not look at the next rdDelay setting.  Returns rxDLL=128 if fail.
 */
NOR_PhyConfig NOR_spiPhyFindRxHigh(OSPI_Handle handle, NOR_PhyConfig start, uint32_t offset)
{
    OSPI_v0_HwAttrs const *hwAttrs= (OSPI_v0_HwAttrs const *)handle->hwAttrs;
    NOR_STATUS             status;

    NOR_spiPhyConfig(handle, start);
    status = NOR_spiPhyRdAttack(hwAttrs->dataAddr + offset);
#ifdef NOR_SPI_TUNE_DEBUG
    norSpiTuneCnt++;
#endif
    while(status == NOR_FAIL)
    {
        start.rxDLL--;
        if(start.rxDLL < 25U)
        {
            start.rxDLL = 128U;
            break;
        }
        NOR_spiPhyConfig(handle, start);
        status = NOR_spiPhyRdAttack(hwAttrs->dataAddr + offset);
#ifdef NOR_SPI_TUNE_DEBUG
        norSpiTuneCnt++;
#endif
    }
    return start;
}

/*
 * Searches rxDLL up from start until the tuning basis passes.
 * Does not look at the next rdDelay setting. Returns rxDLL=128 if fail.
 */
NOR_PhyConfig NOR_spiPhyFindRxLow(OSPI_Handle handle, NOR_PhyConfig start, uint32_t offset)
{
    OSPI_v0_HwAttrs const *hwAttrs= (OSPI_v0_HwAttrs const *)handle->hwAttrs;
    NOR_STATUS             status;

    NOR_spiPhyConfig(handle, start);
    status = NOR_spiPhyRdAttack(hwAttrs->dataAddr + offset);
#ifdef NOR_SPI_TUNE_DEBUG
    norSpiTuneCnt++;
#endif
    while(status == NOR_FAIL)
    {
        start.rxDLL++;
        if(start.rxDLL > 10U)
        {
            start.rxDLL = 128U;
            break;
        }
        NOR_spiPhyConfig(handle, start);
        status = NOR_spiPhyRdAttack(hwAttrs->dataAddr + offset);
#ifdef NOR_SPI_TUNE_DEBUG
        norSpiTuneCnt++;
#endif
    }
    return start;
}

double NOR_spiPhyAvgVtmTemp(double vtm125){
    double   avg = 0;
    double   m = 0;
    double   b = 0;
    uint32_t temp;
    uint32_t j;
    uint32_t statReg; /* VTM temperature sensor status register addr */
    uint32_t ctrlReg; /* VTM temperature sensor control register addr */

#if defined (SOC_J721E) || defined (SOC_J7200) || defined(SOC_J721S2) || defined(SOC_J784S4)
    statReg = CSL_WKUP_VTM0_MMR_VBUSP_CFG1_BASE + 0x308U;
    ctrlReg = CSL_WKUP_VTM0_MMR_VBUSP_CFG2_BASE + 0x300U;
#elif defined (SOC_AM65XX)
    statReg = CSL_WKUP_VTM0_CFG0_BASE + 0x308U;
    ctrlReg = CSL_WKUP_VTM0_CFG1_BASE + 0x300U;
#else
    statReg = CSL_VTM0_MMR_VBUSP_CFG1_BASE + 0x308U;
    ctrlReg = CSL_VTM0_MMR_VBUSP_CFG2_BASE + 0x300U;
#endif
    /* Take the average VTM value */
    for (j = 0; j < 5U; j++)
    {
        uintptr_t pCtrl = (uintptr_t)(ctrlReg + (j * 0x20U));
        uintptr_t pStat = (uintptr_t)(statReg + (j * 0x20U));

        /* Setting sensor to continous readout mode. */
        CSL_REG32_WR(pCtrl, (CSL_REG32_RD(pCtrl) & ~0x10U) | (1U << 4U));
        CSL_REG32_WR(pCtrl, (CSL_REG32_RD(pCtrl) & ~0x10U) | (1U << 4U));

        /* Read from pStat register to get temp */
        temp = CSL_REG32_RD(pStat) & 0x3FFU;

        /* Accumlate a number to average */
        avg += temp;
    }
    avg=avg/5U;
    /* Convert to a temperature */
    m = 160U/(vtm125-43U);
    b = (125U/m)-vtm125;
    avg = m*(avg+b);

    return avg;
}

/* Fast tuning in DDR mode (DQS enabled) */
NOR_STATUS Nor_spiPhyDdrTune(OSPI_Handle handle, uint32_t offset)
{
    NOR_STATUS             status;
    OSPI_v0_HwAttrs const *hwAttrs= (OSPI_v0_HwAttrs const *)handle->hwAttrs;
    NOR_PhyConfig          searchPoint;
    NOR_PhyConfig          bottomLeft;
    NOR_PhyConfig          topRight;
    NOR_PhyConfig          gapLow;
    NOR_PhyConfig          gapHigh;
    NOR_PhyConfig          rxLow, rxHigh, txLow, txHigh, temp, left, right;
    int32_t                rdDelay;
    float                  temperature = 0;
    float                  length1,length2;

    /*
     * Bottom left corner is present in initial rdDelay value and search from there.
     * Can be adjusted to save time.
     */
    rdDelay = 1U;

    /*
     * Finding RxDLL fails at some of the TxDLL values based on the HW platform.
     * A window of TxDLL values is used to find the RxDLL without errors.
     * This can increase the number of CPU cycles taken for the PHY tuning
     * in the cases where more TxDLL values need to be parsed to find a stable RxDLL.
     *
     * Update NOR_SPI_PHY_TXDLL_LOW_WINDOW_START based on the TxDLL value where
     * stable RxDLL can be found consistently for a given platform and
     * define the macro NOR_DISABLE_TXDLL_WINDOW after fixing TxDLL value
     * to reduce the time taken for PHY tuning.
     */
#if !defined(NOR_DISABLE_TXDLL_WINDOW)
    /* Look for rxDLL boundaries at a txDLL Window to find rxDLL Min */
    searchPoint.txDLL = NOR_SPI_PHY_TXDLL_LOW_WINDOW_START;
    while(searchPoint.txDLL <= NOR_SPI_PHY_TXDLL_LOW_WINDOW_END)
    {
        searchPoint.rdDelay = rdDelay;
        searchPoint.rxDLL   = 0;
        rxLow = NOR_spiPhyFindRxLow(handle, searchPoint, offset);
        while(rxLow.rxDLL == 128U)
        {
            searchPoint.rdDelay++;
            if(searchPoint.rdDelay > 4U)
            {
                if(searchPoint.txDLL >= NOR_SPI_PHY_TXDLL_LOW_WINDOW_END)
                {
#ifdef NOR_SPI_TUNE_DEBUG
                    NOR_log("Unable to find RX Min\n");
#endif
                    return NOR_FAIL;
                }
                else
                {
                    break;
                }
            }
            rxLow = NOR_spiPhyFindRxLow(handle, searchPoint, offset);
        }

        if(rxLow.rxDLL != 128U)
        {
            break;
        }

        searchPoint.txDLL++;
    }
#else
    /* Look for rxDLL boundaries at txDLL = 16 to find rxDLL Min */
    searchPoint.rdDelay = rdDelay;
    searchPoint.txDLL = NOR_SPI_PHY_TXDLL_LOW_WINDOW_START;
    searchPoint.rxDLL = 0U;
    rxLow = NOR_spiPhyFindRxLow(handle, searchPoint, offset);
    while(rxLow.rxDLL == 128U)
    {
        searchPoint.rdDelay++;
        if(searchPoint.rdDelay > 4U)
        {
#ifdef NOR_SPI_TUNE_DEBUG
            NOR_log("Unable to find RX Min\n");
#endif
            return NOR_FAIL;
        }
        rxLow = NOR_spiPhyFindRxLow(handle, searchPoint, offset);
    }
#endif  /* #if !defined(NOR_DISABLE_TXDLL_WINDOW) */

    /* Find rxDLL Max at a txDLL */
    searchPoint.rxDLL = 63U;
    rxHigh = NOR_spiPhyFindRxHigh(handle, searchPoint, offset);
    while(rxHigh.rxDLL == 128U)
    {
        searchPoint.rdDelay++;
        if(searchPoint.rdDelay > 4U)
        {
#ifdef NOR_SPI_TUNE_DEBUG
            NOR_log("Unable to find RX Min\n");
#endif
            return NOR_FAIL;
        }
        rxHigh = NOR_spiPhyFindRxHigh(handle, searchPoint, offset);
    }

    /*
     * Check a different point if the rxLow and rxHigh are on the same rdDelay.
     * This avoids mistaking the metastability gap for an rxDLL boundary
     */
    if (rxLow.rdDelay == rxHigh.rdDelay)
    {
#ifdef NOR_SPI_TUNE_DEBUG
        NOR_log("rxLow and rxHigh are on the same rdDelay\n");
#endif

    /*
     * Finding RxDLL fails at some of the TxDLL values based on the HW platform.
     * A window of TxDLL values is used to find the RxDLL without errors.
     * This can increase the number of CPU cycles taken for the PHY tuning
     * in the cases where more TxDLL values need to be parsed to find a stable RxDLL.
     *
     * Update NOR_SPI_PHY_TXDLL_HIGH_WINDOW_START based on the TxDLL value where
     * stable RxDLL can be found consistently for a given platform and
     * define the macro NOR_DISABLE_TXDLL_WINDOW after fixing TxDLL value
     * to reduce the time taken for PHY tuning.
     */
#if !defined(NOR_DISABLE_TXDLL_WINDOW)
        /* Look for rxDLL boundaries at a txDLL Window */
        searchPoint.txDLL = NOR_SPI_PHY_TXDLL_HIGH_WINDOW_START;

        /* Find rxDLL Min */
        while(searchPoint.txDLL >= NOR_SPI_PHY_TXDLL_HIGH_WINDOW_END)
        {
            searchPoint.rdDelay = rdDelay;
            searchPoint.rxDLL   = 0;
            temp = NOR_spiPhyFindRxLow(handle, searchPoint, offset);
            while(temp.rxDLL == 128U)
            {
                searchPoint.rdDelay++;
                if(searchPoint.rdDelay > 4U)
                {
                    if(searchPoint.txDLL <= NOR_SPI_PHY_TXDLL_HIGH_WINDOW_END)
                    {
#ifdef NOR_SPI_TUNE_DEBUG
                        NOR_log("Unable to find RX Min\n");
#endif
                        return NOR_FAIL;
                    }
                    else
                    {
                        break;
                    }
                }
                temp = NOR_spiPhyFindRxLow(handle, searchPoint, offset);
            }

            if(temp.rxDLL != 128U)
            {
                break;
            }

            searchPoint.txDLL--;
        }
#else
        /* Look for rxDLL boundaries at txDLL=48 */
        searchPoint.rdDelay = rdDelay;
        searchPoint.txDLL = NOR_SPI_PHY_TXDLL_HIGH_WINDOW_START;
        searchPoint.rxDLL = 0;

        /* Find rxDLL Min */
        temp = NOR_spiPhyFindRxLow(handle, searchPoint, offset);
        while(temp.rxDLL == 128U)
        {
            searchPoint.rdDelay++;
            if(searchPoint.rdDelay > 4U)
            {
#ifdef NOR_SPI_TUNE_DEBUG
                NOR_log("Unable to find RX Min\n");
#endif
                return NOR_FAIL;
            }
            temp = NOR_spiPhyFindRxLow(handle, searchPoint, offset);
        }
#endif

        if(temp.rxDLL<rxLow.rxDLL){
            rxLow = temp;
        }

        /* Find rxDLL Max */
        searchPoint.rxDLL = 63U;
        temp = NOR_spiPhyFindRxHigh(handle, searchPoint, offset);
        while(temp.rxDLL == 128U)
        {
            searchPoint.rdDelay++;
            if(searchPoint.rdDelay > 4U)
            {
#ifdef NOR_SPI_TUNE_DEBUG
                NOR_log("Unable to find RX Max\n");
#endif
                return NOR_FAIL;
            }
            temp = NOR_spiPhyFindRxHigh(handle, searchPoint, offset);
        }
        if(temp.rxDLL > rxHigh.rxDLL)
        {
            rxHigh = temp;
        }
    }

    /*
     * Look for txDLL boundaries at 1/4 of rxDLL window
     * Find txDLL Min
     */
    searchPoint.rdDelay = rdDelay;
    searchPoint.rxDLL = (rxHigh.rxDLL+rxLow.rxDLL)/4U;
    searchPoint.txDLL = 0U;
    txLow = NOR_spiPhyFindTxLow(handle,searchPoint,offset);
    while(txLow.txDLL==128U){
        searchPoint.rdDelay++;
        txLow = NOR_spiPhyFindTxLow(handle,searchPoint,offset);
        if(searchPoint.rdDelay>4U){
#ifdef NOR_SPI_TUNE_DEBUG
            NOR_log("Unable to find TX Min\n");
#endif
            return NOR_FAIL;
        }
    }

    /* Find txDLL Max */
    searchPoint.txDLL = 63U;
    txHigh = NOR_spiPhyFindTxHigh(handle,searchPoint,offset);
    while(txHigh.txDLL==128U){
        searchPoint.rdDelay++;
        txHigh = NOR_spiPhyFindTxHigh(handle,searchPoint,offset);
        if(searchPoint.rdDelay>4U){
#ifdef NOR_SPI_TUNE_DEBUG
            NOR_log("Unable to find TX Max\n");
#endif
            return NOR_FAIL;
        }
    }

    /*
     * Check a different point if the txLow and txHigh are on the same rdDelay.
     * This avoids mistaking the metastability gap for an rxDLL boundary
     */
    if(txLow.rdDelay==txHigh.rdDelay){
        /* Look for txDLL boundaries at 3/4 of rxDLL window
           Find txDLL Min */
        searchPoint.rdDelay = rdDelay;
        searchPoint.rxDLL = 3U*(rxHigh.rxDLL+rxLow.rxDLL)/4U;
        searchPoint.txDLL = 0U;
        temp = NOR_spiPhyFindTxLow(handle,searchPoint,offset);
        while(temp.txDLL==128U){
            searchPoint.rdDelay++;
            temp = NOR_spiPhyFindTxLow(handle,searchPoint,offset);
            if(searchPoint.rdDelay>4U){
#ifdef NOR_SPI_TUNE_DEBUG
                NOR_log("Unable to find TX Min\n");
#endif
                return NOR_FAIL;
            }
        }
        if(temp.txDLL<txLow.txDLL){
            txLow = temp;
        }

        /* Find txDLL Max */
        searchPoint.txDLL = 63U;
        temp = NOR_spiPhyFindTxHigh(handle,searchPoint,offset);
        while(temp.txDLL==128U){
            searchPoint.rdDelay++;
            temp = NOR_spiPhyFindTxHigh(handle,searchPoint,offset);
            if(searchPoint.rdDelay>4U){
#ifdef NOR_SPI_TUNE_DEBUG
                NOR_log("Unable to find TX Max\n");
#endif
                return NOR_FAIL;
            }
        }
        if(temp.txDLL>txHigh.txDLL){
            txHigh = temp;
        }
    }

    /*
     * Set bottom left and top right right corners.  These are theoretical corners. They may not actually be "good" points.
     * But the longest diagonal of the shmoo will be between these corners.
     */
    /* Bottom Left */
    bottomLeft.txDLL = txLow.txDLL;
    bottomLeft.rxDLL = rxLow.rxDLL;
    if(txLow.rdDelay<=rxLow.rdDelay){
        bottomLeft.rdDelay = txLow.rdDelay;
    }else bottomLeft.rdDelay = rxLow.rdDelay;
    temp = bottomLeft;
    temp.txDLL += 4U;
    temp.rxDLL += 4U;
    NOR_spiPhyConfig(handle, temp);
    status = NOR_spiPhyRdAttack(hwAttrs->dataAddr + offset);
#ifdef NOR_SPI_TUNE_DEBUG
    norSpiTuneCnt++;
#endif
    if(status == NOR_FAIL){
        temp.rdDelay--;
        NOR_spiPhyConfig(handle, temp);
        status = NOR_spiPhyRdAttack(hwAttrs->dataAddr + offset);
#ifdef NOR_SPI_TUNE_DEBUG
        norSpiTuneCnt++;
#endif
    }
    if (status == NOR_PASS){
        bottomLeft.rdDelay = temp.rdDelay;
    }

    /* Top Right */
    topRight.txDLL = txHigh.txDLL;
    topRight.rxDLL = rxHigh.rxDLL;
    if(txHigh.rdDelay>=rxHigh.rdDelay){
        topRight.rdDelay = txHigh.rdDelay;
    }else topRight.rdDelay = rxHigh.rdDelay;
    temp = topRight;
    temp.txDLL -= 4U;
    temp.rxDLL -= 4U;
    NOR_spiPhyConfig(handle, temp);
    status = NOR_spiPhyRdAttack(hwAttrs->dataAddr + offset);
#ifdef NOR_SPI_TUNE_DEBUG
    norSpiTuneCnt++;
#endif
    if(status == NOR_FAIL){
        temp.rdDelay++;
        NOR_spiPhyConfig(handle, temp);
        status = NOR_spiPhyRdAttack(hwAttrs->dataAddr + offset);
#ifdef NOR_SPI_TUNE_DEBUG
        norSpiTuneCnt++;
#endif
    }
    if(status == NOR_PASS){
        topRight.rdDelay = temp.rdDelay;
    }

	left  = bottomLeft;
	right = topRight;

	searchPoint.txDLL = left.txDLL + ((right.txDLL - left.txDLL) / 2);
	searchPoint.rxDLL = left.rxDLL + ((right.rxDLL - left.rxDLL) / 2);
	searchPoint.rdDelay = left.rdDelay;

    do{
        NOR_spiPhyConfig(handle,searchPoint);
        status = NOR_spiPhyRdAttack(hwAttrs->dataAddr + offset);
        if(status == NOR_FAIL){
            /*
             * Since we couldn't find the pattern, we need to go the
             * the upper half.
             */
            right.txDLL = searchPoint.txDLL;
            right.rxDLL = searchPoint.rxDLL;
            
            searchPoint.txDLL = left.txDLL + ((searchPoint.txDLL - left.txDLL)/2);
            searchPoint.rxDLL = left.rxDLL + ((searchPoint.rxDLL - left.rxDLL)/2);
        }else{
            /*
             * Since we found the pattern, we need to go to the
             * lower half.
             */
            left.txDLL = searchPoint.txDLL;
            left.rxDLL = searchPoint.rxDLL;
            
            searchPoint.txDLL = searchPoint.txDLL + ((right.txDLL - searchPoint.txDLL)/2);
            searchPoint.rxDLL = searchPoint.rxDLL + ((right.rxDLL - searchPoint.rxDLL)/2);
        }
#ifdef NOR_SPI_TUNE_DEBUG
        norSpiTuneCnt++;
#endif
    /* Break the loop if the window has closed. */
    } while ((right.txDLL - left.txDLL >= 2) && (right.rxDLL - left.rxDLL >= 2));
    gapLow = searchPoint;

    /* If there's only one segment, put tuning point in the middle and adjust for temperature */
    if(bottomLeft.rdDelay==topRight.rdDelay){
        //The "true" top right corner was too small to find, so the start of the metastability gap is a good approximation
        topRight = gapLow;
        searchPoint.rdDelay = bottomLeft.rdDelay;
        searchPoint.txDLL = (bottomLeft.txDLL+topRight.txDLL)/2U;
        searchPoint.rxDLL = (bottomLeft.rxDLL+topRight.rxDLL)/2U;
#ifdef NOR_SPI_TUNE_DEBUG
        NOR_log("Only one passing window found, from txDLL,rxDLL of %d,%d to %d,%d, and a rdDelay of %d\n",bottomLeft.txDLL,bottomLeft.rxDLL,topRight.txDLL,topRight.rxDLL,topRight.rdDelay);
#endif
        temperature = NOR_spiPhyAvgVtmTemp(NOR_SPI_PHY_VTM_TARGET);
        searchPoint.txDLL+= (topRight.txDLL-bottomLeft.txDLL)*(0.5*(temperature-42.5)/165U);
        searchPoint.rxDLL+= (topRight.rxDLL-bottomLeft.rxDLL)*(0.5*(temperature-42.5)/165U);
    }else{
        /* If there are two segments, find the start and end of the second one */

        left  = bottomLeft;
        right = topRight;

        searchPoint.txDLL = left.txDLL + ((right.txDLL - left.txDLL) / 2);
        searchPoint.rxDLL = left.rxDLL + ((right.rxDLL - left.rxDLL) / 2);
        searchPoint.rdDelay = right.rdDelay;

        do{
            NOR_spiPhyConfig(handle,searchPoint);
            status = NOR_spiPhyRdAttack(hwAttrs->dataAddr + offset);
            if(status == NOR_FAIL){
                /*
			     * Since we couldn't find the pattern, we need to go the
			     * the upper half.
			     */
                left.txDLL = searchPoint.txDLL;
                left.rxDLL = searchPoint.rxDLL;
                
                searchPoint.txDLL = searchPoint.txDLL + ((right.txDLL - searchPoint.txDLL)/2);
                searchPoint.rxDLL = searchPoint.rxDLL + ((right.rxDLL - searchPoint.rxDLL)/2);
            }else{
                /*
			     * Since we found the pattern, we need to go to the
			     * lower half.
			     */
                right.txDLL = searchPoint.txDLL;
                right.rxDLL = searchPoint.rxDLL;
                
                searchPoint.txDLL = left.txDLL + ((searchPoint.txDLL - left.txDLL)/2);
                searchPoint.rxDLL = left.rxDLL + ((searchPoint.rxDLL - left.rxDLL)/2);
            }
#ifdef NOR_SPI_TUNE_DEBUG
            norSpiTuneCnt++;
#endif
        /* Break the loop if the window has closed. */
        } while ((right.txDLL - left.txDLL >= 2) && (right.rxDLL - left.rxDLL >= 2));

        gapHigh = searchPoint;
        /* Place the final tuning point of the PHY in the corner furthest from the gap */
        length1 = abs(gapLow.txDLL-bottomLeft.txDLL) + abs(gapLow.rxDLL-bottomLeft.rxDLL);
        length2 = abs(gapHigh.txDLL-topRight.txDLL) + abs(gapHigh.rxDLL-topRight.rxDLL);
        if(length2>length1){
            searchPoint = topRight;
            searchPoint.txDLL-=16U;
            searchPoint.rxDLL-= 16U * ((float)topRight.rxDLL-(float)bottomLeft.rxDLL)/((float)topRight.txDLL-(float)bottomLeft.txDLL);
        }else{
            searchPoint = bottomLeft;
            searchPoint.txDLL+=16U;
            searchPoint.rxDLL+=16U * ((float)topRight.rxDLL-(float)bottomLeft.rxDLL)/((float)topRight.txDLL-(float)bottomLeft.txDLL);
        }
#ifdef NOR_SPI_TUNE_DEBUG
        NOR_log("Bottom left found at txDLL,rxDLL of %d,%d to %d,%d, and a rdDelay of %d\n",bottomLeft.txDLL,bottomLeft.rxDLL,gapLow.txDLL,gapLow.rxDLL,gapLow.rdDelay);
        NOR_log("Top Right found at txDLL,rxDLL of %d,%d to %d,%d, and a rdDelay of %d\n",gapHigh.txDLL,gapHigh.rxDLL,topRight.txDLL,topRight.rxDLL,gapHigh.rdDelay);
#endif
    }
#ifdef NOR_SPI_TUNE_DEBUG
    NOR_log("Tuning was complete in %d steps\n", norSpiTuneCnt);
    NOR_log("Tuning PHY to txDLL,rxDLL of %d,%d and rdDelay of %d\n",searchPoint.txDLL,searchPoint.rxDLL,searchPoint.rdDelay);
#endif
    NOR_spiPhyConfig(handle,searchPoint);

    /* Save SDR tuning config point data */
    ddrTuningPoint = searchPoint;

    return NOR_PASS;
}

/* Returns the first rxDLL value which passes the tuning basis test, searching up from given txDLL,rxDLL */
static int32_t NOR_spiPhyFindRxStart(OSPI_Handle handle, int32_t txDLL, int32_t rxDLL, uint32_t offset)
{
    OSPI_v0_HwAttrs const        *hwAttrs= (OSPI_v0_HwAttrs const *)handle->hwAttrs;
    const CSL_ospi_flash_cfgRegs *pRegs = (const CSL_ospi_flash_cfgRegs *)(hwAttrs->baseAddr);
    NOR_STATUS                    status;
    int32_t                       txSaved;
    int32_t                       rxSaved;

    txSaved = CSL_REG32_FEXT(&pRegs->PHY_CONFIGURATION_REG,
                             OSPI_FLASH_CFG_PHY_CONFIGURATION_REG_PHY_CONFIG_TX_DLL_DELAY_FLD);
    rxSaved = CSL_REG32_FEXT(&pRegs->PHY_CONFIGURATION_REG,
                             OSPI_FLASH_CFG_PHY_CONFIGURATION_REG_PHY_CONFIG_RX_DLL_DELAY_FLD);

    NOR_spiTxRxDllConfig(handle, txDLL, rxDLL);
    status = NOR_spiPhyRdAttack(hwAttrs->dataAddr + offset);
#ifdef NOR_SPI_TUNE_DEBUG
    norSpiTuneCnt++;
#endif
    if (status == NOR_PASS)
        return rxDLL;
    while(status == NOR_FAIL){
        rxDLL++;
        if(rxDLL==128U) break;
        NOR_spiTxRxDllConfig(handle,txDLL,rxDLL);
        status = NOR_spiPhyRdAttack(hwAttrs->dataAddr + offset);
#ifdef NOR_SPI_TUNE_DEBUG
        norSpiTuneCnt++;
#endif
    }
    NOR_spiTxRxDllConfig(handle,txSaved,rxSaved);
    return rxDLL;
}

/*
 * Returns the last rxDLL value which passes the tuning basis test, searching up from given txDLL,rxDLL
 * Returns rxDLL passed into the function if failure
 */
static int32_t NOR_spiPhyFindRxEnd(OSPI_Handle handle, int32_t txDLL, int32_t rxDLL, uint32_t offset)
{
    OSPI_v0_HwAttrs const        *hwAttrs= (OSPI_v0_HwAttrs const *)handle->hwAttrs;
    const CSL_ospi_flash_cfgRegs *pRegs = (const CSL_ospi_flash_cfgRegs *)(hwAttrs->baseAddr);
    NOR_STATUS                    status;
    int32_t                       startRx = rxDLL;
    int32_t                       txSaved;
    int32_t                       rxSaved;

    txSaved = CSL_REG32_FEXT(&pRegs->PHY_CONFIGURATION_REG,
                             OSPI_FLASH_CFG_PHY_CONFIGURATION_REG_PHY_CONFIG_TX_DLL_DELAY_FLD);
    rxSaved = CSL_REG32_FEXT(&pRegs->PHY_CONFIGURATION_REG,
                             OSPI_FLASH_CFG_PHY_CONFIGURATION_REG_PHY_CONFIG_RX_DLL_DELAY_FLD);

    NOR_spiTxRxDllConfig(handle,txDLL,rxDLL);
    status = NOR_spiPhyRdAttack(hwAttrs->dataAddr + offset);
#ifdef NOR_SPI_TUNE_DEBUG
    norSpiTuneCnt++;
#endif
    if(status == NOR_FAIL){
        NOR_spiTxRxDllConfig(handle,txSaved,rxSaved);
        return startRx;
    }
    while (status == NOR_PASS){
        rxDLL++;
        NOR_spiTxRxDllConfig(handle,txDLL,rxDLL);
        status = NOR_spiPhyRdAttack(hwAttrs->dataAddr + offset);
#ifdef NOR_SPI_TUNE_DEBUG
        norSpiTuneCnt++;
#endif
    }
    NOR_spiTxRxDllConfig(handle,txSaved,rxSaved);

    return rxDLL;
}


/* Tries to find an rxDLL window at a given txDLL point. Puts start and end of the rxDLL window into the pointers */
static NOR_STATUS NOR_spiPhyFindRxWindow(OSPI_Handle handle, int32_t txDLL, int32_t *rxStart, int32_t *rxEnd, uint32_t offset)
{
    /* Search up from 0 to find the start of the Rx window */
    *rxStart = NOR_spiPhyFindRxStart(handle,txDLL,0,offset);

    /* If rxStart gets all the way to rxDLL=128 and doesn't pass, there is no rxDLL window */
    if(*rxStart == 128U)
        return NOR_FAIL;

    /* Find the end of the rxDLL window, searching up from rxStart */
    *rxEnd = NOR_spiPhyFindRxEnd(handle,txDLL,*rxStart+4U,offset);

    /* If rxEnd is greater than rxStart, we found a window. */
    if(*rxEnd>*rxStart+4U)
        return NOR_PASS;
    else
        return NOR_FAIL;
}

/*
 * Prints out DLL settings, and check the lock status bits
 *     0 = Full cycle
 *     2 = Half cycle
 *     3 = Failed to lock
 * if not full cycl locked, turn on the master PHY bypass mode
 */
static void NOR_spiPhyDllObserve(OSPI_Handle handle)
{
    OSPI_v0_HwAttrs const        *hwAttrs= (OSPI_v0_HwAttrs const *)handle->hwAttrs;
    const CSL_ospi_flash_cfgRegs *pRegs = (const CSL_ospi_flash_cfgRegs *)(hwAttrs->baseAddr);
    uint32_t                      dll_lock_mode;

#ifdef NOR_SPI_TUNE_DEBUG
    uint32_t rx_decode, tx_decode, dll_lock_value, dll_lock_status;

    /* Parse the observable upper and lower registers for the bit fields */
    rx_decode = CSL_REG32_FEXT(&pRegs->DLL_OBSERVABLE_UPPER_REG,
                               OSPI_FLASH_CFG_DLL_OBSERVABLE_UPPER_REG_DLL_OBSERVABLE__UPPER_RX_DECODER_OUTPUT_FLD);
    tx_decode = CSL_REG32_FEXT(&pRegs->DLL_OBSERVABLE_UPPER_REG,
                               OSPI_FLASH_CFG_DLL_OBSERVABLE_UPPER_REG_DLL_OBSERVABLE_UPPER_TX_DECODER_OUTPUT_FLD);
    dll_lock_value = CSL_REG32_FEXT(&pRegs->DLL_OBSERVABLE_LOWER_REG,
                                    OSPI_FLASH_CFG_DLL_OBSERVABLE_LOWER_REG_DLL_OBSERVABLE_LOWER_LOCK_VALUE_FLD);
    dll_lock_mode = CSL_REG32_FEXT(&pRegs->DLL_OBSERVABLE_LOWER_REG,
                                   OSPI_FLASH_CFG_DLL_OBSERVABLE_LOWER_REG_DLL_OBSERVABLE_LOWER_LOCK_MODE_FLD);
    dll_lock_status = CSL_REG32_FEXT(&pRegs->DLL_OBSERVABLE_LOWER_REG,
                                     OSPI_FLASH_CFG_DLL_OBSERVABLE_LOWER_REG_DLL_OBSERVABLE_LOWER_LOOPBACK_LOCK_FLD);

    /* Print out lock status, the lock value, and the tx/rx decoded value */
    switch(dll_lock_mode)
    {
        case 0b00:
            NOR_log("Decoded TX,RX is %d,%d\nDLL locked on full cycle with %d Delay elements\n",tx_decode,rx_decode,dll_lock_value);
            break;
        case 0b10:
            NOR_log("Decoded TX,RX is %d,%d\nDLL locked on half cycle with %d Delay elements\n",tx_decode,rx_decode,dll_lock_value);
            break;
        case 0b11:
            NOR_log("Decoded TX,RX is %d,%d\nDLL did not lock\n",tx_decode,rx_decode);
            break;
        default:
            break;
    }
    NOR_log("lock mode is %d, lock status is %d, \n",dll_lock_mode,dll_lock_status);
#else
    dll_lock_mode = CSL_REG32_FEXT(&pRegs->DLL_OBSERVABLE_LOWER_REG,
                                   OSPI_FLASH_CFG_DLL_OBSERVABLE_LOWER_REG_DLL_OBSERVABLE_LOWER_LOCK_MODE_FLD);
#endif
    if(dll_lock_mode != 0U){
        /* Put DLL into bypass mode */
       CSL_REG32_FINS(&pRegs->PHY_MASTER_CONTROL_REG,
                      OSPI_FLASH_CFG_PHY_MASTER_CONTROL_REG_PHY_MASTER_BYPASS_MODE_FLD, 1U);
    }
}

/*
 * This is a fast tuning algorithm.
 * It takes in the handle for the ospi instance it must tune.
 * Assumes Protocol is SDR, clock mode is internal loopback and PHY is in DLL Master mode.
 */
NOR_STATUS Nor_spiPhySdrTune(OSPI_Handle handle, uint32_t offset)
{
    int32_t       rdDelay1 = 0;
    int32_t       rdDelay2;
    int32_t       rxStart1,rxEnd1;
    int32_t       rxStart2,rxEnd2;
    NOR_PhyConfig startPoint, tuningPoint;
    float         rxWindow1 = 0;
    float         rxWindow2 = 0;
    float         temperature = 0;

    /* SDR tuning requires as much delay as possible. If locked on a half cycle, go into bypass mode */
    startPoint.txDLL = 16;
    startPoint.rxDLL = 16;
    startPoint.rdDelay = rdDelay1;

    NOR_spiPhyConfig(handle, startPoint);
    /* Check if PHY DLL is locked */
    NOR_spiPhyDllObserve(handle);
    while(NOR_spiPhyFindRxWindow(handle, 64U, &rxStart1, &rxEnd1, offset) == NOR_FAIL)
    {
        rdDelay1++;
        NOR_spiRdDelayConfig(handle, rdDelay1);
        if(rdDelay1>4){
#ifdef NOR_SPI_TUNE_DEBUG
            NOR_log("Unable to find any rxDLL window.  Panic!\n");
#endif
            break;
        }
    }
    rxWindow1 = rxEnd1-rxStart1;
    rdDelay2 = rdDelay1+1;
    NOR_spiRdDelayConfig(handle, rdDelay2);
    if(NOR_spiPhyFindRxWindow(handle, 64U, &rxStart2, &rxEnd2, offset) == NOR_PASS)
    {
        rxWindow2 = rxEnd2-rxStart2;
    }else{
        rxWindow2 = 0;
    }

    temperature = NOR_spiPhyAvgVtmTemp(NOR_SPI_PHY_VTM_TARGET);
    if(rxWindow2>rxWindow1){
        rdDelay1 = rdDelay2;
        rxWindow1 = rxWindow2;
        rxStart1 = rxStart2;
        rxEnd1 = rxEnd2;
    }
#ifdef NOR_SPI_TUNE_DEBUG
    NOR_log("rxDLL Window of width %d found from %d to %d at txDLL of 64 and Read Delay of %d\n",(int)rxWindow1,rxStart1,rxEnd1,rdDelay1);
#endif
    tuningPoint.rdDelay = rdDelay1;
    tuningPoint.txDLL = 64U;
    tuningPoint.rxDLL = rxStart1;
    tuningPoint.rxDLL = (int)(((double)tuningPoint.rxDLL+rxWindow1/2U) - ((temperature-42.5)/165)*rxWindow1*0.75);
#ifdef NOR_SPI_TUNE_DEBUG
    NOR_log("Tuning was complete in %d steps\n", norSpiTuneCnt);
    NOR_log("Tuning PHY to txDLL,rxDLL of %d,%d and rdDelay of %d\n",tuningPoint.txDLL,tuningPoint.rxDLL,tuningPoint.rdDelay);
#endif
    NOR_spiPhyConfig(handle, tuningPoint);

    /* Save ddr tuning config point data */
    sdrTuningPoint = tuningPoint;

    return NOR_PASS;
}

NOR_STATUS Nor_spiPhyTune(OSPI_Handle handle, uint32_t offset)
{
    NOR_STATUS                    status = NOR_PASS;
    OSPI_v0_HwAttrs const        *hwAttrs = (OSPI_v0_HwAttrs const *)handle->hwAttrs;
    const CSL_ospi_flash_cfgRegs *pRegs = (const CSL_ospi_flash_cfgRegs *)(hwAttrs->baseAddr);

#ifdef NOR_SPI_TUNE_PROFILE
    uint64_t          startTime;        /* start time stamp in usec */
    uint64_t          elapsedTime;      /* elapsed time in usec */
    startTime = TimerP_getTimeInUsecs();
#endif

#ifdef NOR_SPI_TUNE_DEBUG
    NOR_log("\n");
    NOR_log("\n Fast Tuning at temperature %dC\n",(int)NOR_spiPhyAvgVtmTemp(NOR_SPI_PHY_VTM_TARGET));
#endif
    CSL_REG32_FINS(&pRegs->DEV_INSTR_RD_CONFIG_REG,
                   OSPI_FLASH_CFG_DEV_INSTR_RD_CONFIG_REG_DUMMY_RD_CLK_CYCLES_FLD,
                   NOR_OCTAL_READ_DUMMY_CYCLE - 1U);
    if (hwAttrs->dtrEnable)
    {
        if ((ddrTuningPoint.txDLL == 0U) && (ddrTuningPoint.rxDLL == 0U))
        {
            /* process the PHY tuning only once */
            status = Nor_spiPhyDdrTune(handle, offset);
        }
        else
        {
            NOR_spiPhyConfig(handle, ddrTuningPoint);
        }
    }
    else
    {
        if ((sdrTuningPoint.txDLL == 0U) && (sdrTuningPoint.rxDLL == 0U))
        {
            /* process the PHY tuning only once */
            status = Nor_spiPhySdrTune(handle, offset);
        }
        else
        {
            NOR_spiPhyConfig(handle, sdrTuningPoint);
        }
    }

#ifdef NOR_SPI_TUNE_PROFILE
    elapsedTime = TimerP_getTimeInUsecs() - startTime;
    NOR_log("\n PHY tuning elapsed %d us", (uint32_t)elapsedTime);
#endif

    return status;
}

void Nor_spiPhyTuneReset(bool ddrMode)
{
    if (ddrMode == (bool)true)
    {
        ddrTuningPoint.txDLL   = 0;
        ddrTuningPoint.rxDLL   = 0;
        ddrTuningPoint.rdDelay = 0;
    }
    else
    {
        sdrTuningPoint.txDLL   = 0;
        sdrTuningPoint.rxDLL   = 0;
        sdrTuningPoint.rdDelay = 0;
    }
}
