/*
 * System Firmware Trace Layer
 *
 * Utility itoa function for number to string conversion
 *
 * Copyright (C) 2018-2020, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
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
 */

#include <types/short_types.h>

u8 *lib_itoa(u32 value, u8 *str, u32 base)
{
	u32 idx = 0;
	u32 val;
	u32 i;

	if (value == 0U) {
		str[0] = (u8) '0';
		idx++;
	}

	while (value > 0U) {
		val = value % base;
		if (val < 10) {
			str[idx] = (u8) (val + '0');
		} else {
			str[idx] = (u8) ((val - 10U) + 'A');
		}

		idx++;
		value /= base;
	}

	str[idx] = (u8) '\0';

	if (idx > 1U) {
		/* Get length of string - NULL terminator*/
		idx--;

		/* Reverse the string as we converted from low digit to high */
		for (i = 0U; i <= (idx / 2U); i++) {
			val = str[idx - i];
			str[idx - i] = str[i];
			str[i] = (u8) val;
		}
	}

	return str;
}
