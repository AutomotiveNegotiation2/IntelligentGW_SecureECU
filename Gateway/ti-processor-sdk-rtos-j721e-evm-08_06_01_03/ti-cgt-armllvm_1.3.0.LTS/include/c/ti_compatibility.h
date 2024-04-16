/*****************************************************************************/
/*  ti_compatibility.h v#####                                                */
/*  Copyright (c) 2018@%%%%  Texas Instruments Incorporated                  */
/*                                                                           */
/*  Compatibility header for TI Intrinsics for use with tiarmclang compiler  */
/*                                                                           */
/*****************************************************************************/
#ifndef _TI_COMPAT_H
#define _TI_COMPAT_H

#include <_defs.h>
#include <arm_acle.h>

/******************************************************************************/
/* TI-Specific Macro Definitions                                              */
/******************************************************************************/
#define __TMS470__ 1
#define __TI_ARM__ 1

#ifdef __thumb__
#  define __16bis__ 1
#else
#  define __32bis__ 1
#endif /* __thumb__ */

#define __eabi__ 1
#define __TI_EABI_SUPPORT__ __eabi__

#if __ARM_FP
#  define __TI_VFP_SUPPORT__ 1
#  if (__ARM_ARCH == 7 && __ARM_ARCH_PROFILE == 'M')
#    define __TI_FPV4SPD16_SUPPORT__ 1
#    define __TI_FPv4SPD16_SUPPORT__ __TI_FPV4SPD16_SUPPORT__
#  elif (__ARM_ARCH == 7 && __ARM_ARCH_PROFILE == 'R')
#    define __TI_VFPV3D16_SUPPORT__ 1
#  endif /* __ARM_ARCH && __ARM_ARCH_PROFILE */
#else
#  define __TI_VFPLIB_SUPPORT__ 1
#endif /* __ARM_FP */

#if __ARM_ARCH_PROFILE == 'M'
#  if __ARM_ARCH == 6
#    define __TI_ARM_V6M0__ 1
#  elif __ARM_ARCH == 7
#    if __ARM_FEATURE_SIMD32 == 1
#      define __TI_TMS470_V7M4__ 1
#      define __TI_ARM_V7M4__ __TI_TMS470_V7M4__
#    elif !defined(__ARM_FEATURE_SIMD32)
#      define __TI_TMS470_V7M3__ 1
#      define __TI_ARM_V7M3__ __TI_TMS470_V7M3__
#    endif /* __ARM_FEATURE_SIMD32 */
#  endif /* __ARM_ARCH */
#elif __ARM_ARCH_PROFILE == 'R'
#  if __ARM_ARCH == 7
#    define __TI_TMS470_V7R4__ 1
#    define __TI_ARM_V7R4__ __TI_TMS470_V7R4__
#  endif /* __ARM_ARCH */
#endif /* __ARM_ARCH_PROFILE */

#ifdef __ARM_BIG_ENDIAN
#  define __big_endian__ 1
#  define __BIG_ENDIAN__ 1
#else
#  define __little_endian__ 1
#  define __LITTLE_ENDIAN__ 1
#endif /* __ARM_BIG_ENDIAN */

#ifdef __CHAR_UNSIGNED__
#  define __unsigned_chars__ 1
#else
#  define __signed_chars__ 1
#endif /* __CHAR_UNSIGNED__ */

#define __WCHAR_T_TYPE__ __WCHAR_TYPE__

/******************************************************************************/
/* Get Current Program Counter                                                */
/******************************************************************************/
static __inline__ void * __attribute__((always_inline))
__curpc(void) {
    unsigned char *pc;
    __asm volatile ("MOV %0, pc" :  "=r" (pc) : : );
#ifdef __thumb__
    return pc-4;
#else
    return pc-8;
#endif
}

/******************************************************************************/
/* Run Address Check                                                          */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
__run_address_check(void)
{
    return 0;
}

/******************************************************************************/
/* Get High Bits of a Double                                                  */
/******************************************************************************/
static __inline__ uint32_t __attribute__((always_inline))
_hi(double x) {
    uint64_t temp = __f64_bits_as_u64(x);
    return (uint32_t)(temp >> 32);
}

/******************************************************************************/
/* Get Low Bits of a Double                                                   */
/******************************************************************************/
static __inline__ uint32_t __attribute__((always_inline))
_lo(double x) {
    uint64_t temp = __f64_bits_as_u64(x);
    return (uint32_t)(temp & 0xFFFFFFFF);
}

/******************************************************************************/
/* Combine Two Ints to Double                                                 */
/******************************************************************************/
static __inline__ double __attribute__((always_inline))
_itod(uint32_t x, uint32_t y) {
    uint64_t res = ((uint64_t)(x) << 32) | y;
    return __u64_bits_as_f64(res);
}

/******************************************************************************/
/* Convert Int to Float                                                       */
/******************************************************************************/
static __inline__ float __attribute__((always_inline))
_itof(uint32_t x)
{
    return __u32_bits_as_f32(x);
}

/******************************************************************************/
/* Convert Float to Int                                                       */
/******************************************************************************/
static __inline__ uint32_t __attribute__((always_inline))
_ftoi(float x)
{
    return __f32_bits_as_u32(x);
}

/******************************************************************************/
/* Add/Subtract with carry TI intrinsics are not supported as the handling of */
/* the carry bit differs in a way that cannot be resolved.                    */
/******************************************************************************/
/******************************************************************************/
/* Subtract with Carry                                                        */
/******************************************************************************/
/* static __inline__ int32_t __attribute__((always_inline))
** _subc(int32_t x, int32_t y);
*/

/******************************************************************************/
/* Add with Carry                                                             */
/******************************************************************************/
/* static __inline__ int32_t __attribute__((always_inline))
** _addc(int32_t x, int32_t y);
*/

/******************************************************************************/
/* The following functions are TI builtins for 32-bit SIMD instructions       */
/******************************************************************************/
#if __ARM_FEATURE_SIMD32 == 1

/******************************************************************************/
/* Saturated Signed Addition                                                  */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_sadd(int32_t x, int32_t y)
{
    return __builtin_arm_qadd(x, y);
}

/******************************************************************************/
/* Saturated Signed Subtraction                                               */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_ssub(int32_t x, int32_t y)
{
    return __builtin_arm_qsub(x, y);
}

/******************************************************************************/
/* Saturated Double and Addition                                             */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_sdadd(int32_t x, int32_t y)
{
    int32_t res = 0;
    __asm ("QDADD %0, %1, %2" : "=r" (res) : "r" (x), "r" (y) : );
    return res;
}

/******************************************************************************/
/* Saturated Double and Subtraction                                           */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_sdsub(int32_t x, int32_t y)
{
    int32_t res = 0;
    __asm ("QDSUB %0, %1, %2" : "=r" (res) : "r" (x), "r" (y) : );
    return res;
}

/******************************************************************************/
/* Saturated Multiplication                                                   */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_smpy(int32_t x, int32_t y)
{
    int32_t temp = __builtin_arm_smulbb(x, y);
    return _sadd(temp, temp);
}

/******************************************************************************/
/* Saturated Multiply Accumulate Addition                                     */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_smac(int16_t x, int16_t y, int32_t z)
{
    int32_t temp = __builtin_arm_smulbb(x, y);
    return _sdadd(z, temp);
}

/******************************************************************************/
/* Saturated Multiply Accumulate Subtraction                                  */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_smsub(int16_t x, int16_t y, int32_t z)
{
    int32_t temp = __builtin_arm_smulbb(x, y);
    return _ssub(z, temp);
}

/******************************************************************************/
/* Signed Multiply Bottom Half-Words                                          */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_smulbb(int32_t x, int32_t y)
{
    return __builtin_arm_smulbb(x, y);
}

/******************************************************************************/
/* Signed Multiply Bottom and Top Half-Words                                  */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_smulbt(int32_t x, int32_t y)
{
    return __builtin_arm_smulbt(x, y);
}

/******************************************************************************/
/* Signed Multiply Top and Bottom Half-Words                                  */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_smultb(int32_t x, int32_t y)
{
    return __builtin_arm_smultb(x, y);
}

/******************************************************************************/
/* Signed Multiply Top Half-Words                                             */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_smultt(int32_t x, int32_t y)
{
    return __builtin_arm_smultt(x, y);
}

/******************************************************************************/
/* Signed Multiply Accumulate Bottom                                          */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_smlabb(int32_t x, int32_t y, int32_t z)
{
    return __builtin_arm_smlabb(x, y, z);
}

/******************************************************************************/
/* Signed Multiply Accumulate Bottom Top                                      */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_smlabt(int32_t x, int32_t y, int32_t z)
{
    return __builtin_arm_smlabt(x, y, z);
}

/******************************************************************************/
/* Signed Multiply Accumulate Top bottom                                      */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_smlatb(int32_t x, int32_t y, int32_t z)
{
    return __builtin_arm_smlatb(x, y, z);
}

/******************************************************************************/
/* Signed Multiply Accumulate Top                                             */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_smlatt(int32_t x, int32_t y, int32_t z)
{
    return __builtin_arm_smlatt(x, y, z);
}

/******************************************************************************/
/* Signed Multiply Accumulate Long Bottom                                     */
/******************************************************************************/
static __inline__ int64_t __attribute__((always_inline))
_smlalbb(int64_t x, int16_t y, int16_t z)
{
    int64_t ret = 0;
    int32_t res_lo = x & 0xFFFFFFFF;
    int32_t res_hi = (x >> 32) & 0xFFFFFFFF;
    __asm ("SMLALBB %0, %1, %2, %3" : : "r" (res_lo), "r" (res_hi), "r" (y), "r" (z) : );
    ret = (int64_t)res_lo & (int64_t)res_hi << 32;
    return ret;
}

/******************************************************************************/
/* Signed Multiply Accumulate Long Bottom Top                                 */
/******************************************************************************/
static __inline__ int64_t __attribute__((always_inline))
_smlalbt(int64_t x, int16_t y, int32_t z)
{
    int64_t ret = 0;
    int32_t res_lo = x & 0xFFFFFFFF;
    int32_t res_hi = (x >> 32) & 0xFFFFFFFF;
    __asm ("SMLALBT %0, %1, %2, %3" : : "r" (res_lo), "r" (res_hi), "r" (y), "r" (z) : );
    ret = (int64_t)res_lo & (int64_t)res_hi << 32;
    return ret;
}

/******************************************************************************/
/* Signed Multiply Accumulate Long Top Bottom                                 */
/******************************************************************************/
static __inline__ int64_t __attribute__((always_inline))
_smlaltb(int64_t x, int32_t y, int16_t z)
{
    int64_t ret = 0;
    int32_t res_lo = x & 0xFFFFFFFF;
    int32_t res_hi = (x >> 32) & 0xFFFFFFFF;
    __asm  ("SMLALTB %0, %1, %2, %3" : : "r" (res_lo), "r" (res_hi), "r" (y), "r" (z) : );
    ret = (int64_t)res_lo & (int64_t)res_hi << 32;
    return ret;
}

/******************************************************************************/
/* Signed Multiply Accumulate Long Top                                        */
/******************************************************************************/
static __inline__ int64_t __attribute__((always_inline))
_smlaltt(int64_t x, int32_t y, int16_t z)
{
    int64_t ret = 0;
    int32_t res_lo = x & 0xFFFFFFFF;
    int32_t res_hi = (x >> 32) & 0xFFFFFFFF;
    __asm  ("SMLALTT %0, %1, %2, %3" : : "r" (res_lo), "r" (res_hi), "r" (y), "r" (z) : );
    ret = (int64_t)res_lo & (int64_t)res_hi << 32;
    return ret;
}

/******************************************************************************/
/* Signed Multiply Word and Bottom                                            */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_smulwb(int32_t x, int32_t y)
{
    return __builtin_arm_smulwb(x, y);
}

/******************************************************************************/
/* Signed Multiply Word and Top                                               */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_smulwt(int32_t x, int32_t y)
{
    return __builtin_arm_smulwt(x, y);
}

/******************************************************************************/
/* Signed Multiply Accumulate Word and Bottom                                 */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_smlawb(int32_t x, int32_t y, int32_t z)
{
    return __builtin_arm_smlawb(x, y, z);
}

/******************************************************************************/
/* Signed Multiply Accumulate Word and Top                                    */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_smlawt(int32_t x, int32_t y, int32_t z)
{
    return __builtin_arm_smlawt(x, y, z);
}

/******************************************************************************/
/* Add Top Halfwords, Subtract Bottom Halfwords                               */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_saddsubx(int32_t x, int32_t y)
{
    int32_t res = 0;
    __asm  ("SADDSUBX %0, %1, %2" : "=r" (res) : "r" (x), "r" (y) : );
    return res;
}

/******************************************************************************/
/* Subtract Top Halfwords, Add Bottom Halfwords                               */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_ssubaddx(int32_t x, int32_t y)
{
    int32_t res = 0;
    __asm  ("SSUBADDX %0, %1, %2" : "=r" (res) : "r" (x), "r" (y) : );
    return res;
}

/******************************************************************************/
/* Unsigned Add Top Halfwords, Subtract Bottom Halfwords                      */
/******************************************************************************/
static __inline__ uint32_t __attribute__((always_inline))
_uaddsubx(uint32_t x, uint32_t y)
{
    uint32_t res = 0;
    __asm  ("UADDSUBX %0, %1, %2" : "=r" (res) : "r" (x), "r" (y) : );
    return res;
}

/******************************************************************************/
/* Unsigned Subtract Top Halfwords, Add Bottom Halfwords                      */
/******************************************************************************/
static __inline__ uint32_t __attribute__((always_inline))
_usubaddx(uint32_t x, uint32_t y)
{
    uint32_t res = 0;
    __asm  ("USUBADDX %0, %1, %2" : "=r" (res) : "r" (x), "r" (y) : );
    return res;
}

/******************************************************************************/
/*Signed-saturate-add top halfwords, signed-saturate-subtract bottom halfwords*/
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_qaddsubx(int32_t x, int32_t y)
{
    int32_t res = 0;
    __asm  ("QASX %0, %1, %2" : "=r" (res) : "r" (x), "r" (y) : );
    return res;
}

/******************************************************************************/
/*Signed-saturate-subtract top halfwords, signed-saturate-add bottom halfwords*/
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_qsubaddx(int32_t x, int32_t y)
{
    int32_t res = 0;
    __asm  ("QSUBADDX %0, %1, %2" : "=r" (res) : "r" (x), "r" (y) : );
    return res;
}

/******************************************************************************/
/* Saturate-add top halfwords, Saturate-subtract bottom halfwords             */
/******************************************************************************/
static __inline__ uint32_t __attribute__((always_inline))
_uqaddsubx(uint32_t x, uint32_t y)
{
    uint32_t res = 0;
    __asm  ("UQADDSUBX %0, %1, %2" : "=r" (res) : "r" (x), "r" (y) : );
    return res;
}

/******************************************************************************/
/* Saturate-subtract top halfwords, Saturate-add bottom halfwords             */
/******************************************************************************/
static __inline__ uint32_t __attribute__((always_inline))
_uqsubaddx(uint32_t x, uint32_t y)
{
    uint32_t res = 0;
    __asm  ("UQSUBADDX %0, %1, %2" : "=r" (res) : "r" (x), "r" (y) : );
    return res;
}

/******************************************************************************/
/* Add top halfwords, subtract bottom halfwords, results are halved           */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_shaddsubx(int32_t x, int32_t y)
{
    int32_t res = 0;
    __asm  ("SHADDSUBX %0, %1, %2" : "=r" (res) : "r" (x), "r" (y) : );
    return res;
}

/******************************************************************************/
/* Subtract top halfwords, add bottom halfwords, results are halved           */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_shsubaddx(int32_t x, int32_t y)
{
    int32_t res = 0;
    __asm  ("SHSUBADDX %0, %1, %2" : "=r" (res) : "r" (x), "r" (y) : );
    return res;
}

/******************************************************************************/
/* Add top halfwords, subtract bottom halfwords, results are halved           */
/******************************************************************************/
static __inline__ uint32_t __attribute__((always_inline))
_uhaddsubx(uint32_t x, uint32_t y)
{
    uint32_t res = 0;
    __asm  ("UHADDSUBX %0, %1, %2" : "=r" (res) : "r" (x), "r" (y) : );
    return res;
}

/******************************************************************************/
/* Subtract top halfwords, add bottom halfwords, results are halved           */
/******************************************************************************/
static __inline__ uint32_t __attribute__((always_inline))
_uhsubaddx(uint32_t x, uint32_t y)
{
    uint32_t res = 0;
    __asm  ("UHSUBADDX %0, %1, %2" : "=r" (res) : "r" (x), "r" (y) : );
    return res;
}

/******************************************************************************/
/* The following mappings are defined in arm_acle.h                           */
/******************************************************************************/
#define _sadd16(x,y) __sadd16(x,y)
#define _ssub16(x,y) __ssub16(x,y)
#define _sadd8(x,y) __sadd8(x,y)
#define _ssub8(x,y) __ssub8(x,y)
#define _qadd16(x,y) __qadd16(x,y)
#define _qsub16(x,y) __qsub16(x,y)
#define _qadd8(x,y) __qadd8(x,y)
#define _qsub8(x,y) __qsub8(x,y)
#define _shadd16(x,y) __shadd16(x,y)
#define _shsub16(x,y) __shsub16(x,y)
#define _shadd8(x,y) __shadd8(x,y)
#define _shsub8(x,y) __shsub8(x,y)
#define _uadd16(x,y) __uadd16(x,y)
#define _usub16(x,y) __usub16(x,y)
#define _uadd8(x,y) __uadd8(x,y)
#define _usub8(x,y) __usub8(x,y)
#define _uqadd16(x,y) __uqadd16(x,y)
#define _uqsub16(x,y) __uqsub16(x,y)
#define _uqadd8(x,y) __uqadd8(x,y)
#define _uqsub8(x,y) __uqsub8(x,y)
#define _uhadd16(x,y) __uhadd16(x,y)
#define _uhsub16(x,y) __uhsub16(x,y)
#define _uhadd8(x,y) __uhadd8(x,y)
#define _uhsub8(x,y) __uhsub8(x,y)
#define _ssat16(x,y) __ssat16(x,y)
#define _usat16(x,y) __usat16(x,y)
#define _sel(x,y) __sel(x,y)
#define _smlad(x,y,z) __smlad(x,y,z)
#define _smladx(x,y,z) __smladx(x,y,z)
#define _smlsd(x,y,z) __smlsd(x,y,z)
#define _smlaldx(x,y,z) __smlaldx(x,y,z)
#define _smlsld(x,y,z) __smlsld(x,y,z)
#define _smlsldx(x,y,z) __smlsldx(x,y,z)
#define _smuad(x,y) __smuad(x,y)
#define _smuadx(x,y) __smuadx(x,y)
#define _smusd(x,y) __smusd(x,y)
#define _smusdx(x,y) __smusdx(x,y)
#define _smlsdx(x,y,z) __smlsdx(x,y,z)
#define _smlald(x,y,z) __smlald(x,y,z)
#define _usad8(x,y) __usad8(x,y)
#define _usada8(x,y,z) __usada8(x,y,z)

/******************************************************************************/
/* Rotate, sign extend and add halfwords                                      */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_sxtab16(int32_t x, int8_t y, int8_t z)
{
    int32_t res = 0;
    switch (z)
    {
        case 0:
            __asm  ("SXTAB16 %0, %1, %2" : "=r" (res) : "r" (x), "r" (y) : );
            break;
        case 8:
            __asm  ("SXTAB16 %0, %1, %2, ROR #8" : "=r" (res) : "r" (x), "r" (y) : );
            break;
        case 16:
            __asm  ("SXTAB16 %0, %1, %2, ROR #16" : "=r" (res) : "r" (x), "r" (y) : );
            break;
        case 24:
            __asm  ("SXTAB16 %0, %1, %2, ROR #24" : "=r" (res) : "r" (x), "r" (y) : );
            break;
    }
    return res;
}

/******************************************************************************/
/* Rotate, zero extend and add halfwords                                      */
/******************************************************************************/
static __inline__ uint32_t __attribute__((always_inline))
_uxtab16(uint32_t x, uint8_t y, uint8_t z)
{
    uint32_t res = 0;
    switch (z)
    {
        case 0:
            __asm  ("UXTAB16 %0, %1, %2" : "=r" (res) : "r" (x), "r" (y) : );
            break;
        case 8:
            __asm  ("UXTAB16 %0, %1, %2, ROR #8" : "=r" (res) : "r" (x), "r" (y) : );
            break;
        case 16:
            __asm  ("UXTAB16 %0, %1, %2, ROR #16" : "=r" (res) : "r" (x), "r" (y) : );
            break;
        case 24:
            __asm  ("UXTAB16 %0, %1, %2, ROR #24" : "=r" (res) : "r" (x), "r" (y) : );
            break;
    }
    return res;
}

/******************************************************************************/
/* Extend 8bit to 32 bit signed, with add                                     */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_sxtab(int32_t x, int32_t y, int32_t z)
{
    int32_t res = 0;
    switch (z)
    {
        case 0:
            __asm  ("SXTAB %0, %1, %2" : "=r" (res) : "r" (x), "r" (y) : );
            break;
        case 8:
            __asm  ("SXTAB %0, %1, %2, ROR #8" : "=r" (res) : "r" (x), "r" (y) : );
            break;
        case 16:
            __asm  ("SXTAB %0, %1, %2, ROR #16" : "=r" (res) : "r" (x), "r" (y) : );
            break;
        case 24:
            __asm  ("SXTAB %0, %1, %2, ROR #24" : "=r" (res) : "r" (x), "r" (y) : );
            break;
    }
    return res;
}

/******************************************************************************/
/* Extend 16bit to 32 bit signed, with add                                    */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_sxtah(int32_t x, int32_t y, int32_t z)
{
    int32_t res = 0;
    switch (z)
    {
        case 0:
            __asm  ("SXTAH %0, %1, %2" : "=r" (res) : "r" (x), "r" (y) : );
            break;
        case 8:
            __asm  ("SXTAH %0, %1, %2, ROR #8" : "=r" (res) : "r" (x), "r" (y) : );
            break;
        case 16:
            __asm  ("SXTAH %0, %1, %2, ROR #16" : "=r" (res) : "r" (x), "r" (y) : );
            break;
        case 24:
            __asm  ("SXTAH %0, %1, %2, ROR #24" : "=r" (res) : "r" (x), "r" (y) : );
            break;
    }
    return res;
}

/******************************************************************************/
/* Extend 8bit to 32 bit unsigned, with add                                   */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_uxtab(int32_t x, int32_t y, int32_t z)
{
    int32_t res = 0;
    switch (z)
    {
        case 0:
            __asm  ("UXTAB %0, %1, %2" : "=r" (res) : "r" (x), "r" (y) : );
            break;
        case 8:
            __asm  ("UXTAB %0, %1, %2, ROR #8" : "=r" (res) : "r" (x), "r" (y) : );
            break;
        case 16:
            __asm  ("UXTAB %0, %1, %2, ROR #16" : "=r" (res) : "r" (x), "r" (y) : );
            break;
        case 24:
            __asm  ("UXTAB %0, %1, %2, ROR #24" : "=r" (res) : "r" (x), "r" (y) : );
            break;
    }
    return res;
}

/******************************************************************************/
/* Extend 16bit to 32 bit unsigned, with add                                  */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_uxtah(int32_t x, int32_t y, int32_t z)
{
    int32_t res = 0;
    switch (z)
    {
        case 0:
            __asm  ("UXTAH %0, %1, %2" : "=r" (res) : "r" (x), "r" (y) : );
            break;
        case 8:
            __asm  ("UXTAH %0, %1, %2, ROR #8" : "=r" (res) : "r" (x), "r" (y) : );
            break;
        case 16:
            __asm  ("UXTAH %0, %1, %2, ROR #16" : "=r" (res) : "r" (x), "r" (y) : );
            break;
        case 24:
            __asm  ("UXTAH %0, %1, %2, ROR #24" : "=r" (res) : "r" (x), "r" (y) : );
            break;
    }
    return res;
}

/******************************************************************************/
/* Sign extend two bytes                                                      */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_sxtb16(int8_t x, int8_t y)
{
    int32_t res = 0;
    switch (y)
    {
        case 0:
            __asm  ("SXTB16 %0, %1" : "=r" (res) : "r" (x) : );
            break;
        case 8:
            __asm  ("SXTB16 %0, %1, ROR #8" : "=r" (res) : "r" (x) : );
            break;
        case 16:
            __asm  ("SXTB16 %0, %1, ROR #16" : "=r" (res) : "r" (x) : );
            break;
        case 24:
            __asm  ("SXTB16 %0, %1, ROR #24" : "=r" (res) : "r" (x) : );
            break;
    }
    return res;
}

/******************************************************************************/
/* Zero extend two bytes                                                      */
/******************************************************************************/
static __inline__ uint32_t __attribute__((always_inline))
_uxtb16(uint8_t x, uint8_t y)
{
    uint32_t res = 0;
    switch (y)
    {
        case 0:
            __asm  ("UXTB16 %0, %1" : "=r" (res) : "r" (x) : );
            break;
        case 8:
            __asm  ("UXTB16 %0, %1, ROR #8" : "=r" (res) : "r" (x) : );
            break;
        case 16:
            __asm  ("UXTB16 %0, %1, ROR #16" : "=r" (res) : "r" (x) : );
            break;
        case 24:
            __asm  ("UXTB16 %0, %1, ROR #24" : "=r" (res) : "r" (x) : );
            break;
    }
    return res;
}

/******************************************************************************/
/* Signed multiply, add and accumulate                                        */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_smmla(int32_t x, int32_t y, int32_t z)
{
    int32_t res = 0;
    __asm volatile ("SMMLA %0, %1, %2, %3" : "=r" (res) : "r" (x), "r" (y), "r" (z) : );
    return res;
}

/******************************************************************************/
/* Signed multiply, round product, add and accumulate                         */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_smmlar(int32_t x, int32_t y, int32_t z)
{
    int32_t res = 0;
    __asm volatile ("SMMLAR %0, %1, %2, %3" : "=r" (res) : "r" (x), "r" (y), "r" (z) : );
    return res;
}

/******************************************************************************/
/* Signed multiply, subtract from accumulate                                  */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_smmls(int32_t x, int32_t y, int32_t z)
{
    int32_t res = 0;
    __asm volatile ("SMMLS %0, %1, %2, %3" : "=r" (res) : "r" (x), "r" (y), "r" (z) : );
    return res;
}

/******************************************************************************/
/* Signed multiply, round product, subtract from accumulate                   */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_smmlsr(int32_t x, int32_t y, int32_t z)
{
    int32_t res = 0;
    __asm volatile ("SMMLSR %0, %1, %2, %3" : "=r" (res) : "r" (x), "r" (y), "r" (z) : );
    return res;
}

/******************************************************************************/
/* Signed multiply and store top word                                         */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_smmul(int32_t x, int32_t y)
{
    int32_t res = 0;
    __asm  ("SMMUL %0, %1, %2" : "=r" (res) : "r" (x), "r" (y) : );
    return res;
}

/******************************************************************************/
/* Signed multiply, round  and store top word                                 */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_smmulr(int32_t x, int32_t y)
{
    int32_t res = 0;
    __asm  ("SMMULR %0, %1, %2" : "=r" (res) : "r" (x), "r" (y) : );
    return res;
}

/******************************************************************************/
/* Unsigned multiply, store entire result                                     */
/******************************************************************************/
static __inline__ int64_t __attribute__((always_inline))
_umaal(int64_t x, int32_t y, int32_t z)
{
    int32_t x_lo = x & 0xFFFFFFFF;
    int32_t x_hi = (x >> 8) & 0xFFFFFFFF;
    int64_t res = 0;
    __asm  ("UMAAL %0, %1, %2, %3" : : "r" (x_lo), "r" (x_hi), "r" (y), "r" (z) : );
    res = (int64_t)x_lo & ((int64_t)x_hi << 8);
    return res;
}

/******************************************************************************/
/* Combine bottom halfword with shifted top halfword                          */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_pkhbt(int32_t x, int32_t y, int32_t z)
{
    int32_t res = 0;
    int32_t shifted = y << z;
    __asm ("PKHBT %0, %1, %2" : "=r" (res) : "r" (x), "r" (shifted) : );
    return res;
}

/******************************************************************************/
/* Combine top halfword with shifted bottom halfword                          */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_pkhtb(int32_t x, int32_t y, int32_t z)
{
    int32_t res = 0;
    int32_t shifted = y >> z;
    __asm ("PKHTB %0, %1, %2" : "=r" (res) : "r" (x), "r" (shifted) : );
    return res;
}

#endif /* __ARM_FEATURE_SIMD32 */

/******************************************************************************/
/* Normalization                                                              */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_norm(int32_t x)
{
    return __clz(x);
}

static __inline__ int16_t __attribute__((always_inline))
_shr16(int16_t var1, int16_t var2);

static __inline__ int32_t __attribute__((always_inline))
_shr(int32_t var1, int16_t var2);

/******************************************************************************/
/* _SHL16 - Saturating left shift of a short int.                             */
/******************************************************************************/
static __inline__ int16_t __attribute__((always_inline))
_shl16(int16_t var1, int16_t var2)
{
   int result;

   if (var1 ==   0)  return 0;
   if (var2 >=  15)  return (var1 < 0) ? INT16_MIN : INT16_MAX;
   if (var2 <= -15)  return (var1 < 0) ? -1     : 0;
   if (var2 <    0)  return _shr16(var1, -var2);

   result = var1 << var2;

   if (result != (int16_t)result)  return (var1 < 0) ? INT16_MIN : INT16_MAX;
   return result;
}

/******************************************************************************/
/* _SHR16 - Saturating right shift of a short int.                            */
/******************************************************************************/
static __inline__ int16_t __attribute__((always_inline))
_shr16(int16_t var1, int16_t var2)
{
   if (var1 ==   0)  return 0;
   if (var2 >=  15)  return (var1 < 0) ? -1 : 0;
   if (var2 <= -15)  return (var1 < 0) ? INT16_MIN : INT16_MAX;
   if (var2 <    0)  return _shl16(var1, -var2);

   return var1 >> var2;
}

/******************************************************************************/
/* _SHL - Saturating left shift.                                              */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_shl(int32_t var1, int16_t var2)
{
   int32_t tmp;

   if (var1 ==   0)  return 0;
   if (var2 >=  31)  return (var1 < 0) ? INT32_MIN : INT32_MAX;
   if (var2 <= -31)  return (var1 < 0) ? -1     : 0;
   if (var2 <    0)  return _shr(var1, -var2);

   tmp = var1 >> (31 - var2);
   if (var1 < 0) { if (tmp != -1)  return INT32_MIN; }
   else            if (tmp !=  0)  return INT32_MAX;

   return var1 << var2;
}

/******************************************************************************/
/* _SHR - Saturating right shift.                                             */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_shr(int32_t var1, int16_t var2)
{
   if (var1 ==   0)  return 0;
   if (var2 >=  31)  return (var1 < 0) ? -1 : 0;
   if (var2 <= -31)  return (var1 < 0) ? INT32_MIN : INT32_MAX;
   if (var2 <    0)  return _shl(var1, -var2);

   return var1 >> var2;
}

/******************************************************************************/
/* _ABS16_S - Saturating absolute value of a short int.                       */
/******************************************************************************/
static __inline__ int16_t __attribute__((always_inline))
_abs16_s(int16_t var1)
{
   if (var1 == INT16_MIN)  return INT16_MAX;
   return (var1 < 0) ? -var1 : var1;
}

/******************************************************************************/
/* _ABS_S - Saturating absolute value.                                        */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_abs_s(int32_t var1)
{
   if (var1 == INT32_MIN)  return INT32_MAX;
   return (var1 < 0) ? -var1 : var1;
}

/******************************************************************************/
/* Extend 8bit to 32 bit signed                                               */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_sxtb(int32_t x, int32_t y)
{
    int32_t res = 0;
    switch (y)
    {
        case 0:
            __asm  ("SXTB %0, %1" : "=r" (res) : "r" (x) : );
            break;
#if __ARM_ARCH > 6
        case 8:
            __asm  ("SXTB %0, %1, ROR #8" : "=r" (res) : "r" (x) : );
            break;
        case 16:
            __asm  ("SXTB %0, %1, ROR #16" : "=r" (res) : "r" (x) : );
            break;
        case 24:
            __asm  ("SXTB %0, %1, ROR #24" : "=r" (res) : "r" (x) : );
            break;
#endif /* __ARM_ARCH > 6 */
    }
    return res;
}

/******************************************************************************/
/* Extend 16bit to 32 bit signed                                              */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_sxth(int32_t x, int32_t y)
{
    int32_t res = 0;
    switch (y)
    {
        case 0:
            __asm  ("SXTH %0, %1" : "=r" (res) : "r" (x) : );
            break;
#if __ARM_ARCH > 6
        case 8:
            __asm  ("SXTH %0, %1, ROR #8" : "=r" (res) : "r" (x) : );
            break;
        case 16:
            __asm  ("SXTH %0, %1, ROR #16" : "=r" (res) : "r" (x) : );
            break;
        case 24:
            __asm  ("SXTH %0, %1, ROR #24" : "=r" (res) : "r" (x) : );
            break;
#endif /* __ARM_ARCH > 6 */
    }
    return res;
}

/******************************************************************************/
/* Extend 8bit to 32 bit unsigned                                             */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_uxtb(int32_t x, int32_t y)
{
    int32_t res = 0;
    switch (y)
    {
        case 0:
            __asm  ("UXTB %0, %1" : "=r" (res) : "r" (x) : );
            break;
#if __ARM_ARCH > 6
        case 8:
            __asm  ("UXTB %0, %1, ROR #8" : "=r" (res) : "r" (x) : );
            break;
        case 16:
            __asm  ("UXTB %0, %1, ROR #16" : "=r" (res) : "r" (x) : );
            break;
        case 24:
            __asm  ("UXTB %0, %1, ROR #24" : "=r" (res) : "r" (x) : );
            break;
#endif /* __ARM_ARCH > 6 */
    }
    return res;
}

/******************************************************************************/
/* Extend 16bit to 32 bit unsigned                                            */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_uxth(int32_t x, int32_t y)
{
    int32_t res = 0;
    switch (y)
    {
        case 0:
            __asm  ("UXTH %0, %1" : "=r" (res) : "r" (x) : );
            break;
#if __ARM_ARCH > 6
        case 8:
            __asm  ("UXTH %0, %1, ROR #8" : "=r" (res) : "r" (x) : );
            break;
        case 16:
            __asm  ("UXTH %0, %1, ROR #16" : "=r" (res) : "r" (x) : );
            break;
        case 24:
            __asm  ("UXTH %0, %1, ROR #24" : "=r" (res) : "r" (x) : );
            break;
#endif /* __ARM_ARCH > 6 */
    }
    return res;
}

#if __ARM_ARCH > 6



/******************************************************************************/
/* Optionally Left shift and saturate                                         */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_ssatl(int32_t x, int32_t y, int32_t z)
{
    /* Can't be emulated by intrinsics because z must be constant */
    int32_t shifted = x << y;
    int32_t sat_min = -1 * (1 << (z - 1));
    int32_t sat_max = (1 << (z - 1)) - 1;
    int32_t res = shifted;
    if (shifted <= sat_min)
    {
        res = sat_min;
    }
    else if (shifted >= sat_max)
    {
        res = sat_max;
    }
    return res;
}

/******************************************************************************/
/* Optionally Left shift and saturate                                         */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_usatl(int32_t x, int32_t y, int32_t z)
{
    /* Can't be emulated by intrinsics because z must be constant */
    int32_t shifted = x << y;
    int32_t sat_min = 0;
    int32_t sat_max = (1 << z) - 1;
    int32_t res = shifted;
    if (shifted <= sat_min)
    {
        res = sat_min;
    }
    else if (shifted >= sat_max)
    {
        res = sat_max;
    }
    return res;
}

/******************************************************************************/
/* Optionally right shift and saturate                                        */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
_ssata(int32_t x, int32_t y, int32_t z)
{
    /* Can't be emulated by intrinsics because z must be constant */
    int32_t shifted = x >> y;
    int32_t sat_min = -1 * (1 << (z - 1));
    int32_t sat_max = (1 << (z - 1)) - 1;
    int32_t res = shifted;
    if (shifted <= sat_min)
    {
        res = sat_min;
    }
    else if (shifted >= sat_max)
    {
        res = sat_max;
    }
    return res;
}

/******************************************************************************/
/* Optionally right shift and saturate                                        */
/******************************************************************************/
static __inline__ uint32_t __attribute__((always_inline))
_usata(int32_t x, uint32_t y, uint32_t z)
{
    /* Can't be emulated by intrinsics because z must be constant */
    int32_t shifted = x >> y;
    int32_t sat_min = 0;
    int32_t sat_max = (1 << z) - 1;
    int32_t res = shifted;
    if (shifted <= sat_min)
    {
        res = sat_min;
    }
    else if (shifted >= sat_max)
    {
        res = sat_max;
    }
    return res;
}

#endif /* __ARM_ARCH > 6 */

#if ((__ARM_ARCH >= 6) && (__ARM_ARCH_PROFILE != 'M'))

/******************************************************************************/
/* Load double word exclusive                                                 */
/******************************************************************************/
static __inline__ uint32_t __attribute__((always_inline))
__ldrexd(void* x)
{
    return __builtin_arm_ldrexd(x);
}

/******************************************************************************/
/* Store double word exclusive                                                */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
__strexd(long long x, void* y)
{
    return __builtin_arm_strexd(x, y);
}

/******************************************************************************/
/* Set CPSR register, control and flag bytes                                  */
/******************************************************************************/
static __inline__ void __attribute__((always_inline))
_set_CPSR(uint32_t x)
{
    __asm volatile ("MSR CPSR_cf, %0" : : "r" (x) : );
}

/******************************************************************************/
/* Set CPSR register, flag bytes only                                         */
/******************************************************************************/
static __inline__ void __attribute__((always_inline))
_set_CPSR_flg(uint32_t x)
{
    uint32_t shifted = (x << 28);
    __asm volatile ("MSR CPSR_f, %0" : : "r" (shifted) : );
}

/******************************************************************************/
/* Return CPSR register                                                       */
/******************************************************************************/
static __inline__ uint32_t __attribute__((always_inline))
_get_CPSR(void)
{
    uint32_t res = 0;
    __asm volatile ("MRS %0, CPSR" :  "=r" (res) : : );
    return res;
}

/******************************************************************************/
/* Enable FIQ status bit and return CPSR                                      */
/******************************************************************************/
static __inline__ uint32_t __attribute__((always_inline))
_enable_FIQ(void)
{
    uint32_t res = 0;
    __asm volatile ("MRS %0, CPSR" : "=r" (res) : : );
    __asm volatile ("CPSIE F" : : : );
    return res;
}

/******************************************************************************/
/* Disable FIQ status bit and return CPSR                                     */
/******************************************************************************/
static __inline__ uint32_t __attribute__((always_inline))
_disable_FIQ(void)
{
    uint32_t res = 0;
    __asm volatile ("MRS %0, CPSR" : "=r" (res) : : );
    __asm volatile ("CPSID F" : : : );
    return res;
}

#endif /* ((__ARM_ARCH >= 6) && (__ARM_ARCH_PROFILE != 'M')) */

#if !((__ARM_ARCH_PROFILE == 'M') && (__ARM_ARCH == 6))

/******************************************************************************/
/* Load byte exclusive                                                        */
/******************************************************************************/
static __inline__ uint32_t __attribute__((always_inline))
__ldrexb(void* y)
{
    uint32_t res = 0;
    __asm volatile ("LDREXB %0, [%1]" : "=r" (res) : "r" (y) : );
    return res;
}

/******************************************************************************/
/* Load half word exclusive                                                   */
/******************************************************************************/
static __inline__ uint32_t __attribute__((always_inline))
__ldrexh(void* y)
{
    uint32_t res = 0;
    __asm volatile ("LDREXH %0, [%1]" : "=r" (res) : "r" (y) : );
    return res;
}

/******************************************************************************/
/* Load word exclusive                                                        */
/******************************************************************************/
static __inline__ uint32_t __attribute__((always_inline))
__ldrex(void* x)
{
    return __builtin_arm_ldrex((uint32_t*)x);
}

/******************************************************************************/
/* Store byte exclusive                                                       */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
__strexb(uint8_t x, void* y)
{
    int32_t res = 0;
    __asm volatile ("STREXB %0, %1, [%2]" : "=r" (res) : "r" (x), "r" (y) : );
    return res;
}

/******************************************************************************/
/* Store half word exclusive                                                  */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
__strexh(uint16_t x, void* y)
{
    int32_t res = 0;
    __asm volatile ("STREXH %0, %1, [%2]" : "=r" (res) : "r" (x), "r" (y) : );
    return res;
}

/******************************************************************************/
/* Store word exclusive                                                       */
/******************************************************************************/
static __inline__ int32_t __attribute__((always_inline))
__strex(uint32_t x, void* p)
{
    return __builtin_arm_strex(x,(uint32_t*)p);
}

#endif /* !((__ARM_ARCH_PROFILE == 'M') && (__ARM_ARCH == 6)) */

/******************************************************************************/
/* Data memory barrier                                                        */
/******************************************************************************/
static __inline__ void __attribute__((always_inline))
_dmb(void)
{
    __asm volatile ("DMB" : : );
}

/******************************************************************************/
/* Data synchronization barrier                                               */
/******************************************************************************/
static __inline__ void __attribute__((always_inline))
_dsb(void)
{
    __asm volatile ("DSB" : : );
}

/******************************************************************************/
/* Instruction synchronization barrier                                        */
/******************************************************************************/
static __inline__ void __attribute__((always_inline))
_isb(void)
{
    __asm volatile ("ISB" : : );
}

/******************************************************************************/
/* Call SWI                                                                   */
/******************************************************************************/
#define _call_swi(x) __asm volatile ("SVC %0" : : "i" (x) : );

/******************************************************************************/
/* Set the MSP register                                                       */
/******************************************************************************/
static __inline__ void __attribute__((always_inline))
__set_MSP(uint32_t x)
{
    __asm volatile ("MSR MSP, %0" : : "r" (x) : );
}

/******************************************************************************/
/* Return the MSP register                                                    */
/******************************************************************************/
static __inline__ uint32_t __attribute__((always_inline))
__get_MSP(void)
{
    uint32_t res = 0;
    __asm volatile ("MRS %0, MSP" :  "=r" (res) : : );
    return res;
}

/******************************************************************************/
/* Set the PRIMASK register                                                   */
/******************************************************************************/
static __inline__ uint32_t __attribute__((always_inline))
__set_PRIMASK(uint32_t x)
{
    uint32_t res = 0;
    __asm volatile ("MRS %0, PRIMASK" :  "=r" (res) : : );
    __asm volatile ("MSR PRIMASK, %0" : : "r" (x) : );
    return res;
}

/******************************************************************************/
/* Return the PRIMASK register                                                */
/******************************************************************************/
static __inline__ uint32_t __attribute__((always_inline))
__get_PRIMASK(void)
{
    uint32_t res = 0;
    __asm volatile ("MRS %0, PRIMASK" :  "=r" (res) : : );
    return res;
}

/******************************************************************************/
/* Set the interrupt priority                                                 */
/******************************************************************************/
#if __ARM_ARCH_PROFILE == 'M' && (__ARM_ARCH == 6 || __ARM_ARCH == 7)
static __inline__ uint32_t __attribute__((always_inline))
_set_interrupt_priority(uint32_t x)
{
    uint32_t res = 0;
    __asm volatile ("MRS %0, BASEPRI" : "=r" (res) : : );
    __asm volatile ("MSR BASEPRI, %0" : : "r" (x) : );
    return res;
}
#endif

/******************************************************************************/
/* The following mappings are defined in arm_acle.h                           */
/******************************************************************************/
/* The current version of the TI ARM LLVM compiler does not support the       */
/* following coprocessor intrinsics at this time.                             */
/******************************************************************************/
/*
#define __MCR(x,y,z,a,b,c) __arm_mcr(x,y,z,a,b,c)
#define __MRC(x,y,z,a,b) __arm_mrc(x,y,z,a,b)
#define __MCR2(x,y,z,a,b,c) __arm_mcr2(x,y,z,a,b,c)
#define __MRC2(x,y,z,a,b) __arm_mrc2(x,y,z,a,b)
#define __MCRR(x,y,z,a) __arm_mcrr(x,y,z,a)
#define __MRRC(x,y,z) __arm_mrrc(x,y,z)
#define __MCRR2(x,y,z,a) __arm_mcrr2(x,y,z,a)
#define __MRRC2(x,y,z) __arm_mrrc2(x,y,z)
*/

/******************************************************************************/
/* Enable IRQ status bit and return CPSR                                      */
/******************************************************************************/
static __inline__ uint32_t __attribute__((always_inline))
_enable_IRQ(void)
{
#if __ARM_ARCH_PROFILE == 'M' && (__ARM_ARCH == 6 || __ARM_ARCH == 7)
    uint32_t primask = __get_PRIMASK();
    __asm volatile ("CPSIE I" : : : );
    return primask;
#else
    return 0;
#endif
}

/******************************************************************************/
/* Disable IRQ status bit and return CPSR                                     */
/******************************************************************************/
static __inline__ uint32_t __attribute__((always_inline))
_disable_IRQ(void)
{
#if __ARM_ARCH_PROFILE == 'M' && (__ARM_ARCH == 6 || __ARM_ARCH == 7)
    uint32_t primask = __get_PRIMASK();
    __asm volatile ("CPSID I" : : : );
    return primask;
#else
    return 0;
#endif
}

/******************************************************************************/
/* Enable interrupts                                                          */
/******************************************************************************/
static __inline__ uint32_t __attribute__((always_inline))
_enable_interrupts(void)
{
#if __ARM_ARCH_PROFILE == 'M' && __ARM_ARCH == 6
    return _enable_IRQ();
#elif __ARM_ARCH_PROFILE == 'M' && __ARM_ARCH == 7
    uint32_t res = 0;
    __asm volatile ("MRS %0, FAULTMASK" : "=r" (res) : : );
    __asm volatile ("CPSIE F" : : : );
    return res;
#elif __ARM_ARCH >= 7
    uint32_t res = _get_CPSR();
     __asm volatile ("CPSIE IF" : : : );
    return res;
#else
    return 0;
#endif
}

/******************************************************************************/
/* Disable interrupts                                                         */
/******************************************************************************/
static __inline__ uint32_t __attribute__((always_inline))
_disable_interrupts(void)
{
#if __ARM_ARCH_PROFILE == 'M' && __ARM_ARCH == 6
    return _disable_IRQ();
#elif __ARM_ARCH_PROFILE == 'M' && __ARM_ARCH == 7
    uint32_t res = 0;
    __asm volatile ("MRS %0, FAULTMASK" : "=r" (res) : : );
    __asm volatile ("CPSID F" : : : );
    return res;
#elif __ARM_ARCH >= 7
    uint32_t res = _get_CPSR();
     __asm volatile ("CPSID IF" : : : );
    return res;
#else
    return 0
#endif
}

/******************************************************************************/
/* Restore interrupts                                                         */
/******************************************************************************/
static __inline__ void __attribute__((always_inline))
_restore_interrupts(uint32_t x)
{
#if __ARM_ARCH_PROFILE == 'M' && __ARM_ARCH == 6
    __asm volatile ("MSR PRIMASK, %0" : : "r" (x) : );
#elif __ARM_ARCH_PROFILE == 'M' && __ARM_ARCH == 7
    __asm volatile ("MSR FAULTMASK, %0" : : "r" (x) : );
#elif __ARM_ARCH >= 7
    __asm volatile ("MSR CPSR_fc, %0" : : "r" (x) : );
#endif
}

/******************************************************************************/
/* Delay cycles intrinsic is not supported.                                   */
/******************************************************************************/
/* static __inline__ void __attribute__((always_inline))
** __delay_cycles(uint32_t x)
*/

#endif /* _TI_COMPAT_H */
