/********************************************************************
*
* SOC INTERRUPT. header file
*
* Copyright (C) 2023 Texas Instruments Incorporated.
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
*
*/
#ifndef LLDR_SOC_INTR_IN_H
#define LLDR_SOC_INTR_IN_H

#include <hw_include/lldr.h>
#include <hw_include/tistdtypes.h>
#ifdef __cplusplus
extern "C"
{
#endif

/*
* Auto-generated list of IP Level Interrupt Header Files:
*/

#include <hw_include/soc/j784s4/src/lldr_intr_cmpevent_intrtr0.h>
#include <hw_include/soc/j784s4/src/lldr_intr_compute_cluster0.h>
#include <hw_include/soc/j784s4/src/lldr_intr_cpsw1.h>
#include <hw_include/soc/j784s4/src/lldr_intr_dmpac0.h>
#include <hw_include/soc/j784s4/src/lldr_intr_esm0.h>
#include <hw_include/soc/j784s4/src/lldr_intr_gluelogic_a72_ipc_intr_glue.h>
#include <hw_include/soc/j784s4/src/lldr_intr_gluelogic_dbg_cbass_intr_or_glue.h>
#include <hw_include/soc/j784s4/src/lldr_intr_gluelogic_fw_cbass_intr_or_glue.h>
#include <hw_include/soc/j784s4/src/lldr_intr_gluelogic_gpu_gpio_int_glue.h>
#include <hw_include/soc/j784s4/src/lldr_intr_gluelogic_main_cbass_intr_or_glue.h>
#include <hw_include/soc/j784s4/src/lldr_intr_gluelogic_nonfw_cbass_intr_or_glue.h>
#include <hw_include/soc/j784s4/src/lldr_intr_gpiomux_intrtr0.h>
#include <hw_include/soc/j784s4/src/lldr_intr_main2mcu_lvl_intrtr0.h>
#include <hw_include/soc/j784s4/src/lldr_intr_main2mcu_pls_intrtr0.h>
#include <hw_include/soc/j784s4/src/lldr_intr_main_gpio0_virt.h>
#include <hw_include/soc/j784s4/src/lldr_intr_mcu_adc12fcc0.h>
#include <hw_include/soc/j784s4/src/lldr_intr_mcu_adc12fcc1.h>
#include <hw_include/soc/j784s4/src/lldr_intr_mcu_cpsw0.h>
#include <hw_include/soc/j784s4/src/lldr_intr_mcu_esm0.h>
#include <hw_include/soc/j784s4/src/lldr_intr_mcu_navss0.h>
#include <hw_include/soc/j784s4/src/lldr_intr_mcu_pdma0.h>
#include <hw_include/soc/j784s4/src/lldr_intr_mcu_pdma1.h>
#include <hw_include/soc/j784s4/src/lldr_intr_mcu_pdma2.h>
#include <hw_include/soc/j784s4/src/lldr_intr_mcu_pdma3.h>
#include <hw_include/soc/j784s4/src/lldr_intr_mcu_r5fss0.h>
#include <hw_include/soc/j784s4/src/lldr_intr_navss0.h>
#include <hw_include/soc/j784s4/src/lldr_intr_pcie1.h>
#include <hw_include/soc/j784s4/src/lldr_intr_pdma0.h>
#include <hw_include/soc/j784s4/src/lldr_intr_pdma1.h>
#include <hw_include/soc/j784s4/src/lldr_intr_pdma2.h>
#include <hw_include/soc/j784s4/src/lldr_intr_pdma3.h>
#include <hw_include/soc/j784s4/src/lldr_intr_pdma4.h>
#include <hw_include/soc/j784s4/src/lldr_intr_pdma5.h>
#include <hw_include/soc/j784s4/src/lldr_intr_pdma6.h>
#include <hw_include/soc/j784s4/src/lldr_intr_pdma7.h>
#include <hw_include/soc/j784s4/src/lldr_intr_pdma8.h>
#include <hw_include/soc/j784s4/src/lldr_intr_pinfunction_sync0_outout.h>
#include <hw_include/soc/j784s4/src/lldr_intr_pinfunction_sync1_outout.h>
#include <hw_include/soc/j784s4/src/lldr_intr_pinfunction_sync2_outout.h>
#include <hw_include/soc/j784s4/src/lldr_intr_pinfunction_sync3_outout.h>
#include <hw_include/soc/j784s4/src/lldr_intr_r5fss0.h>
#include <hw_include/soc/j784s4/src/lldr_intr_r5fss1.h>
#include <hw_include/soc/j784s4/src/lldr_intr_timesync_intrtr0.h>
#include <hw_include/soc/j784s4/src/lldr_intr_vusr_dual0.h>
#include <hw_include/soc/j784s4/src/lldr_intr_wkup_esm0.h>
#include <hw_include/soc/j784s4/src/lldr_intr_wkup_gpio_virt.h>
#include <hw_include/soc/j784s4/src/lldr_intr_wkup_gpiomux_intrtr0.h>

#ifdef __cplusplus
}
#endif
#endif /* lldr_SOC_INTR_IN_H */

