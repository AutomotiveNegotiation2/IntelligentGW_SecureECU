/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 * Copyright (c) 2015 Runtime Inc
 * Copyright 2021 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdint.h>
#include <string.h>
#include "flash_map.h"
//#include "flash_partitioning.h"
#include "sysflash/sysflash.h"
#include "mflash_drv.h"

#if !defined(ARRAY_SIZE)
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

#define ALIGN_VAL  1
#define ERASED_VAL 0xFF

static uint32_t flash_page_buf[MFLASH_PAGE_SIZE / sizeof(uint32_t)];

int boot_flash_area_read(uint32_t off, void *dst, uint32_t len)
{
    uint32_t addr = off;
    uint32_t i;

    uint8_t *buffer_u8 = dst;

    /* inter-page lenght of the first read can be smaller than page size */
    size_t plen = MFLASH_PAGE_SIZE - (addr % MFLASH_PAGE_SIZE);

    while (len > 0)
    {
        size_t readsize = (len > plen) ? plen : len;

#if defined(MFLASH_PAGE_INTEGRITY_CHECKS) && MFLASH_PAGE_INTEGRITY_CHECKS
        if (mflash_drv_is_readable(addr) != kStatus_Success)
        {
            /* PRINTF("%s: UNREADABLE PAGE at %x\n", __func__, addr); */
            memset(buffer_u8, ERASED_VAL, readsize);
        }
        else
#endif
        {
            void *flash_ptr = mflash_drv_phys2log(addr, readsize);
            if (flash_ptr == NULL)
            {
                return -1;
            }
            /* use direct memcpy as mflash_drv_read low layer may expects len to be word aligned */
            memcpy(buffer_u8, flash_ptr, readsize);
        }

        len -= readsize;
        addr += readsize;
        buffer_u8 += readsize;

        plen = MFLASH_PAGE_SIZE;
    }

    return 0;
}

int boot_flash_area_write(uint32_t off, const void *src, uint32_t len)
{
    status_t status = kStatus_Success;

    uint8_t *src_ptr  = (uint8_t *)src;
    uint32_t dst_addr = off;
    uint32_t page_addr;

    uint32_t chunk_size;
    uint32_t chunk_ofs;

    /* offset within the first page and max size that would fit */
    chunk_ofs  = dst_addr % MFLASH_PAGE_SIZE;
    chunk_size = MFLASH_PAGE_SIZE - chunk_ofs;

    /* calculate starting address of the page */
    page_addr = dst_addr - chunk_ofs;

    while (len > 0)
    {
        if (chunk_size > len)
        {
            chunk_size = len; /* last chunk of data */
        }

        /* check if part of the buffer is not going to be filled with data */
        if ((chunk_ofs > 0) || (chunk_size < MFLASH_PAGE_SIZE))
        {
            /* fill the buffer with erased value, tweaking to clean just the unused range does not pay off */
            memset(flash_page_buf, ERASED_VAL, MFLASH_PAGE_SIZE);
        }

        memcpy((uint8_t *)flash_page_buf + chunk_ofs, src_ptr, chunk_size);
        status = mflash_drv_page_program(page_addr, flash_page_buf);
        if (status != kStatus_Success)
        {
            break;
        }

        src_ptr += chunk_size;
        len -= chunk_size;

        /* re-initialize chunk to full size of the page */
        chunk_ofs  = 0;
        chunk_size = MFLASH_PAGE_SIZE;

        /* advance to next page */
        page_addr += MFLASH_PAGE_SIZE;
    }

    if (status != kStatus_Success)
    {
        /* some callers check only for negative error codes, translate to -1 to stay on the safe side */
        return -1;
    }

    return 0;
}

int boot_flash_area_erase(uint32_t off, uint32_t len)
{
    status_t status  = kStatus_Success;
    uint32_t address = off;

    if ((address % MFLASH_SECTOR_SIZE) || (len % MFLASH_SECTOR_SIZE))
    {
        return -1;
    }

    for (; len > 0; len -= MFLASH_SECTOR_SIZE)
    {
        /* Erase sectors. */
        status = mflash_drv_sector_erase(address);
        if (status != kStatus_Success)
        {
            break;
        }

        address += MFLASH_SECTOR_SIZE;
    }

    if (status != kStatus_Success)
    {
        /* some callers check only for negative error codes, translate to -1 to stay on the safe side */
        return -1;
    }

    return 0;
}
