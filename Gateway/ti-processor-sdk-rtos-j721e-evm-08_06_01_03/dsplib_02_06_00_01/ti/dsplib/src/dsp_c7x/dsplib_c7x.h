/******************************************************************************
 *                                                                             *
 * module name       :MMALIB                                                   *
 *                                                                             *
 * module descripton :Matrix Multiply Accelerator Library module for C7x+MMA   *
 *                                                                             *
 * Copyright (C) 2017-2018 Texas Instruments Incorporated - http://www.ti.com/ *
 * ALL RIGHTS RESERVED                                                         *
 *                                                                             *
 ******************************************************************************/

/**
 ******************************************************************************
 *  @file     dsplib_c7x.h
 *
 *  @brief    File to hold buffer parameter related info for MMALIB
 *
 *  @version  0.1 - Jan 2018 : Initial Version with as a template [PKS]
 *
 *******************************************************************************
 */
#ifndef _DSPLIB_C7X_H_
#define _DSPLIB_C7X_H_

//#include "DSPLIB_firSmall_ixX_ixX_oxX/DSPLIB_firSmall_ixX_ixX_oxX.h"
#include "DSPLIB_fir/DSPLIB_fir.h"
#include "DSPLIB_cascadeBiquad/DSPLIB_cascadeBiquad.h"
#include "DSPLIB_add/DSPLIB_add.h"
#include "DSPLIB_addConstant/DSPLIB_addConstant.h"
#include "DSPLIB_sub/DSPLIB_sub.h"
#include "DSPLIB_subConstant/DSPLIB_subConstant.h"
#include "DSPLIB_mul/DSPLIB_mul.h"
#include "DSPLIB_mulConstant/DSPLIB_mulConstant.h"
#include "DSPLIB_max/DSPLIB_max.h"
#include "DSPLIB_min/DSPLIB_min.h"
#include "DSPLIB_sqr/DSPLIB_sqr.h"
#include "DSPLIB_sqrAdd/DSPLIB_sqrAdd.h"
#endif /*_DSPLIB_C7X_H_*/

/*!
 * \defgroup DSPLIB Digital Signal Processing (DSP) kernels
 * \brief This module consists of kernels that implement DSP
 *        algorithms.
 *
 */
