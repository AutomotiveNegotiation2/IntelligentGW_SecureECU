/*
 * Copyright 2020-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SFW_H__
#define __SFW_H__

#include <stdint.h>

#include "mcuboot_app_support.h"

#define IMG_VERIFY_NONE     0
#define IMG_VERIFY_DENYED   1
#define IMG_VERIFY_PASSED   2
#define IMG_VERIFY_FAILED   3
#define IMG_VERIFY_UNKNOWN  4

/* SFW error code definitions */
#define OK                          0               /**< There is no error */
#define ERROR                        1               /**< A generic error happens */
#define ERROR_TIMEOUT                     2               /**< Timed out */
#define ERROR_FULL                        3               /**< The resource is full */
#define ERROR_EMPTY                       4               /**< The resource is empty */
#define ERROR_NOMEM                       5               /**< No memory */
#define ERROR_NOSYS                       6               /**< No system */
#define ERROR_BUSY                        7               /**< Busy */
#define ERROR_IO                          8               /**< IO error */
#define ERROR_INTR                        9               /**< Interrupted system call */
#define ERROR_INVAL                       10              /**< Invalid argument */

#define SLOT_0							0
#define SLOT_1							1
#define SLOT_2							2
#define SLOT_3							3

#define SWF_MAIN_TASK_DELAY_TIME		1000

//void sfw_main(void *arg);
void sfw_main(void);
void print_image_version(void);

#endif
