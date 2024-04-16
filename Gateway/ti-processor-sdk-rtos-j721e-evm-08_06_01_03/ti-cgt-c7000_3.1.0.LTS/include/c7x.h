/*****************************************************************************/
/*  C7X.H                                                                    */
/*                                                                           */
/* Copyright (c) 2015 Texas Instruments Incorporated                         */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/
#ifndef __C7X_H
#define __C7X_H
#define __C7X_H_INCLUDE__

#include <stdbool.h>

#define __RD           __attribute__((memread))
#define __WR           __attribute__((memwrite))
#define __IMPURE       __attribute__((impure))
#define __OVERLOADABLE __attribute__((overloadable))
#define __BIF    __attribute__((builtin))
#define __BIFM   __BIF __IMPURE
#define __OVBIF  __BIF __OVERLOADABLE
#define __OVBIFM __BIFM __OVERLOADABLE

#define __CST(lb, ub) __attribute__((constrange((lb), (ub))))
#define __CST_RANGE __CST(0, 0x7ffffff)

/*****************************************************************************/
/* VECTOR POINTER CONVERSION INTRINSICS                                      */
/* (Deprecated in favor of C-style casts)                                    */
/*                                                                           */
/* These intrinsics are used to convert between vector type pointers and     */
/* component element type pointers. Use of these intrinsics is required when */
/* using the host emulation package and are defined here for compatiblity    */
/* when porting programs to the C7000 compiler.                              */
/*****************************************************************************/
/* C-style cast: uchar64* p = (uchar64*)(pointer);                           */
#define stov_ptr(type, addr) (type*)(addr)
/* C-style cast: uint8_t *p = (uint8_t*)(pointer);                           */
#define vtos_ptr(type, addr) (type*)(addr)
/* C-style cast: cint* p = (cint*)(pointer);                                 */
#define stoc_ptr(type, addr) (type*)(addr)
/* C-style cast: int32_t* p = (int32_t*)(pointer);                           */
#define ctos_ptr(type, addr) (type*)(addr)

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*****************************************************************************/
/* Include the CR (Control Register) set.                                    */
/*****************************************************************************/
#include <c7x_cr.h>

/*****************************************************************************/
/* Include the ECR (Extended Control Register) set.                          */
/*****************************************************************************/
#include <c7x_ecr.h>

/*****************************************************************************/
/* Include low-level "vpred" operations, some of which are overloaded below. */
/*****************************************************************************/
#include <c7x_vpred.h>

/*****************************************************************************/
/* FLAG STATUS REGISTER (FSR) CONTROL REGISTER ACCESS                        */
/*                                                                           */
/* This API is provided to assist the user in extracting pertinent floating  */
/* point status bit information for floating point instructions.  The result */
/* is an 8bit value containing the following fields:                         */
/*                                                                           */
/* Bit 7: SAT   - NOT SUPPORTED FOR C7000 OPERATIONS                         */
/* Bit 6: UNORD - Compare result is unordered Floating Point Flag            */
/* Bit 5: DEN   - Source is a Denorm Floating Point Flag                     */
/* Bit 4: INEX  - Result is inexact Floating Point Flag                      */
/* Bit 3: UNDER - Result is underflow Floating Point Flag                    */
/* Bit 2: OVER  - Result is overflow Floating Point Flag                     */
/* Bit 1: DIV0  - Divide by zero Floating Point Flag                         */
/* Bit 0: INVAL - Invalid Operations Floating Point Flag                     */
/*                                                                           */
/* Please specify the scalar or vector floating point type as an argument    */
/* corresponding to the size of the pertinent floating point data, and the   */
/* API will return an "OR" of the data bits for all pertinent vector lanes   */
/* in a single, 8bit chunk of data.                                          */
/*                                                                           */
/*        e.g.:                                                              */
/*              float4 a = ... ;                                             */
/*              float4 b = ... ;                                             */
/*              float4 c = a * b;                                            */
/*              uint8_t fsr_val = __get_FSR(float4);                         */
/*                                                                           */
/* NOTE: Accessing the SAT-bit is NOT SUPPORTED for C7000 operations.  It is */
/* only supported for C6000 legacy operations to facilitate compatibility on */
/* legacy C6000 source code (see c6x_migration.h).                           */
/*****************************************************************************/
#define __get_FSR(type) __get_fsr_##type(sizeof(type))

/*****************************************************************************/
/* GTSC CONTROL REGISTER ACCESS                                              */
/*****************************************************************************/
#define __get_GTSC(opt) __get_indexed(__GTSC, opt)

/*****************************************************************************/
/* INSTRUCTION CACHE FLUSH AND REFRESH                                       */
/*****************************************************************************/
typedef enum __attribute__((__packed__))
{
    __IINVAL_MMUNONE = 0,
    __IINVAL_MMU0    = 1,
    __IINVAL_MMU1    = 2,
    __IINVAL_MMUALL  = 3
} __IINVAL_TYPE;
void __BIFM __instr_cache_invalidate(__CST(0,3) __IINVAL_TYPE);

/*****************************************************************************/
/* BOOLEAN VECTOR CREATION                                                   */
/*                                                                           */
/* Create a boolean vector as a mask of 'k' consecutive booleans set to true */
/*****************************************************************************/
/*

bool2  = __mask_bool2(uint);
bool2  = __mask_bool2((uchar)(k={0-2}));

bool3  = __mask_bool3(uint);
bool3  = __mask_bool3((uchar)(k={0-3}));

bool4  = __mask_bool4(uint);
bool4  = __mask_bool4((uchar)(k={0-4}));

bool8  = __mask_bool8(uint);
bool8  = __mask_bool8((uchar)(k={0-8}));

bool16 = __mask_bool16(uint);
bool16 = __mask_bool16((uchar)(k={0-16}));

bool32 = __mask_bool32(uint);
bool32 = __mask_bool32((uchar)(k={0-32}));

#if __C7X_VEC_SIZE_BITS__ >= 512
bool64 = __mask_bool64(uint);
bool64 = __mask_bool64((uchar)(k={0-64}));
#endif

*/

#define __mask_bool2(a)  __overload("__mask_bool2",(a))((a))
#define __mask_bool3(a)  __overload("__mask_bool3",(a))((a))
#define __mask_bool4(a)  __overload("__mask_bool4",(a))((a))
#define __mask_bool8(a)  __overload("__mask_bool8",(a))((a))
#define __mask_bool16(a) __overload("__mask_bool16",(a))((a))
#define __mask_bool32(a) __overload("__mask_bool32",(a))((a))
#if __C7X_VEC_SIZE_BITS__ >= 512
#define __mask_bool64(a) __overload("__mask_bool64",(a))((a))
#endif

/*****************************************************************************/
/* BOOLEAN VECTOR CONVERSION                                                 */
/*****************************************************************************/
__bool2  __OVBIF __reduce_bool2(__bool3);
__bool2  __OVBIF __reduce_bool2(__bool4);
__bool2  __OVBIF __reduce_bool2(__bool8);
__bool2  __OVBIF __reduce_bool2(__bool16);
__bool2  __OVBIF __reduce_bool2(__bool32);
#if __C7X_VEC_SIZE_BITS__ >= 512
__bool2  __OVBIF __reduce_bool2(__bool64);
#endif

__bool3  __OVBIF __extend_bool3(__bool2);
__bool3  __OVBIF __reduce_bool3(__bool4);
__bool3  __OVBIF __reduce_bool3(__bool8);
__bool3  __OVBIF __reduce_bool3(__bool16);
__bool3  __OVBIF __reduce_bool3(__bool32);
#if __C7X_VEC_SIZE_BITS__ >= 512
__bool3  __OVBIF __reduce_bool3(__bool64);
#endif

__bool4  __OVBIF __extend_bool4(__bool2);
__bool4  __OVBIF __extend_bool4(__bool3);
__bool4  __OVBIF __reduce_bool4(__bool8);
__bool4  __OVBIF __reduce_bool4(__bool16);
__bool4  __OVBIF __reduce_bool4(__bool32);
#if __C7X_VEC_SIZE_BITS__ >= 512
__bool4  __OVBIF __reduce_bool4(__bool64);
#endif

__bool8  __OVBIF __extend_bool8(__bool2);
__bool8  __OVBIF __extend_bool8(__bool3);
__bool8  __OVBIF __extend_bool8(__bool4);
__bool8  __OVBIF __reduce_bool8(__bool16);
__bool8  __OVBIF __reduce_bool8(__bool32);
#if __C7X_VEC_SIZE_BITS__ >= 512
__bool8  __OVBIF __reduce_bool8(__bool64);
#endif

__bool16  __OVBIF __extend_bool16(__bool2);
__bool16  __OVBIF __extend_bool16(__bool3);
__bool16  __OVBIF __extend_bool16(__bool4);
__bool16  __OVBIF __extend_bool16(__bool8);
__bool16  __OVBIF __reduce_bool16(__bool32);
#if __C7X_VEC_SIZE_BITS__ >= 512
__bool16  __OVBIF __reduce_bool16(__bool64);
#endif

__bool32  __OVBIF __extend_bool32(__bool2);
__bool32  __OVBIF __extend_bool32(__bool3);
__bool32  __OVBIF __extend_bool32(__bool4);
__bool32  __OVBIF __extend_bool32(__bool8);
__bool32  __OVBIF __extend_bool32(__bool16);
#if __C7X_VEC_SIZE_BITS__ >= 512
__bool32  __OVBIF __reduce_bool32(__bool64);
#endif

#if __C7X_VEC_SIZE_BITS__ >= 512
__bool64  __OVBIF __extend_bool64(__bool2);
__bool64  __OVBIF __extend_bool64(__bool3);
__bool64  __OVBIF __extend_bool64(__bool4);
__bool64  __OVBIF __extend_bool64(__bool8);
__bool64  __OVBIF __extend_bool64(__bool16);
__bool64  __OVBIF __extend_bool64(__bool32);
#endif

__bool2  __OVBIF __create_bool2(__ulong);
__bool3  __OVBIF __create_bool3(__ulong);
__bool4  __OVBIF __create_bool4(__ulong);
__bool8  __OVBIF __create_bool8(__ulong);
__bool16  __OVBIF __create_bool16(__ulong);
__bool32  __OVBIF __create_bool32(__ulong);
#if __C7X_VEC_SIZE_BITS__ >= 512
__bool64  __OVBIF __create_bool64(__ulong);
#endif

#define __reduce_bool2(a)  __overload("__reduce_bool2",(a))((a))
#define __reduce_bool3(a)  __overload("__reduce_bool3",(a))((a))
#define __reduce_bool4(a)  __overload("__reduce_bool4",(a))((a))
#define __reduce_bool8(a)  __overload("__reduce_bool8",(a))((a))
#define __reduce_bool16(a)  __overload("__reduce_bool16",(a))((a))
#if __C7X_VEC_SIZE_BITS__ >= 512
#define __reduce_bool32(a)  __overload("__reduce_bool32",(a))((a))
#endif

#define __extend_bool3(a)  __overload("__extend_bool3",(a))((a))
#define __extend_bool4(a)  __overload("__extend_bool4",(a))((a))
#define __extend_bool8(a)  __overload("__extend_bool8",(a))((a))
#define __extend_bool16(a)  __overload("__extend_bool16",(a))((a))
#define __extend_bool32(a)  __overload("__extend_bool32",(a))((a))
#if __C7X_VEC_SIZE_BITS__ >= 512
#define __extend_bool64(a)  __overload("__extend_bool64",(a))((a))
#endif

#define __create_bool2(a)  __overload("__create_bool2",(a))((a))
#define __create_bool3(a)  __overload("__create_bool3",(a))((a))
#define __create_bool4(a)  __overload("__create_bool4",(a))((a))
#define __create_bool8(a)  __overload("__create_bool8",(a))((a))
#define __create_bool16(a)  __overload("__create_bool16",(a))((a))
#define __create_bool32(a)  __overload("__create_bool32",(a))((a))
#if __C7X_VEC_SIZE_BITS__ >= 512
#define __create_bool64(a)  __overload("__create_bool64",(a))((a))
#endif

__ulong __OVBIF __create_scalar(__bool2);
__ulong __OVBIF __create_scalar(__bool3);
__ulong __OVBIF __create_scalar(__bool4);
__ulong __OVBIF __create_scalar(__bool8);
__ulong __OVBIF __create_scalar(__bool16);
__ulong __OVBIF __create_scalar(__bool32);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong __OVBIF __create_scalar(__bool64);
#endif

#define __create_scalar(a)  __overload("__create_scalar",(a))((a))

/*****************************************************************************/
/* STREAMING ENGINE / ADDRESS GENERATOR COMMON CONTROLS                      */
/*                                                                           */
/* PLEASE REFER TO c7x_strm.h (INCLUDED BELOW) FOR MORE INFORMATION ON SETUP */
/* AND USE                                                                   */
/*****************************************************************************/
/* LOOKUP TABLE / HISTOGRAM COMMON CONTROLS                                  */
/*                                                                           */
/* PLEASE REFER TO c7x_luthist.h (INCLUDED BELOW) FOR MORE INFORMATION ON    */
/* SETUP AND USE                                                             */
/*****************************************************************************/

/*****************************************************************************/
/*                                                                           */
/* Vector Data Types in TI Compiler                                          */
/*                                                                           */
/* A vector data type name consists of the following:                        */
/* - main part: char, short, int, long, float, double                        */
/* - prefix: 'c' for complex (TI extension!!)                                */
/* - prefix: 'u' for unsigned, can not be specified for complex vectors      */
/* - suffix: digits for number of elements in the vector                     */
/*           (valid values: 2,3,4,8,16,32,64)                                */
/*                                                                           */
/*                                                                           */
/* e.g. uint2: a 64-bit vector consisting of 2 unsigned int elements         */
/* e.g. char4: a 32-bit vector consisting of 4 signed chars                  */
/* e.g. cfloat: a 64-bit complex float consisting of a float real (R) and    */
/*              a float imaginary (I)                                        */
/* e.g. cshort4: a 128-bit vector consisting of 4 complex signed shorts      */
/*                                                                           */
/* - The TI compiler defines extended width vectors up to and including      */
/*   512-bits, in addition to vectors with up to 16 elements.                */
/*                                                                           */
/* Note on complex:                                                          */
/*   Complex values on C7000 follow C99 Standard rules in memory, with the   */
/*   real part in mem[0] and imaginary part in mem[1].                       */
/*                                                                           */
/*   Two accessors are available.                                            */
/*    - .r() returns the real parts of each complex in a vector              */
/*    - .i() returns the imaginary parts of each complex in a vector         */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
/* The following native vector types are defined by the compiler as of v1.0  */
/* of the C7000 compiler.                                                    */
/* In strict mode, only vector types beginning with double underscores are   */
/* defined, otherwise equivalents with no underscores may be used.           */
/*****************************************************************************/
/*****************************************************************************/
/* Built-in base types                                                       */
/* NOTE: When using host emulation, a host emulation compatible type must    */
/*       also be used.                                                       */
/*****************************************************************************/
/* Native cl7x type:            Host emulation compatible type:              */
/* signed char                  int8_t                                       */
/* unsigned char                uint8_t                                      */
/* short                        int16_t                                      */
/* unsigned short               uint16_t                                     */
/* int                          int32_t                                      */
/* unsigned int                 uint32_t                                     */
/* long                         int64_t                                      */
/* unsigned long                uint64_t                                     */
/* float                        float                                        */
/* double                       double                                       */
/*****************************************************************************/
/* Non-complex vector data types                                             */
/*****************************************************************************/
/* __uchar  is equivalent to unsigned char                                   */
/* __ushort is equivalent to unsigned short                                  */
/* __uint   is equivalent to unsigned int                                    */
/* __ulong  is equivalent to unsigned long                                   */
/*                                                                           */
/* __char2  is equivalent to a vector of 2  signed char                      */
/* __char3  is equivalent to a vector of 3  signed char                      */
/* __char4  is equivalent to a vector of 4  signed char                      */
/* __char8  is equivalent to a vector of 8  signed char                      */
/* __char16 is equivalent to a vector of 16 signed char                      */
/* __char32 is equivalent to a vector of 32 signed char                      */
/* __char64 is equivalent to a vector of 64 signed char                      */
/*                                                                           */
/* __uchar2  is equivalent to a vector of 2  __uchar                         */
/* __uchar3  is equivalent to a vector of 3  __uchar                         */
/* __uchar4  is equivalent to a vector of 4  __uchar                         */
/* __uchar8  is equivalent to a vector of 8  __uchar                         */
/* __uchar16 is equivalent to a vector of 16 __uchar                         */
/* __uchar32 is equivalent to a vector of 32 __uchar                         */
/* __uchar64 is equivalent to a vector of 64 __uchar                         */
/*                                                                           */
/* __short2  is equivalent to a vector of 2  short                           */
/* __short3  is equivalent to a vector of 3  short                           */
/* __short4  is equivalent to a vector of 4  short                           */
/* __short8  is equivalent to a vector of 8  short                           */
/* __short16 is equivalent to a vector of 16 short                           */
/* __short32 is equivalent to a vector of 32 short                           */
/*                                                                           */
/* __ushort2  is equivalent to a vector of 2  __ushort                       */
/* __ushort3  is equivalent to a vector of 3  __ushort                       */
/* __ushort4  is equivalent to a vector of 4  __ushort                       */
/* __ushort8  is equivalent to a vector of 8  __ushort                       */
/* __ushort16 is equivalent to a vector of 16 __ushort                       */
/* __ushort32 is equivalent to a vector of 32 __ushort                       */
/*                                                                           */
/* __int2  is equivalent to a vector of 2  int                               */
/* __int3  is equivalent to a vector of 3  int                               */
/* __int4  is equivalent to a vector of 4  int                               */
/* __int8  is equivalent to a vector of 8  int                               */
/* __int16 is equivalent to a vector of 16 int                               */
/*                                                                           */
/* __uint2  is equivalent to a vector of 2  __uint                           */
/* __uint3  is equivalent to a vector of 3  __uint                           */
/* __uint4  is equivalent to a vector of 4  __uint                           */
/* __uint8  is equivalent to a vector of 8  __uint                           */
/* __uint16 is equivalent to a vector of 16 __uint                           */
/*                                                                           */
/* __long2  is equivalent to a vector of 2  long                             */
/* __long3  is equivalent to a vector of 3  long                             */
/* __long4  is equivalent to a vector of 4  long                             */
/* __long8  is equivalent to a vector of 8  long                             */
/*                                                                           */
/* __ulong2  is equivalent to a vector of 2  __ulong                         */
/* __ulong3  is equivalent to a vector of 3  __ulong                         */
/* __ulong4  is equivalent to a vector of 4  __ulong                         */
/* __ulong8  is equivalent to a vector of 8  __ulong                         */
/*                                                                           */
/* __float2  is equivalent to a vector of 2  float                           */
/* __float3  is equivalent to a vector of 3  float                           */
/* __float4  is equivalent to a vector of 4  float                           */
/* __float8  is equivalent to a vector of 8  float                           */
/* __float16 is equivalent to a vector of 16 float                           */
/*                                                                           */
/* __double2  is equivalent to a vector of 2  double                         */
/* __double3  is equivalent to a vector of 3  double                         */
/* __double4  is equivalent to a vector of 4  double                         */
/* __double8  is equivalent to a vector of 8  double                         */
/*****************************************************************************/
/* Complex data type and complex vector data types                           */
/*****************************************************************************/
/* __cchar      is equivalent to a complex signed char                       */
/* __cchar2     is equivalent to a vector of 2  complex signed char          */
/* __cchar4     is equivalent to a vector of 4  complex signed char          */
/* __cchar8     is equivalent to a vector of 8  complex signed char          */
/* __cchar16    is equivalent to a vector of 16 complex signed char          */
/* __cchar32    is equivalent to a vector of 32 complex signed char          */
/*                                                                           */
/* __cshort     is equivalent to a complex short                             */
/* __cshort2    is equivalent to a vector of 2  complex short                */
/* __cshort4    is equivalent to a vector of 4  complex short                */
/* __cshort8    is equivalent to a vector of 8  complex short                */
/* __cshort16   is equivalent to a vector of 16 complex short                */
/*                                                                           */
/* __cint       is equivalent to a complex int                               */
/* __cint2      is equivalent to a vector of 2 complex int                   */
/* __cint4      is equivalent to a vector of 4 complex int                   */
/* __cint8      is equivalent to a vector of 8 complex int                   */
/*                                                                           */
/* __clong      is equivalent to a complex long                              */
/* __clong2     is equivalent to a vector of 2 complex long                  */
/* __clong4     is equivalent to a vector of 4 complex long                  */
/*                                                                           */
/* __cfloat     is equivalent to a complex float                             */
/* __cfloat2    is equivalent to a vector of 2 complex float                 */
/* __cfloat4    is equivalent to a vector of 4 complex float                 */
/* __cfloat8    is equivalent to a vector of 8 complex float                 */
/*                                                                           */
/* __cdouble    is equivalent to a complex double                            */
/* __cdouble2   is equivalent to a vector of 2 complex double                */
/* __cdouble4   is equivalent to a vector of 4 complex double                */
/*****************************************************************************/

/* Complex multiply pseudo-instruction: VCMPYSP + VADDSP */
__cfloat  __OVBIF __complex_multiply          (__cfloat,  __cfloat);
__cfloat2 __OVBIF __complex_multiply          (__cfloat2, __cfloat2);
__cfloat4 __OVBIF __complex_multiply          (__cfloat4, __cfloat4);
#if __C7X_VEC_SIZE_BITS__ >= 512
__cfloat8 __OVBIF __complex_multiply          (__cfloat8, __cfloat8);
#endif

#define __complex_multiply(a,b) __overload("__complex_multiply",(a),(b))((a),(b))

/* Complex Conjugate multiply pseudo-instruction: VCMPYSP + VSUBSP */
__cfloat  __OVBIF __complex_conjugate_multiply(__cfloat,  __cfloat);
__cfloat2 __OVBIF __complex_conjugate_multiply(__cfloat2, __cfloat2);
__cfloat4 __OVBIF __complex_conjugate_multiply(__cfloat4, __cfloat4);
#if __C7X_VEC_SIZE_BITS__ >= 512
__cfloat8 __OVBIF __complex_conjugate_multiply(__cfloat8, __cfloat8);
#endif

#define __complex_conjugate_multiply(a,b) __overload("__complex_conjugate_multiply",(a),(b))((a),(b))
/*
cfloat  __OVBIF __conj_cmpy(__cfloat,  __cfloat);
cfloat2 __OVBIF __conj_cmpy(__cfloat2, __cfloat2);
cfloat4 __OVBIF __conj_cmpy(__cfloat4, __cfloat4);
#if __C7X_VEC_SIZE_BITS__ >= 512
cfloat8 __OVBIF __conj_cmpy(__cfloat8, __cfloat8);
#endif
*/

/* NOTE: this #define maps the conj_cmpy (created by the infix
   notation) to the complex_conjugate_multiply intrinsic (above) --
   the immediately preceding (commented out) function calls are only
   here for exposition; all conj_cmpy versions are expected to go
   through this #define; this should be removed someday, and the Jira
   entry for just that eventuality is CODEGEN-9989 
*/
#define __conj_cmpy(a,b) __complex_conjugate_multiply((a),(b)) 

/* Floating point VMATMPY pseudo-instruction: VMATMPYSP + VADDSP */
/* The VMATMPYSP instruction does notexist on the 7504 architecture */
#if __C7X_VEC_SIZE_BITS__ == 512
/* Floating point VMATMPY pseudo-instruction: VMATMPYSP + VADDSP */
__float2 __OVBIF __float_matmpy(__float2, __float4);
__float4 __OVBIF __float_matmpy(__float4, __float8);
__float8 __OVBIF __float_matmpy(__float8, __float16);

#define __float_matmpy(a,b) __overload("__float_matmpy",(a),(b))((a),(b))
#endif

/*****************************************************************************/
/* VECTOR LOADS AND PREDICATED VECTOR LOADS                                  */
/*                                                                           */
/* On C7120 and later devices, implicit predication occurs on loads that use */
/* streaming address generator (SA) operands. If an SA may be used as an     */
/* operand to a load AND that SA may generate predicates with one or more    */
/* predicate bits off, then a predicated load must be used to avoid          */
/* unexpected behavior. Use the following idiom with implicitly predicated   */
/* SA loads:                                                                 */
/*                                                                           */
/* bool2 pred = __SA0_BOOL(char2);                                           */
/* char2* ptr = __SA0ADV(char2, base_ptr);                                   */
/* char2 data = __vload_pred(pred, ptr);                                     */
/*                                                                           */
/* If implicit predication is not available (C7100), the idiom is malformed, */
/* or the compiler fails to optimize the idiom, an equivalent series of      */
/* instructions will instead be generated to load and then predicate.        */
/*****************************************************************************/
/* VLD8B, VLD16B, VLD32B, VLD64B */
__char2   __OVBIF __vload_pred(__bool2, __RD const __char2*);
__char4   __OVBIF __vload_pred(__bool4, __RD const __char4*);
__char8   __OVBIF __vload_pred(__bool8, __RD const __char8*);
__char16  __OVBIF __vload_pred(__bool16, __RD const __char16*);
__char32  __OVBIF __vload_pred(__bool32, __RD const __char32*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__char64  __OVBIF __vload_pred(__bool64, __RD const __char64*);
#endif

__uchar2  __OVBIF __vload_pred(__bool2, __RD const __uchar2*);
__uchar4  __OVBIF __vload_pred(__bool4, __RD const __uchar4*);
__uchar8  __OVBIF __vload_pred(__bool8, __RD const __uchar8*);
__uchar16 __OVBIF __vload_pred(__bool16, __RD const __uchar16*);
__uchar32 __OVBIF __vload_pred(__bool32, __RD const __uchar32*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uchar64 __OVBIF __vload_pred(__bool64, __RD const __uchar64*);
#endif

/* VLD4H, VLD8H, VLD16H, VLD32H */
__short2   __OVBIF __vload_pred(__bool2, __RD const __short2*);
__short4   __OVBIF __vload_pred(__bool4, __RD const __short4*);
__short8   __OVBIF __vload_pred(__bool8, __RD const __short8*);
__short16  __OVBIF __vload_pred(__bool16, __RD const __short16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__short32  __OVBIF __vload_pred(__bool32, __RD const __short32*);
#endif

__ushort2  __OVBIF __vload_pred(__bool2, __RD const __ushort2*);
__ushort4  __OVBIF __vload_pred(__bool4, __RD const __ushort4*);
__ushort8  __OVBIF __vload_pred(__bool8, __RD const __ushort8*);
__ushort16 __OVBIF __vload_pred(__bool16, __RD const __ushort16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ushort32 __OVBIF __vload_pred(__bool32, __RD const __ushort32*);
#endif

/* VLDHSWAPB */
__cchar2   __OVBIF __vload_pred(__bool2, __RD const __cchar2*);
__cchar4   __OVBIF __vload_pred(__bool4, __RD const __cchar4*);
__cchar8   __OVBIF __vload_pred(__bool8, __RD const __cchar8*);
__cchar16  __OVBIF __vload_pred(__bool16, __RD const __cchar16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__cchar32  __OVBIF __vload_pred(__bool32, __RD const __cchar32*);
#endif

/* VLD2W, VLD4W, VLD8W, VLD16W */
__int2   __OVBIF __vload_pred(__bool2, __RD const __int2*);
__int4   __OVBIF __vload_pred(__bool4, __RD const __int4*);
__int8   __OVBIF __vload_pred(__bool8, __RD const __int8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16  __OVBIF __vload_pred(__bool16, __RD const __int16*);
#endif

__uint2  __OVBIF __vload_pred(__bool2, __RD const __uint2*);
__uint4  __OVBIF __vload_pred(__bool4, __RD const __uint4*);
__uint8  __OVBIF __vload_pred(__bool8, __RD const __uint8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16 __OVBIF __vload_pred(__bool16, __RD const __uint16*);
#endif

__float2   __OVBIF __vload_pred(__bool2, __RD const __float2*);
__float4   __OVBIF __vload_pred(__bool4, __RD const __float4*);
__float8   __OVBIF __vload_pred(__bool8, __RD const __float8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__float16  __OVBIF __vload_pred(__bool16, __RD const __float16*);
#endif

/* VLDWSWAPH */
__cshort2   __OVBIF __vload_pred(__bool2, __RD const __cshort2*);
__cshort4   __OVBIF __vload_pred(__bool4, __RD const __cshort4*);
__cshort8   __OVBIF __vload_pred(__bool8, __RD const __cshort8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__cshort16  __OVBIF __vload_pred(__bool16, __RD const __cshort16*);
#endif

/* VLD2D, VLD4D, VLD8D */
__long2     __OVBIF __vload_pred(__bool2, __RD const __long2*);
__long4     __OVBIF __vload_pred(__bool4, __RD const __long4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8     __OVBIF __vload_pred(__bool8, __RD const __long8*);
#endif

__ulong2    __OVBIF __vload_pred(__bool2, __RD const __ulong2*);
__ulong4    __OVBIF __vload_pred(__bool4, __RD const __ulong4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8    __OVBIF __vload_pred(__bool8, __RD const __ulong8*);
#endif

__double2   __OVBIF __vload_pred(__bool2, __RD const __double2*);
__double4   __OVBIF __vload_pred(__bool4, __RD const __double4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__double8   __OVBIF __vload_pred(__bool8, __RD const __double8*);
#endif

/* VLDDSWAPW */
__cint2   __OVBIF __vload_pred(__bool2, __RD const __cint2*);
__cint4   __OVBIF __vload_pred(__bool4, __RD const __cint4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__cint8   __OVBIF __vload_pred(__bool8, __RD const __cint8*);
#endif
__cfloat2   __OVBIF __vload_pred(__bool2, __RD const __cfloat2*);
__cfloat4   __OVBIF __vload_pred(__bool4, __RD const __cfloat4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__cfloat8   __OVBIF __vload_pred(__bool8, __RD const __cfloat8*);
#endif

#define __vload_pred(a,b)  __overload("__vload_pred",(a),(b))((a),(b))

/* VLDDUP2B, VLDDUP4B, VLDDUP8B, VLDDUP16B, VLDDUP32B, VLDDUP64B */
#if __C7X_VEC_SIZE_BITS__ == 512
__char64      __OVBIF __vload_dup(__RD const __char32*);
__char64      __OVBIF __vload_dup(__RD const __char16*);
__char64      __OVBIF __vload_dup(__RD const __char8*);
__char64      __OVBIF __vload_dup(__RD const __char4*);
__char64      __OVBIF __vload_dup(__RD const __char2*);
__char64      __OVBIF __vload_dup(__RD const signed char*);
__uchar64     __OVBIF __vload_dup(__RD const __uchar32*);
__uchar64     __OVBIF __vload_dup(__RD const __uchar16*);
__uchar64     __OVBIF __vload_dup(__RD const __uchar8*);
__uchar64     __OVBIF __vload_dup(__RD const __uchar4*);
__uchar64     __OVBIF __vload_dup(__RD const __uchar2*);
__uchar64     __OVBIF __vload_dup(__RD const __uchar*);

__char64      __OVBIF __vload_pred_dup(__bool32, __RD const __char32*);
__char64      __OVBIF __vload_pred_dup(__bool16, __RD const __char16*);
__char64      __OVBIF __vload_pred_dup(__bool8, __RD const __char8*);
__char64      __OVBIF __vload_pred_dup(__bool4, __RD const __char4*);
__char64      __OVBIF __vload_pred_dup(__bool2, __RD const __char2*);
__uchar64     __OVBIF __vload_pred_dup(__bool32, __RD const __uchar32*);
__uchar64     __OVBIF __vload_pred_dup(__bool16, __RD const __uchar16*);
__uchar64     __OVBIF __vload_pred_dup(__bool8, __RD const __uchar8*);
__uchar64     __OVBIF __vload_pred_dup(__bool4, __RD const __uchar4*);
__uchar64     __OVBIF __vload_pred_dup(__bool2, __RD const __uchar2*);
#elif __C7X_VEC_SIZE_BITS__ == 256
__char32      __OVBIF __vload_dup(__RD const __char16*);
__char32      __OVBIF __vload_dup(__RD const __char8*);
__char32      __OVBIF __vload_dup(__RD const __char4*);
__char32      __OVBIF __vload_dup(__RD const __char2*);
__char32      __OVBIF __vload_dup(__RD const signed char*);
__uchar32     __OVBIF __vload_dup(__RD const __uchar16*);
__uchar32     __OVBIF __vload_dup(__RD const __uchar8*);
__uchar32     __OVBIF __vload_dup(__RD const __uchar4*);
__uchar32     __OVBIF __vload_dup(__RD const __uchar2*);
__uchar32     __OVBIF __vload_dup(__RD const __uchar*);

__char32      __OVBIF __vload_pred_dup(__bool16, __RD const __char16*);
__char32      __OVBIF __vload_pred_dup(__bool8, __RD const __char8*);
__char32      __OVBIF __vload_pred_dup(__bool4, __RD const __char4*);
__char32      __OVBIF __vload_pred_dup(__bool2, __RD const __char2*);
__uchar32     __OVBIF __vload_pred_dup(__bool16, __RD const __uchar16*);
__uchar32     __OVBIF __vload_pred_dup(__bool8, __RD const __uchar8*);
__uchar32     __OVBIF __vload_pred_dup(__bool4, __RD const __uchar4*);
__uchar32     __OVBIF __vload_pred_dup(__bool2, __RD const __uchar2*);
#endif

/* VLDDUP2H, VLDDUP4H, VLDDUP8H, VLDDUP16H, VLDDUP32H */
#if __C7X_VEC_SIZE_BITS__ == 512
__short32     __OVBIF __vload_dup(__RD const __short16*);
__short32     __OVBIF __vload_dup(__RD const __short8*);
__short32     __OVBIF __vload_dup(__RD const __short4*);
__short32     __OVBIF __vload_dup(__RD const __short2*);
__short32     __OVBIF __vload_dup(__RD const short*);
__ushort32    __OVBIF __vload_dup(__RD const __ushort16*);
__ushort32    __OVBIF __vload_dup(__RD const __ushort8*);
__ushort32    __OVBIF __vload_dup(__RD const __ushort4*);
__ushort32    __OVBIF __vload_dup(__RD const __ushort2*);
__ushort32    __OVBIF __vload_dup(__RD const __ushort*);

__short32     __OVBIF __vload_pred_dup(__bool16, __RD const __short16*);
__short32     __OVBIF __vload_pred_dup(__bool8, __RD const __short8*);
__short32     __OVBIF __vload_pred_dup(__bool4, __RD const __short4*);
__short32     __OVBIF __vload_pred_dup(__bool2, __RD const __short2*);
__ushort32    __OVBIF __vload_pred_dup(__bool16, __RD const __ushort16*);
__ushort32    __OVBIF __vload_pred_dup(__bool8, __RD const __ushort8*);
__ushort32    __OVBIF __vload_pred_dup(__bool4, __RD const __ushort4*);
__ushort32    __OVBIF __vload_pred_dup(__bool2, __RD const __ushort2*);
#elif __C7X_VEC_SIZE_BITS__ == 256
__short16     __OVBIF __vload_dup(__RD const __short8*);
__short16     __OVBIF __vload_dup(__RD const __short4*);
__short16     __OVBIF __vload_dup(__RD const __short2*);
__short16     __OVBIF __vload_dup(__RD const short*);
__ushort16    __OVBIF __vload_dup(__RD const __ushort8*);
__ushort16    __OVBIF __vload_dup(__RD const __ushort4*);
__ushort16    __OVBIF __vload_dup(__RD const __ushort2*);
__ushort16    __OVBIF __vload_dup(__RD const __ushort*);

__short16     __OVBIF __vload_pred_dup(__bool8, __RD const __short8*);
__short16     __OVBIF __vload_pred_dup(__bool4, __RD const __short4*);
__short16     __OVBIF __vload_pred_dup(__bool2, __RD const __short2*);
__ushort16    __OVBIF __vload_pred_dup(__bool8, __RD const __ushort8*);
__ushort16    __OVBIF __vload_pred_dup(__bool4, __RD const __ushort4*);
__ushort16    __OVBIF __vload_pred_dup(__bool2, __RD const __ushort2*);
#endif

/* VLDDUP2W, VLDDUP4W, VLDDUP8W, VLDDUP16W */
#if __C7X_VEC_SIZE_BITS__ == 512
__int16       __OVBIF __vload_dup(__RD const __int8*);
__int16       __OVBIF __vload_dup(__RD const __int4*);
__int16       __OVBIF __vload_dup(__RD const __int2*);
__int16       __OVBIF __vload_dup(__RD const int*);
__uint16      __OVBIF __vload_dup(__RD const __uint8*);
__uint16      __OVBIF __vload_dup(__RD const __uint4*);
__uint16      __OVBIF __vload_dup(__RD const __uint2*);
__uint16      __OVBIF __vload_dup(__RD const __uint*);
__float16     __OVBIF __vload_dup(__RD const __float8*);
__float16     __OVBIF __vload_dup(__RD const __float4*);
__float16     __OVBIF __vload_dup(__RD const __float2*);
__float16     __OVBIF __vload_dup(__RD const float*);

__int16       __OVBIF __vload_pred_dup(__bool8, __RD const __int8*);
__int16       __OVBIF __vload_pred_dup(__bool4, __RD const __int4*);
__int16       __OVBIF __vload_pred_dup(__bool2, __RD const __int2*);
__uint16      __OVBIF __vload_pred_dup(__bool8, __RD const __uint8*);
__uint16      __OVBIF __vload_pred_dup(__bool4, __RD const __uint4*);
__uint16      __OVBIF __vload_pred_dup(__bool2, __RD const __uint2*);
__float16     __OVBIF __vload_pred_dup(__bool8, __RD const __float8*);
__float16     __OVBIF __vload_pred_dup(__bool4, __RD const __float4*);
__float16     __OVBIF __vload_pred_dup(__bool2, __RD const __float2*);
#elif __C7X_VEC_SIZE_BITS__ == 256
__int8       __OVBIF __vload_dup(__RD const __int4*);
__int8       __OVBIF __vload_dup(__RD const __int2*);
__int8       __OVBIF __vload_dup(__RD const int*);
__uint8      __OVBIF __vload_dup(__RD const __uint4*);
__uint8      __OVBIF __vload_dup(__RD const __uint2*);
__uint8      __OVBIF __vload_dup(__RD const __uint*);
__float8     __OVBIF __vload_dup(__RD const __float4*);
__float8     __OVBIF __vload_dup(__RD const __float2*);
__float8     __OVBIF __vload_dup(__RD const float*);

__int8       __OVBIF __vload_pred_dup(__bool4, __RD const __int4*);
__int8       __OVBIF __vload_pred_dup(__bool2, __RD const __int2*);
__uint8      __OVBIF __vload_pred_dup(__bool4, __RD const __uint4*);
__uint8      __OVBIF __vload_pred_dup(__bool2, __RD const __uint2*);
__float8     __OVBIF __vload_pred_dup(__bool4, __RD const __float4*);
__float8     __OVBIF __vload_pred_dup(__bool2, __RD const __float2*);
#endif

/* VLDDUP2D, VLDDUP4D, VLDDUP8D */
#if __C7X_VEC_SIZE_BITS__ == 512
__long8       __OVBIF __vload_dup(__RD const __long4*);
__long8       __OVBIF __vload_dup(__RD const __long2*);
__long8       __OVBIF __vload_dup(__RD const long*);
__ulong8      __OVBIF __vload_dup(__RD const __ulong4*);
__ulong8      __OVBIF __vload_dup(__RD const __ulong2*);
__ulong8      __OVBIF __vload_dup(__RD const __ulong*);
__double8     __OVBIF __vload_dup(__RD const __double4*);
__double8     __OVBIF __vload_dup(__RD const __double2*);
__double8     __OVBIF __vload_dup(__RD const double*);

__long8       __OVBIF __vload_pred_dup(__bool4, __RD const __long4*);
__long8       __OVBIF __vload_pred_dup(__bool2, __RD const __long2*);
__ulong8      __OVBIF __vload_pred_dup(__bool4, __RD const __ulong4*);
__ulong8      __OVBIF __vload_pred_dup(__bool2, __RD const __ulong2*);
__double8     __OVBIF __vload_pred_dup(__bool4, __RD const __double4*);
__double8     __OVBIF __vload_pred_dup(__bool2, __RD const __double2*);
#elif __C7X_VEC_SIZE_BITS__ == 256
__long4       __OVBIF __vload_dup(__RD const __long2*);
__long4       __OVBIF __vload_dup(__RD const long*);
__ulong4      __OVBIF __vload_dup(__RD const __ulong2*);
__ulong4      __OVBIF __vload_dup(__RD const __ulong*);
__double4     __OVBIF __vload_dup(__RD const __double2*);
__double4     __OVBIF __vload_dup(__RD const double*);

__long4       __OVBIF __vload_pred_dup(__bool2, __RD const __long2*);
__ulong4      __OVBIF __vload_pred_dup(__bool2, __RD const __ulong2*);
__double4     __OVBIF __vload_pred_dup(__bool2, __RD const __double2*);
#endif

#define __vload_dup(a)  __overload("__vload_dup",(a))((a))
#define __vload_pred_dup(a,b)  __overload("__vload_pred_dup",(a),(b))((a),(b))

/* VLDDUP4G8H, VLDDUP8G4H */
#if __C7X_VEC_SIZE_BITS__ >= 512
__short32     __OVBIF __vload_dup_vec(__RD const __short8*);
__ushort32    __OVBIF __vload_dup_vec(__RD const __ushort8*);
__short32     __OVBIF __vload_dup_vec(__RD const __short4*);
__ushort32    __OVBIF __vload_dup_vec(__RD const __ushort4*);

__short32     __OVBIF __vload_pred_dup_vec(__bool8, __RD const __short8*);
__ushort32    __OVBIF __vload_pred_dup_vec(__bool8, __RD const __ushort8*);
__short32     __OVBIF __vload_pred_dup_vec(__bool4, __RD const __short4*);
__ushort32    __OVBIF __vload_pred_dup_vec(__bool4, __RD const __ushort4*);

#define __vload_dup_vec(a)  __overload("__vload_dup_vec",(a))((a))
#define __vload_pred_dup_vec(a,b)  __overload("__vload_pred_dup_vec",(a),(b))((a),(b))
#endif

/* VLDBUNPKH, VLDBUNPKHU */
short       __OVBIF __vload_unpack_short(__RD const signed char*);
__short2    __OVBIF __vload_unpack_short(__RD const __char2*);
__short4    __OVBIF __vload_unpack_short(__RD const __char4*);
__short8    __OVBIF __vload_unpack_short(__RD const __char8*);
__short16   __OVBIF __vload_unpack_short(__RD const __char16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__short32   __OVBIF __vload_unpack_short(__RD const __char32*);
#endif
__ushort    __OVBIF __vload_unpack_short(__RD const __uchar*);
__ushort2   __OVBIF __vload_unpack_short(__RD const __uchar2*);
__ushort4   __OVBIF __vload_unpack_short(__RD const __uchar4*);
__ushort8   __OVBIF __vload_unpack_short(__RD const __uchar8*);
__ushort16  __OVBIF __vload_unpack_short(__RD const __uchar16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ushort32  __OVBIF __vload_unpack_short(__RD const __uchar32*);
#endif

__short2    __OVBIF __vload_pred_unpack_short(__bool2, __RD const __char2*);
__short4    __OVBIF __vload_pred_unpack_short(__bool4, __RD const __char4*);
__short8    __OVBIF __vload_pred_unpack_short(__bool8, __RD const __char8*);
__short16   __OVBIF __vload_pred_unpack_short(__bool16, __RD const __char16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__short32   __OVBIF __vload_pred_unpack_short(__bool32, __RD const __char32*);
#endif

__ushort2   __OVBIF __vload_pred_unpack_short(__bool2, __RD const __uchar2*);
__ushort4   __OVBIF __vload_pred_unpack_short(__bool4, __RD const __uchar4*);
__ushort8   __OVBIF __vload_pred_unpack_short(__bool8, __RD const __uchar8*);
__ushort16  __OVBIF __vload_pred_unpack_short(__bool16, __RD const __uchar16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ushort32  __OVBIF __vload_pred_unpack_short(__bool32, __RD const __uchar32*);
#endif

#define __vload_unpack_short(a)  __overload("__vload_unpack_short",(a))((a))
#define __vload_pred_unpack_short(a,b)  __overload("__vload_pred_unpack_short",(a),(b))((a),(b))

/* VLDBUNPKW, VLDBUNPKWU */
int         __OVBIF __vload_unpack_int(__RD const signed char*);
__int2      __OVBIF __vload_unpack_int(__RD const __char2*);
__int4      __OVBIF __vload_unpack_int(__RD const __char4*);
__int8      __OVBIF __vload_unpack_int(__RD const __char8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16     __OVBIF __vload_unpack_int(__RD const __char16*);
#endif

__uint      __OVBIF __vload_unpack_int(__RD const __uchar*);
__uint2     __OVBIF __vload_unpack_int(__RD const __uchar2*);
__uint4     __OVBIF __vload_unpack_int(__RD const __uchar4*);
__uint8     __OVBIF __vload_unpack_int(__RD const __uchar8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16    __OVBIF __vload_unpack_int(__RD const __uchar16*);
#endif

__int2      __OVBIF __vload_pred_unpack_int(__bool2, __RD const __char2*);
__int4      __OVBIF __vload_pred_unpack_int(__bool4, __RD const __char4*);
__int8      __OVBIF __vload_pred_unpack_int(__bool8, __RD const __char8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16     __OVBIF __vload_pred_unpack_int(__bool16, __RD const __char16*);
#endif

__uint2     __OVBIF __vload_pred_unpack_int(__bool2, __RD const __uchar2*);
__uint4     __OVBIF __vload_pred_unpack_int(__bool4, __RD const __uchar4*);
__uint8     __OVBIF __vload_pred_unpack_int(__bool8, __RD const __uchar8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16    __OVBIF __vload_pred_unpack_int(__bool16, __RD const __uchar16*);
#endif

/* VLDHUNPKW, VLDHUNPKWU */
int         __OVBIF __vload_unpack_int(__RD const short*);
__int2      __OVBIF __vload_unpack_int(__RD const __short2*);
__int4      __OVBIF __vload_unpack_int(__RD const __short4*);
__int8      __OVBIF __vload_unpack_int(__RD const __short8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16     __OVBIF __vload_unpack_int(__RD const __short16*);
#endif

__uint      __OVBIF __vload_unpack_int(__RD const __ushort*);
__uint2     __OVBIF __vload_unpack_int(__RD const __ushort2*);
__uint4     __OVBIF __vload_unpack_int(__RD const __ushort4*);
__uint8     __OVBIF __vload_unpack_int(__RD const __ushort8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16    __OVBIF __vload_unpack_int(__RD const __ushort16*);
#endif

__int2      __OVBIF __vload_pred_unpack_int(__bool2, __RD const __short2*);
__int4      __OVBIF __vload_pred_unpack_int(__bool4, __RD const __short4*);
__int8      __OVBIF __vload_pred_unpack_int(__bool8, __RD const __short8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16     __OVBIF __vload_pred_unpack_int(__bool16, __RD const __short16*);
#endif

__uint2     __OVBIF __vload_pred_unpack_int(__bool2, __RD const __ushort2*);
__uint4     __OVBIF __vload_pred_unpack_int(__bool4, __RD const __ushort4*);
__uint8     __OVBIF __vload_pred_unpack_int(__bool8, __RD const __ushort8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16    __OVBIF __vload_pred_unpack_int(__bool16, __RD const __ushort16*);
#endif

#define __vload_unpack_int(a)  __overload("__vload_unpack_int",(a))((a))
#define __vload_pred_unpack_int(a,b)  __overload("__vload_pred_unpack_int",(a),(b))((a),(b))

/* VLDBUNPKD, VLDBUNPKDU */
long        __OVBIF __vload_unpack_long(__RD const signed char*);
__long2     __OVBIF __vload_unpack_long(__RD const __char2*);
__long4     __OVBIF __vload_unpack_long(__RD const __char4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8     __OVBIF __vload_unpack_long(__RD const __char8*);
#endif

__ulong     __OVBIF __vload_unpack_long(__RD const __uchar*);
__ulong2    __OVBIF __vload_unpack_long(__RD const __uchar2*);
__ulong4    __OVBIF __vload_unpack_long(__RD const __uchar4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8    __OVBIF __vload_unpack_long(__RD const __uchar8*);
#endif

__long2     __OVBIF __vload_pred_unpack_long(__bool2, __RD const __char2*);
__long4     __OVBIF __vload_pred_unpack_long(__bool4, __RD const __char4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8     __OVBIF __vload_pred_unpack_long(__bool8, __RD const __char8*);
#endif

__ulong2    __OVBIF __vload_pred_unpack_long(__bool2, __RD const __uchar2*);
__ulong4    __OVBIF __vload_pred_unpack_long(__bool4, __RD const __uchar4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8    __OVBIF __vload_pred_unpack_long(__bool8, __RD const __uchar8*);
#endif

/* VLDHUNPKD, VLDHUNPKDU */
long        __OVBIF __vload_unpack_long(__RD const short*);
__long2     __OVBIF __vload_unpack_long(__RD const __short2*);
__long4     __OVBIF __vload_unpack_long(__RD const __short4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8     __OVBIF __vload_unpack_long(__RD const __short8*);
#endif

__ulong     __OVBIF __vload_unpack_long(__RD const __ushort*);
__ulong2    __OVBIF __vload_unpack_long(__RD const __ushort2*);
__ulong4    __OVBIF __vload_unpack_long(__RD const __ushort4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8    __OVBIF __vload_unpack_long(__RD const __ushort8*);
#endif

__long2     __OVBIF __vload_pred_unpack_long(__bool2, __RD const __short2*);
__long4     __OVBIF __vload_pred_unpack_long(__bool4, __RD const __short4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8     __OVBIF __vload_pred_unpack_long(__bool8, __RD const __short8*);
#endif

__ulong2    __OVBIF __vload_pred_unpack_long(__bool2, __RD const __ushort2*);
__ulong4    __OVBIF __vload_pred_unpack_long(__bool4, __RD const __ushort4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8    __OVBIF __vload_pred_unpack_long(__bool8, __RD const __ushort8*);
#endif

/* VLDWUNPKD, VLDWUNPKDU */
long        __OVBIF __vload_unpack_long(__RD const int*);
__long2     __OVBIF __vload_unpack_long(__RD const __int2*);
__long4     __OVBIF __vload_unpack_long(__RD const __int4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8     __OVBIF __vload_unpack_long(__RD const __int8*);
#endif

__ulong     __OVBIF __vload_unpack_long(__RD const __uint*);
__ulong2    __OVBIF __vload_unpack_long(__RD const __uint2*);
__ulong4    __OVBIF __vload_unpack_long(__RD const __uint4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8    __OVBIF __vload_unpack_long(__RD const __uint8*);
#endif

__long2     __OVBIF __vload_pred_unpack_long(__bool2, __RD const __int2*);
__long4     __OVBIF __vload_pred_unpack_long(__bool4, __RD const __int4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8     __OVBIF __vload_pred_unpack_long(__bool8, __RD const __int8*);
#endif

__ulong2    __OVBIF __vload_pred_unpack_long(__bool2, __RD const __uint2*);
__ulong4    __OVBIF __vload_pred_unpack_long(__bool4, __RD const __uint4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8    __OVBIF __vload_pred_unpack_long(__bool8, __RD const __uint8*);
#endif

#define __vload_unpack_long(a)  __overload("__vload_unpack_long",(a))((a))
#define __vload_pred_unpack_long(a,b)  __overload("__vload_pred_unpack_long",(a),(b))((a),(b))

/* VLDEBUNPKW, VLDEHUNPKW */
int         __OVBIF __vload_deinterleave_int(__RD const __char2*);
__int2      __OVBIF __vload_deinterleave_int(__RD const __char4*);
__int4      __OVBIF __vload_deinterleave_int(__RD const __char8*);
__int8      __OVBIF __vload_deinterleave_int(__RD const __char16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16     __OVBIF __vload_deinterleave_int(__RD const __char32*);
#endif

int         __OVBIF __vload_deinterleave_int(__RD const __short2*);
__int2      __OVBIF __vload_deinterleave_int(__RD const __short4*);
__int4      __OVBIF __vload_deinterleave_int(__RD const __short8*);
__int8      __OVBIF __vload_deinterleave_int(__RD const __short16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16     __OVBIF __vload_deinterleave_int(__RD const __short32*);
#endif

int         __OVBIF __vload_pred_deinterleave_int(__bool2, __RD const __char2*);
__int2      __OVBIF __vload_pred_deinterleave_int(__bool4, __RD const __char4*);
__int4      __OVBIF __vload_pred_deinterleave_int(__bool8, __RD const __char8*);
__int8      __OVBIF __vload_pred_deinterleave_int(__bool16, __RD const __char16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16     __OVBIF __vload_pred_deinterleave_int(__bool32, __RD const __char32*);
#endif
int         __OVBIF __vload_pred_deinterleave_int(__bool2, __RD const __short2*);
__int2      __OVBIF __vload_pred_deinterleave_int(__bool4, __RD const __short4*);
__int4      __OVBIF __vload_pred_deinterleave_int(__bool8, __RD const __short8*);
__int8      __OVBIF __vload_pred_deinterleave_int(__bool16, __RD const __short16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16     __OVBIF __vload_pred_deinterleave_int(__bool32, __RD const __short32*);
#endif

/* VLDEBUNPKWU, VLDEHUNPKWU */
__uint       __OVBIF __vload_deinterleave_int(__RD const __uchar2*);
__uint2      __OVBIF __vload_deinterleave_int(__RD const __uchar4*);
__uint4      __OVBIF __vload_deinterleave_int(__RD const __uchar8*);
__uint8      __OVBIF __vload_deinterleave_int(__RD const __uchar16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16     __OVBIF __vload_deinterleave_int(__RD const __uchar32*);
#endif

__uint       __OVBIF __vload_deinterleave_int(__RD const __ushort2*);
__uint2      __OVBIF __vload_deinterleave_int(__RD const __ushort4*);
__uint4      __OVBIF __vload_deinterleave_int(__RD const __ushort8*);
__uint8      __OVBIF __vload_deinterleave_int(__RD const __ushort16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16     __OVBIF __vload_deinterleave_int(__RD const __ushort32*);
#endif

__uint       __OVBIF __vload_pred_deinterleave_int(__bool2, __RD const __uchar2*);
__uint2      __OVBIF __vload_pred_deinterleave_int(__bool4, __RD const __uchar4*);
__uint4      __OVBIF __vload_pred_deinterleave_int(__bool8, __RD const __uchar8*);
__uint8      __OVBIF __vload_pred_deinterleave_int(__bool16, __RD const __uchar16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16     __OVBIF __vload_pred_deinterleave_int(__bool32, __RD const __uchar32*);
#endif

__uint       __OVBIF __vload_pred_deinterleave_int(__bool2, __RD const __ushort2*);
__uint2      __OVBIF __vload_pred_deinterleave_int(__bool4, __RD const __ushort4*);
__uint4      __OVBIF __vload_pred_deinterleave_int(__bool8, __RD const __ushort8*);
__uint8      __OVBIF __vload_pred_deinterleave_int(__bool16, __RD const __ushort16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16     __OVBIF __vload_pred_deinterleave_int(__bool32, __RD const __ushort32*);
#endif

#define __vload_deinterleave_int(a)  __overload("__vload_deinterleave_int",(a))((a))
#define __vload_pred_deinterleave_int(a,b)  __overload("__vload_pred_deinterleave_int",(a),(b))((a),(b))

/* VLDEBUNPKD, VLDEHUNPKD */
long         __OVBIF __vload_deinterleave_long(__RD const __char2*);
__long2      __OVBIF __vload_deinterleave_long(__RD const __char4*);
__long4      __OVBIF __vload_deinterleave_long(__RD const __char8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8      __OVBIF __vload_deinterleave_long(__RD const __char16*);
#endif

long         __OVBIF __vload_deinterleave_long(__RD const __short2*);
__long2      __OVBIF __vload_deinterleave_long(__RD const __short4*);
__long4      __OVBIF __vload_deinterleave_long(__RD const __short8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8      __OVBIF __vload_deinterleave_long(__RD const __short16*);
#endif

long         __OVBIF __vload_pred_deinterleave_long(__bool2, __RD const __char2*);
__long2      __OVBIF __vload_pred_deinterleave_long(__bool4, __RD const __char4*);
__long4      __OVBIF __vload_pred_deinterleave_long(__bool8, __RD const __char8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8      __OVBIF __vload_pred_deinterleave_long(__bool16, __RD const __char16*);
#endif

long         __OVBIF __vload_pred_deinterleave_long(__bool2, __RD const __short2*);
__long2      __OVBIF __vload_pred_deinterleave_long(__bool4, __RD const __short4*);
__long4      __OVBIF __vload_pred_deinterleave_long(__bool8, __RD const __short8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8      __OVBIF __vload_pred_deinterleave_long(__bool16, __RD const __short16*);
#endif

/* VLDEBUNPKDU, VLDEHUNPKDU */
__ulong       __OVBIF __vload_deinterleave_long(__RD const __uchar2*);
__ulong2      __OVBIF __vload_deinterleave_long(__RD const __uchar4*);
__ulong4      __OVBIF __vload_deinterleave_long(__RD const __uchar8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8      __OVBIF __vload_deinterleave_long(__RD const __uchar16*);
#endif

__ulong       __OVBIF __vload_deinterleave_long(__RD const __ushort2*);
__ulong2      __OVBIF __vload_deinterleave_long(__RD const __ushort4*);
__ulong4      __OVBIF __vload_deinterleave_long(__RD const __ushort8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8      __OVBIF __vload_deinterleave_long(__RD const __ushort16*);
#endif

__ulong       __OVBIF __vload_pred_deinterleave_long(__bool2, __RD const __uchar2*);
__ulong2      __OVBIF __vload_pred_deinterleave_long(__bool4, __RD const __uchar4*);
__ulong4      __OVBIF __vload_pred_deinterleave_long(__bool8, __RD const __uchar8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8      __OVBIF __vload_pred_deinterleave_long(__bool16, __RD const __uchar16*);
#endif

__ulong       __OVBIF __vload_pred_deinterleave_long(__bool2, __RD const __ushort2*);
__ulong2      __OVBIF __vload_pred_deinterleave_long(__bool4, __RD const __ushort4*);
__ulong4      __OVBIF __vload_pred_deinterleave_long(__bool8, __RD const __ushort8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8      __OVBIF __vload_pred_deinterleave_long(__bool16, __RD const __ushort16*);
#endif

#define __vload_deinterleave_long(a)  __overload("__vload_deinterleave_long",(a))((a))
#define __vload_pred_deinterleave_long(a,b)  __overload("__vload_pred_deinterleave_long",(a),(b))((a),(b))

/*****************************************************************************/
/* VECTOR STORES AND PREDICATED VECTOR STORES                                */
/*                                                                           */
/* On all C7000 devices, implicit predication occurs on stores that use      */
/* streaming address generator (SA) operands. If an SA may be used as an     */
/* operand to a store AND that SA may generate predicates with one or more   */
/* predicate bits off, then a predicated store must be used to avoid         */
/* unexpected behavior. Use the following idiom with implicitly predicated   */
/* SA stores:                                                                */
/*                                                                           */
/* bool2 pred = __SA0_BOOL(char2);                                           */
/* char2* ptr = __SA0ADV(char2, base_ptr);                                   */
/* __vstore_pred(pred, ptr, data);                                           */
/*                                                                           */
/* If the idiom is malformed or the compiler fails to optimize the idiom, an */
/* equivalent series of instructions will instead be generated to create the */
/* predicate and then store with explicit predication.                       */
/*****************************************************************************/
/* VSTINTLB, VSTINTLH, VSTINTLW, VSTINTLD - STORES EVERY EVEN ELEMENT */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_interleave(__WR __char64*,   __char64,   __char64);
void __OVBIFM __vstore_interleave(__WR __short32*,  __short32,  __short32);
void __OVBIFM __vstore_interleave(__WR __int16*,    __int16,    __int16);
void __OVBIFM __vstore_interleave(__WR __long8*,    __long8,    __long8);
void __OVBIFM __vstore_interleave(__WR __uchar64*,  __uchar64,  __uchar64);
void __OVBIFM __vstore_interleave(__WR __ushort32*, __ushort32, __ushort32);
void __OVBIFM __vstore_interleave(__WR __uint16*,   __uint16,   __uint16);
void __OVBIFM __vstore_interleave(__WR __ulong8*,   __ulong8,   __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_interleave(__WR __char32*,   __char32,   __char32);
void __OVBIFM __vstore_interleave(__WR __short16*,  __short16,  __short16);
void __OVBIFM __vstore_interleave(__WR __int8*,    __int8,    __int8);
void __OVBIFM __vstore_interleave(__WR __long4*,    __long4,    __long4);
void __OVBIFM __vstore_interleave(__WR __uchar32*,  __uchar32,  __uchar32);
void __OVBIFM __vstore_interleave(__WR __ushort16*, __ushort16, __ushort16);
void __OVBIFM __vstore_interleave(__WR __uint8*,   __uint8,   __uint8);
void __OVBIFM __vstore_interleave(__WR __ulong4*,   __ulong4,   __ulong4);
#endif

#define __vstore_interleave(a,b,c) __overload("__vstore_interleave",(a),(b),(c))((a),(b),(c))

#ifndef __C7100__
/* VSTINTHB, VSTINTHH, VSTINTHW, VSTINTHD - STORES EVERY ODD ELEMENT */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_interleave_odd(__WR __char64*,   __char64,   __char64);
void __OVBIFM __vstore_interleave_odd(__WR __short32*,  __short32,  __short32);
void __OVBIFM __vstore_interleave_odd(__WR __int16*,    __int16,    __int16);
void __OVBIFM __vstore_interleave_odd(__WR __long8*,    __long8,    __long8);
void __OVBIFM __vstore_interleave_odd(__WR __uchar64*,  __uchar64,  __uchar64);
void __OVBIFM __vstore_interleave_odd(__WR __ushort32*, __ushort32, __ushort32);
void __OVBIFM __vstore_interleave_odd(__WR __uint16*,   __uint16,   __uint16);
void __OVBIFM __vstore_interleave_odd(__WR __ulong8*,   __ulong8,   __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_interleave_odd(__WR __char32*,   __char32,   __char32);
void __OVBIFM __vstore_interleave_odd(__WR __short16*,  __short16,  __short16);
void __OVBIFM __vstore_interleave_odd(__WR __int8*,    __int8,    __int8);
void __OVBIFM __vstore_interleave_odd(__WR __long4*,    __long4,    __long4);
void __OVBIFM __vstore_interleave_odd(__WR __uchar32*,  __uchar32,  __uchar32);
void __OVBIFM __vstore_interleave_odd(__WR __ushort16*, __ushort16, __ushort16);
void __OVBIFM __vstore_interleave_odd(__WR __uint8*,   __uint8,   __uint8);
void __OVBIFM __vstore_interleave_odd(__WR __ulong4*,   __ulong4,   __ulong4);
#endif

#define __vstore_interleave_odd(a,b,c) __overload("__vstore_interleave_odd",(a),(b),(c))((a),(b),(c))
#endif /* ! __C7100__ */

/* VSTINTLB4 - STORES EVERY FOURTH ELEMENT */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_interleave4(__WR __char32*,   __char64,   __char64);
void __OVBIFM __vstore_interleave4(__WR __uchar32*,  __uchar64,  __uchar64);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_interleave4(__WR __char16*,   __char32,   __char32);
void __OVBIFM __vstore_interleave4(__WR __uchar16*,  __uchar32,  __uchar32);
#endif

#define __vstore_interleave4(a,b,c) __overload("__vstore_interleave4",(a),(b),(c))((a),(b),(c))

#ifndef __C7100__
/* VSTLLINTB, VSTLLINTH, VSTLLINTW, VSTLLINTD - STORES LOW VECTOR HALVES */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_interleave_low_low(__WR __char64*,   __char64,   __char64);
void __OVBIFM __vstore_interleave_low_low(__WR __short32*,  __short32,  __short32);
void __OVBIFM __vstore_interleave_low_low(__WR __int16*,    __int16,    __int16);
void __OVBIFM __vstore_interleave_low_low(__WR __long8*,    __long8,    __long8);
void __OVBIFM __vstore_interleave_low_low(__WR __uchar64*,  __uchar64,  __uchar64);
void __OVBIFM __vstore_interleave_low_low(__WR __ushort32*, __ushort32, __ushort32);
void __OVBIFM __vstore_interleave_low_low(__WR __uint16*,   __uint16,   __uint16);
void __OVBIFM __vstore_interleave_low_low(__WR __ulong8*,   __ulong8,   __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_interleave_low_low(__WR __char32*,   __char32,   __char32);
void __OVBIFM __vstore_interleave_low_low(__WR __short16*,  __short16,  __short16);
void __OVBIFM __vstore_interleave_low_low(__WR __int8*,    __int8,    __int8);
void __OVBIFM __vstore_interleave_low_low(__WR __long4*,    __long4,    __long4);
void __OVBIFM __vstore_interleave_low_low(__WR __uchar32*,  __uchar32,  __uchar32);
void __OVBIFM __vstore_interleave_low_low(__WR __ushort16*, __ushort16, __ushort16);
void __OVBIFM __vstore_interleave_low_low(__WR __uint8*,   __uint8,   __uint8);
void __OVBIFM __vstore_interleave_low_low(__WR __ulong4*,   __ulong4,   __ulong4);
#endif

/* Half-vector form of VSTLLINT[BHWD]. */  
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_interleave_low_low(__WR __char64*,   __char32,   __char32);
void __OVBIFM __vstore_interleave_low_low(__WR __short32*,  __short16,  __short16);
void __OVBIFM __vstore_interleave_low_low(__WR __int16*,    __int8,    __int8);
void __OVBIFM __vstore_interleave_low_low(__WR __long8*,    __long4,    __long4);
void __OVBIFM __vstore_interleave_low_low(__WR __uchar64*,  __uchar32,  __uchar32);
void __OVBIFM __vstore_interleave_low_low(__WR __ushort32*, __ushort16, __ushort16);
void __OVBIFM __vstore_interleave_low_low(__WR __uint16*,   __uint8,   __uint8);
void __OVBIFM __vstore_interleave_low_low(__WR __ulong8*,   __ulong4,   __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_interleave_low_low(__WR __char32*,   __char16,   __char16);
void __OVBIFM __vstore_interleave_low_low(__WR __short16*,  __short8,  __short8);
void __OVBIFM __vstore_interleave_low_low(__WR __int8*,    __int4,    __int4);
void __OVBIFM __vstore_interleave_low_low(__WR __long4*,    __long2,    __long2);
void __OVBIFM __vstore_interleave_low_low(__WR __uchar32*,  __uchar16,  __uchar16);
void __OVBIFM __vstore_interleave_low_low(__WR __ushort16*, __ushort8, __ushort8);
void __OVBIFM __vstore_interleave_low_low(__WR __uint8*,   __uint4,   __uint4);
void __OVBIFM __vstore_interleave_low_low(__WR __ulong4*,   __ulong2,   __ulong2);
#endif

#define __vstore_interleave_low_low(a,b,c) __overload("__vstore_interleave_low_low",(a),(b),(c))((a),(b),(c))

/* VSTHHINTB, VSTHHINTH, VSTHHINTW, VSTHHINTD - STORES HIGH VECTOR HALVES */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_interleave_high_high(__WR __char64*,   __char64,   __char64);
void __OVBIFM __vstore_interleave_high_high(__WR __short32*,  __short32,  __short32);
void __OVBIFM __vstore_interleave_high_high(__WR __int16*,    __int16,    __int16);
void __OVBIFM __vstore_interleave_high_high(__WR __long8*,    __long8,    __long8);
void __OVBIFM __vstore_interleave_high_high(__WR __uchar64*,  __uchar64,  __uchar64);
void __OVBIFM __vstore_interleave_high_high(__WR __ushort32*, __ushort32, __ushort32);
void __OVBIFM __vstore_interleave_high_high(__WR __uint16*,   __uint16,   __uint16);
void __OVBIFM __vstore_interleave_high_high(__WR __ulong8*,   __ulong8,   __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_interleave_high_high(__WR __char32*,   __char32,   __char32);
void __OVBIFM __vstore_interleave_high_high(__WR __short16*,  __short16,  __short16);
void __OVBIFM __vstore_interleave_high_high(__WR __int8*,    __int8,    __int8);
void __OVBIFM __vstore_interleave_high_high(__WR __long4*,    __long4,    __long4);
void __OVBIFM __vstore_interleave_high_high(__WR __uchar32*,  __uchar32,  __uchar32);
void __OVBIFM __vstore_interleave_high_high(__WR __ushort16*, __ushort16, __ushort16);
void __OVBIFM __vstore_interleave_high_high(__WR __uint8*,   __uint8,   __uint8);
void __OVBIFM __vstore_interleave_high_high(__WR __ulong4*,   __ulong4,   __ulong4);
#endif

#define __vstore_interleave_high_high(a,b,c) __overload("__vstore_interleave_high_high",(a),(b),(c))((a),(b),(c))
#endif /* ! __C7100__ */

/* VSTPINTLB, VSTPINTLH, VSTPINTLW, VSTPINTLD - STORES EVERY EVEN ELEMENT */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_interleave(__bool64, __WR __char64*,  __char64,  __char64);
void __OVBIFM __vstore_pred_interleave(__bool32, __WR __short32*, __short32, __short32);
void __OVBIFM __vstore_pred_interleave(__bool16, __WR __int16*,   __int16,   __int16);
void __OVBIFM __vstore_pred_interleave(__bool8, __WR __long8*,   __long8,   __long8);
void __OVBIFM __vstore_pred_interleave(__bool64, __WR __uchar64*, __uchar64, __uchar64);
void __OVBIFM __vstore_pred_interleave(__bool32, __WR __ushort32*,__ushort32,__ushort32);
void __OVBIFM __vstore_pred_interleave(__bool16, __WR __uint16*,  __uint16,  __uint16);
void __OVBIFM __vstore_pred_interleave(__bool8, __WR __ulong8*,  __ulong8,  __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_interleave(__bool32, __WR __char32*,  __char32,  __char32);
void __OVBIFM __vstore_pred_interleave(__bool16, __WR __short16*, __short16, __short16);
void __OVBIFM __vstore_pred_interleave(__bool8, __WR __int8*,   __int8,   __int8);
void __OVBIFM __vstore_pred_interleave(__bool4, __WR __long4*,   __long4,   __long4);
void __OVBIFM __vstore_pred_interleave(__bool32, __WR __uchar32*, __uchar32, __uchar32);
void __OVBIFM __vstore_pred_interleave(__bool16, __WR __ushort16*,__ushort16,__ushort16);
void __OVBIFM __vstore_pred_interleave(__bool8, __WR __uint8*,  __uint8,  __uint8);
void __OVBIFM __vstore_pred_interleave(__bool4, __WR __ulong4*,  __ulong4,  __ulong4);
#endif

#define __vstore_pred_interleave(a,b,c,d) __overload("__vstore_pred_interleave",(a),(b),(c),(d))((a),(b),(c),(d))

#ifndef __C7100__
/* VSTPINTHB, VSTPINTHH, VSTPINTHW, VSTPINTHD - STORES EVERY ODD ELEMENT */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_interleave_odd(__bool64, __WR __char64*,  __char64,  __char64);
void __OVBIFM __vstore_pred_interleave_odd(__bool32, __WR __short32*, __short32, __short32);
void __OVBIFM __vstore_pred_interleave_odd(__bool16, __WR __int16*,   __int16,   __int16);
void __OVBIFM __vstore_pred_interleave_odd(__bool8, __WR __long8*,   __long8,   __long8);
void __OVBIFM __vstore_pred_interleave_odd(__bool64, __WR __uchar64*, __uchar64, __uchar64);
void __OVBIFM __vstore_pred_interleave_odd(__bool32, __WR __ushort32*,__ushort32,__ushort32);
void __OVBIFM __vstore_pred_interleave_odd(__bool16, __WR __uint16*,  __uint16,  __uint16);
void __OVBIFM __vstore_pred_interleave_odd(__bool8, __WR __ulong8*,  __ulong8,  __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_interleave_odd(__bool32, __WR __char32*,  __char32,  __char32);
void __OVBIFM __vstore_pred_interleave_odd(__bool16, __WR __short16*, __short16, __short16);
void __OVBIFM __vstore_pred_interleave_odd(__bool8, __WR __int8*,   __int8,   __int8);
void __OVBIFM __vstore_pred_interleave_odd(__bool4, __WR __long4*,   __long4,   __long4);
void __OVBIFM __vstore_pred_interleave_odd(__bool32, __WR __uchar32*, __uchar32, __uchar32);
void __OVBIFM __vstore_pred_interleave_odd(__bool16, __WR __ushort16*,__ushort16,__ushort16);
void __OVBIFM __vstore_pred_interleave_odd(__bool8, __WR __uint8*,  __uint8,  __uint8);
void __OVBIFM __vstore_pred_interleave_odd(__bool4, __WR __ulong4*,  __ulong4,  __ulong4);
#endif

#define __vstore_pred_interleave_odd(a,b,c,d) __overload("__vstore_pred_interleave_odd",(a),(b),(c),(d))((a),(b),(c),(d))
#endif /* ! __C7100__ */

/* VSTPINTLB4 - STORES EVERY FOURTH ELEMENT */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_interleave4(__bool32, __WR __char32*,  __char64,   __char64);
void __OVBIFM __vstore_pred_interleave4(__bool32, __WR __uchar32*, __uchar64,  __uchar64);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_interleave4(__bool16, __WR __char16*,  __char32,   __char32);
void __OVBIFM __vstore_pred_interleave4(__bool16, __WR __uchar16*, __uchar32,  __uchar32);
#endif

#define __vstore_pred_interleave4(a,b,c,d) __overload("__vstore_pred_interleave4",(a),(b),(c),(d))((a),(b),(c),(d))

#ifndef __C7100__
/* VSTPLLINTB, VSTPLLINTH, VSTPLLINTW, VSTPLLINTD - STORES LOW VECTOR HALVES */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_interleave_low_low(__bool64, __WR __char64*,  __char64,  __char64);
void __OVBIFM __vstore_pred_interleave_low_low(__bool32, __WR __short32*, __short32, __short32);
void __OVBIFM __vstore_pred_interleave_low_low(__bool16, __WR __int16*,   __int16,   __int16);
void __OVBIFM __vstore_pred_interleave_low_low(__bool8, __WR __long8*,   __long8,   __long8);
void __OVBIFM __vstore_pred_interleave_low_low(__bool64, __WR __uchar64*, __uchar64, __uchar64);
void __OVBIFM __vstore_pred_interleave_low_low(__bool32, __WR __ushort32*,__ushort32,__ushort32);
void __OVBIFM __vstore_pred_interleave_low_low(__bool16, __WR __uint16*,  __uint16,  __uint16);
void __OVBIFM __vstore_pred_interleave_low_low(__bool8, __WR __ulong8*,  __ulong8,  __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_interleave_low_low(__bool32, __WR __char32*,  __char32,  __char32);
void __OVBIFM __vstore_pred_interleave_low_low(__bool16, __WR __short16*, __short16, __short16);
void __OVBIFM __vstore_pred_interleave_low_low(__bool8, __WR __int8*,   __int8,   __int8);
void __OVBIFM __vstore_pred_interleave_low_low(__bool4, __WR __long4*,   __long4,   __long4);
void __OVBIFM __vstore_pred_interleave_low_low(__bool32, __WR __uchar32*, __uchar32, __uchar32);
void __OVBIFM __vstore_pred_interleave_low_low(__bool16, __WR __ushort16*,__ushort16,__ushort16);
void __OVBIFM __vstore_pred_interleave_low_low(__bool8, __WR __uint8*,  __uint8,  __uint8);
void __OVBIFM __vstore_pred_interleave_low_low(__bool4, __WR __ulong4*,  __ulong4,  __ulong4);
#endif

/* Half-vector form of VSTPLLINT[BHWD]. */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_interleave_low_low(__bool64, __WR __char64*,  __char32,  __char32);
void __OVBIFM __vstore_pred_interleave_low_low(__bool32, __WR __short32*, __short16, __short16);
void __OVBIFM __vstore_pred_interleave_low_low(__bool16, __WR __int16*,   __int8,   __int8);
void __OVBIFM __vstore_pred_interleave_low_low(__bool8, __WR __long8*,   __long4,   __long4);
void __OVBIFM __vstore_pred_interleave_low_low(__bool64, __WR __uchar64*, __uchar32, __uchar32);
void __OVBIFM __vstore_pred_interleave_low_low(__bool32, __WR __ushort32*,__ushort16,__ushort16);
void __OVBIFM __vstore_pred_interleave_low_low(__bool16, __WR __uint16*,  __uint8,  __uint8);
void __OVBIFM __vstore_pred_interleave_low_low(__bool8, __WR __ulong8*,  __ulong4,  __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_interleave_low_low(__bool32, __WR __char32*,  __char16,  __char16);
void __OVBIFM __vstore_pred_interleave_low_low(__bool16, __WR __short16*, __short8, __short8);
void __OVBIFM __vstore_pred_interleave_low_low(__bool8, __WR __int8*,   __int4,   __int4);
void __OVBIFM __vstore_pred_interleave_low_low(__bool4, __WR __long4*,   __long2,   __long2);
void __OVBIFM __vstore_pred_interleave_low_low(__bool32, __WR __uchar32*, __uchar16, __uchar16);
void __OVBIFM __vstore_pred_interleave_low_low(__bool16, __WR __ushort16*,__ushort8,__ushort8);
void __OVBIFM __vstore_pred_interleave_low_low(__bool8, __WR __uint8*,  __uint4,  __uint4);
void __OVBIFM __vstore_pred_interleave_low_low(__bool4, __WR __ulong4*,  __ulong2,  __ulong2);
#endif

#define __vstore_pred_interleave_low_low(a,b,c,d) __overload("__vstore_pred_interleave_low_low",(a),(b),(c),(d))((a),(b),(c),(d))

/* VSTPHHINTB, VSTPHHINTH, VSTPHHINTW, VSTPHHINTD - STORES HIGH VECTOR HALVES */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_interleave_high_high(__bool64, __WR __char64*,  __char64,  __char64);
void __OVBIFM __vstore_pred_interleave_high_high(__bool32, __WR __short32*, __short32, __short32);
void __OVBIFM __vstore_pred_interleave_high_high(__bool16, __WR __int16*,   __int16,   __int16);
void __OVBIFM __vstore_pred_interleave_high_high(__bool8, __WR __long8*,   __long8,   __long8);
void __OVBIFM __vstore_pred_interleave_high_high(__bool64, __WR __uchar64*, __uchar64, __uchar64);
void __OVBIFM __vstore_pred_interleave_high_high(__bool32, __WR __ushort32*,__ushort32,__ushort32);
void __OVBIFM __vstore_pred_interleave_high_high(__bool16, __WR __uint16*,  __uint16,  __uint16);
void __OVBIFM __vstore_pred_interleave_high_high(__bool8, __WR __ulong8*,  __ulong8,  __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_interleave_high_high(__bool32, __WR __char32*,  __char32,  __char32);
void __OVBIFM __vstore_pred_interleave_high_high(__bool16, __WR __short16*, __short16, __short16);
void __OVBIFM __vstore_pred_interleave_high_high(__bool8, __WR __int8*,   __int8,   __int8);
void __OVBIFM __vstore_pred_interleave_high_high(__bool4, __WR __long4*,   __long4,   __long4);
void __OVBIFM __vstore_pred_interleave_high_high(__bool32, __WR __uchar32*, __uchar32, __uchar32);
void __OVBIFM __vstore_pred_interleave_high_high(__bool16, __WR __ushort16*,__ushort16,__ushort16);
void __OVBIFM __vstore_pred_interleave_high_high(__bool8, __WR __uint8*,  __uint8,  __uint8);
void __OVBIFM __vstore_pred_interleave_high_high(__bool4, __WR __ulong4*,  __ulong4,  __ulong4);
#endif

#define __vstore_pred_interleave_high_high(a,b,c,d) __overload("__vstore_pred_interleave_high_high",(a),(b),(c),(d))((a),(b),(c),(d))
#endif /* ! __C7100__ */

/* VSTP2B, VSTP4B, VSTP8B, VSTP16B, VSTP32B, VSTP64B */
void __OVBIFM __vstore_pred(__bool2,  __WR __char2*,   __char2);
void __OVBIFM __vstore_pred(__bool4,  __WR __char4*,   __char4);
void __OVBIFM __vstore_pred(__bool8,  __WR __char8*,   __char8);
void __OVBIFM __vstore_pred(__bool16, __WR __char16*,  __char16);
void __OVBIFM __vstore_pred(__bool32, __WR __char32*,  __char32);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__bool64, __WR __char64*,  __char64);
#endif

void __OVBIFM __vstore_pred(__bool2,  __WR __uchar2*,  __uchar2);
void __OVBIFM __vstore_pred(__bool4,  __WR __uchar4*,  __uchar4);
void __OVBIFM __vstore_pred(__bool8,  __WR __uchar8*,  __uchar8);
void __OVBIFM __vstore_pred(__bool16, __WR __uchar16*, __uchar16);
void __OVBIFM __vstore_pred(__bool32, __WR __uchar32*, __uchar32);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__bool64, __WR __uchar64*, __uchar64);
#endif

/* VSTP2H, VSTP4H, VSTP8H, VSTP16H, VSTP32H */
void __OVBIFM __vstore_pred(__bool2,  __WR __short2*, __short2);
void __OVBIFM __vstore_pred(__bool4,  __WR __short4*, __short4);
void __OVBIFM __vstore_pred(__bool8,  __WR __short8*, __short8);
void __OVBIFM __vstore_pred(__bool16, __WR __short16*, __short16);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__bool32, __WR __short32*, __short32);
#endif

void __OVBIFM __vstore_pred(__bool2,  __WR __ushort2*, __ushort2);
void __OVBIFM __vstore_pred(__bool4,  __WR __ushort4*, __ushort4);
void __OVBIFM __vstore_pred(__bool8,  __WR __ushort8*, __ushort8);
void __OVBIFM __vstore_pred(__bool16, __WR __ushort16*, __ushort16);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__bool32, __WR __ushort32*, __ushort32);
#endif

void __OVBIFM __vstore_pred(__bool2,  __WR __cchar2*, __cchar2);
void __OVBIFM __vstore_pred(__bool4,  __WR __cchar4*, __cchar4);
void __OVBIFM __vstore_pred(__bool8,  __WR __cchar8*, __cchar8);
void __OVBIFM __vstore_pred(__bool16, __WR __cchar16*, __cchar16);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__bool32, __WR __cchar32*, __cchar32);
#endif

/* VSTP2W, VSTP4W, VSTP8W, VSTP16W */
void __OVBIFM __vstore_pred(__bool2,  __WR __int2*,     __int2);
void __OVBIFM __vstore_pred(__bool4,  __WR __int4*,     __int4);
void __OVBIFM __vstore_pred(__bool8,  __WR __int8*,     __int8);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__bool16, __WR __int16*,    __int16);
#endif

void __OVBIFM __vstore_pred(__bool2,  __WR __uint2*,    __uint2);
void __OVBIFM __vstore_pred(__bool4,  __WR __uint4*,    __uint4);
void __OVBIFM __vstore_pred(__bool8,  __WR __uint8*,    __uint8);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__bool16, __WR __uint16*,   __uint16);
#endif

void __OVBIFM __vstore_pred(__bool2,  __WR __float2*,   __float2);
void __OVBIFM __vstore_pred(__bool4,  __WR __float4*,   __float4);
void __OVBIFM __vstore_pred(__bool8,  __WR __float8*,   __float8);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__bool16, __WR __float16*,  __float16);
#endif

void __OVBIFM __vstore_pred(__bool2,  __WR __cshort2*,  __cshort2);
void __OVBIFM __vstore_pred(__bool4,  __WR __cshort4*,  __cshort4);
void __OVBIFM __vstore_pred(__bool8,  __WR __cshort8*,  __cshort8);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__bool16, __WR __cshort16*, __cshort16);
#endif

/* VSTP2D, VSTP4D, VSTP8D */
void __OVBIFM __vstore_pred(__bool2, __WR __long2*,   __long2);
void __OVBIFM __vstore_pred(__bool4, __WR __long4*,   __long4);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__bool8, __WR __long8*,   __long8);
#endif

void __OVBIFM __vstore_pred(__bool2, __WR __ulong2*,  __ulong2);
void __OVBIFM __vstore_pred(__bool4, __WR __ulong4*,  __ulong4);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__bool8, __WR __ulong8*,  __ulong8);
#endif

void __OVBIFM __vstore_pred(__bool2, __WR __double2*, __double2);
void __OVBIFM __vstore_pred(__bool4, __WR __double4*, __double4);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__bool8, __WR __double8*, __double8);
#endif

void __OVBIFM __vstore_pred(__bool2, __WR __cint2*,   __cint2);
void __OVBIFM __vstore_pred(__bool4, __WR __cint4*,   __cint4);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__bool8, __WR __cint8*,   __cint8);
#endif

void __OVBIFM __vstore_pred(__bool2, __WR __cfloat2*, __cfloat2);
void __OVBIFM __vstore_pred(__bool4, __WR __cfloat4*, __cfloat4);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__bool8, __WR __cfloat8*, __cfloat8);
#endif

#define __vstore_pred(a,b,c) __overload("__vstore_pred",(a),(b),(c))((a),(b),(c))

/* VSTPBSVPACKL, VSTPBSVPACKH, VSTPBSVPACKHS1: PRED CORRESPONDS TO SRC DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_packl(__bool16,   __WR __char16*,  __short16);
void __OVBIFM __vstore_pred_packl(__bool16,   __WR __uchar16*, __ushort16);
void __OVBIFM __vstore_pred_packh(__bool16,   __WR __char16*,  __short16);
void __OVBIFM __vstore_pred_packh(__bool16,   __WR __uchar16*, __ushort16);
void __OVBIFM __vstore_pred_packhs1(__bool16, __WR __char16*,  __short16);
void __OVBIFM __vstore_pred_packhs1(__bool16, __WR __uchar16*, __ushort16);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_packl(__bool32,   __WR __char32*,  __short32);
void __OVBIFM __vstore_pred_packl(__bool32,   __WR __uchar32*, __ushort32);
void __OVBIFM __vstore_pred_packh(__bool32,   __WR __char32*,  __short32);
void __OVBIFM __vstore_pred_packh(__bool32,   __WR __uchar32*, __ushort32);
void __OVBIFM __vstore_pred_packhs1(__bool32, __WR __char32*,  __short32);
void __OVBIFM __vstore_pred_packhs1(__bool32, __WR __uchar32*, __ushort32);
#endif

/* VSTPHSVPACKL, VSTPHSVPACKH, VSTPHSVPACKHS1: PRED CORRESPONDS TO SRC DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_packl(__bool8,   __WR __short8*,  __int8);
void __OVBIFM __vstore_pred_packl(__bool8,   __WR __ushort8*, __uint8);
void __OVBIFM __vstore_pred_packh(__bool8,   __WR __short8*,  __int8);
void __OVBIFM __vstore_pred_packh(__bool8,   __WR __ushort8*, __uint8);
void __OVBIFM __vstore_pred_packhs1(__bool8, __WR __short8*,  __int8);
void __OVBIFM __vstore_pred_packhs1(__bool8, __WR __ushort8*, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_packl(__bool16,   __WR __short16*,  __int16);
void __OVBIFM __vstore_pred_packl(__bool16,   __WR __ushort16*, __uint16);
void __OVBIFM __vstore_pred_packh(__bool16,   __WR __short16*,  __int16);
void __OVBIFM __vstore_pred_packh(__bool16,   __WR __ushort16*, __uint16);
void __OVBIFM __vstore_pred_packhs1(__bool16, __WR __short16*,  __int16);
void __OVBIFM __vstore_pred_packhs1(__bool16, __WR __ushort16*, __uint16);
#endif

/* VSTPWSVPACKB: PRED CORRESPONDS TO SRC DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_pack_byte(__bool8, __WR __char8*,  __int8);
void __OVBIFM __vstore_pred_pack_byte(__bool8, __WR __uchar8*, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_pack_byte(__bool16, __WR __char16*,  __int16);
void __OVBIFM __vstore_pred_pack_byte(__bool16, __WR __uchar16*, __uint16);
#endif

/* VSTPWSVPACKL, VSTPWSVPACKH, VSTPWSVPACKHS1: PRED CORRESPONDS TO SRC DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_packl(__bool4,   __WR __int4*,  __long4);
void __OVBIFM __vstore_pred_packl(__bool4,   __WR __uint4*, __ulong4);
void __OVBIFM __vstore_pred_packh(__bool4,   __WR __int4*,  __long4);
void __OVBIFM __vstore_pred_packh(__bool4,   __WR __uint4*, __ulong4);
void __OVBIFM __vstore_pred_packhs1(__bool4, __WR __int4*,  __long4);
void __OVBIFM __vstore_pred_packhs1(__bool4, __WR __uint4*, __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_packl(__bool8,   __WR __int8*,  __long8);
void __OVBIFM __vstore_pred_packl(__bool8,   __WR __uint8*, __ulong8);
void __OVBIFM __vstore_pred_packh(__bool8,   __WR __int8*,  __long8);
void __OVBIFM __vstore_pred_packh(__bool8,   __WR __uint8*, __ulong8);
void __OVBIFM __vstore_pred_packhs1(__bool8, __WR __int8*,  __long8);
void __OVBIFM __vstore_pred_packhs1(__bool8, __WR __uint8*, __ulong8);
#endif

#define __vstore_pred_packl(a,b,c) __overload("__vstore_pred_packl",(a),(b),(c))((a),(b),(c))
#define __vstore_pred_packh(a,b,c) __overload("__vstore_pred_packh",(a),(b),(c))((a),(b),(c))
#define __vstore_pred_packhs1(a,b,c) __overload("__vstore_pred_packhs1",(a),(b),(c))((a),(b),(c))
#define __vstore_pred_pack_byte(a,b,c) __overload("__vstore_pred_pack_byte",(a),(b),(c))((a),(b),(c))

/* VSTPBPACKL, VSTPBPACKH, VSTPBPACKHS1: PRED CORRESPONDS TO PACKED DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_packl_2src(__bool32,   __WR __char32*, __short16,  __short16);
void __OVBIFM __vstore_pred_packl_2src(__bool32,   __WR __uchar32*, __ushort16, __ushort16);
void __OVBIFM __vstore_pred_packh_2src(__bool32,   __WR __char32*, __short16,  __short16);
void __OVBIFM __vstore_pred_packh_2src(__bool32,   __WR __uchar32*, __ushort16, __ushort16);
void __OVBIFM __vstore_pred_packhs1_2src(__bool32, __WR __char32*, __short16,  __short16);
void __OVBIFM __vstore_pred_packhs1_2src(__bool32, __WR __uchar32*, __ushort16, __ushort16);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_packl_2src(__bool64,   __WR __char64*, __short32,  __short32);
void __OVBIFM __vstore_pred_packl_2src(__bool64,   __WR __uchar64*, __ushort32, __ushort32);
void __OVBIFM __vstore_pred_packh_2src(__bool64,   __WR __char64*, __short32,  __short32);
void __OVBIFM __vstore_pred_packh_2src(__bool64,   __WR __uchar64*, __ushort32, __ushort32);
void __OVBIFM __vstore_pred_packhs1_2src(__bool64, __WR __char64*, __short32,  __short32);
void __OVBIFM __vstore_pred_packhs1_2src(__bool64, __WR __uchar64*, __ushort32, __ushort32);
#endif

/* VSTPHPACKL, VSTPHPACKH, VSTPHPACKHS1: PRED CORRESPONDS TO PACKED DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_packl_2src(__bool16,   __WR __short16*, __int8,   __int8);
void __OVBIFM __vstore_pred_packl_2src(__bool16,   __WR __ushort16*, __uint8, __uint8);
void __OVBIFM __vstore_pred_packh_2src(__bool16,   __WR __short16*, __int8,   __int8);
void __OVBIFM __vstore_pred_packh_2src(__bool16,   __WR __ushort16*, __uint8, __uint8);
void __OVBIFM __vstore_pred_packhs1_2src(__bool16, __WR __short16*, __int8,   __int8);
void __OVBIFM __vstore_pred_packhs1_2src(__bool16, __WR __ushort16*, __uint8, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_packl_2src(__bool32,   __WR __short32*, __int16,   __int16);
void __OVBIFM __vstore_pred_packl_2src(__bool32,   __WR __ushort32*, __uint16, __uint16);
void __OVBIFM __vstore_pred_packh_2src(__bool32,   __WR __short32*, __int16,   __int16);
void __OVBIFM __vstore_pred_packh_2src(__bool32,   __WR __ushort32*, __uint16, __uint16);
void __OVBIFM __vstore_pred_packhs1_2src(__bool32, __WR __short32*, __int16,   __int16);
void __OVBIFM __vstore_pred_packhs1_2src(__bool32, __WR __ushort32*, __uint16, __uint16);
#endif

/* VSTPWPACKB: PRED CORRESPONDS TO PACKED DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_pack_byte_2src(__bool16, __WR __char16*, __int8,  __int8);
void __OVBIFM __vstore_pred_pack_byte_2src(__bool16, __WR __uchar16*, __uint8, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_pack_byte_2src(__bool32, __WR __char32*, __int16,  __int16);
void __OVBIFM __vstore_pred_pack_byte_2src(__bool32, __WR __uchar32*, __uint16, __uint16);
#endif

/* VSTPWPACKL, VSTPWPACKH, VSTPWPACKHS1: PRED CORRESPONDS TO PACKED DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_packl_2src(__bool8,   __WR __int8*, __long4,  __long4);
void __OVBIFM __vstore_pred_packl_2src(__bool8,   __WR __uint8*, __ulong4, __ulong4);
void __OVBIFM __vstore_pred_packh_2src(__bool8,   __WR __int8*, __long4,   __long4);
void __OVBIFM __vstore_pred_packh_2src(__bool8,   __WR __uint8*, __ulong4, __ulong4);
void __OVBIFM __vstore_pred_packhs1_2src(__bool8, __WR __int8*, __long4,   __long4);
void __OVBIFM __vstore_pred_packhs1_2src(__bool8, __WR __uint8*, __ulong4, __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_packl_2src(__bool16,   __WR __int16*, __long8,  __long8);
void __OVBIFM __vstore_pred_packl_2src(__bool16,   __WR __uint16*, __ulong8, __ulong8);
void __OVBIFM __vstore_pred_packh_2src(__bool16,   __WR __int16*, __long8,   __long8);
void __OVBIFM __vstore_pred_packh_2src(__bool16,   __WR __uint16*, __ulong8, __ulong8);
void __OVBIFM __vstore_pred_packhs1_2src(__bool16, __WR __int16*, __long8,   __long8);
void __OVBIFM __vstore_pred_packhs1_2src(__bool16, __WR __uint16*, __ulong8, __ulong8);
#endif

/* VSTPDPACKL, VSTPDPACKH, VSTPDPACKHS1: PRED CORRESPONDS TO PACKED DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_packl_long_2src(__bool4,   __WR __long4*, __long4, __long4);
void __OVBIFM __vstore_pred_packl_long_2src(__bool4,   __WR __ulong4*, __ulong4,__ulong4);
void __OVBIFM __vstore_pred_packh_long_2src(__bool4,   __WR __long4*, __long4, __long4);
void __OVBIFM __vstore_pred_packh_long_2src(__bool4,   __WR __ulong4*, __ulong4,__ulong4);
void __OVBIFM __vstore_pred_packhs1_long_2src(__bool4, __WR __long4*, __long4, __long4);
void __OVBIFM __vstore_pred_packhs1_long_2src(__bool4, __WR __ulong4*, __ulong4,__ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_packl_long_2src(__bool8,   __WR __long8*, __long8, __long8);
void __OVBIFM __vstore_pred_packl_long_2src(__bool8,   __WR __ulong8*, __ulong8,__ulong8);
void __OVBIFM __vstore_pred_packh_long_2src(__bool8,   __WR __long8*, __long8, __long8);
void __OVBIFM __vstore_pred_packh_long_2src(__bool8,   __WR __ulong8*, __ulong8,__ulong8);
void __OVBIFM __vstore_pred_packhs1_long_2src(__bool8, __WR __long8*, __long8, __long8);
void __OVBIFM __vstore_pred_packhs1_long_2src(__bool8, __WR __ulong8*, __ulong8,__ulong8);
#endif

#define __vstore_pred_packl_2src(a,b,c,d) __overload("__vstore_pred_packl_2src",(a),(b),(c),(d))((a),(b),(c),(d))
#define __vstore_pred_packh_2src(a,b,c,d) __overload("__vstore_pred_packh_2src",(a),(b),(c),(d))((a),(b),(c),(d))
#define __vstore_pred_packhs1_2src(a,b,c,d) __overload("__vstore_pred_packhs1_2src",(a),(b),(c),(d))((a),(b),(c),(d))
#define __vstore_pred_pack_byte_2src(a,b,c,d) __overload("__vstore_pred_pack_byte_2src",(a),(b),(c),(d))((a),(b),(c),(d))
#define __vstore_pred_packl_long_2src(a,b,c,d) __overload("__vstore_pred_packl_long_2src",(a),(b),(c),(d))((a),(b),(c),(d))
#define __vstore_pred_packh_long_2src(a,b,c,d) __overload("__vstore_pred_packh_long_2src",(a),(b),(c),(d))((a),(b),(c),(d))
#define __vstore_pred_packhs1_long_2src(a,b,c,d) __overload("__vstore_pred_packhs1_long_2src",(a),(b),(c),(d))((a),(b),(c),(d))

/* VSTPBITRWH */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_reverse_bit(__bool16, __WR __cshort16*, __cshort16);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_reverse_bit(__bool8, __WR __cshort8*, __cshort8);
#endif

/* VSTPBITRDW */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_reverse_bit(__bool8, __WR __cint8*,   __cint8);
void __OVBIFM __vstore_pred_reverse_bit(__bool8, __WR __cfloat8*, __cfloat8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_reverse_bit(__bool4, __WR __cint4*,   __cint4);
void __OVBIFM __vstore_pred_reverse_bit(__bool4, __WR __cfloat4*, __cfloat4);
#endif

#define __vstore_pred_reverse_bit(a,b,c) __overload("__vstore_pred_reverse_bit",(a),(b),(c))((a),(b),(c))

/* STKW, ST0KW */
void __BIFM __vstore_const       (__WR __uint*,   __CST_RANGE __uint);

/* VSTK2W, VST0K2W */
void __BIFM __vstore_const_uint2 (__WR __uint2*,  __CST_RANGE __uint);

/* VSTK4W, VST0K4W */
void __BIFM __vstore_const_uint4 (__WR __uint4*,  __CST_RANGE __uint);

/* VSTK8W, VST0K8W */
void __BIFM __vstore_const_uint8 (__WR __uint8*,  __CST_RANGE __uint);

/* VSTK16W, VST0K16W */
#if __C7X_VEC_SIZE_BITS__ >= 512
void __BIFM __vstore_const_uint16(__WR __uint16*, __CST_RANGE __uint);
#endif

/* VSTBSVPACKL, VSTBSVPACKH, VSTBSVPACKHS1 */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_packl(__WR __char16*, __short16);
void __OVBIFM __vstore_packl(__WR __uchar16*, __ushort16);
void __OVBIFM __vstore_packh(__WR __char16*, __short16);
void __OVBIFM __vstore_packh(__WR __uchar16*, __ushort16);
void __OVBIFM __vstore_packhs1(__WR __char16*, __short16);
void __OVBIFM __vstore_packhs1(__WR __uchar16*, __ushort16);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_packl(__WR __char32*, __short32);
void __OVBIFM __vstore_packl(__WR __uchar32*, __ushort32);
void __OVBIFM __vstore_packh(__WR __char32*, __short32);
void __OVBIFM __vstore_packh(__WR __uchar32*, __ushort32);
void __OVBIFM __vstore_packhs1(__WR __char32*, __short32);
void __OVBIFM __vstore_packhs1(__WR __uchar32*, __ushort32);
#endif

/* VSTHSVPACKL, VSTHSVPACKH, VSTHSVPACKHS1 */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_packl(__WR __short8*, __int8);
void __OVBIFM __vstore_packl(__WR __ushort8*, __uint8);
void __OVBIFM __vstore_packh(__WR __short8*, __int8);
void __OVBIFM __vstore_packh(__WR __ushort8*, __uint8);
void __OVBIFM __vstore_packhs1(__WR __short8*, __int8);
void __OVBIFM __vstore_packhs1(__WR __ushort8*, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_packl(__WR __short16*, __int16);
void __OVBIFM __vstore_packl(__WR __ushort16*, __uint16);
void __OVBIFM __vstore_packh(__WR __short16*, __int16);
void __OVBIFM __vstore_packh(__WR __ushort16*, __uint16);
void __OVBIFM __vstore_packhs1(__WR __short16*, __int16);
void __OVBIFM __vstore_packhs1(__WR __ushort16*, __uint16);
#endif

/* VSTWSVPACKB */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pack_byte(__WR __char8*, __int8);
void __OVBIFM __vstore_pack_byte(__WR __uchar8*, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pack_byte(__WR __char16*, __int16);
void __OVBIFM __vstore_pack_byte(__WR __uchar16*, __uint16);
#endif

/* VSTWSVPACKL, VSTWSVPACKH, VSTWSVPACKHS1 */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_packl(__WR __int4*, __long4);
void __OVBIFM __vstore_packl(__WR __uint4*, __ulong4);
void __OVBIFM __vstore_packh(__WR __int4*, __long4);
void __OVBIFM __vstore_packh(__WR __uint4*, __ulong4);
void __OVBIFM __vstore_packhs1(__WR __int4*, __long4);
void __OVBIFM __vstore_packhs1(__WR __uint4*, __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_packl(__WR __int8*, __long8);
void __OVBIFM __vstore_packl(__WR __uint8*, __ulong8);
void __OVBIFM __vstore_packh(__WR __int8*, __long8);
void __OVBIFM __vstore_packh(__WR __uint8*, __ulong8);
void __OVBIFM __vstore_packhs1(__WR __int8*, __long8);
void __OVBIFM __vstore_packhs1(__WR __uint8*, __ulong8);
#endif

/* VSTDSVPACKL, VSTDSVPACKH, VSTDSVPACKHS1 */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_packl(__WR __long2*, __long4);
void __OVBIFM __vstore_packl(__WR __ulong2*, __ulong4);
void __OVBIFM __vstore_packh(__WR __long2*, __long4);
void __OVBIFM __vstore_packh(__WR __ulong2*, __ulong4);
void __OVBIFM __vstore_packhs1(__WR __long2*, __long4);
void __OVBIFM __vstore_packhs1(__WR __ulong2*, __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_packl(__WR __long4*, __long8);
void __OVBIFM __vstore_packl(__WR __ulong4*, __ulong8);
void __OVBIFM __vstore_packh(__WR __long4*, __long8);
void __OVBIFM __vstore_packh(__WR __ulong4*, __ulong8);
void __OVBIFM __vstore_packhs1(__WR __long4*, __long8);
void __OVBIFM __vstore_packhs1(__WR __ulong4*, __ulong8);
#endif

#define __vstore_packl(a,b) __overload("__vstore_packl",(a),(b))((a),(b))
#define __vstore_packh(a,b) __overload("__vstore_packh",(a),(b))((a),(b))
#define __vstore_packhs1(a,b) __overload("__vstore_packhs1",(a),(b))((a),(b))
#define __vstore_pack_byte(a,b) __overload("__vstore_pack_byte",(a),(b))((a),(b))

/* VSTBPACKL, VSTBPACKH, VSTBPACKHS1 */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_packl_2src(__WR __char32*, __short16, __short16);
void __OVBIFM __vstore_packl_2src(__WR __uchar32*, __ushort16, __ushort16);
void __OVBIFM __vstore_packh_2src(__WR __char32*, __short16, __short16);
void __OVBIFM __vstore_packh_2src(__WR __uchar32*, __ushort16, __ushort16);
void __OVBIFM __vstore_packhs1_2src(__WR __char32*, __short16, __short16);
void __OVBIFM __vstore_packhs1_2src(__WR __uchar32*, __ushort16, __ushort16);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_packl_2src(__WR __char64*, __short32, __short32);
void __OVBIFM __vstore_packl_2src(__WR __uchar64*, __ushort32, __ushort32);
void __OVBIFM __vstore_packh_2src(__WR __char64*, __short32, __short32);
void __OVBIFM __vstore_packh_2src(__WR __uchar64*, __ushort32, __ushort32);
void __OVBIFM __vstore_packhs1_2src(__WR __char64*, __short32, __short32);
void __OVBIFM __vstore_packhs1_2src(__WR __uchar64*, __ushort32, __ushort32);
#endif

/* VSTHPACKL, VSTHPACKH, VSTHPACKHS1 */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_packl_2src(__WR __short16*, __int8, __int8);
void __OVBIFM __vstore_packl_2src(__WR __ushort16*, __uint8, __uint8);
void __OVBIFM __vstore_packh_2src(__WR __short16*, __int8, __int8);
void __OVBIFM __vstore_packh_2src(__WR __ushort16*, __uint8, __uint8);
void __OVBIFM __vstore_packhs1_2src(__WR __short16*, __int8, __int8);
void __OVBIFM __vstore_packhs1_2src(__WR __ushort16*, __uint8, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_packl_2src(__WR __short32*, __int16, __int16);
void __OVBIFM __vstore_packl_2src(__WR __ushort32*, __uint16, __uint16);
void __OVBIFM __vstore_packh_2src(__WR __short32*, __int16, __int16);
void __OVBIFM __vstore_packh_2src(__WR __ushort32*, __uint16, __uint16);
void __OVBIFM __vstore_packhs1_2src(__WR __short32*, __int16, __int16);
void __OVBIFM __vstore_packhs1_2src(__WR __ushort32*, __uint16, __uint16);
#endif

/* VSTWPACKB */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pack_byte_2src(__WR __char16*, __int8, __int8);
void __OVBIFM __vstore_pack_byte_2src(__WR __uchar16*, __uint8, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pack_byte_2src(__WR __char32*, __int16, __int16);
void __OVBIFM __vstore_pack_byte_2src(__WR __uchar32*, __uint16, __uint16);
#endif

/* VSTWPACKL, VSTWPACKH, VSTWPACKHS1 */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_packl_2src(__WR __int8*, __long4, __long4);
void __OVBIFM __vstore_packl_2src(__WR __uint8*, __ulong4, __ulong4);
void __OVBIFM __vstore_packh_2src(__WR __int8*, __long4, __long4);
void __OVBIFM __vstore_packh_2src(__WR __uint8*, __ulong4, __ulong4);
void __OVBIFM __vstore_packhs1_2src(__WR __int8*, __long4, __long4);
void __OVBIFM __vstore_packhs1_2src(__WR __uint8*, __ulong4, __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_packl_2src(__WR __int16*, __long8, __long8);
void __OVBIFM __vstore_packl_2src(__WR __uint16*, __ulong8, __ulong8);
void __OVBIFM __vstore_packh_2src(__WR __int16*, __long8, __long8);
void __OVBIFM __vstore_packh_2src(__WR __uint16*, __ulong8, __ulong8);
void __OVBIFM __vstore_packhs1_2src(__WR __int16*, __long8, __long8);
void __OVBIFM __vstore_packhs1_2src(__WR __uint16*, __ulong8, __ulong8);
#endif

/* VSTDPACKL, VSTDPACKH, VSTDPACKHS1 */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_packl_2src(__WR __long4*, __long4, __long4);
void __OVBIFM __vstore_packl_2src(__WR __ulong4*, __ulong4, __ulong4);
void __OVBIFM __vstore_packh_2src(__WR __long4*, __long4, __long4);
void __OVBIFM __vstore_packh_2src(__WR __ulong4*, __ulong4, __ulong4);
void __OVBIFM __vstore_packhs1_2src(__WR __long4*, __long4, __long4);
void __OVBIFM __vstore_packhs1_2src(__WR __ulong4*, __ulong4, __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_packl_2src(__WR __long8*, __long8, __long8);
void __OVBIFM __vstore_packl_2src(__WR __ulong8*, __ulong8, __ulong8);
void __OVBIFM __vstore_packh_2src(__WR __long8*, __long8, __long8);
void __OVBIFM __vstore_packh_2src(__WR __ulong8*, __ulong8, __ulong8);
void __OVBIFM __vstore_packhs1_2src(__WR __long8*, __long8, __long8);
void __OVBIFM __vstore_packhs1_2src(__WR __ulong8*, __ulong8, __ulong8);
#endif

#define __vstore_packl_2src(a,b,c) __overload("__vstore_packl_2src",(a),(b),(c))((a),(b),(c))
#define __vstore_packh_2src(a,b,c) __overload("__vstore_packh_2src",(a),(b),(c))((a),(b),(c))
#define __vstore_packhs1_2src(a,b,c) __overload("__vstore_packhs1_2src",(a),(b),(c))((a),(b),(c))
#define __vstore_pack_byte_2src(a,b,c) __overload("__vstore_pack_byte_2src",(a),(b),(c))((a),(b),(c))

/* VSTBITRWH */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_reverse_bit(__WR __short32*, __short32);
void __OVBIFM __vstore_reverse_bit(__WR __ushort32*, __ushort32);
void __OVBIFM __vstore_reverse_bit(__WR __cshort16*, __cshort16);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_reverse_bit(__WR __short16*, __short16);
void __OVBIFM __vstore_reverse_bit(__WR __ushort16*, __ushort16);
void __OVBIFM __vstore_reverse_bit(__WR __cshort8*, __cshort8);
#endif

/* VSTBITRDW */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_reverse_bit(__WR __int16*, __int16);
void __OVBIFM __vstore_reverse_bit(__WR __uint16*, __uint16);
void __OVBIFM __vstore_reverse_bit(__WR __float16*, __float16);
void __OVBIFM __vstore_reverse_bit(__WR __cint8*, __cint8);
void __OVBIFM __vstore_reverse_bit(__WR __cfloat8*, __cfloat8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_reverse_bit(__WR __int8*, __int8);
void __OVBIFM __vstore_reverse_bit(__WR __uint8*, __uint8);
void __OVBIFM __vstore_reverse_bit(__WR __float8*, __float8);
void __OVBIFM __vstore_reverse_bit(__WR __cint4*, __cint4);
void __OVBIFM __vstore_reverse_bit(__WR __cfloat4*, __cfloat4);
#endif

#define __vstore_reverse_bit(a,b) __overload("__vstore_reverse_bit",(a),(b))((a),(b))

/* ASW */
int      __OVBIFM __atomic_swap(__WR int*, int, int);

/* ASD */
long     __OVBIFM __atomic_swap(__WR long*, long, long);

#define __atomic_swap(a,b,c) __overload("__atomic_swap",(a),(b),(c))((a),(b),(c))

/* CASW */
int      __OVBIFM __atomic_compare_swap(__WR int*, int, int);

/* CASD */
long     __OVBIFM __atomic_compare_swap(__WR long*, long, long);

#define __atomic_compare_swap(a,b,c) __overload("__atomic_compare_swap",(a),(b),(c))((a),(b),(c))

/* PFS */
void __BIFM __prefetch(void*, __CST(0, 31) unsigned);

/* MTAG argument */
typedef enum __attribute__((__packed__))
{
    __MTAG_COLOR0        = 0x0,
    __MTAG_COLOR1        = 0x1,
    __MTAG_SWITCH_COLORS = 0x1f
} __MTAG_COLOR;

/* MTAG */
void __BIFM __mtag(__CST(0, 31) __MTAG_COLOR);

/* MFENCE/MFENCEST argument */
typedef enum __attribute__((__packed__))
{
    __MFENCE_COLOR0     = 0x0,
    __MFENCE_COLOR1     = 0x1,
    __MFENCE_ALL_COLORS = 0x1f
} __MFENCE_COLOR;

/* MFENCE */
void __BIFM __memory_fence(__CST(0, 31) __MFENCE_COLOR);

/* MFENCEST */
void __BIFM __memory_fence_store(__CST(0, 31) __MFENCE_COLOR);

/*-----------------------------------------------------------------------------
* Extract and Duplicate
*-----------------------------------------------------------------------------
* VGETDUPB (C syntax -- using intrinsic or cast):
*         char64 src, dst;
*         dst = __duplicate(src.s[10]);  OR
*         dst = char64(src.s[10]);
*
* VGETDUPH (C syntax -- using intrinsic or cast):
*         short32 src, dst;
*         dst = __duplicate(src.s[10]);   OR
*         dst = short32(src.s[10]);
*
* VGETDUPW (C syntax -- using intrinsic or cast):
*         int16 src, dst;
*         dst = __duplicate(src.s[7]);   OR
*         dst = int16(src.s[7]);
*
* VGETDUPD (C syntax -- using intrinsic or cast):
*         long8 src, dst;
*         dst = __duplicate(src.s[7]);   OR
*         dst = long8(src.s[7]);
*----------------------------------------------------------------------------*/

/******************************************************************************/
/* The following is a full list of intrinsics and operations available using  */
/* vector types. In addition, each example will also show the C7000           */
/* instruction to which the intrinsic will map.                               */
/*                                                                            */
/* In cases of vectors, constants must be converted to the proper vector type */
/* for the intrinsic to match properly.                                       */
/* E.g: For a vector addition of char8 a by constant 4, the code should be    */
/*      written: a + char8(4)                                                 */
/*                                                                            */
/* NOTE:                                                                      */
/*                                                                            */
/* There are a handful of complicated instructions that cannot be accessed    */
/* using the below vector intrinsics or C idioms. Please refer to the list of */
/* direct-mapped intrinsics listed in c7x_direct.h for the following          */
/* instructions:                                                              */
/*                                                                            */
/*  'EXTV'                                                                    */
/*  'EXTUV'                                                                   */
/*  'REPLACEV'                                                                */
/*  'VFIR8HD'                                                                 */
/*  'VFIR8HW'                                                                 */
/*  'VFIR8SUHD'                                                               */
/*  'VFIR8SUHW'                                                               */
/*  'VFIR8UHD'                                                                */
/*  'VFIR8UHW'                                                                */
/*  'VMATMPYHD'                                                               */
/*  'VMATMPYSP'                                                               */
/*  'VMATMPYSUHD'                                                             */
/*  'VMATMPYSUHW'                                                             */
/*  'VMATMPYUHD'                                                              */
/*  'VMATMPYUHW'                                                              */
/*  'VMATMPYUSHD'                                                             */
/*  'VSAD16OU16H16W'                                                          */
/*  'VSAD16OU8H16W'                                                           */
/*  'VSAD8OU16B32H'                                                           */
/*  'VSADM16OU16H16W'                                                         */
/*  'VSADM16OU8H16W'                                                          */
/*  'VSADM8OU16B32H'                                                          */
/*  'VDSAD16OU8H8W'                                                           */
/*  'VDSAD8OU16B16H'                                                          */
/*  'VDSADM16OU8H8W'                                                          */
/*  'VDSADM8OU16B16H'                                                         */
/*  'VCDOTPM2OPN16B32H'                                                       */
/*  'VCDOTPM2OPN1H32H'                                                        */
/*  'VCDOTPM2OPN8H16W'                                                        */
/*  'VCDOTPM2OPN8W16W'                                                        */
/*  'VCDOTPM32OPN16B32H'                                                      */
/*                                                                            */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* ID: __gather_set_bits                                                      */
/*----------------------------------------------------------------------------*/
/*

VGATHERB
char2 = __gather_set_bits(bool2, char2);
char3 = __gather_set_bits(bool3, char3);
char4 = __gather_set_bits(bool4, char4);
char8 = __gather_set_bits(bool8, char8);
char16 = __gather_set_bits(bool16, char16);
char32 = __gather_set_bits(bool32, char32);
#if __C7X_VEC_SIZE_BITS__ >= 512
char64 = __gather_set_bits(bool64, char64);
#endif

*/

#define __gather_set_bits(a,b) __overload("__gather_set_bits",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __gather_unset_bits                                                    */
/*----------------------------------------------------------------------------*/
/*

VGATHERNB
char2 = __gather_unset_bits(bool2, char2);
char3 = __gather_unset_bits(bool3, char3);
char4 = __gather_unset_bits(bool4, char4);
char8 = __gather_unset_bits(bool8, char8);
char16 = __gather_unset_bits(bool16, char16);
char32 = __gather_unset_bits(bool32, char32);
#if __C7X_VEC_SIZE_BITS__ >= 512
char64 = __gather_unset_bits(bool64, char64);
#endif

*/

#define __gather_unset_bits(a,b) __overload("__gather_unset_bits",(a),(b))((a),(b))

/******************************************************************************/
/* __SE_REG and __SE_REG_PAIR Streaming Engine Operands                       */
/*                                                                            */
/* Some intrinsics, such as __matmpy() and __matmpy_u2s() below, take a       */
/* streaming engine operand, which is an enumeration with values representing */
/* which streaming engine to use as well as whether that streaming engine     */
/* advances. All other values are invalid and will produce an error.          */
/******************************************************************************/
typedef enum __attribute__((__packed__))
{
    __SE_REG_0     = 0,
    __SE_REG_0_ADV = 1,
    __SE_REG_1     = 2,
    __SE_REG_1_ADV = 3,
    __SE_REG_LAST  = 3 /* Don't use directly. */
} __SE_REG;

typedef enum __attribute__((__packed__))
{
    __SE_REG_PAIR_0     = 0,
    __SE_REG_PAIR_0_ADV = 1,
    __SE_REG_PAIR_LAST  = 1 /* Don't use directly. */
} __SE_REG_PAIR;

/*----------------------------------------------------------------------------*/
/* ID: __matmpy                                                               */
/*----------------------------------------------------------------------------*/
/*

VMATMPYHW
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __matmpy(__SE_REG, __SE_REG);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __matmpy_u2s                                                           */
/*----------------------------------------------------------------------------*/
/*

VMATMPYUSHW
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __matmpy_u2s(__SE_REG, __SE_REG);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __popcount_gather                                                      */
/*----------------------------------------------------------------------------*/
/*

PCNTGATHERB
__popcount_gather(bool2, uint&, bool2&);
__popcount_gather(bool3, uint&, bool3&);
__popcount_gather(bool4, uint&, bool4&);
__popcount_gather(bool8, uint&, bool8&);
__popcount_gather(bool16, uint&, bool16&);
__popcount_gather(bool32, uint&, bool32&);
#if __C7X_VEC_SIZE_BITS__ >= 512
__popcount_gather(bool64, uint&, bool64&);
#endif

*/

#define __popcount_gather(a,b,c) __overload("__popcount_gather",(a),(b),(c))((a),(b),(c))

/*----------------------------------------------------------------------------*/
/* ID: __rightmost_bit_detect                                                 */
/*----------------------------------------------------------------------------*/
/*

PRMBDB
uint = __rightmost_bit_detect(bool2);
uint = __rightmost_bit_detect(bool3);
uint = __rightmost_bit_detect(bool4);
uint = __rightmost_bit_detect(bool8);
uint = __rightmost_bit_detect(bool16);
uint = __rightmost_bit_detect(bool32);
#if __C7X_VEC_SIZE_BITS__ >= 512
uint = __rightmost_bit_detect(bool64);
#endif

*/

#define __rightmost_bit_detect(a) __overload("__rightmost_bit_detect",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __scatter_set_bits                                                     */
/*----------------------------------------------------------------------------*/
/*

VSCATTERB
char2 = __scatter_set_bits(bool2, char2);
char3 = __scatter_set_bits(bool3, char3);
char4 = __scatter_set_bits(bool4, char4);
char8 = __scatter_set_bits(bool8, char8);
char16 = __scatter_set_bits(bool16, char16);
char32 = __scatter_set_bits(bool32, char32);
#if __C7X_VEC_SIZE_BITS__ >= 512
char64 = __scatter_set_bits(bool64, char64);
#endif

*/

#define __scatter_set_bits(a,b) __overload("__scatter_set_bits",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __scatter_unset_bits                                                   */
/*----------------------------------------------------------------------------*/
/*

VSCATTERNB
char2 = __scatter_unset_bits(bool2, char2);
char3 = __scatter_unset_bits(bool3, char3);
char4 = __scatter_unset_bits(bool4, char4);
char8 = __scatter_unset_bits(bool8, char8);
char16 = __scatter_unset_bits(bool16, char16);
char32 = __scatter_unset_bits(bool32, char32);
#if __C7X_VEC_SIZE_BITS__ >= 512
char64 = __scatter_unset_bits(bool64, char64);
#endif

*/

#define __scatter_unset_bits(a,b) __overload("__scatter_unset_bits",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: SCONV                                                                  */
/*----------------------------------------------------------------------------*/
/*

VBUNPKD
long = __convert_long(signed char);
long2 = __convert_long2(char2);
long3 = __convert_long3(char3);
long4 = __convert_long4(char4);
long8 = __convert_long8(char8);
clong = __convert_clong(cchar);
clong2 = __convert_clong2(cchar2);
clong4 = __convert_clong4(cchar4);

VBUNPKDU
ulong = __convert_ulong(uchar);
ulong2 = __convert_ulong2(uchar2);
ulong3 = __convert_ulong3(uchar3);
ulong4 = __convert_ulong4(uchar4);
ulong8 = __convert_ulong8(uchar8);
long = __convert_long(uchar);
long2 = __convert_long2(uchar2);
long3 = __convert_long3(uchar3);
long4 = __convert_long4(uchar4);
long8 = __convert_long8(uchar8);

VBUNPKH
short = __convert_short(signed char);
short2 = __convert_short2(char2);
short3 = __convert_short3(char3);
short4 = __convert_short4(char4);
short8 = __convert_short8(char8);
short16 = __convert_short16(char16);
short32 = __convert_short32(char32);
cshort = __convert_cshort(cchar);
cshort2 = __convert_cshort2(cchar2);
cshort4 = __convert_cshort4(cchar4);
cshort8 = __convert_cshort8(cchar8);
cshort16 = __convert_cshort16(cchar16);

VBUNPKHU
ushort = __convert_ushort(uchar);
ushort2 = __convert_ushort2(uchar2);
ushort3 = __convert_ushort3(uchar3);
ushort4 = __convert_ushort4(uchar4);
ushort8 = __convert_ushort8(uchar8);
ushort16 = __convert_ushort16(uchar16);
ushort32 = __convert_ushort32(uchar32);
short = __convert_short(uchar);
short2 = __convert_short2(uchar2);
short3 = __convert_short3(uchar3);
short4 = __convert_short4(uchar4);
short8 = __convert_short8(uchar8);
short16 = __convert_short16(uchar16);
short32 = __convert_short32(uchar32);

VBUNPKW
int = __convert_int(signed char);
int2 = __convert_int2(char2);
int3 = __convert_int3(char3);
int4 = __convert_int4(char4);
int8 = __convert_int8(char8);
int16 = __convert_int16(char16);
cint = __convert_cint(cchar);
cint2 = __convert_cint2(cchar2);
cint4 = __convert_cint4(cchar4);
cint8 = __convert_cint8(cchar8);

VBUNPKWU
uint = __convert_uint(uchar);
uint2 = __convert_uint2(uchar2);
uint3 = __convert_uint3(uchar3);
uint4 = __convert_uint4(uchar4);
uint8 = __convert_uint8(uchar8);
uint16 = __convert_uint16(uchar16);
int = __convert_int(uchar);
int2 = __convert_int2(uchar2);
int3 = __convert_int3(uchar3);
int4 = __convert_int4(uchar4);
int8 = __convert_int8(uchar8);
int16 = __convert_int16(uchar16);

VHUNPKD
long = __convert_long(short);
long2 = __convert_long2(short2);
long3 = __convert_long3(short3);
long4 = __convert_long4(short4);
long8 = __convert_long8(short8);
clong = __convert_clong(cshort);
clong2 = __convert_clong2(cshort2);
clong4 = __convert_clong4(cshort4);

VHUNPKDU
ulong = __convert_ulong(ushort);
ulong2 = __convert_ulong2(ushort2);
ulong3 = __convert_ulong3(ushort3);
ulong4 = __convert_ulong4(ushort4);
ulong8 = __convert_ulong8(ushort8);
long = __convert_long(ushort);
long2 = __convert_long2(ushort2);
long3 = __convert_long3(ushort3);
long4 = __convert_long4(ushort4);
long8 = __convert_long8(ushort8);

VHUNPKW
int = __convert_int(short);
int2 = __convert_int2(short2);
int3 = __convert_int3(short3);
int4 = __convert_int4(short4);
int8 = __convert_int8(short8);
int16 = __convert_int16(short16);
cint = __convert_cint(cshort);
cint2 = __convert_cint2(cshort2);
cint4 = __convert_cint4(cshort4);
cint8 = __convert_cint8(cshort8);

VHUNPKWU
uint = __convert_uint(ushort);
uint2 = __convert_uint2(ushort2);
uint3 = __convert_uint3(ushort3);
uint4 = __convert_uint4(ushort4);
uint8 = __convert_uint8(ushort8);
uint16 = __convert_uint16(ushort16);
int = __convert_int(ushort);
int2 = __convert_int2(ushort2);
int3 = __convert_int3(ushort3);
int4 = __convert_int4(ushort4);
int8 = __convert_int8(ushort8);
int16 = __convert_int16(ushort16);

VINTSP
float = __convert_float(int);
float2 = __convert_float2(int2);
float3 = __convert_float3(int3);
float4 = __convert_float4(int4);
float8 = __convert_float8(int8);
float16 = __convert_float16(int16);

VINTSPU
float = __convert_float(uint);
float2 = __convert_float2(uint2);
float3 = __convert_float3(uint3);
float4 = __convert_float4(uint4);
float8 = __convert_float8(uint8);
float16 = __convert_float16(uint16);

VSPTRUNC
int = __convert_int(float);
int2 = __convert_int2(float2);
int3 = __convert_int3(float3);
int4 = __convert_int4(float4);
int8 = __convert_int8(float8);
int16 = __convert_int16(float16);

VWUNPKD
long = __convert_long(int);
long2 = __convert_long2(int2);
long3 = __convert_long3(int3);
long4 = __convert_long4(int4);
long8 = __convert_long8(int8);
clong = __convert_clong(cint);
clong2 = __convert_clong2(cint2);
clong4 = __convert_clong4(cint4);

VWUNPKDU
ulong = __convert_ulong(uint);
ulong2 = __convert_ulong2(uint2);
ulong3 = __convert_ulong3(uint3);
ulong4 = __convert_ulong4(uint4);
ulong8 = __convert_ulong8(uint8);
long = __convert_long(uint);
long2 = __convert_long2(uint2);
long3 = __convert_long3(uint3);
long4 = __convert_long4(uint4);
long8 = __convert_long8(uint8);

*/

/*----------------------------------------------------------------------------*/
/* ID: __shuffle (Convenience form of __shuffle_stride2_low_low)              */
/*----------------------------------------------------------------------------*/
/*

VSHFL2DLL
#if __C7X_VEC_SIZE_BITS__ == 256
long4 = __shuffle(long2, long2);
double4 = __shuffle(double2, double2);
cfloat4 = __shuffle(cfloat2, cfloat2);
ulong4 = __shuffle(ulong2, ulong2);
cint4 = __shuffle(cint2, cint2);
#elif __C7X_VEC_SIZE_BITS__ == 512
long8 = __shuffle(long4, long4);
double8 = __shuffle(double4, double4);
cfloat8 = __shuffle(cfloat4, cfloat4);
ulong8 = __shuffle(ulong4, ulong4);
cint8 = __shuffle(cint4, cint4);
#endif

VSHFL2HLL
#if __C7X_VEC_SIZE_BITS__ == 256
short16 = __shuffle(short8, short8);
ushort16 = __shuffle(ushort8, ushort8);
cchar16 = __shuffle(cchar8, cchar8);
#elif __C7X_VEC_SIZE_BITS__ == 512
short32 = __shuffle(short16, short16);
ushort32 = __shuffle(ushort16, ushort16);
cchar32 = __shuffle(cchar16, cchar16);
#endif

VSHFL2WLL
#if __C7X_VEC_SIZE_BITS__ == 256
int8 = __shuffle(int4, int4);
float8 = __shuffle(float4, float4);
uint8 = __shuffle(uint4, uint4);
cshort8 = __shuffle(cshort4, cshort4);
#elif __C7X_VEC_SIZE_BITS__ == 512
int16 = __shuffle(int8, int8);
float16 = __shuffle(float8, float8);
uint16 = __shuffle(uint8, uint8);
cshort16 = __shuffle(cshort8, cshort8);
#endif

*/

#define __shuffle(a,b) __overload("__shuffle",(a),(b))((a),(b))

/*-----------------------------------------------------------------------------
* ID: __popcount
*----------------------------------------------------------------------------*/
/*

PBITCNTB
uint = __popcount(bool2);
uint = __popcount(bool3);
uint = __popcount(bool4);
uint = __popcount(bool8);
uint = __popcount(bool16);
uint = __popcount(bool32);
#if __C7X_VEC_SIZE_BITS__ >= 512
uint = __popcount(bool64);
#endif

*/

/* AUTOGEN MARKER */
/*----------------------------------------------------------------------------*/
/* ID: ANDB                                                                   */
/*----------------------------------------------------------------------------*/
/*

ANDD, ANDW, VANDW
signed char = signed char & signed char;
signed char = signed char & (signed char)(k);
char2 = char2 & char2;
char2 = char2 & (char2)(k);
char3 = char3 & char3;
char3 = char3 & (char3)(k);
char4 = char4 & char4;
char4 = char4 & (char4)(k);
char8 = char8 & char8;
char16 = char16 & char16;
char32 = char32 & char32;
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = char64 & char64;
#endif
uchar = uchar & uchar;
uchar = uchar & (uchar)(k);
uchar2 = uchar2 & uchar2;
uchar2 = uchar2 & (uchar2)(k);
uchar3 = uchar3 & uchar3;
uchar3 = uchar3 & (uchar3)(k);
uchar4 = uchar4 & uchar4;
uchar4 = uchar4 & (uchar4)(k);
uchar8 = uchar8 & uchar8;
uchar16 = uchar16 & uchar16;
uchar32 = uchar32 & uchar32;
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = uchar64 & uchar64;
#endif
short = short & short;
short = short & (short)(k);
short2 = short2 & short2;
short2 = short2 & (short2)(k);
short3 = short3 & short3;
short4 = short4 & short4;
short8 = short8 & short8;
short16 = short16 & short16;
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = short32 & short32;
#endif
ushort = ushort & ushort;
ushort = ushort & (ushort)(k);
ushort2 = ushort2 & ushort2;
ushort2 = ushort2 & (ushort2)(k);
ushort3 = ushort3 & ushort3;
ushort4 = ushort4 & ushort4;
ushort8 = ushort8 & ushort8;
ushort16 = ushort16 & ushort16;
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = ushort32 & ushort32;
#endif
int = int & int;
int = int & (int)(k);
int2 = int2 & int2;
int2 = int2 & (int2)(k);
int3 = int3 & int3;
int3 = int3 & (int3)(k);
int4 = int4 & int4;
int4 = int4 & (int4)(k);
int8 = int8 & int8;
int8 = int8 & (int8)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = int16 & int16;
int16 = int16 & (int16)(k);
#endif
uint = uint & uint;
uint = uint & (uint)(k);
uint2 = uint2 & uint2;
uint2 = uint2 & (uint2)(k);
uint3 = uint3 & uint3;
uint3 = uint3 & (uint3)(k);
uint4 = uint4 & uint4;
uint4 = uint4 & (uint4)(k);
uint8 = uint8 & uint8;
uint8 = uint8 & (uint8)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = uint16 & uint16;
uint16 = uint16 & (uint16)(k);
#endif

ANDD, VANDW
long = long & long;
long = long & (long)(k);
long2 = long2 & long2;
long3 = long3 & long3;
long4 = long4 & long4;
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = long8 & long8;
#endif
ulong = ulong & ulong;
ulong = ulong & (ulong)(k);
ulong2 = ulong2 & ulong2;
ulong3 = ulong3 & ulong3;
ulong4 = ulong4 & ulong4;
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = ulong8 & ulong8;
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: DIV                                                                    */
/*----------------------------------------------------------------------------*/
/*

DIVW
int = int / int;

DIVUW
uint = uint / uint;

DIVDW
long = long / int;

DIVUDW
ulong = ulong / uint;

*/

/*----------------------------------------------------------------------------*/
/* ID: MINUS                                                                  */
/*----------------------------------------------------------------------------*/
/*

VSUBB
signed char = signed char - signed char;
signed char = signed char - (signed char)(k);
char2 = char2 - char2;
char2 = char2 - (char2)(k);
char3 = char3 - char3;
char3 = char3 - (char3)(k);
char4 = char4 - char4;
char4 = char4 - (char4)(k);
char8 = char8 - char8;
char8 = char8 - (char8)(k);
char16 = char16 - char16;
char16 = char16 - (char16)(k);
char32 = char32 - char32;
char32 = char32 - (char32)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = char64 - char64;
char64 = char64 - (char64)(k);
#endif
uchar = uchar - uchar;
uchar = uchar - (uchar)(k);
uchar2 = uchar2 - uchar2;
uchar2 = uchar2 - (uchar2)(k);
uchar3 = uchar3 - uchar3;
uchar3 = uchar3 - (uchar3)(k);
uchar4 = uchar4 - uchar4;
uchar4 = uchar4 - (uchar4)(k);
uchar8 = uchar8 - uchar8;
uchar8 = uchar8 - (uchar8)(k);
uchar16 = uchar16 - uchar16;
uchar16 = uchar16 - (uchar16)(k);
uchar32 = uchar32 - uchar32;
uchar32 = uchar32 - (uchar32)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = uchar64 - uchar64;
uchar64 = uchar64 - (uchar64)(k);
#endif
cchar = cchar - cchar;
cchar2 = cchar2 - cchar2;
cchar4 = cchar4 - cchar4;
cchar8 = cchar8 - cchar8;
cchar16 = cchar16 - cchar16;
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = cchar32 - cchar32;
#endif

VSUBH
short = short - short;
short = short - (short)(k);
short2 = short2 - short2;
short2 = short2 - (short2)(k);
short3 = short3 - short3;
short3 = short3 - (short3)(k);
short4 = short4 - short4;
short4 = short4 - (short4)(k);
short8 = short8 - short8;
short8 = short8 - (short8)(k);
short16 = short16 - short16;
short16 = short16 - (short16)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = short32 - short32;
short32 = short32 - (short32)(k);
#endif
ushort = ushort - ushort;
ushort = ushort - (ushort)(k);
ushort2 = ushort2 - ushort2;
ushort2 = ushort2 - (ushort2)(k);
ushort3 = ushort3 - ushort3;
ushort3 = ushort3 - (ushort3)(k);
ushort4 = ushort4 - ushort4;
ushort4 = ushort4 - (ushort4)(k);
ushort8 = ushort8 - ushort8;
ushort8 = ushort8 - (ushort8)(k);
ushort16 = ushort16 - ushort16;
ushort16 = ushort16 - (ushort16)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = ushort32 - ushort32;
ushort32 = ushort32 - (ushort32)(k);
#endif
cshort = cshort - cshort;
cshort2 = cshort2 - cshort2;
cshort4 = cshort4 - cshort4;
cshort8 = cshort8 - cshort8;
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = cshort16 - cshort16;
#endif

SUBW, VSUBW
int = int - int;
int = int - (int)(k);
int2 = int2 - int2;
int2 = int2 - (int2)(k);
int3 = int3 - int3;
int3 = int3 - (int3)(k);
int4 = int4 - int4;
int4 = int4 - (int4)(k);
int8 = int8 - int8;
int8 = int8 - (int8)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = int16 - int16;
int16 = int16 - (int16)(k);
#endif
uint = uint - uint;
uint = uint - (uint)(k);
uint2 = uint2 - uint2;
uint2 = uint2 - (uint2)(k);
uint3 = uint3 - uint3;
uint3 = uint3 - (uint3)(k);
uint4 = uint4 - uint4;
uint4 = uint4 - (uint4)(k);
uint8 = uint8 - uint8;
uint8 = uint8 - (uint8)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = uint16 - uint16;
uint16 = uint16 - (uint16)(k);
#endif

SUBSP, VSUBSP
float = float - float;
float2 = float2 - float2;
float3 = float3 - float3;
float4 = float4 - float4;
float8 = float8 - float8;
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = float16 - float16;
#endif

VSUBW
cint = cint - cint;
cint2 = cint2 - cint2;
cint4 = cint4 - cint4;
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = cint8 - cint8;
#endif

VSUBSP
cfloat = cfloat - cfloat;
cfloat2 = cfloat2 - cfloat2;
cfloat4 = cfloat4 - cfloat4;
#if __C7X_VEC_SIZE_BITS__ == 512
cfloat8 = cfloat8 - cfloat8;
#endif

SUBD, VSUBD
long = long - long;
long = long - (long)(k);
long2 = long2 - long2;
long2 = long2 - (long2)(k);
long3 = long3 - long3;
long3 = long3 - (long3)(k);
long4 = long4 - long4;
long4 = long4 - (long4)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = long8 - long8;
long8 = long8 - (long8)(k);
#endif
ulong = ulong - ulong;
ulong = ulong - (ulong)(k);
ulong2 = ulong2 - ulong2;
ulong2 = ulong2 - (ulong2)(k);
ulong3 = ulong3 - ulong3;
ulong3 = ulong3 - (ulong3)(k);
ulong4 = ulong4 - ulong4;
ulong4 = ulong4 - (ulong4)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = ulong8 - ulong8;
ulong8 = ulong8 - (ulong8)(k);
#endif

SUBDP, VSUBDP
double = double - double;
double2 = double2 - double2;
double3 = double3 - double3;
double4 = double4 - double4;
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = double8 - double8;
#endif

VSUBD
clong = clong - clong;
clong2 = clong2 - clong2;
#if __C7X_VEC_SIZE_BITS__ == 512
clong4 = clong4 - clong4;
#endif

VSUBDP
cdouble = cdouble - cdouble;
cdouble2 = cdouble2 - cdouble2;
#if __C7X_VEC_SIZE_BITS__ == 512
cdouble4 = cdouble4 - cdouble4;
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: MOD                                                                    */
/*----------------------------------------------------------------------------*/
/*

MODW
int = int % int;

MODUW
uint = uint % uint;

MODDW
long = long % int;

MODUDW
ulong = ulong % uint;

*/

/*----------------------------------------------------------------------------*/
/* ID: MULT                                                                   */
/*----------------------------------------------------------------------------*/
/*

VMPYBB
signed char = signed char * signed char;
char2 = char2 * char2;
char3 = char3 * char3;
char4 = char4 * char4;
char8 = char8 * char8;
char16 = char16 * char16;
char32 = char32 * char32;
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = char64 * char64;
#endif
uchar = uchar * uchar;
uchar2 = uchar2 * uchar2;
uchar3 = uchar3 * uchar3;
uchar4 = uchar4 * uchar4;
uchar8 = uchar8 * uchar8;
uchar16 = uchar16 * uchar16;
uchar32 = uchar32 * uchar32;
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = uchar64 * uchar64;
#endif

VMPYHH
short = short * short;
short2 = short2 * short2;
short3 = short3 * short3;
short4 = short4 * short4;
short8 = short8 * short8;
short16 = short16 * short16;
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = short32 * short32;
#endif

MPYHW
int = short * short;

MPYSUHW
int = short * ushort;

VMPYHH
ushort = ushort * ushort;
ushort2 = ushort2 * ushort2;
ushort3 = ushort3 * ushort3;
ushort4 = ushort4 * ushort4;
ushort8 = ushort8 * ushort8;
ushort16 = ushort16 * ushort16;
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = ushort32 * ushort32;
#endif

MPYUHW
uint = ushort * ushort;

MPYWW, VMPYWW
int = int * int;
int2 = int2 * int2;
int3 = int3 * int3;
int4 = int4 * int4;
int8 = int8 * int8;
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = int16 * int16;
#endif
uint = uint * uint;
uint2 = uint2 * uint2;
uint3 = uint3 * uint3;
uint4 = uint4 * uint4;
uint8 = uint8 * uint8;
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = uint16 * uint16;
#endif

MPYSP, VMPYSP
float = float * float;
float2 = float2 * float2;
float3 = float3 * float3;
float4 = float4 * float4;
float8 = float8 * float8;
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = float16 * float16;
#endif

MPYDD, VMPYDD
long = long * long;
long2 = long2 * long2;
long3 = long3 * long3;
long4 = long4 * long4;
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = long8 * long8;
#endif
ulong = ulong * ulong;
ulong2 = ulong2 * ulong2;
ulong3 = ulong3 * ulong3;
ulong4 = ulong4 * ulong4;
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = ulong8 * ulong8;
#endif

MPYDP, VMPYDP
double = double * double;
double2 = double2 * double2;
double3 = double3 * double3;
double4 = double4 * double4;
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = double8 * double8;
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: ORB                                                                    */
/*----------------------------------------------------------------------------*/
/*

ORD, ORW, VORW
signed char = signed char | signed char;
signed char = signed char | (signed char)(k);
char2 = char2 | char2;
char2 = char2 | (char2)(k);
char3 = char3 | char3;
char3 = char3 | (char3)(k);
char4 = char4 | char4;
char4 = char4 | (char4)(k);
char8 = char8 | char8;
char16 = char16 | char16;
char32 = char32 | char32;
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = char64 | char64;
#endif
uchar = uchar | uchar;
uchar = uchar | (uchar)(k);
uchar2 = uchar2 | uchar2;
uchar2 = uchar2 | (uchar2)(k);
uchar3 = uchar3 | uchar3;
uchar3 = uchar3 | (uchar3)(k);
uchar4 = uchar4 | uchar4;
uchar4 = uchar4 | (uchar4)(k);
uchar8 = uchar8 | uchar8;
uchar16 = uchar16 | uchar16;
uchar32 = uchar32 | uchar32;
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = uchar64 | uchar64;
#endif
short = short | short;
short = short | (short)(k);
short2 = short2 | short2;
short2 = short2 | (short2)(k);
short3 = short3 | short3;
short4 = short4 | short4;
short8 = short8 | short8;
short16 = short16 | short16;
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = short32 | short32;
#endif
ushort = ushort | ushort;
ushort = ushort | (ushort)(k);
ushort2 = ushort2 | ushort2;
ushort2 = ushort2 | (ushort2)(k);
ushort3 = ushort3 | ushort3;
ushort4 = ushort4 | ushort4;
ushort8 = ushort8 | ushort8;
ushort16 = ushort16 | ushort16;
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = ushort32 | ushort32;
#endif
int = int | int;
int = int | (int)(k);
int2 = int2 | int2;
int2 = int2 | (int2)(k);
int3 = int3 | int3;
int3 = int3 | (int3)(k);
int4 = int4 | int4;
int4 = int4 | (int4)(k);
int8 = int8 | int8;
int8 = int8 | (int8)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = int16 | int16;
int16 = int16 | (int16)(k);
#endif
uint = uint | uint;
uint = uint | (uint)(k);
uint2 = uint2 | uint2;
uint2 = uint2 | (uint2)(k);
uint3 = uint3 | uint3;
uint3 = uint3 | (uint3)(k);
uint4 = uint4 | uint4;
uint4 = uint4 | (uint4)(k);
uint8 = uint8 | uint8;
uint8 = uint8 | (uint8)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = uint16 | uint16;
uint16 = uint16 | (uint16)(k);
#endif

ORD, VORW
long = long | long;
long = long | (long)(k);
long2 = long2 | long2;
long3 = long3 | long3;
long4 = long4 | long4;
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = long8 | long8;
#endif
ulong = ulong | ulong;
ulong = ulong | (ulong)(k);
ulong2 = ulong2 | ulong2;
ulong3 = ulong3 | ulong3;
ulong4 = ulong4 | ulong4;
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = ulong8 | ulong8;
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: PLUS                                                                   */
/*----------------------------------------------------------------------------*/
/*

VADDB
signed char = signed char + signed char;
signed char = signed char + (signed char)(k);
char2 = char2 + char2;
char2 = char2 + (char2)(k);
char3 = char3 + char3;
char3 = char3 + (char3)(k);
char4 = char4 + char4;
char4 = char4 + (char4)(k);
char8 = char8 + char8;
char8 = char8 + (char8)(k);
char16 = char16 + char16;
char16 = char16 + (char16)(k);
char32 = char32 + char32;
char32 = char32 + (char32)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = char64 + char64;
char64 = char64 + (char64)(k);
#endif
uchar = uchar + uchar;
uchar = uchar + (uchar)(k);
uchar2 = uchar2 + uchar2;
uchar2 = uchar2 + (uchar2)(k);
uchar3 = uchar3 + uchar3;
uchar3 = uchar3 + (uchar3)(k);
uchar4 = uchar4 + uchar4;
uchar4 = uchar4 + (uchar4)(k);
uchar8 = uchar8 + uchar8;
uchar8 = uchar8 + (uchar8)(k);
uchar16 = uchar16 + uchar16;
uchar16 = uchar16 + (uchar16)(k);
uchar32 = uchar32 + uchar32;
uchar32 = uchar32 + (uchar32)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = uchar64 + uchar64;
uchar64 = uchar64 + (uchar64)(k);
#endif
cchar = cchar + cchar;
cchar2 = cchar2 + cchar2;
cchar4 = cchar4 + cchar4;
cchar8 = cchar8 + cchar8;
cchar16 = cchar16 + cchar16;
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = cchar32 + cchar32;
#endif

VADDH
short = short + short;
short = short + (short)(k);
short2 = short2 + short2;
short2 = short2 + (short2)(k);
short3 = short3 + short3;
short3 = short3 + (short3)(k);
short4 = short4 + short4;
short4 = short4 + (short4)(k);
short8 = short8 + short8;
short8 = short8 + (short8)(k);
short16 = short16 + short16;
short16 = short16 + (short16)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = short32 + short32;
short32 = short32 + (short32)(k);
#endif
ushort = ushort + ushort;
ushort = ushort + (ushort)(k);
ushort2 = ushort2 + ushort2;
ushort2 = ushort2 + (ushort2)(k);
ushort3 = ushort3 + ushort3;
ushort3 = ushort3 + (ushort3)(k);
ushort4 = ushort4 + ushort4;
ushort4 = ushort4 + (ushort4)(k);
ushort8 = ushort8 + ushort8;
ushort8 = ushort8 + (ushort8)(k);
ushort16 = ushort16 + ushort16;
ushort16 = ushort16 + (ushort16)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = ushort32 + ushort32;
ushort32 = ushort32 + (ushort32)(k);
#endif
cshort = cshort + cshort;
cshort2 = cshort2 + cshort2;
cshort4 = cshort4 + cshort4;
cshort8 = cshort8 + cshort8;
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = cshort16 + cshort16;
#endif

ADDW, VADDW
int = int + int;
int = int + (int)(k);
int2 = int2 + int2;
int2 = int2 + (int2)(k);
int3 = int3 + int3;
int3 = int3 + (int3)(k);
int4 = int4 + int4;
int4 = int4 + (int4)(k);
int8 = int8 + int8;
int8 = int8 + (int8)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = int16 + int16;
int16 = int16 + (int16)(k);
#endif
uint = uint + uint;
uint = uint + (uint)(k);
uint2 = uint2 + uint2;
uint2 = uint2 + (uint2)(k);
uint3 = uint3 + uint3;
uint3 = uint3 + (uint3)(k);
uint4 = uint4 + uint4;
uint4 = uint4 + (uint4)(k);
uint8 = uint8 + uint8;
uint8 = uint8 + (uint8)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = uint16 + uint16;
uint16 = uint16 + (uint16)(k);
#endif

ADDSP, VADDSP
float = float + float;
float2 = float2 + float2;
float3 = float3 + float3;
float4 = float4 + float4;
float8 = float8 + float8;
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = float16 + float16;
#endif

VADDW
cint = cint + cint;
cint2 = cint2 + cint2;
cint4 = cint4 + cint4;
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = cint8 + cint8;
#endif

VADDSP
cfloat = cfloat + cfloat;
cfloat2 = cfloat2 + cfloat2;
cfloat4 = cfloat4 + cfloat4;
#if __C7X_VEC_SIZE_BITS__ == 512
cfloat8 = cfloat8 + cfloat8;
#endif

ADDD, VADDD
long = long + long;
long = long + (long)(k);
long2 = long2 + long2;
long2 = long2 + (long2)(k);
long3 = long3 + long3;
long3 = long3 + (long3)(k);
long4 = long4 + long4;
long4 = long4 + (long4)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = long8 + long8;
long8 = long8 + (long8)(k);
#endif
ulong = ulong + ulong;
ulong = ulong + (ulong)(k);
ulong2 = ulong2 + ulong2;
ulong2 = ulong2 + (ulong2)(k);
ulong3 = ulong3 + ulong3;
ulong3 = ulong3 + (ulong3)(k);
ulong4 = ulong4 + ulong4;
ulong4 = ulong4 + (ulong4)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = ulong8 + ulong8;
ulong8 = ulong8 + (ulong8)(k);
#endif

ADDDP, VADDDP
double = double + double;
double2 = double2 + double2;
double3 = double3 + double3;
double4 = double4 + double4;
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = double8 + double8;
#endif

VADDD
clong = clong + clong;
clong2 = clong2 + clong2;
#if __C7X_VEC_SIZE_BITS__ == 512
clong4 = clong4 + clong4;
#endif

VADDDP
cdouble = cdouble + cdouble;
cdouble2 = cdouble2 + cdouble2;
#if __C7X_VEC_SIZE_BITS__ == 512
cdouble4 = cdouble4 + cdouble4;
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: SLL                                                                    */
/*----------------------------------------------------------------------------*/
/*

VSHLB
signed char = signed char << (signed char)(k={0-63});
char2 = char2 << (char2)(k={0-63});
char3 = char3 << (char3)(k={0-63});
char4 = char4 << (char4)(k={0-63});
char8 = char8 << (char8)(k={0-63});
char16 = char16 << (char16)(k={0-63});
char32 = char32 << (char32)(k={0-63});
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = char64 << (char64)(k={0-63});
#endif
uchar = uchar << (uchar)(k={0-63});
uchar2 = uchar2 << (uchar2)(k={0-63});
uchar3 = uchar3 << (uchar3)(k={0-63});
uchar4 = uchar4 << (uchar4)(k={0-63});
uchar8 = uchar8 << (uchar8)(k={0-63});
uchar16 = uchar16 << (uchar16)(k={0-63});
uchar32 = uchar32 << (uchar32)(k={0-63});
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = uchar64 << (uchar64)(k={0-63});
#endif

VSHLH
short = short << (short)(k={0-63});
short2 = short2 << (short2)(k={0-63});
short3 = short3 << (short3)(k={0-63});
short4 = short4 << (short4)(k={0-63});
short8 = short8 << (short8)(k={0-63});
short16 = short16 << (short16)(k={0-63});
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = short32 << (short32)(k={0-63});
#endif
ushort = ushort << (ushort)(k={0-63});
ushort2 = ushort2 << (ushort2)(k={0-63});
ushort3 = ushort3 << (ushort3)(k={0-63});
ushort4 = ushort4 << (ushort4)(k={0-63});
ushort8 = ushort8 << (ushort8)(k={0-63});
ushort16 = ushort16 << (ushort16)(k={0-63});
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = ushort32 << (ushort32)(k={0-63});
#endif

SHLW
int = int << (uchar)(k={0-63});

SHLW, VSHLW
int = int << int;
int = int << (int)(k);
int2 = int2 << int2;
int2 = int2 << (int2)(k);
int3 = int3 << int3;
int3 = int3 << (int3)(k);
int4 = int4 << int4;
int4 = int4 << (int4)(k);
int8 = int8 << int8;
int8 = int8 << (int8)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = int16 << int16;
int16 = int16 << (int16)(k);
#endif

SHLW
uint = uint << (uchar)(k={0-63});

SHLW, VSHLW
uint = uint << uint;
uint = uint << (uint)(k);
uint2 = uint2 << uint2;
uint2 = uint2 << (uint2)(k);
uint3 = uint3 << uint3;
uint3 = uint3 << (uint3)(k);
uint4 = uint4 << uint4;
uint4 = uint4 << (uint4)(k);
uint8 = uint8 << uint8;
uint8 = uint8 << (uint8)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = uint16 << uint16;
uint16 = uint16 << (uint16)(k);
#endif

SHLD
long = long << (uchar)(k={0-63});
long = long << int;

VSHLD
long = long << long;
long = long << (long)(k);
long2 = long2 << long2;
long2 = long2 << (long2)(k);
long3 = long3 << long3;
long3 = long3 << (long3)(k);
long4 = long4 << long4;
long4 = long4 << (long4)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = long8 << long8;
long8 = long8 << (long8)(k);
#endif

SHLD
ulong = ulong << (uchar)(k={0-63});
ulong = ulong << uint;

VSHLD
ulong = ulong << ulong;
ulong = ulong << (ulong)(k);
ulong2 = ulong2 << ulong2;
ulong2 = ulong2 << (ulong2)(k);
ulong3 = ulong3 << ulong3;
ulong3 = ulong3 << (ulong3)(k);
ulong4 = ulong4 << ulong4;
ulong4 = ulong4 << (ulong4)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = ulong8 << ulong8;
ulong8 = ulong8 << (ulong8)(k);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: SRL                                                                    */
/*----------------------------------------------------------------------------*/
/*

SHRW
int = int >> (uchar)(k={0-63});

SHRW, VSHRW
int = int >> int;
int = int >> (int)(k);
int2 = int2 >> int2;
int2 = int2 >> (int2)(k);
int3 = int3 >> int3;
int3 = int3 >> (int3)(k);
int4 = int4 >> int4;
int4 = int4 >> (int4)(k);
int8 = int8 >> int8;
int8 = int8 >> (int8)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = int16 >> int16;
int16 = int16 >> (int16)(k);
#endif

SHRUW
uint = uint >> (uchar)(k={0-63});

SHRUW, VSHRUW
uint = uint >> uint;
uint = uint >> (uint)(k);
uint2 = uint2 >> uint2;
uint2 = uint2 >> (uint2)(k);
uint3 = uint3 >> uint3;
uint3 = uint3 >> (uint3)(k);
uint4 = uint4 >> uint4;
uint4 = uint4 >> (uint4)(k);
uint8 = uint8 >> uint8;
uint8 = uint8 >> (uint8)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = uint16 >> uint16;
uint16 = uint16 >> (uint16)(k);
#endif

SHRD
long = long >> (uchar)(k={0-63});
long = long >> int;

VSHRD
long = long >> long;
long = long >> (long)(k);
long2 = long2 >> long2;
long2 = long2 >> (long2)(k);
long3 = long3 >> long3;
long3 = long3 >> (long3)(k);
long4 = long4 >> long4;
long4 = long4 >> (long4)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = long8 >> long8;
long8 = long8 >> (long8)(k);
#endif

SHRUD
ulong = ulong >> (uchar)(k={0-63});
ulong = ulong >> uint;

VSHRUD
ulong = ulong >> ulong;
ulong = ulong >> (ulong)(k);
ulong2 = ulong2 >> ulong2;
ulong2 = ulong2 >> (ulong2)(k);
ulong3 = ulong3 >> ulong3;
ulong3 = ulong3 >> (ulong3)(k);
ulong4 = ulong4 >> ulong4;
ulong4 = ulong4 >> (ulong4)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = ulong8 >> ulong8;
ulong8 = ulong8 >> (ulong8)(k);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: XORB                                                                   */
/*----------------------------------------------------------------------------*/
/*

VXORW, XORD, XORW
signed char = signed char ^ signed char;
signed char = signed char ^ (signed char)(k);
char2 = char2 ^ char2;
char2 = char2 ^ (char2)(k);
char3 = char3 ^ char3;
char3 = char3 ^ (char3)(k);
char4 = char4 ^ char4;
char4 = char4 ^ (char4)(k);
char8 = char8 ^ char8;
char16 = char16 ^ char16;
char32 = char32 ^ char32;
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = char64 ^ char64;
#endif
uchar = uchar ^ uchar;
uchar = uchar ^ (uchar)(k);
uchar2 = uchar2 ^ uchar2;
uchar2 = uchar2 ^ (uchar2)(k);
uchar3 = uchar3 ^ uchar3;
uchar3 = uchar3 ^ (uchar3)(k);
uchar4 = uchar4 ^ uchar4;
uchar4 = uchar4 ^ (uchar4)(k);
uchar8 = uchar8 ^ uchar8;
uchar16 = uchar16 ^ uchar16;
uchar32 = uchar32 ^ uchar32;
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = uchar64 ^ uchar64;
#endif
short = short ^ short;
short = short ^ (short)(k);
short2 = short2 ^ short2;
short2 = short2 ^ (short2)(k);
short3 = short3 ^ short3;
short4 = short4 ^ short4;
short8 = short8 ^ short8;
short16 = short16 ^ short16;
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = short32 ^ short32;
#endif
ushort = ushort ^ ushort;
ushort = ushort ^ (ushort)(k);
ushort2 = ushort2 ^ ushort2;
ushort2 = ushort2 ^ (ushort2)(k);
ushort3 = ushort3 ^ ushort3;
ushort4 = ushort4 ^ ushort4;
ushort8 = ushort8 ^ ushort8;
ushort16 = ushort16 ^ ushort16;
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = ushort32 ^ ushort32;
#endif
int = int ^ int;
int = int ^ (int)(k);
int2 = int2 ^ int2;
int2 = int2 ^ (int2)(k);
int3 = int3 ^ int3;
int3 = int3 ^ (int3)(k);
int4 = int4 ^ int4;
int4 = int4 ^ (int4)(k);
int8 = int8 ^ int8;
int8 = int8 ^ (int8)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = int16 ^ int16;
int16 = int16 ^ (int16)(k);
#endif
uint = uint ^ uint;
uint = uint ^ (uint)(k);
uint2 = uint2 ^ uint2;
uint2 = uint2 ^ (uint2)(k);
uint3 = uint3 ^ uint3;
uint3 = uint3 ^ (uint3)(k);
uint4 = uint4 ^ uint4;
uint4 = uint4 ^ (uint4)(k);
uint8 = uint8 ^ uint8;
uint8 = uint8 ^ (uint8)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = uint16 ^ uint16;
uint16 = uint16 ^ (uint16)(k);
#endif

VXORW, XORD
long = long ^ long;
long = long ^ (long)(k);
long2 = long2 ^ long2;
long3 = long3 ^ long3;
long4 = long4 ^ long4;
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = long8 ^ long8;
#endif
ulong = ulong ^ ulong;
ulong = ulong ^ (ulong)(k);
ulong2 = ulong2 ^ ulong2;
ulong3 = ulong3 ^ ulong3;
ulong4 = ulong4 ^ ulong4;
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = ulong8 ^ ulong8;
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __abs                                                                  */
/*----------------------------------------------------------------------------*/
/*

VABSB
signed char = __abs(signed char);
char2 = __abs(char2);
char3 = __abs(char3);
char4 = __abs(char4);
char8 = __abs(char8);
char16 = __abs(char16);
char32 = __abs(char32);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __abs(char64);
#endif
cchar = __abs(cchar);
cchar2 = __abs(cchar2);
cchar4 = __abs(cchar4);
cchar8 = __abs(cchar8);
cchar16 = __abs(cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = __abs(cchar32);
#endif

VABSH
short = __abs(short);
short2 = __abs(short2);
short3 = __abs(short3);
short4 = __abs(short4);
short8 = __abs(short8);
short16 = __abs(short16);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __abs(short32);
#endif
cshort = __abs(cshort);
cshort2 = __abs(cshort2);
cshort4 = __abs(cshort4);
cshort8 = __abs(cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = __abs(cshort16);
#endif

VABSW
int = __abs(int);
int2 = __abs(int2);
int3 = __abs(int3);
int4 = __abs(int4);
int8 = __abs(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __abs(int16);
#endif

VABSSP
float = __abs(float);
float2 = __abs(float2);
float3 = __abs(float3);
float4 = __abs(float4);
float8 = __abs(float8);
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __abs(float16);
#endif

VABSW
cint = __abs(cint);
cint2 = __abs(cint2);
cint4 = __abs(cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __abs(cint8);
#endif

VABSSP
cfloat = __abs(cfloat);
cfloat2 = __abs(cfloat2);
cfloat4 = __abs(cfloat4);
#if __C7X_VEC_SIZE_BITS__ == 512
cfloat8 = __abs(cfloat8);
#endif

VABSD
long = __abs(long);
long2 = __abs(long2);
long3 = __abs(long3);
long4 = __abs(long4);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __abs(long8);
#endif

VABSDP
double = __abs(double);
double2 = __abs(double2);
double3 = __abs(double3);
double4 = __abs(double4);
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = __abs(double8);
#endif

VABSD
clong = __abs(clong);
clong2 = __abs(clong2);
#if __C7X_VEC_SIZE_BITS__ == 512
clong4 = __abs(clong4);
#endif

VABSDP
cdouble = __abs(cdouble);
cdouble2 = __abs(cdouble2);
#if __C7X_VEC_SIZE_BITS__ == 512
cdouble4 = __abs(cdouble4);
#endif

*/

#define __abs(a) __overload("__abs",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __abs_diff                                                             */
/*----------------------------------------------------------------------------*/
/*

VSUBABSB
uchar = __abs_diff(uchar, uchar);
uchar2 = __abs_diff(uchar2, uchar2);
uchar3 = __abs_diff(uchar3, uchar3);
uchar4 = __abs_diff(uchar4, uchar4);
uchar8 = __abs_diff(uchar8, uchar8);
uchar16 = __abs_diff(uchar16, uchar16);
uchar32 = __abs_diff(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __abs_diff(uchar64, uchar64);
#endif

VSUBABSH
ushort = __abs_diff(ushort, ushort);
ushort2 = __abs_diff(ushort2, ushort2);
ushort3 = __abs_diff(ushort3, ushort3);
ushort4 = __abs_diff(ushort4, ushort4);
ushort8 = __abs_diff(ushort8, ushort8);
ushort16 = __abs_diff(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __abs_diff(ushort32, ushort32);
#endif

VSUBABSW
uint = __abs_diff(uint, uint);
uint2 = __abs_diff(uint2, uint2);
uint3 = __abs_diff(uint3, uint3);
uint4 = __abs_diff(uint4, uint4);
uint8 = __abs_diff(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __abs_diff(uint16, uint16);
#endif

VSUBABSD
ulong = __abs_diff(ulong, ulong);
ulong2 = __abs_diff(ulong2, ulong2);
ulong3 = __abs_diff(ulong3, ulong3);
ulong4 = __abs_diff(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __abs_diff(ulong8, ulong8);
#endif

*/

#define __abs_diff(a,b) __overload("__abs_diff",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __add                                                                  */
/*----------------------------------------------------------------------------*/
/*

VADDCB
char2 = __add(bool2, char2, char2);
char3 = __add(bool3, char3, char3);
char4 = __add(bool4, char4, char4);
char8 = __add(bool8, char8, char8);
char16 = __add(bool16, char16, char16);
char32 = __add(bool32, char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __add(bool64, char64, char64);
#endif
uchar2 = __add(bool2, uchar2, uchar2);
uchar3 = __add(bool3, uchar3, uchar3);
uchar4 = __add(bool4, uchar4, uchar4);
uchar8 = __add(bool8, uchar8, uchar8);
uchar16 = __add(bool16, uchar16, uchar16);
uchar32 = __add(bool32, uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __add(bool64, uchar64, uchar64);
#endif

VADDCH
short2 = __add(bool2, short2, short2);
short3 = __add(bool3, short3, short3);
short4 = __add(bool4, short4, short4);
short8 = __add(bool8, short8, short8);
short16 = __add(bool16, short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __add(bool32, short32, short32);
#endif
ushort2 = __add(bool2, ushort2, ushort2);
ushort3 = __add(bool3, ushort3, ushort3);
ushort4 = __add(bool4, ushort4, ushort4);
ushort8 = __add(bool8, ushort8, ushort8);
ushort16 = __add(bool16, ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __add(bool32, ushort32, ushort32);
#endif

VADDCW
int2 = __add(bool2, int2, int2);
int3 = __add(bool3, int3, int3);
int4 = __add(bool4, int4, int4);
int8 = __add(bool8, int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __add(bool16, int16, int16);
#endif
uint2 = __add(bool2, uint2, uint2);
uint3 = __add(bool3, uint3, uint3);
uint4 = __add(bool4, uint4, uint4);
uint8 = __add(bool8, uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __add(bool16, uint16, uint16);
#endif

VADDCD
long2 = __add(bool2, long2, long2);
long3 = __add(bool3, long3, long3);
long4 = __add(bool4, long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __add(bool8, long8, long8);
#endif
ulong2 = __add(bool2, ulong2, ulong2);
ulong3 = __add(bool3, ulong3, ulong3);
ulong4 = __add(bool4, ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __add(bool8, ulong8, ulong8);
#endif

*/

#define __add(a,b,c) __overload("__add",(a),(b),(c))((a),(b),(c))

/*----------------------------------------------------------------------------*/
/* ID: __add_sat                                                              */
/*----------------------------------------------------------------------------*/
/*

VSADDB
signed char = __add_sat(signed char, signed char);
signed char = __add_sat(signed char, (signed char)(k));
char2 = __add_sat(char2, char2);
char2 = __add_sat(char2, (char2)(k));
char3 = __add_sat(char3, char3);
char3 = __add_sat(char3, (char3)(k));
char4 = __add_sat(char4, char4);
char4 = __add_sat(char4, (char4)(k));
char8 = __add_sat(char8, char8);
char8 = __add_sat(char8, (char8)(k));
char16 = __add_sat(char16, char16);
char16 = __add_sat(char16, (char16)(k));
char32 = __add_sat(char32, char32);
char32 = __add_sat(char32, (char32)(k));
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __add_sat(char64, char64);
char64 = __add_sat(char64, (char64)(k));
#endif

VSADDUSB
uchar = __add_sat(uchar, signed char);
uchar2 = __add_sat(uchar2, char2);
uchar3 = __add_sat(uchar3, char3);
uchar4 = __add_sat(uchar4, char4);
uchar8 = __add_sat(uchar8, char8);
uchar16 = __add_sat(uchar16, char16);
uchar32 = __add_sat(uchar32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __add_sat(uchar64, char64);
#endif

VSADDUB
uchar = __add_sat(uchar, uchar);
uchar2 = __add_sat(uchar2, uchar2);
uchar3 = __add_sat(uchar3, uchar3);
uchar4 = __add_sat(uchar4, uchar4);
uchar8 = __add_sat(uchar8, uchar8);
uchar16 = __add_sat(uchar16, uchar16);
uchar32 = __add_sat(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __add_sat(uchar64, uchar64);
#endif

VSADDB
cchar = __add_sat(cchar, cchar);
cchar2 = __add_sat(cchar2, cchar2);
cchar4 = __add_sat(cchar4, cchar4);
cchar8 = __add_sat(cchar8, cchar8);
cchar16 = __add_sat(cchar16, cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = __add_sat(cchar32, cchar32);
#endif

VSADDH
short = __add_sat(short, short);
short = __add_sat(short, (short)(k));
short2 = __add_sat(short2, short2);
short2 = __add_sat(short2, (short2)(k));
short3 = __add_sat(short3, short3);
short3 = __add_sat(short3, (short3)(k));
short4 = __add_sat(short4, short4);
short4 = __add_sat(short4, (short4)(k));
short8 = __add_sat(short8, short8);
short8 = __add_sat(short8, (short8)(k));
short16 = __add_sat(short16, short16);
short16 = __add_sat(short16, (short16)(k));
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __add_sat(short32, short32);
short32 = __add_sat(short32, (short32)(k));
#endif

VSADDUSH
ushort = __add_sat(ushort, short);
ushort2 = __add_sat(ushort2, short2);
ushort3 = __add_sat(ushort3, short3);
ushort4 = __add_sat(ushort4, short4);
ushort8 = __add_sat(ushort8, short8);
ushort16 = __add_sat(ushort16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __add_sat(ushort32, short32);
#endif

VSADDUH
ushort = __add_sat(ushort, ushort);
ushort2 = __add_sat(ushort2, ushort2);
ushort3 = __add_sat(ushort3, ushort3);
ushort4 = __add_sat(ushort4, ushort4);
ushort8 = __add_sat(ushort8, ushort8);
ushort16 = __add_sat(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __add_sat(ushort32, ushort32);
#endif

VSADDH
cshort = __add_sat(cshort, cshort);
cshort2 = __add_sat(cshort2, cshort2);
cshort4 = __add_sat(cshort4, cshort4);
cshort8 = __add_sat(cshort8, cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = __add_sat(cshort16, cshort16);
#endif

VSADDW
int = __add_sat(int, int);
int = __add_sat(int, (int)(k));
int2 = __add_sat(int2, int2);
int2 = __add_sat(int2, (int2)(k));
int3 = __add_sat(int3, int3);
int3 = __add_sat(int3, (int3)(k));
int4 = __add_sat(int4, int4);
int4 = __add_sat(int4, (int4)(k));
int8 = __add_sat(int8, int8);
int8 = __add_sat(int8, (int8)(k));
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __add_sat(int16, int16);
int16 = __add_sat(int16, (int16)(k));
#endif

VSADDUSW
uint = __add_sat(uint, int);
uint2 = __add_sat(uint2, int2);
uint3 = __add_sat(uint3, int3);
uint4 = __add_sat(uint4, int4);
uint8 = __add_sat(uint8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __add_sat(uint16, int16);
#endif

VSADDUW
uint = __add_sat(uint, uint);
uint2 = __add_sat(uint2, uint2);
uint3 = __add_sat(uint3, uint3);
uint4 = __add_sat(uint4, uint4);
uint8 = __add_sat(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __add_sat(uint16, uint16);
#endif

VSADDW
cint = __add_sat(cint, cint);
cint2 = __add_sat(cint2, cint2);
cint4 = __add_sat(cint4, cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __add_sat(cint8, cint8);
#endif

*/

#define __add_sat(a,b) __overload("__add_sat",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __and                                                                  */
/*----------------------------------------------------------------------------*/
/*

AND
bool2 = __and(bool2, bool2);
bool3 = __and(bool3, bool3);
bool4 = __and(bool4, bool4);
bool8 = __and(bool8, bool8);
bool16 = __and(bool16, bool16);
bool32 = __and(bool32, bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
bool64 = __and(bool64, bool64);
#endif

*/

#define __and(a,b) __overload("__and",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __andn                                                                 */
/*----------------------------------------------------------------------------*/
/*

ANDND, ANDNW, VANDNW
signed char = __andn(signed char, signed char);
signed char = __andn(signed char, (signed char)(k));
char2 = __andn(char2, char2);
char2 = __andn(char2, (char2)(k));
char3 = __andn(char3, char3);
char3 = __andn(char3, (char3)(k));
char4 = __andn(char4, char4);
char4 = __andn(char4, (char4)(k));
char8 = __andn(char8, char8);
char16 = __andn(char16, char16);
char32 = __andn(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __andn(char64, char64);
#endif
uchar = __andn(uchar, uchar);
uchar = __andn(uchar, (uchar)(k));
uchar2 = __andn(uchar2, uchar2);
uchar2 = __andn(uchar2, (uchar2)(k));
uchar3 = __andn(uchar3, uchar3);
uchar3 = __andn(uchar3, (uchar3)(k));
uchar4 = __andn(uchar4, uchar4);
uchar4 = __andn(uchar4, (uchar4)(k));
uchar8 = __andn(uchar8, uchar8);
uchar16 = __andn(uchar16, uchar16);
uchar32 = __andn(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __andn(uchar64, uchar64);
#endif
short = __andn(short, short);
short = __andn(short, (short)(k));
short2 = __andn(short2, short2);
short2 = __andn(short2, (short2)(k));
short3 = __andn(short3, short3);
short4 = __andn(short4, short4);
short8 = __andn(short8, short8);
short16 = __andn(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __andn(short32, short32);
#endif
ushort = __andn(ushort, ushort);
ushort = __andn(ushort, (ushort)(k));
ushort2 = __andn(ushort2, ushort2);
ushort2 = __andn(ushort2, (ushort2)(k));
ushort3 = __andn(ushort3, ushort3);
ushort4 = __andn(ushort4, ushort4);
ushort8 = __andn(ushort8, ushort8);
ushort16 = __andn(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __andn(ushort32, ushort32);
#endif
int = __andn(int, int);
int = __andn(int, (int)(k));
int2 = __andn(int2, int2);
int2 = __andn(int2, (int2)(k));
int3 = __andn(int3, int3);
int3 = __andn(int3, (int3)(k));
int4 = __andn(int4, int4);
int4 = __andn(int4, (int4)(k));
int8 = __andn(int8, int8);
int8 = __andn(int8, (int8)(k));
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __andn(int16, int16);
int16 = __andn(int16, (int16)(k));
#endif
uint = __andn(uint, uint);
uint = __andn(uint, (uint)(k));
uint2 = __andn(uint2, uint2);
uint2 = __andn(uint2, (uint2)(k));
uint3 = __andn(uint3, uint3);
uint3 = __andn(uint3, (uint3)(k));
uint4 = __andn(uint4, uint4);
uint4 = __andn(uint4, (uint4)(k));
uint8 = __andn(uint8, uint8);
uint8 = __andn(uint8, (uint8)(k));
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __andn(uint16, uint16);
uint16 = __andn(uint16, (uint16)(k));
#endif

ANDND, VANDNW
long = __andn(long, long);
long = __andn(long, (long)(k));
long2 = __andn(long2, long2);
long3 = __andn(long3, long3);
long4 = __andn(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __andn(long8, long8);
#endif
ulong = __andn(ulong, ulong);
ulong = __andn(ulong, (ulong)(k));
ulong2 = __andn(ulong2, ulong2);
ulong3 = __andn(ulong3, ulong3);
ulong4 = __andn(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __andn(ulong8, ulong8);
#endif

ANDN
bool2 = __andn(bool2, bool2);
bool3 = __andn(bool3, bool3);
bool4 = __andn(bool4, bool4);
bool8 = __andn(bool8, bool8);
bool16 = __andn(bool16, bool16);
bool32 = __andn(bool32, bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
bool64 = __andn(bool64, bool64);
#endif

*/

#define __andn(a,b) __overload("__andn",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __apply_sign                                                           */
/*----------------------------------------------------------------------------*/
/*

VAPYSB
signed char = __apply_sign(signed char, signed char);
char2 = __apply_sign(char2, char2);
char3 = __apply_sign(char3, char3);
char4 = __apply_sign(char4, char4);
char8 = __apply_sign(char8, char8);
char16 = __apply_sign(char16, char16);
char32 = __apply_sign(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __apply_sign(char64, char64);
#endif

VAPYSH
short = __apply_sign(short, short);
short2 = __apply_sign(short2, short2);
short3 = __apply_sign(short3, short3);
short4 = __apply_sign(short4, short4);
short8 = __apply_sign(short8, short8);
short16 = __apply_sign(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __apply_sign(short32, short32);
#endif

VAPYSW
int = __apply_sign(int, int);
int2 = __apply_sign(int2, int2);
int3 = __apply_sign(int3, int3);
int4 = __apply_sign(int4, int4);
int8 = __apply_sign(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __apply_sign(int16, int16);
#endif

VAPYSD
long = __apply_sign(long, long);
long2 = __apply_sign(long2, long2);
long3 = __apply_sign(long3, long3);
long4 = __apply_sign(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __apply_sign(long8, long8);
#endif

*/

#define __apply_sign(a,b) __overload("__apply_sign",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __binary_log                                                           */
/*----------------------------------------------------------------------------*/
/*

VBINLOGW
uint = __binary_log(uint);
uint2 = __binary_log(uint2);
uint3 = __binary_log(uint3);
uint4 = __binary_log(uint4);
uint8 = __binary_log(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __binary_log(uint16);
#endif

*/

#define __binary_log(a) __overload("__binary_log",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __bit_reverse                                                          */
/*----------------------------------------------------------------------------*/
/*

VBITRW
int = __bit_reverse(int);
int2 = __bit_reverse(int2);
int3 = __bit_reverse(int3);
int4 = __bit_reverse(int4);
int8 = __bit_reverse(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __bit_reverse(int16);
#endif
uint = __bit_reverse(uint);
uint2 = __bit_reverse(uint2);
uint3 = __bit_reverse(uint3);
uint4 = __bit_reverse(uint4);
uint8 = __bit_reverse(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __bit_reverse(uint16);
#endif

VBITRD
long = __bit_reverse(long);
long2 = __bit_reverse(long2);
long3 = __bit_reverse(long3);
long4 = __bit_reverse(long4);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __bit_reverse(long8);
#endif
ulong = __bit_reverse(ulong);
ulong2 = __bit_reverse(ulong2);
ulong3 = __bit_reverse(ulong3);
ulong4 = __bit_reverse(ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __bit_reverse(ulong8);
#endif

BITR
#if __C7X_VEC_SIZE_BITS__ == 256
bool32 = __bit_reverse(bool32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
bool64 = __bit_reverse(bool64);
#endif

*/

#define __bit_reverse(a) __overload("__bit_reverse",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __bit_transpose                                                        */
/*----------------------------------------------------------------------------*/
/*

VBITTRAN8B
uchar8 = __bit_transpose(uchar8);
uchar16 = __bit_transpose(uchar16);
uchar32 = __bit_transpose(uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __bit_transpose(uchar64);
#endif

*/

#define __bit_transpose(a) __overload("__bit_transpose",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __classify                                                             */
/*----------------------------------------------------------------------------*/
/*

VCLASSSP
int = __classify(float);
int2 = __classify(float2);
int3 = __classify(float3);
int4 = __classify(float4);
int8 = __classify(float8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __classify(float16);
#endif

VCLASSDP
long = __classify(double);
long2 = __classify(double2);
long3 = __classify(double3);
long4 = __classify(double4);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __classify(double8);
#endif

*/

#define __classify(a) __overload("__classify",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __clear                                                                */
/*----------------------------------------------------------------------------*/
/*

CLR
uint = __clear(uint, uint);

*/

/*----------------------------------------------------------------------------*/
/* ID: __cmatmpy_ext                                                          */
/*----------------------------------------------------------------------------*/
/*

VCMATMPYHW
cint2 = __cmatmpy_ext(cshort2, cshort4);
cint4 = __cmatmpy_ext(cshort4, cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __cmatmpy_ext(cshort8, cshort16);
#endif

*/

#define __cmatmpy_ext(a,b) __overload("__cmatmpy_ext",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __cmatmpy_fx                                                           */
/*----------------------------------------------------------------------------*/
/*

VCMATMPYR1HH
cshort2 = __cmatmpy_fx(cshort2, cshort4);
cshort4 = __cmatmpy_fx(cshort4, cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
cshort8 = __cmatmpy_fx(cshort8, cshort16);
#endif

*/

#define __cmatmpy_fx(a,b) __overload("__cmatmpy_fx",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __cmp_eq                                                               */
/*----------------------------------------------------------------------------*/
/*

CMPEQW
int = __cmp_eq(int, int);
int = __cmp_eq(int, (int)(k));

CMPEQSP
int = __cmp_eq(float, float);

CMPEQD
int = __cmp_eq(long, (int)(k));
int = __cmp_eq(long, long);

CMPEQDP
int = __cmp_eq(double, double);

*/

#define __cmp_eq(a,b) __overload("__cmp_eq",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __cmp_eq_bool                                                          */
/*----------------------------------------------------------------------------*/
/*

VCMPEQB
bool2 = __cmp_eq_bool(char2, char2);
bool3 = __cmp_eq_bool(char3, char3);
bool4 = __cmp_eq_bool(char4, char4);
bool8 = __cmp_eq_bool(char8, char8);
bool16 = __cmp_eq_bool(char16, char16);
bool32 = __cmp_eq_bool(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
bool64 = __cmp_eq_bool(char64, char64);
#endif
bool2 = __cmp_eq_bool(uchar2, uchar2);
bool3 = __cmp_eq_bool(uchar3, uchar3);
bool4 = __cmp_eq_bool(uchar4, uchar4);
bool8 = __cmp_eq_bool(uchar8, uchar8);
bool16 = __cmp_eq_bool(uchar16, uchar16);
bool32 = __cmp_eq_bool(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
bool64 = __cmp_eq_bool(uchar64, uchar64);
#endif

VCMPEQH
bool2 = __cmp_eq_bool(short2, short2);
bool3 = __cmp_eq_bool(short3, short3);
bool4 = __cmp_eq_bool(short4, short4);
bool8 = __cmp_eq_bool(short8, short8);
bool16 = __cmp_eq_bool(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
bool32 = __cmp_eq_bool(short32, short32);
#endif
bool2 = __cmp_eq_bool(ushort2, ushort2);
bool3 = __cmp_eq_bool(ushort3, ushort3);
bool4 = __cmp_eq_bool(ushort4, ushort4);
bool8 = __cmp_eq_bool(ushort8, ushort8);
bool16 = __cmp_eq_bool(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
bool32 = __cmp_eq_bool(ushort32, ushort32);
#endif

VCMPEQW
bool2 = __cmp_eq_bool(int2, int2);
bool3 = __cmp_eq_bool(int3, int3);
bool4 = __cmp_eq_bool(int4, int4);
bool8 = __cmp_eq_bool(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
bool16 = __cmp_eq_bool(int16, int16);
#endif
bool2 = __cmp_eq_bool(uint2, uint2);
bool3 = __cmp_eq_bool(uint3, uint3);
bool4 = __cmp_eq_bool(uint4, uint4);
bool8 = __cmp_eq_bool(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
bool16 = __cmp_eq_bool(uint16, uint16);
#endif

VCMPEQSP
bool2 = __cmp_eq_bool(float2, float2);
bool3 = __cmp_eq_bool(float3, float3);
bool4 = __cmp_eq_bool(float4, float4);
bool8 = __cmp_eq_bool(float8, float8);
#if __C7X_VEC_SIZE_BITS__ == 512
bool16 = __cmp_eq_bool(float16, float16);
#endif

VCMPEQD
bool2 = __cmp_eq_bool(long2, long2);
bool3 = __cmp_eq_bool(long3, long3);
bool4 = __cmp_eq_bool(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
bool8 = __cmp_eq_bool(long8, long8);
#endif
bool2 = __cmp_eq_bool(ulong2, ulong2);
bool3 = __cmp_eq_bool(ulong3, ulong3);
bool4 = __cmp_eq_bool(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
bool8 = __cmp_eq_bool(ulong8, ulong8);
#endif

VCMPEQDP
bool2 = __cmp_eq_bool(double2, double2);
bool3 = __cmp_eq_bool(double3, double3);
bool4 = __cmp_eq_bool(double4, double4);
#if __C7X_VEC_SIZE_BITS__ == 512
bool8 = __cmp_eq_bool(double8, double8);
#endif

*/

#define __cmp_eq_bool(a,b) __overload("__cmp_eq_bool",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __cmp_ge                                                               */
/*----------------------------------------------------------------------------*/
/*

CMPGEW
int = __cmp_ge(int, int);
int = __cmp_ge(int, (int)(k));

CMPGEUW
int = __cmp_ge(uint, uint);
int = __cmp_ge(uint, (uint)(k));

CMPGED
int = __cmp_ge(long, (int)(k));
int = __cmp_ge(long, long);

CMPGEUD
int = __cmp_ge(ulong, (uint)(k));
int = __cmp_ge(ulong, ulong);

*/

#define __cmp_ge(a,b) __overload("__cmp_ge",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __cmp_ge_bool                                                          */
/*----------------------------------------------------------------------------*/
/*

VCMPGEB
bool2 = __cmp_ge_bool(char2, char2);
bool3 = __cmp_ge_bool(char3, char3);
bool4 = __cmp_ge_bool(char4, char4);
bool8 = __cmp_ge_bool(char8, char8);
bool16 = __cmp_ge_bool(char16, char16);
bool32 = __cmp_ge_bool(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
bool64 = __cmp_ge_bool(char64, char64);
#endif

VCMPGEUB
bool2 = __cmp_ge_bool(uchar2, uchar2);
bool3 = __cmp_ge_bool(uchar3, uchar3);
bool4 = __cmp_ge_bool(uchar4, uchar4);
bool8 = __cmp_ge_bool(uchar8, uchar8);
bool16 = __cmp_ge_bool(uchar16, uchar16);
bool32 = __cmp_ge_bool(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
bool64 = __cmp_ge_bool(uchar64, uchar64);
#endif

VCMPGEH
bool2 = __cmp_ge_bool(short2, short2);
bool3 = __cmp_ge_bool(short3, short3);
bool4 = __cmp_ge_bool(short4, short4);
bool8 = __cmp_ge_bool(short8, short8);
bool16 = __cmp_ge_bool(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
bool32 = __cmp_ge_bool(short32, short32);
#endif

VCMPGEUH
bool2 = __cmp_ge_bool(ushort2, ushort2);
bool3 = __cmp_ge_bool(ushort3, ushort3);
bool4 = __cmp_ge_bool(ushort4, ushort4);
bool8 = __cmp_ge_bool(ushort8, ushort8);
bool16 = __cmp_ge_bool(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
bool32 = __cmp_ge_bool(ushort32, ushort32);
#endif

VCMPGEW
bool2 = __cmp_ge_bool(int2, int2);
bool3 = __cmp_ge_bool(int3, int3);
bool4 = __cmp_ge_bool(int4, int4);
bool8 = __cmp_ge_bool(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
bool16 = __cmp_ge_bool(int16, int16);
#endif

VCMPGEUW
bool2 = __cmp_ge_bool(uint2, uint2);
bool3 = __cmp_ge_bool(uint3, uint3);
bool4 = __cmp_ge_bool(uint4, uint4);
bool8 = __cmp_ge_bool(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
bool16 = __cmp_ge_bool(uint16, uint16);
#endif

VCMPGED
bool2 = __cmp_ge_bool(long2, long2);
bool3 = __cmp_ge_bool(long3, long3);
bool4 = __cmp_ge_bool(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
bool8 = __cmp_ge_bool(long8, long8);
#endif

VCMPGEUD
bool2 = __cmp_ge_bool(ulong2, ulong2);
bool3 = __cmp_ge_bool(ulong3, ulong3);
bool4 = __cmp_ge_bool(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
bool8 = __cmp_ge_bool(ulong8, ulong8);
#endif

*/

#define __cmp_ge_bool(a,b) __overload("__cmp_ge_bool",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __cmp_gt                                                               */
/*----------------------------------------------------------------------------*/
/*

CMPGTW
int = __cmp_gt(int, int);
int = __cmp_gt(int, (int)(k));

CMPGTUW
int = __cmp_gt(uint, uint);
int = __cmp_gt(uint, (uint)(k));

CMPGTD
int = __cmp_gt(long, (int)(k));
int = __cmp_gt(long, long);

CMPGTUD
int = __cmp_gt(ulong, (uint)(k));
int = __cmp_gt(ulong, ulong);

*/

#define __cmp_gt(a,b) __overload("__cmp_gt",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __cmp_gt_bool                                                          */
/*----------------------------------------------------------------------------*/
/*

VCMPGTB
bool2 = __cmp_gt_bool(char2, char2);
bool3 = __cmp_gt_bool(char3, char3);
bool4 = __cmp_gt_bool(char4, char4);
bool8 = __cmp_gt_bool(char8, char8);
bool16 = __cmp_gt_bool(char16, char16);
bool32 = __cmp_gt_bool(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
bool64 = __cmp_gt_bool(char64, char64);
#endif

VCMPGTUB
bool2 = __cmp_gt_bool(uchar2, uchar2);
bool3 = __cmp_gt_bool(uchar3, uchar3);
bool4 = __cmp_gt_bool(uchar4, uchar4);
bool8 = __cmp_gt_bool(uchar8, uchar8);
bool16 = __cmp_gt_bool(uchar16, uchar16);
bool32 = __cmp_gt_bool(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
bool64 = __cmp_gt_bool(uchar64, uchar64);
#endif

VCMPGTH
bool2 = __cmp_gt_bool(short2, short2);
bool3 = __cmp_gt_bool(short3, short3);
bool4 = __cmp_gt_bool(short4, short4);
bool8 = __cmp_gt_bool(short8, short8);
bool16 = __cmp_gt_bool(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
bool32 = __cmp_gt_bool(short32, short32);
#endif

VCMPGTUH
bool2 = __cmp_gt_bool(ushort2, ushort2);
bool3 = __cmp_gt_bool(ushort3, ushort3);
bool4 = __cmp_gt_bool(ushort4, ushort4);
bool8 = __cmp_gt_bool(ushort8, ushort8);
bool16 = __cmp_gt_bool(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
bool32 = __cmp_gt_bool(ushort32, ushort32);
#endif

VCMPGTW
bool2 = __cmp_gt_bool(int2, int2);
bool3 = __cmp_gt_bool(int3, int3);
bool4 = __cmp_gt_bool(int4, int4);
bool8 = __cmp_gt_bool(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
bool16 = __cmp_gt_bool(int16, int16);
#endif

VCMPGTUW
bool2 = __cmp_gt_bool(uint2, uint2);
bool3 = __cmp_gt_bool(uint3, uint3);
bool4 = __cmp_gt_bool(uint4, uint4);
bool8 = __cmp_gt_bool(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
bool16 = __cmp_gt_bool(uint16, uint16);
#endif

VCMPGTD
bool2 = __cmp_gt_bool(long2, long2);
bool3 = __cmp_gt_bool(long3, long3);
bool4 = __cmp_gt_bool(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
bool8 = __cmp_gt_bool(long8, long8);
#endif

VCMPGTUD
bool2 = __cmp_gt_bool(ulong2, ulong2);
bool3 = __cmp_gt_bool(ulong3, ulong3);
bool4 = __cmp_gt_bool(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
bool8 = __cmp_gt_bool(ulong8, ulong8);
#endif

*/

#define __cmp_gt_bool(a,b) __overload("__cmp_gt_bool",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __cmp_le                                                               */
/*----------------------------------------------------------------------------*/
/*

CMPLESP
int = __cmp_le(float, float);

CMPLEDP
int = __cmp_le(double, double);

*/

#define __cmp_le(a,b) __overload("__cmp_le",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __cmp_le_bool                                                          */
/*----------------------------------------------------------------------------*/
/*

VCMPLESP
bool2 = __cmp_le_bool(float2, float2);
bool3 = __cmp_le_bool(float3, float3);
bool4 = __cmp_le_bool(float4, float4);
bool8 = __cmp_le_bool(float8, float8);
#if __C7X_VEC_SIZE_BITS__ == 512
bool16 = __cmp_le_bool(float16, float16);
#endif

VCMPLEDP
bool2 = __cmp_le_bool(double2, double2);
bool3 = __cmp_le_bool(double3, double3);
bool4 = __cmp_le_bool(double4, double4);
#if __C7X_VEC_SIZE_BITS__ == 512
bool8 = __cmp_le_bool(double8, double8);
#endif

*/

#define __cmp_le_bool(a,b) __overload("__cmp_le_bool",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __cmp_lt                                                               */
/*----------------------------------------------------------------------------*/
/*

CMPLTSP
int = __cmp_lt(float, float);

CMPLTDP
int = __cmp_lt(double, double);

*/

#define __cmp_lt(a,b) __overload("__cmp_lt",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __cmp_lt_bool                                                          */
/*----------------------------------------------------------------------------*/
/*

VCMPLTSP
bool2 = __cmp_lt_bool(float2, float2);
bool3 = __cmp_lt_bool(float3, float3);
bool4 = __cmp_lt_bool(float4, float4);
bool8 = __cmp_lt_bool(float8, float8);
#if __C7X_VEC_SIZE_BITS__ == 512
bool16 = __cmp_lt_bool(float16, float16);
#endif

VCMPLTDP
bool2 = __cmp_lt_bool(double2, double2);
bool3 = __cmp_lt_bool(double3, double3);
bool4 = __cmp_lt_bool(double4, double4);
#if __C7X_VEC_SIZE_BITS__ == 512
bool8 = __cmp_lt_bool(double8, double8);
#endif

*/

#define __cmp_lt_bool(a,b) __overload("__cmp_lt_bool",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __cmpy_conj_ext                                                        */
/*----------------------------------------------------------------------------*/
/*

VCCMPYHW
cint = __cmpy_conj_ext(cshort, cshort);
cint2 = __cmpy_conj_ext(cshort2, cshort2);
cint4 = __cmpy_conj_ext(cshort4, cshort4);
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __cmpy_conj_ext(cshort8, cshort8);
#endif

*/

#define __cmpy_conj_ext(a,b) __overload("__cmpy_conj_ext",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __cmpy_conj_fx                                                         */
/*----------------------------------------------------------------------------*/
/*

VCCMPYR1HH
cshort = __cmpy_conj_fx(cshort, cshort);
cshort2 = __cmpy_conj_fx(cshort2, cshort2);
cshort4 = __cmpy_conj_fx(cshort4, cshort4);
cshort8 = __cmpy_conj_fx(cshort8, cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = __cmpy_conj_fx(cshort16, cshort16);
#endif

VCCMPYR1WW
cint = __cmpy_conj_fx(cint, cint);
cint2 = __cmpy_conj_fx(cint2, cint2);
cint4 = __cmpy_conj_fx(cint4, cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __cmpy_conj_fx(cint8, cint8);
#endif

*/

#define __cmpy_conj_fx(a,b) __overload("__cmpy_conj_fx",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __cmpy_ext                                                             */
/*----------------------------------------------------------------------------*/
/*

VCMPYHW
cint = __cmpy_ext(cshort, cshort);
cint2 = __cmpy_ext(cshort2, cshort2);
cint4 = __cmpy_ext(cshort4, cshort4);
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __cmpy_ext(cshort8, cshort8);
#endif

VCMPYSP
float4 = __cmpy_ext(cfloat, cfloat);
float8 = __cmpy_ext(cfloat2, cfloat2);
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __cmpy_ext(cfloat4, cfloat4);
#endif

*/

#define __cmpy_ext(a,b) __overload("__cmpy_ext",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __cmpy_fx                                                              */
/*----------------------------------------------------------------------------*/
/*

VCMPYR1HH
cshort = __cmpy_fx(cshort, cshort);
cshort2 = __cmpy_fx(cshort2, cshort2);
cshort4 = __cmpy_fx(cshort4, cshort4);
cshort8 = __cmpy_fx(cshort8, cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = __cmpy_fx(cshort16, cshort16);
#endif

VCMPYR1WW
cint = __cmpy_fx(cint, cint);
cint2 = __cmpy_fx(cint2, cint2);
cint4 = __cmpy_fx(cint4, cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __cmpy_fx(cint8, cint8);
#endif

*/

#define __cmpy_fx(a,b) __overload("__cmpy_fx",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __cmpyr_fx                                                             */
/*----------------------------------------------------------------------------*/
/*

VCMPYRHH
cshort = __cmpyr_fx(cshort, cshort);
cshort2 = __cmpyr_fx(cshort2, cshort2);
cshort4 = __cmpyr_fx(cshort4, cshort4);
cshort8 = __cmpyr_fx(cshort8, cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = __cmpyr_fx(cshort16, cshort16);
#endif

*/

#define __cmpyr_fx(a,b) __overload("__cmpyr_fx",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __compress_set_bits_left                                               */
/*----------------------------------------------------------------------------*/
/*

COMPRESSL
#if __C7X_VEC_SIZE_BITS__ == 256
bool32 = __compress_set_bits_left(bool32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
bool64 = __compress_set_bits_left(bool64);
#endif

*/

#define __compress_set_bits_left(a) __overload("__compress_set_bits_left",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __compress_set_bits_right                                              */
/*----------------------------------------------------------------------------*/
/*

COMPRESSR
#if __C7X_VEC_SIZE_BITS__ == 256
bool32 = __compress_set_bits_right(bool32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
bool64 = __compress_set_bits_right(bool64);
#endif

*/

#define __compress_set_bits_right(a) __overload("__compress_set_bits_right",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __conj_cmatmpy_ext                                                     */
/*----------------------------------------------------------------------------*/
/*

VCCMATMPYHW
cint2 = __conj_cmatmpy_ext(cshort2, cshort4);
cint4 = __conj_cmatmpy_ext(cshort4, cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __conj_cmatmpy_ext(cshort8, cshort16);
#endif

*/

#define __conj_cmatmpy_ext(a,b) __overload("__conj_cmatmpy_ext",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __conj_cmatmpy_fx                                                      */
/*----------------------------------------------------------------------------*/
/*

VCCMATMPYR1HH
cshort2 = __conj_cmatmpy_fx(cshort2, cshort4);
cshort4 = __conj_cmatmpy_fx(cshort4, cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
cshort8 = __conj_cmatmpy_fx(cshort8, cshort16);
#endif

*/

#define __conj_cmatmpy_fx(a,b) __overload("__conj_cmatmpy_fx",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __crot270                                                              */
/*----------------------------------------------------------------------------*/
/*

VCROT270H
cshort = __crot270(cshort);
cshort2 = __crot270(cshort2);
cshort4 = __crot270(cshort4);
cshort8 = __crot270(cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = __crot270(cshort16);
#endif

VCROT270W
cint = __crot270(cint);
cint2 = __crot270(cint2);
cint4 = __crot270(cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __crot270(cint8);
#endif

VCROT270SP
cfloat = __crot270(cfloat);
cfloat2 = __crot270(cfloat2);
cfloat4 = __crot270(cfloat4);
#if __C7X_VEC_SIZE_BITS__ == 512
cfloat8 = __crot270(cfloat8);
#endif

*/

#define __crot270(a) __overload("__crot270",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __crot90                                                               */
/*----------------------------------------------------------------------------*/
/*

VCROT90H
cshort = __crot90(cshort);
cshort2 = __crot90(cshort2);
cshort4 = __crot90(cshort4);
cshort8 = __crot90(cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = __crot90(cshort16);
#endif

VCROT90W
cint = __crot90(cint);
cint2 = __crot90(cint2);
cint4 = __crot90(cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __crot90(cint8);
#endif

VCROT90SP
cfloat = __crot90(cfloat);
cfloat2 = __crot90(cfloat2);
cfloat4 = __crot90(cfloat4);
#if __C7X_VEC_SIZE_BITS__ == 512
cfloat8 = __crot90(cfloat8);
#endif

*/

#define __crot90(a) __overload("__crot90",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __deal_bit                                                             */
/*----------------------------------------------------------------------------*/
/*

VBITDEALW
int = __deal_bit(int);
int2 = __deal_bit(int2);
int3 = __deal_bit(int3);
int4 = __deal_bit(int4);
int8 = __deal_bit(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __deal_bit(int16);
#endif
uint = __deal_bit(uint);
uint2 = __deal_bit(uint2);
uint3 = __deal_bit(uint3);
uint4 = __deal_bit(uint4);
uint8 = __deal_bit(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __deal_bit(uint16);
#endif

VBITDEALD
long = __deal_bit(long);
long2 = __deal_bit(long2);
long3 = __deal_bit(long3);
long4 = __deal_bit(long4);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __deal_bit(long8);
#endif
ulong = __deal_bit(ulong);
ulong2 = __deal_bit(ulong2);
ulong3 = __deal_bit(ulong3);
ulong4 = __deal_bit(ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __deal_bit(ulong8);
#endif

*/

#define __deal_bit(a) __overload("__deal_bit",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __deal_stride2                                                         */
/*----------------------------------------------------------------------------*/
/*

VDEAL2B
#if __C7X_VEC_SIZE_BITS__ == 256
char32 = __deal_stride2(char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __deal_stride2(char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
uchar32 = __deal_stride2(uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __deal_stride2(uchar64);
#endif

VDEAL2H
#if __C7X_VEC_SIZE_BITS__ == 256
cchar16 = __deal_stride2(cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = __deal_stride2(cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
short16 = __deal_stride2(short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __deal_stride2(short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ushort16 = __deal_stride2(ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __deal_stride2(ushort32);
#endif

VDEAL2W
#if __C7X_VEC_SIZE_BITS__ == 256
cshort8 = __deal_stride2(cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = __deal_stride2(cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
int8 = __deal_stride2(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __deal_stride2(int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
uint8 = __deal_stride2(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __deal_stride2(uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
float8 = __deal_stride2(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __deal_stride2(float16);
#endif

VDEAL2D
#if __C7X_VEC_SIZE_BITS__ == 256
cint4 = __deal_stride2(cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __deal_stride2(cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
cfloat4 = __deal_stride2(cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cfloat8 = __deal_stride2(cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long4 = __deal_stride2(long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __deal_stride2(long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ulong4 = __deal_stride2(ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __deal_stride2(ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
double4 = __deal_stride2(double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = __deal_stride2(double8);
#endif

*/

#define __deal_stride2(a) __overload("__deal_stride2",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __deal_stride4                                                         */
/*----------------------------------------------------------------------------*/
/*

VDEAL4B
#if __C7X_VEC_SIZE_BITS__ == 256
char32 = __deal_stride4(char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __deal_stride4(char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
uchar32 = __deal_stride4(uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __deal_stride4(uchar64);
#endif

VDEAL4H
#if __C7X_VEC_SIZE_BITS__ == 256
cchar16 = __deal_stride4(cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = __deal_stride4(cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
short16 = __deal_stride4(short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __deal_stride4(short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ushort16 = __deal_stride4(ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __deal_stride4(ushort32);
#endif

*/

#define __deal_stride4(a) __overload("__deal_stride4",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __decimate                                                             */
/*----------------------------------------------------------------------------*/
/*

DECIMATEB
#if __C7X_VEC_SIZE_BITS__ == 256
bool32 = __decimate(bool32, bool32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
bool64 = __decimate(bool64, bool64);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __dot_posneg128_mask                                                   */
/*----------------------------------------------------------------------------*/
/*

VDOTPMPN16W8D
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __dot_posneg128_mask(ushort32, ushort8, int16);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __dot_posneg128_mask_ext                                               */
/*----------------------------------------------------------------------------*/
/*

VDOTPMPNU16W8D
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __dot_posneg128_mask_ext(ushort32, ushort8, uint16);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __dot_posneg256_mask                                                   */
/*----------------------------------------------------------------------------*/
/*

VDOTPMPN16H16W
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __dot_posneg256_mask(ushort32, ushort16, short16);
#endif

VDOTPMPNU16H16W
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __dot_posneg256_mask(ushort32, ushort16, ushort16);
#endif

VDOTPMPN32H8W
#if __C7X_VEC_SIZE_BITS__ == 512
int8 = __dot_posneg256_mask(uint8, uint8, short32);
#endif

VDOTPMPNU32H8W
#if __C7X_VEC_SIZE_BITS__ == 512
uint8 = __dot_posneg256_mask(uint8, uint8, ushort32);
#endif

*/

#define __dot_posneg256_mask(a,b,c) __overload("__dot_posneg256_mask",(a),(b),(c))((a),(b),(c))

/*----------------------------------------------------------------------------*/
/* ID: __dot_posneg512_mask                                                   */
/*----------------------------------------------------------------------------*/
/*

VDOTPMPN16B32H
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __dot_posneg512_mask(ushort32, ushort32, char16);
#endif

VDOTPMPN32B16H
#if __C7X_VEC_SIZE_BITS__ == 512
short16 = __dot_posneg512_mask(uint16, uint16, char32);
#endif

VDOTPMPNU32B16H
#if __C7X_VEC_SIZE_BITS__ == 512
ushort16 = __dot_posneg512_mask(uint16, uint16, uchar32);
#endif

*/

#define __dot_posneg512_mask(a,b,c) __overload("__dot_posneg512_mask",(a),(b),(c))((a),(b),(c))

/*----------------------------------------------------------------------------*/
/* ID: __dot_posneg512_mask_ext                                               */
/*----------------------------------------------------------------------------*/
/*

VDOTPMPN32B16W
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __dot_posneg512_mask_ext(uint16, uint16, char32);
#endif

VDOTPMPNU32B16W
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __dot_posneg512_mask_ext(uint16, uint16, uchar32);
#endif

*/

#define __dot_posneg512_mask_ext(a,b,c) __overload("__dot_posneg512_mask_ext",(a),(b),(c))((a),(b),(c))

/*----------------------------------------------------------------------------*/
/* ID: __dotp2                                                                */
/*----------------------------------------------------------------------------*/
/*

VDOTP2SUBH
short = __dotp2(char2, uchar2);
short2 = __dotp2(char4, uchar4);
short4 = __dotp2(char8, uchar8);
short8 = __dotp2(char16, uchar16);
short16 = __dotp2(char32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __dotp2(char64, uchar64);
#endif

VDOTP2UBH
ushort = __dotp2(uchar2, uchar2);
ushort2 = __dotp2(uchar4, uchar4);
ushort4 = __dotp2(uchar8, uchar8);
ushort8 = __dotp2(uchar16, uchar16);
ushort16 = __dotp2(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __dotp2(uchar64, uchar64);
#endif

VDOTP2HW
int = __dotp2(short2, short2);
int2 = __dotp2(short4, short4);
int4 = __dotp2(short8, short8);
int8 = __dotp2(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __dotp2(short32, short32);
#endif

VDOTP2SUHW
int = __dotp2(short2, ushort2);
int2 = __dotp2(short4, ushort4);
int4 = __dotp2(short8, ushort8);
int8 = __dotp2(short16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __dotp2(short32, ushort32);
#endif

VDOTP2UHW
uint = __dotp2(ushort2, ushort2);
uint2 = __dotp2(ushort4, ushort4);
uint4 = __dotp2(ushort8, ushort8);
uint8 = __dotp2(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __dotp2(ushort32, ushort32);
#endif

VCDOTP2HW
cint = __dotp2(cshort2, cshort2);
cint2 = __dotp2(cshort4, cshort4);
cint4 = __dotp2(cshort8, cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __dotp2(cshort16, cshort16);
#endif

VDOTP2WD
long = __dotp2(int2, int2);
long2 = __dotp2(int4, int4);
long4 = __dotp2(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __dotp2(int16, int16);
#endif

*/

#define __dotp2(a,b) __overload("__dotp2",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __dotp2_conj                                                           */
/*----------------------------------------------------------------------------*/
/*

VCCDOTP2HW
cint = __dotp2_conj(cshort2, cshort2);
cint2 = __dotp2_conj(cshort4, cshort4);
cint4 = __dotp2_conj(cshort8, cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __dotp2_conj(cshort16, cshort16);
#endif

*/

#define __dotp2_conj(a,b) __overload("__dotp2_conj",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __dotp2_cross                                                          */
/*----------------------------------------------------------------------------*/
/*

VDOTP2XWD
long = __dotp2_cross(int2, int2);
long2 = __dotp2_cross(int4, int4);
long4 = __dotp2_cross(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __dotp2_cross(int16, int16);
#endif

*/

#define __dotp2_cross(a,b) __overload("__dotp2_cross",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __dotp2_cross_negate                                                   */
/*----------------------------------------------------------------------------*/
/*

VDOTP2NXWD
long = __dotp2_cross_negate(int2, int2);
long2 = __dotp2_cross_negate(int4, int4);
long4 = __dotp2_cross_negate(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __dotp2_cross_negate(int16, int16);
#endif

*/

#define __dotp2_cross_negate(a,b) __overload("__dotp2_cross_negate",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __dotp2_ext                                                            */
/*----------------------------------------------------------------------------*/
/*

VDOTP2HD
long = __dotp2_ext(short2, short2);
long2 = __dotp2_ext(short4, short4);
long4 = __dotp2_ext(short8, short8);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __dotp2_ext(short16, short16);
#endif

VDOTP2SUHD
long = __dotp2_ext(short2, ushort2);
long2 = __dotp2_ext(short4, ushort4);
long4 = __dotp2_ext(short8, ushort8);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __dotp2_ext(short16, ushort16);
#endif

VDOTP2UHD
ulong = __dotp2_ext(ushort2, ushort2);
ulong2 = __dotp2_ext(ushort4, ushort4);
ulong4 = __dotp2_ext(ushort8, ushort8);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __dotp2_ext(ushort16, ushort16);
#endif

*/

#define __dotp2_ext(a,b) __overload("__dotp2_ext",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __dotp2_fx_ext                                                         */
/*----------------------------------------------------------------------------*/
/*

C6DOTP2RSUHW
int = __dotp2_fx_ext(short2, ushort2);

*/

/*----------------------------------------------------------------------------*/
/* ID: __dotp2_negate                                                         */
/*----------------------------------------------------------------------------*/
/*

C6DOTPN2HW
int = __dotp2_negate(short2, short2);

C6DOTPN2RSUHH
int = __dotp2_negate(short2, ushort2);

VDOTP2NWD
long = __dotp2_negate(int2, int2);
long2 = __dotp2_negate(int4, int4);
long4 = __dotp2_negate(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __dotp2_negate(int16, int16);
#endif

*/

#define __dotp2_negate(a,b) __overload("__dotp2_negate",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __dotp4                                                                */
/*----------------------------------------------------------------------------*/
/*

VDOTP4HW
int = __dotp4(short4, short4);
int2 = __dotp4(short8, short8);
int4 = __dotp4(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
int8 = __dotp4(short32, short32);
#endif

VDOTP4SUHW
int = __dotp4(short4, ushort4);
int2 = __dotp4(short8, ushort8);
int4 = __dotp4(short16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
int8 = __dotp4(short32, ushort32);
#endif

*/

#define __dotp4(a,b) __overload("__dotp4",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __dotp4_ext                                                            */
/*----------------------------------------------------------------------------*/
/*

VDOTP4SUBW
int = __dotp4_ext(char4, uchar4);
int2 = __dotp4_ext(char8, uchar8);
int4 = __dotp4_ext(char16, uchar16);
int8 = __dotp4_ext(char32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __dotp4_ext(char64, uchar64);
#endif

VDOTP4UBW
uint = __dotp4_ext(uchar4, uchar4);
uint2 = __dotp4_ext(uchar8, uchar8);
uint4 = __dotp4_ext(uchar16, uchar16);
uint8 = __dotp4_ext(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __dotp4_ext(uchar64, uchar64);
#endif

VDOTP4HD
long = __dotp4_ext(short4, short4);
long2 = __dotp4_ext(short8, short8);
long4 = __dotp4_ext(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __dotp4_ext(short32, short32);
#endif

VDOTP4SUHD
long = __dotp4_ext(short4, ushort4);
long2 = __dotp4_ext(short8, ushort8);
long4 = __dotp4_ext(short16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __dotp4_ext(short32, ushort32);
#endif

VDOTP4UHD
ulong = __dotp4_ext(ushort4, ushort4);
ulong2 = __dotp4_ext(ushort8, ushort8);
ulong4 = __dotp4_ext(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __dotp4_ext(ushort32, ushort32);
#endif

*/

#define __dotp4_ext(a,b) __overload("__dotp4_ext",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __dotp8_ext                                                            */
/*----------------------------------------------------------------------------*/
/*

VDOTP8SUBW
int2 = __dotp8_ext(char8, uchar8);
int4 = __dotp8_ext(char16, uchar16);
int8 = __dotp8_ext(char32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __dotp8_ext(char64, uchar64);
#endif

*/

#define __dotp8_ext(a,b) __overload("__dotp8_ext",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __double_to_float                                                      */
/*----------------------------------------------------------------------------*/
/*

VDPSP
float2 = __double_to_float(double);
float4 = __double_to_float(double2);
float8 = __double_to_float(double4);
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __double_to_float(double8);
#endif

*/

#define __double_to_float(a) __overload("__double_to_float",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __double_to_int                                                        */
/*----------------------------------------------------------------------------*/
/*

VDPINT
int2 = __double_to_int(double);
int4 = __double_to_int(double2);
int8 = __double_to_int(double4);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __double_to_int(double8);
#endif

*/

#define __double_to_int(a) __overload("__double_to_int",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __double_to_int_rtz                                                    */
/*----------------------------------------------------------------------------*/
/*

VDPTRUNC
int2 = __double_to_int_rtz(double);
int4 = __double_to_int_rtz(double2);
int8 = __double_to_int_rtz(double4);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __double_to_int_rtz(double8);
#endif

*/

#define __double_to_int_rtz(a) __overload("__double_to_int_rtz",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __dual_horizontal_add_skip1                                            */
/*----------------------------------------------------------------------------*/
/*

VHADDEOW4D
#if __C7X_VEC_SIZE_BITS__ == 512
long4 = __dual_horizontal_add_skip1(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long4 = __dual_horizontal_add_skip1(int8, int8);
#endif

VHADDUEOW4D
#if __C7X_VEC_SIZE_BITS__ == 512
ulong4 = __dual_horizontal_add_skip1(uint16, uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ulong4 = __dual_horizontal_add_skip1(uint8, uint8);
#endif

VHADDEOW4D
#if __C7X_VEC_SIZE_BITS__ == 512
clong2 = __dual_horizontal_add_skip1(cint8, cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
clong2 = __dual_horizontal_add_skip1(cint4, cint4);
#endif

*/

#define __dual_horizontal_add_skip1(a,b) __overload("__dual_horizontal_add_skip1",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __dual_sort_lo_asc_hi_asc                                              */
/*----------------------------------------------------------------------------*/
/*

VDSORTIIH
#if __C7X_VEC_SIZE_BITS__ == 512
short16 = __dual_sort_lo_asc_hi_asc(short16);
short32 = __dual_sort_lo_asc_hi_asc(short32);
#endif

VDSORTIIUH
#if __C7X_VEC_SIZE_BITS__ == 512
ushort16 = __dual_sort_lo_asc_hi_asc(ushort16);
ushort32 = __dual_sort_lo_asc_hi_asc(ushort32);
#endif

*/

#define __dual_sort_lo_asc_hi_asc(a) __overload("__dual_sort_lo_asc_hi_asc",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __dual_sort_lo_asc_hi_asc_perm                                         */
/*----------------------------------------------------------------------------*/
/*

VDSORTPIIH
#if __C7X_VEC_SIZE_BITS__ == 512
uchar32 = __dual_sort_lo_asc_hi_asc_perm(short16);
uchar64 = __dual_sort_lo_asc_hi_asc_perm(short32);
#endif

VDSORTPIIUH
#if __C7X_VEC_SIZE_BITS__ == 512
uchar32 = __dual_sort_lo_asc_hi_asc_perm(ushort16);
uchar64 = __dual_sort_lo_asc_hi_asc_perm(ushort32);
#endif

*/

#define __dual_sort_lo_asc_hi_asc_perm(a) __overload("__dual_sort_lo_asc_hi_asc_perm",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __dual_sort_lo_asc_hi_desc                                             */
/*----------------------------------------------------------------------------*/
/*

VDSORTIDH
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __dual_sort_lo_asc_hi_desc(short32);
#endif

VDSORTIDUH
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __dual_sort_lo_asc_hi_desc(ushort32);
#endif

*/

#define __dual_sort_lo_asc_hi_desc(a) __overload("__dual_sort_lo_asc_hi_desc",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __dual_sort_lo_asc_hi_desc_perm                                        */
/*----------------------------------------------------------------------------*/
/*

VDSORTPIDH
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __dual_sort_lo_asc_hi_desc_perm(short32);
#endif

VDSORTPIDUH
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __dual_sort_lo_asc_hi_desc_perm(ushort32);
#endif

*/

#define __dual_sort_lo_asc_hi_desc_perm(a) __overload("__dual_sort_lo_asc_hi_desc_perm",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __dual_sort_lo_desc_hi_asc                                             */
/*----------------------------------------------------------------------------*/
/*

VDSORTDIH
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __dual_sort_lo_desc_hi_asc(short32);
#endif

VDSORTDIUH
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __dual_sort_lo_desc_hi_asc(ushort32);
#endif

*/

#define __dual_sort_lo_desc_hi_asc(a) __overload("__dual_sort_lo_desc_hi_asc",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __dual_sort_lo_desc_hi_asc_perm                                        */
/*----------------------------------------------------------------------------*/
/*

VDSORTPDIH
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __dual_sort_lo_desc_hi_asc_perm(short32);
#endif

VDSORTPDIUH
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __dual_sort_lo_desc_hi_asc_perm(ushort32);
#endif

*/

#define __dual_sort_lo_desc_hi_asc_perm(a) __overload("__dual_sort_lo_desc_hi_asc_perm",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __dual_sort_lo_desc_hi_desc                                            */
/*----------------------------------------------------------------------------*/
/*

VDSORTDDH
#if __C7X_VEC_SIZE_BITS__ == 512
short16 = __dual_sort_lo_desc_hi_desc(short16);
short32 = __dual_sort_lo_desc_hi_desc(short32);
#endif

VDSORTDDUH
#if __C7X_VEC_SIZE_BITS__ == 512
ushort16 = __dual_sort_lo_desc_hi_desc(ushort16);
ushort32 = __dual_sort_lo_desc_hi_desc(ushort32);
#endif

*/

#define __dual_sort_lo_desc_hi_desc(a) __overload("__dual_sort_lo_desc_hi_desc",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __dual_sort_lo_desc_hi_desc_perm                                       */
/*----------------------------------------------------------------------------*/
/*

VDSORTPDDH
#if __C7X_VEC_SIZE_BITS__ == 512
uchar32 = __dual_sort_lo_desc_hi_desc_perm(short16);
uchar64 = __dual_sort_lo_desc_hi_desc_perm(short32);
#endif

VDSORTPDDUH
#if __C7X_VEC_SIZE_BITS__ == 512
uchar32 = __dual_sort_lo_desc_hi_desc_perm(ushort16);
uchar64 = __dual_sort_lo_desc_hi_desc_perm(ushort32);
#endif

*/

#define __dual_sort_lo_desc_hi_desc_perm(a) __overload("__dual_sort_lo_desc_hi_desc_perm",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __duplicate                                                            */
/*----------------------------------------------------------------------------*/
/*

VDUPB
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __duplicate(signed char);
char64 = __duplicate((signed char)(k));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
char32 = __duplicate(signed char);
char32 = __duplicate((signed char)(k));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __duplicate(uchar);
uchar64 = __duplicate((uchar)(k));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
uchar32 = __duplicate(uchar);
uchar32 = __duplicate((uchar)(k));
#endif

VDUPH
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = __duplicate(cchar);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
cchar16 = __duplicate(cchar);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __duplicate(short);
short32 = __duplicate((short)(k));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
short16 = __duplicate(short);
short16 = __duplicate((short)(k));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __duplicate(ushort);
ushort32 = __duplicate((ushort)(k));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ushort16 = __duplicate(ushort);
ushort16 = __duplicate((ushort)(k));
#endif

VDUPW
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = __duplicate(cshort);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
cshort8 = __duplicate(cshort);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __duplicate(int);
int16 = __duplicate((int)(k));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
int8 = __duplicate(int);
int8 = __duplicate((int)(k));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __duplicate(uint);
uint16 = __duplicate((uint)(k));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
uint8 = __duplicate(uint);
uint8 = __duplicate((uint)(k));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __duplicate(float);
float16 = __duplicate((float)(k));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
float8 = __duplicate(float);
float8 = __duplicate((float)(k));
#endif

VDUPD
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __duplicate(cint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
cint4 = __duplicate(cint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cfloat8 = __duplicate(cfloat);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
cfloat4 = __duplicate(cfloat);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __duplicate(long);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long4 = __duplicate(long);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __duplicate(ulong);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ulong4 = __duplicate(ulong);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = __duplicate(double);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
double4 = __duplicate(double);
#endif

*/

#define __duplicate(a) __overload("__duplicate",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __duplicate16                                                          */
/*----------------------------------------------------------------------------*/
/*

VDUP16B
char16 = __duplicate16(signed char);
char32 = __duplicate16(char2);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __duplicate16(char4);
#endif
uchar16 = __duplicate16(uchar);
uchar32 = __duplicate16(uchar2);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __duplicate16(uchar4);
#endif

VDUP16H
cchar16 = __duplicate16(cchar);
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = __duplicate16(cchar2);
#endif
short16 = __duplicate16(short);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __duplicate16(short2);
#endif
ushort16 = __duplicate16(ushort);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __duplicate16(ushort2);
#endif

*/

#define __duplicate16(a) __overload("__duplicate16",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __duplicate2                                                           */
/*----------------------------------------------------------------------------*/
/*

VDUP2B
char2 = __duplicate2(signed char);
char4 = __duplicate2(char2);
char8 = __duplicate2(char4);
char16 = __duplicate2(char8);
char32 = __duplicate2(char16);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __duplicate2(char32);
#endif
uchar2 = __duplicate2(uchar);
uchar4 = __duplicate2(uchar2);
uchar8 = __duplicate2(uchar4);
uchar16 = __duplicate2(uchar8);
uchar32 = __duplicate2(uchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __duplicate2(uchar32);
#endif

VDUP2H
cchar2 = __duplicate2(cchar);
cchar4 = __duplicate2(cchar2);
cchar8 = __duplicate2(cchar4);
cchar16 = __duplicate2(cchar8);
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = __duplicate2(cchar16);
#endif
short2 = __duplicate2(short);
short4 = __duplicate2(short2);
short8 = __duplicate2(short4);
short16 = __duplicate2(short8);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __duplicate2(short16);
#endif
ushort2 = __duplicate2(ushort);
ushort4 = __duplicate2(ushort2);
ushort8 = __duplicate2(ushort4);
ushort16 = __duplicate2(ushort8);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __duplicate2(ushort16);
#endif

VDUP2W
cshort2 = __duplicate2(cshort);
cshort4 = __duplicate2(cshort2);
cshort8 = __duplicate2(cshort4);
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = __duplicate2(cshort8);
#endif
int2 = __duplicate2(int);
int4 = __duplicate2(int2);
int8 = __duplicate2(int4);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __duplicate2(int8);
#endif
uint2 = __duplicate2(uint);
uint4 = __duplicate2(uint2);
uint8 = __duplicate2(uint4);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __duplicate2(uint8);
#endif
float2 = __duplicate2(float);
float4 = __duplicate2(float2);
float8 = __duplicate2(float4);
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __duplicate2(float8);
#endif

VDUP2D
cint2 = __duplicate2(cint);
cint4 = __duplicate2(cint2);
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __duplicate2(cint4);
#endif
cfloat2 = __duplicate2(cfloat);
cfloat4 = __duplicate2(cfloat2);
#if __C7X_VEC_SIZE_BITS__ == 512
cfloat8 = __duplicate2(cfloat4);
#endif
long2 = __duplicate2(long);
long4 = __duplicate2(long2);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __duplicate2(long4);
#endif
ulong2 = __duplicate2(ulong);
ulong4 = __duplicate2(ulong2);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __duplicate2(ulong4);
#endif
double2 = __duplicate2(double);
double4 = __duplicate2(double2);
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = __duplicate2(double4);
#endif

*/

#define __duplicate2(a) __overload("__duplicate2",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __duplicate32                                                          */
/*----------------------------------------------------------------------------*/
/*

VDUP32B
char32 = __duplicate32(signed char);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __duplicate32(char2);
#endif
uchar32 = __duplicate32(uchar);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __duplicate32(uchar2);
#endif

*/

#define __duplicate32(a) __overload("__duplicate32",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __duplicate4                                                           */
/*----------------------------------------------------------------------------*/
/*

VDUP4B
char4 = __duplicate4(signed char);
char8 = __duplicate4(char2);
char16 = __duplicate4(char4);
char32 = __duplicate4(char8);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __duplicate4(char16);
#endif
uchar4 = __duplicate4(uchar);
uchar8 = __duplicate4(uchar2);
uchar16 = __duplicate4(uchar4);
uchar32 = __duplicate4(uchar8);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __duplicate4(uchar16);
#endif

VDUP4H
cchar4 = __duplicate4(cchar);
cchar8 = __duplicate4(cchar2);
cchar16 = __duplicate4(cchar4);
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = __duplicate4(cchar8);
#endif
short4 = __duplicate4(short);
short8 = __duplicate4(short2);
short16 = __duplicate4(short4);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __duplicate4(short8);
#endif
ushort4 = __duplicate4(ushort);
ushort8 = __duplicate4(ushort2);
ushort16 = __duplicate4(ushort4);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __duplicate4(ushort8);
#endif

VDUP4W
cshort4 = __duplicate4(cshort);
cshort8 = __duplicate4(cshort2);
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = __duplicate4(cshort4);
#endif
int4 = __duplicate4(int);
int8 = __duplicate4(int2);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __duplicate4(int4);
#endif
uint4 = __duplicate4(uint);
uint8 = __duplicate4(uint2);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __duplicate4(uint4);
#endif
float4 = __duplicate4(float);
float8 = __duplicate4(float2);
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __duplicate4(float4);
#endif

VDUP4D
cint4 = __duplicate4(cint);
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __duplicate4(cint2);
#endif
cfloat4 = __duplicate4(cfloat);
#if __C7X_VEC_SIZE_BITS__ == 512
cfloat8 = __duplicate4(cfloat2);
#endif
long4 = __duplicate4(long);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __duplicate4(long2);
#endif
ulong4 = __duplicate4(ulong);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __duplicate4(ulong2);
#endif
double4 = __duplicate4(double);
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = __duplicate4(double2);
#endif

*/

#define __duplicate4(a) __overload("__duplicate4",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __duplicate8                                                           */
/*----------------------------------------------------------------------------*/
/*

VDUP8B
char8 = __duplicate8(signed char);
char16 = __duplicate8(char2);
char32 = __duplicate8(char4);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __duplicate8(char8);
#endif
uchar8 = __duplicate8(uchar);
uchar16 = __duplicate8(uchar2);
uchar32 = __duplicate8(uchar4);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __duplicate8(uchar8);
#endif

VDUP8H
cchar8 = __duplicate8(cchar);
cchar16 = __duplicate8(cchar2);
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = __duplicate8(cchar4);
#endif
short8 = __duplicate8(short);
short16 = __duplicate8(short2);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __duplicate8(short4);
#endif
ushort8 = __duplicate8(ushort);
ushort16 = __duplicate8(ushort2);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __duplicate8(ushort4);
#endif

VDUP8W
cshort8 = __duplicate8(cshort);
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = __duplicate8(cshort2);
#endif
int8 = __duplicate8(int);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __duplicate8(int2);
#endif
uint8 = __duplicate8(uint);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __duplicate8(uint2);
#endif
float8 = __duplicate8(float);
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __duplicate8(float2);
#endif

*/

#define __duplicate8(a) __overload("__duplicate8",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __duplicate_pred_high                                                  */
/*----------------------------------------------------------------------------*/
/*

PDUPH2B
#if __C7X_VEC_SIZE_BITS__ == 256
bool32 = __duplicate_pred_high(bool32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
bool64 = __duplicate_pred_high(bool64);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __duplicate_pred_low                                                   */
/*----------------------------------------------------------------------------*/
/*

PDUPL2B
#if __C7X_VEC_SIZE_BITS__ == 256
bool32 = __duplicate_pred_low(bool32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
bool64 = __duplicate_pred_low(bool64);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __expand                                                               */
/*----------------------------------------------------------------------------*/
/*

VPXPND
char2 = __expand(bool2);
char3 = __expand(bool3);
char4 = __expand(bool4);
char8 = __expand(bool8);
char16 = __expand(bool16);
char32 = __expand(bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __expand(bool64);
#endif

*/

#define __expand(a) __overload("__expand",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __expand_lsb_pack_char                                                 */
/*----------------------------------------------------------------------------*/
/*

XPND8B
char8 = __expand_lsb_pack_char(signed char);
uchar8 = __expand_lsb_pack_char(uchar);

*/

#define __expand_lsb_pack_char(a) __overload("__expand_lsb_pack_char",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __expand_lsb_pack_short                                                */
/*----------------------------------------------------------------------------*/
/*

XPND4H
short4 = __expand_lsb_pack_short(signed char);
ushort4 = __expand_lsb_pack_short(uchar);

*/

#define __expand_lsb_pack_short(a) __overload("__expand_lsb_pack_short",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __float_to_half_float                                                  */
/*----------------------------------------------------------------------------*/
/*

VSPHP
uint = __float_to_half_float(float);
uint2 = __float_to_half_float(float2);
uint3 = __float_to_half_float(float3);
uint4 = __float_to_half_float(float4);
uint8 = __float_to_half_float(float8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __float_to_half_float(float16);
#endif

*/

#define __float_to_half_float(a) __overload("__float_to_half_float",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __float_to_int                                                         */
/*----------------------------------------------------------------------------*/
/*

VSPINT
int = __float_to_int(float);
int2 = __float_to_int(float2);
int3 = __float_to_int(float3);
int4 = __float_to_int(float4);
int8 = __float_to_int(float8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __float_to_int(float16);
#endif

*/

#define __float_to_int(a) __overload("__float_to_int",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __float_to_int_rtz                                                     */
/*----------------------------------------------------------------------------*/
/*

VSPTRUNC
int = __float_to_int_rtz(float);
int2 = __float_to_int_rtz(float2);
int3 = __float_to_int_rtz(float3);
int4 = __float_to_int_rtz(float4);
int8 = __float_to_int_rtz(float8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __float_to_int_rtz(float16);
#endif

*/

#define __float_to_int_rtz(a) __overload("__float_to_int_rtz",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __float_to_short                                                       */
/*----------------------------------------------------------------------------*/
/*

VSPINTH
short2 = __float_to_short(float);
short4 = __float_to_short(float2);
short8 = __float_to_short(float4);
short16 = __float_to_short(float8);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __float_to_short(float16);
#endif

*/

#define __float_to_short(a) __overload("__float_to_short",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __gmpy                                                                 */
/*----------------------------------------------------------------------------*/
/*

VGMPYB
uchar = __gmpy(uchar, uchar);
uchar2 = __gmpy(uchar2, uchar2);
uchar3 = __gmpy(uchar3, uchar3);
uchar4 = __gmpy(uchar4, uchar4);
uchar8 = __gmpy(uchar8, uchar8);
uchar16 = __gmpy(uchar16, uchar16);
uchar32 = __gmpy(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __gmpy(uchar64, uchar64);
#endif

VGMPYW
uint = __gmpy(uint, uint);
uint2 = __gmpy(uint2, uint2);
uint3 = __gmpy(uint3, uint3);
uint4 = __gmpy(uint4, uint4);
uint8 = __gmpy(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __gmpy(uint16, uint16);
#endif

*/

#define __gmpy(a,b) __overload("__gmpy",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __hadd                                                                 */
/*----------------------------------------------------------------------------*/
/*

VAVGNRB
signed char = __hadd(signed char, signed char);
char2 = __hadd(char2, char2);
char3 = __hadd(char3, char3);
char4 = __hadd(char4, char4);
char8 = __hadd(char8, char8);
char16 = __hadd(char16, char16);
char32 = __hadd(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __hadd(char64, char64);
#endif

VAVGNRUB
uchar = __hadd(uchar, uchar);
uchar2 = __hadd(uchar2, uchar2);
uchar3 = __hadd(uchar3, uchar3);
uchar4 = __hadd(uchar4, uchar4);
uchar8 = __hadd(uchar8, uchar8);
uchar16 = __hadd(uchar16, uchar16);
uchar32 = __hadd(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __hadd(uchar64, uchar64);
#endif

VAVGNRH
short = __hadd(short, short);
short2 = __hadd(short2, short2);
short3 = __hadd(short3, short3);
short4 = __hadd(short4, short4);
short8 = __hadd(short8, short8);
short16 = __hadd(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __hadd(short32, short32);
#endif

VAVGNRUH
ushort = __hadd(ushort, ushort);
ushort2 = __hadd(ushort2, ushort2);
ushort3 = __hadd(ushort3, ushort3);
ushort4 = __hadd(ushort4, ushort4);
ushort8 = __hadd(ushort8, ushort8);
ushort16 = __hadd(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __hadd(ushort32, ushort32);
#endif

VAVGNRW
int = __hadd(int, int);
int2 = __hadd(int2, int2);
int3 = __hadd(int3, int3);
int4 = __hadd(int4, int4);
int8 = __hadd(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __hadd(int16, int16);
#endif

VAVGNRUW
uint = __hadd(uint, uint);
uint2 = __hadd(uint2, uint2);
uint3 = __hadd(uint3, uint3);
uint4 = __hadd(uint4, uint4);
uint8 = __hadd(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __hadd(uint16, uint16);
#endif

VAVGNRD
long = __hadd(long, long);
long2 = __hadd(long2, long2);
long3 = __hadd(long3, long3);
long4 = __hadd(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __hadd(long8, long8);
#endif

VAVGNRUD
ulong = __hadd(ulong, ulong);
ulong2 = __hadd(ulong2, ulong2);
ulong3 = __hadd(ulong3, ulong3);
ulong4 = __hadd(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __hadd(ulong8, ulong8);
#endif

*/

#define __hadd(a,b) __overload("__hadd",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __half_float_to_float                                                  */
/*----------------------------------------------------------------------------*/
/*

VHPSP
float = __half_float_to_float(uint);
float2 = __half_float_to_float(uint2);
float3 = __half_float_to_float(uint3);
float4 = __half_float_to_float(uint4);
float8 = __half_float_to_float(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __half_float_to_float(uint16);
#endif

*/

#define __half_float_to_float(a) __overload("__half_float_to_float",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __half_float_to_int                                                    */
/*----------------------------------------------------------------------------*/
/*

VHPINT
int = __half_float_to_int(uint);
int2 = __half_float_to_int(uint2);
int3 = __half_float_to_int(uint3);
int4 = __half_float_to_int(uint4);
int8 = __half_float_to_int(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __half_float_to_int(uint16);
#endif

*/

#define __half_float_to_int(a) __overload("__half_float_to_int",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __high_char_to_short                                                   */
/*----------------------------------------------------------------------------*/
/*

VBUNPKHH
short = __high_char_to_short(char2);
short2 = __high_char_to_short(char4);
short4 = __high_char_to_short(char8);
short8 = __high_char_to_short(char16);
short16 = __high_char_to_short(char32);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __high_char_to_short(char64);
#endif

*/

#define __high_char_to_short(a) __overload("__high_char_to_short",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __high_float_to_double                                                 */
/*----------------------------------------------------------------------------*/
/*

VSPDPH
double = __high_float_to_double(float2);
double2 = __high_float_to_double(float4);
double4 = __high_float_to_double(float8);
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = __high_float_to_double(float16);
#endif

*/

#define __high_float_to_double(a) __overload("__high_float_to_double",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __high_half_int_to_float                                               */
/*----------------------------------------------------------------------------*/
/*

VINTHSPH
float2 = __high_half_int_to_float(short4);
float4 = __high_half_int_to_float(short8);
float8 = __high_half_int_to_float(short16);
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __high_half_int_to_float(short32);
#endif

VINTHSPUH
float2 = __high_half_int_to_float(ushort4);
float4 = __high_half_int_to_float(ushort8);
float8 = __high_half_int_to_float(ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __high_half_int_to_float(ushort32);
#endif

*/

#define __high_half_int_to_float(a) __overload("__high_half_int_to_float",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __high_int_to_double                                                   */
/*----------------------------------------------------------------------------*/
/*

VINTDPH
double = __high_int_to_double(int2);
double2 = __high_int_to_double(int4);
double4 = __high_int_to_double(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = __high_int_to_double(int16);
#endif

VINTDPUH
double = __high_int_to_double(uint2);
double2 = __high_int_to_double(uint4);
double4 = __high_int_to_double(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = __high_int_to_double(uint16);
#endif

*/

#define __high_int_to_double(a) __overload("__high_int_to_double",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __high_int_to_long                                                     */
/*----------------------------------------------------------------------------*/
/*

VWUNPKDH
long = __high_int_to_long(int2);
long2 = __high_int_to_long(int4);
long4 = __high_int_to_long(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __high_int_to_long(int16);
#endif

*/

#define __high_int_to_long(a) __overload("__high_int_to_long",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __high_short_to_int                                                    */
/*----------------------------------------------------------------------------*/
/*

VHUNPKWH
int = __high_short_to_int(short2);
int2 = __high_short_to_int(short4);
int4 = __high_short_to_int(short8);
int8 = __high_short_to_int(short16);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __high_short_to_int(short32);
#endif

*/

#define __high_short_to_int(a) __overload("__high_short_to_int",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __high_uchar_to_ushort                                                 */
/*----------------------------------------------------------------------------*/
/*

VBUNPKUHH
ushort = __high_uchar_to_ushort(uchar2);
ushort2 = __high_uchar_to_ushort(uchar4);
ushort4 = __high_uchar_to_ushort(uchar8);
ushort8 = __high_uchar_to_ushort(uchar16);
ushort16 = __high_uchar_to_ushort(uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __high_uchar_to_ushort(uchar64);
#endif

*/

#define __high_uchar_to_ushort(a) __overload("__high_uchar_to_ushort",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __high_uint_to_ulong                                                   */
/*----------------------------------------------------------------------------*/
/*

VWUNPKUDH
ulong = __high_uint_to_ulong(uint2);
ulong2 = __high_uint_to_ulong(uint4);
ulong4 = __high_uint_to_ulong(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __high_uint_to_ulong(uint16);
#endif

*/

#define __high_uint_to_ulong(a) __overload("__high_uint_to_ulong",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __high_ushort_to_uint                                                  */
/*----------------------------------------------------------------------------*/
/*

VHUNPKUWH
uint = __high_ushort_to_uint(ushort2);
uint2 = __high_ushort_to_uint(ushort4);
uint4 = __high_ushort_to_uint(ushort8);
uint8 = __high_ushort_to_uint(ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __high_ushort_to_uint(ushort32);
#endif

*/

#define __high_ushort_to_uint(a) __overload("__high_ushort_to_uint",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __horizontal_add                                                       */
/*----------------------------------------------------------------------------*/
/*

VHADDB1D
#if __C7X_VEC_SIZE_BITS__ == 512
long = __horizontal_add(char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long = __horizontal_add(char32);
#endif

VHADDUB1D
#if __C7X_VEC_SIZE_BITS__ == 512
ulong = __horizontal_add(uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ulong = __horizontal_add(uchar32);
#endif

VHADDH1D
#if __C7X_VEC_SIZE_BITS__ == 512
long = __horizontal_add(short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long = __horizontal_add(short16);
#endif

VHADDUH1D
#if __C7X_VEC_SIZE_BITS__ == 512
ulong = __horizontal_add(ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ulong = __horizontal_add(ushort16);
#endif

VHADDW1D
#if __C7X_VEC_SIZE_BITS__ == 512
long = __horizontal_add(int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long = __horizontal_add(int8);
#endif

VHADDUW1D
#if __C7X_VEC_SIZE_BITS__ == 512
ulong = __horizontal_add(uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ulong = __horizontal_add(uint8);
#endif

VHADDD1D
#if __C7X_VEC_SIZE_BITS__ == 512
long = __horizontal_add(long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long = __horizontal_add(long4);
#endif

VHADDUD1D
#if __C7X_VEC_SIZE_BITS__ == 512
ulong = __horizontal_add(ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ulong = __horizontal_add(ulong4);
#endif

*/

#define __horizontal_add(a) __overload("__horizontal_add",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __horizontal_add_skip1                                                 */
/*----------------------------------------------------------------------------*/
/*

VHADDEOH2W
#if __C7X_VEC_SIZE_BITS__ == 512
int2 = __horizontal_add_skip1(short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
int2 = __horizontal_add_skip1(short16);
#endif

VHADDUEOH2W
#if __C7X_VEC_SIZE_BITS__ == 512
uint2 = __horizontal_add_skip1(ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
uint2 = __horizontal_add_skip1(ushort16);
#endif

VHADDEOH2W
#if __C7X_VEC_SIZE_BITS__ == 512
cint = __horizontal_add_skip1(cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
cint = __horizontal_add_skip1(cshort8);
#endif

VHADDEOW2D
#if __C7X_VEC_SIZE_BITS__ == 512
long2 = __horizontal_add_skip1(int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long2 = __horizontal_add_skip1(int8);
#endif

VHADDUEOW2D
#if __C7X_VEC_SIZE_BITS__ == 512
ulong2 = __horizontal_add_skip1(uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ulong2 = __horizontal_add_skip1(uint8);
#endif

VHADDEOW2D
#if __C7X_VEC_SIZE_BITS__ == 512
clong = __horizontal_add_skip1(cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
clong = __horizontal_add_skip1(cint4);
#endif

*/

#define __horizontal_add_skip1(a) __overload("__horizontal_add_skip1",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __horizontal_xor                                                       */
/*----------------------------------------------------------------------------*/
/*

VHXORB1B
#if __C7X_VEC_SIZE_BITS__ == 512
short = __horizontal_xor(char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
short = __horizontal_xor(char32);
#endif

VHXORH1H
#if __C7X_VEC_SIZE_BITS__ == 512
short = __horizontal_xor(short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
short = __horizontal_xor(short16);
#endif

VHXORW1W
#if __C7X_VEC_SIZE_BITS__ == 512
int = __horizontal_xor(int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
int = __horizontal_xor(int8);
#endif

VHXORD1D
#if __C7X_VEC_SIZE_BITS__ == 512
long = __horizontal_xor(long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long = __horizontal_xor(long4);
#endif

*/

#define __horizontal_xor(a) __overload("__horizontal_xor",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __int40_to_int_sat                                                     */
/*----------------------------------------------------------------------------*/
/*

VSATLW
long = __int40_to_int_sat(long);
long2 = __int40_to_int_sat(long2);
long3 = __int40_to_int_sat(long3);
long4 = __int40_to_int_sat(long4);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __int40_to_int_sat(long8);
#endif

*/

#define __int40_to_int_sat(a) __overload("__int40_to_int_sat",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __int_to_float                                                         */
/*----------------------------------------------------------------------------*/
/*

VINTSP
float = __int_to_float(int);
float2 = __int_to_float(int2);
float3 = __int_to_float(int3);
float4 = __int_to_float(int4);
float8 = __int_to_float(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __int_to_float(int16);
#endif

VINTSPU
float = __int_to_float(uint);
float2 = __int_to_float(uint2);
float3 = __int_to_float(uint3);
float4 = __int_to_float(uint4);
float8 = __int_to_float(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __int_to_float(uint16);
#endif

*/

#define __int_to_float(a) __overload("__int_to_float",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __int_to_half_float                                                    */
/*----------------------------------------------------------------------------*/
/*

VINTHP
uint = __int_to_half_float(int);
uint2 = __int_to_half_float(int2);
uint3 = __int_to_half_float(int3);
uint4 = __int_to_half_float(int4);
uint8 = __int_to_half_float(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __int_to_half_float(int16);
#endif

*/

#define __int_to_half_float(a) __overload("__int_to_half_float",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __int_to_short_sat                                                     */
/*----------------------------------------------------------------------------*/
/*

VSATWH
int = __int_to_short_sat(int);
int2 = __int_to_short_sat(int2);
int3 = __int_to_short_sat(int3);
int4 = __int_to_short_sat(int4);
int8 = __int_to_short_sat(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __int_to_short_sat(int16);
#endif

*/

#define __int_to_short_sat(a) __overload("__int_to_short_sat",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __leftmost_bit_detect                                                  */
/*----------------------------------------------------------------------------*/
/*

VLMBDB
uchar = __leftmost_bit_detect(uchar, uchar);
uchar2 = __leftmost_bit_detect(uchar2, uchar2);
uchar3 = __leftmost_bit_detect(uchar3, uchar3);
uchar4 = __leftmost_bit_detect(uchar4, uchar4);
uchar8 = __leftmost_bit_detect(uchar8, uchar8);
uchar16 = __leftmost_bit_detect(uchar16, uchar16);
uchar32 = __leftmost_bit_detect(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __leftmost_bit_detect(uchar64, uchar64);
#endif

VLMBDH
ushort = __leftmost_bit_detect(ushort, ushort);
ushort2 = __leftmost_bit_detect(ushort2, ushort2);
ushort3 = __leftmost_bit_detect(ushort3, ushort3);
ushort4 = __leftmost_bit_detect(ushort4, ushort4);
ushort8 = __leftmost_bit_detect(ushort8, ushort8);
ushort16 = __leftmost_bit_detect(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __leftmost_bit_detect(ushort32, ushort32);
#endif

VLMBDW
uint = __leftmost_bit_detect(uint, uint);
uint2 = __leftmost_bit_detect(uint2, uint2);
uint3 = __leftmost_bit_detect(uint3, uint3);
uint4 = __leftmost_bit_detect(uint4, uint4);
uint8 = __leftmost_bit_detect(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __leftmost_bit_detect(uint16, uint16);
#endif

VLMBDD
ulong = __leftmost_bit_detect(ulong, ulong);
ulong2 = __leftmost_bit_detect(ulong2, ulong2);
ulong3 = __leftmost_bit_detect(ulong3, ulong3);
ulong4 = __leftmost_bit_detect(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __leftmost_bit_detect(ulong8, ulong8);
#endif

*/

#define __leftmost_bit_detect(a,b) __overload("__leftmost_bit_detect",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __leftmost_bit_detect_one                                              */
/*----------------------------------------------------------------------------*/
/*

VLMBD1B
uchar = __leftmost_bit_detect_one(uchar);
uchar2 = __leftmost_bit_detect_one(uchar2);
uchar3 = __leftmost_bit_detect_one(uchar3);
uchar4 = __leftmost_bit_detect_one(uchar4);
uchar8 = __leftmost_bit_detect_one(uchar8);
uchar16 = __leftmost_bit_detect_one(uchar16);
uchar32 = __leftmost_bit_detect_one(uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __leftmost_bit_detect_one(uchar64);
#endif

VLMBD1H
ushort = __leftmost_bit_detect_one(ushort);
ushort2 = __leftmost_bit_detect_one(ushort2);
ushort3 = __leftmost_bit_detect_one(ushort3);
ushort4 = __leftmost_bit_detect_one(ushort4);
ushort8 = __leftmost_bit_detect_one(ushort8);
ushort16 = __leftmost_bit_detect_one(ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __leftmost_bit_detect_one(ushort32);
#endif

VLMBD1W
uint = __leftmost_bit_detect_one(uint);
uint2 = __leftmost_bit_detect_one(uint2);
uint3 = __leftmost_bit_detect_one(uint3);
uint4 = __leftmost_bit_detect_one(uint4);
uint8 = __leftmost_bit_detect_one(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __leftmost_bit_detect_one(uint16);
#endif

VLMBD1D
ulong = __leftmost_bit_detect_one(ulong);
ulong2 = __leftmost_bit_detect_one(ulong2);
ulong3 = __leftmost_bit_detect_one(ulong3);
ulong4 = __leftmost_bit_detect_one(ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __leftmost_bit_detect_one(ulong8);
#endif

*/

#define __leftmost_bit_detect_one(a) __overload("__leftmost_bit_detect_one",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __leftmost_bit_detect_zero                                             */
/*----------------------------------------------------------------------------*/
/*

VLMBD0B
uchar = __leftmost_bit_detect_zero(uchar);
uchar2 = __leftmost_bit_detect_zero(uchar2);
uchar3 = __leftmost_bit_detect_zero(uchar3);
uchar4 = __leftmost_bit_detect_zero(uchar4);
uchar8 = __leftmost_bit_detect_zero(uchar8);
uchar16 = __leftmost_bit_detect_zero(uchar16);
uchar32 = __leftmost_bit_detect_zero(uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __leftmost_bit_detect_zero(uchar64);
#endif

VLMBD0H
ushort = __leftmost_bit_detect_zero(ushort);
ushort2 = __leftmost_bit_detect_zero(ushort2);
ushort3 = __leftmost_bit_detect_zero(ushort3);
ushort4 = __leftmost_bit_detect_zero(ushort4);
ushort8 = __leftmost_bit_detect_zero(ushort8);
ushort16 = __leftmost_bit_detect_zero(ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __leftmost_bit_detect_zero(ushort32);
#endif

VLMBD0W
uint = __leftmost_bit_detect_zero(uint);
uint2 = __leftmost_bit_detect_zero(uint2);
uint3 = __leftmost_bit_detect_zero(uint3);
uint4 = __leftmost_bit_detect_zero(uint4);
uint8 = __leftmost_bit_detect_zero(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __leftmost_bit_detect_zero(uint16);
#endif

VLMBD0D
ulong = __leftmost_bit_detect_zero(ulong);
ulong2 = __leftmost_bit_detect_zero(ulong2);
ulong3 = __leftmost_bit_detect_zero(ulong3);
ulong4 = __leftmost_bit_detect_zero(ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __leftmost_bit_detect_zero(ulong8);
#endif

*/

#define __leftmost_bit_detect_zero(a) __overload("__leftmost_bit_detect_zero",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __logical_and                                                          */
/*----------------------------------------------------------------------------*/
/*

LANDD
int = __logical_and(long, long);

*/

/*----------------------------------------------------------------------------*/
/* ID: __logical_andn                                                         */
/*----------------------------------------------------------------------------*/
/*

LANDND
int = __logical_andn(long, long);

*/

/*----------------------------------------------------------------------------*/
/* ID: __logical_or                                                           */
/*----------------------------------------------------------------------------*/
/*

LORD
int = __logical_or(long, long);

*/

/*----------------------------------------------------------------------------*/
/* ID: __long_to_int40_sat                                                    */
/*----------------------------------------------------------------------------*/
/*

VSATDL
long = __long_to_int40_sat(long);
long2 = __long_to_int40_sat(long2);
long3 = __long_to_int40_sat(long3);
long4 = __long_to_int40_sat(long4);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __long_to_int40_sat(long8);
#endif

*/

#define __long_to_int40_sat(a) __overload("__long_to_int40_sat",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __long_to_int_sat                                                      */
/*----------------------------------------------------------------------------*/
/*

VSATDW
long = __long_to_int_sat(long);
long2 = __long_to_int_sat(long2);
long3 = __long_to_int_sat(long3);
long4 = __long_to_int_sat(long4);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __long_to_int_sat(long8);
#endif

*/

#define __long_to_int_sat(a) __overload("__long_to_int_sat",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __low_char_to_short                                                    */
/*----------------------------------------------------------------------------*/
/*

VBUNPKHL
short = __low_char_to_short(char2);
short2 = __low_char_to_short(char4);
short4 = __low_char_to_short(char8);
short8 = __low_char_to_short(char16);
short16 = __low_char_to_short(char32);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __low_char_to_short(char64);
#endif

*/

#define __low_char_to_short(a) __overload("__low_char_to_short",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __low_float_to_double                                                  */
/*----------------------------------------------------------------------------*/
/*

VSPDPL
double = __low_float_to_double(float2);
double2 = __low_float_to_double(float4);
double4 = __low_float_to_double(float8);
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = __low_float_to_double(float16);
#endif

*/

#define __low_float_to_double(a) __overload("__low_float_to_double",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __low_half_int_to_float                                                */
/*----------------------------------------------------------------------------*/
/*

VINTHSPL
float2 = __low_half_int_to_float(short4);
float4 = __low_half_int_to_float(short8);
float8 = __low_half_int_to_float(short16);
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __low_half_int_to_float(short32);
#endif

VINTHSPUL
float2 = __low_half_int_to_float(ushort4);
float4 = __low_half_int_to_float(ushort8);
float8 = __low_half_int_to_float(ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __low_half_int_to_float(ushort32);
#endif

*/

#define __low_half_int_to_float(a) __overload("__low_half_int_to_float",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __low_int_to_double                                                    */
/*----------------------------------------------------------------------------*/
/*

VINTDPL
double = __low_int_to_double(int2);
double2 = __low_int_to_double(int4);
double4 = __low_int_to_double(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = __low_int_to_double(int16);
#endif

VINTDPUL
double = __low_int_to_double(uint2);
double2 = __low_int_to_double(uint4);
double4 = __low_int_to_double(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = __low_int_to_double(uint16);
#endif

*/

#define __low_int_to_double(a) __overload("__low_int_to_double",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __low_int_to_long                                                      */
/*----------------------------------------------------------------------------*/
/*

VWUNPKDL
long = __low_int_to_long(int2);
long2 = __low_int_to_long(int4);
long4 = __low_int_to_long(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __low_int_to_long(int16);
#endif

*/

#define __low_int_to_long(a) __overload("__low_int_to_long",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __low_short_to_int                                                     */
/*----------------------------------------------------------------------------*/
/*

VHUNPKWL
int = __low_short_to_int(short2);
int2 = __low_short_to_int(short4);
int4 = __low_short_to_int(short8);
int8 = __low_short_to_int(short16);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __low_short_to_int(short32);
#endif

*/

#define __low_short_to_int(a) __overload("__low_short_to_int",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __low_uchar_to_ushort                                                  */
/*----------------------------------------------------------------------------*/
/*

VBUNPKUHL
ushort = __low_uchar_to_ushort(uchar2);
ushort2 = __low_uchar_to_ushort(uchar4);
ushort4 = __low_uchar_to_ushort(uchar8);
ushort8 = __low_uchar_to_ushort(uchar16);
ushort16 = __low_uchar_to_ushort(uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __low_uchar_to_ushort(uchar64);
#endif

*/

#define __low_uchar_to_ushort(a) __overload("__low_uchar_to_ushort",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __low_uint_to_ulong                                                    */
/*----------------------------------------------------------------------------*/
/*

VWUNPKUDL
ulong = __low_uint_to_ulong(uint2);
ulong2 = __low_uint_to_ulong(uint4);
ulong4 = __low_uint_to_ulong(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __low_uint_to_ulong(uint16);
#endif

*/

#define __low_uint_to_ulong(a) __overload("__low_uint_to_ulong",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __low_ushort_to_uint                                                   */
/*----------------------------------------------------------------------------*/
/*

VHUNPKUWL
uint = __low_ushort_to_uint(ushort2);
uint2 = __low_ushort_to_uint(ushort4);
uint4 = __low_ushort_to_uint(ushort8);
uint8 = __low_ushort_to_uint(ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __low_ushort_to_uint(ushort32);
#endif

*/

#define __low_ushort_to_uint(a) __overload("__low_ushort_to_uint",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __max                                                                  */
/*----------------------------------------------------------------------------*/
/*

VMAXB
signed char = __max(signed char, signed char);
char2 = __max(char2, char2);
char3 = __max(char3, char3);
char4 = __max(char4, char4);
char8 = __max(char8, char8);
char16 = __max(char16, char16);
char32 = __max(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __max(char64, char64);
#endif

VMAXUB
uchar = __max(uchar, uchar);
uchar2 = __max(uchar2, uchar2);
uchar3 = __max(uchar3, uchar3);
uchar4 = __max(uchar4, uchar4);
uchar8 = __max(uchar8, uchar8);
uchar16 = __max(uchar16, uchar16);
uchar32 = __max(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __max(uchar64, uchar64);
#endif

VMAXH
short = __max(short, short);
short2 = __max(short2, short2);
short3 = __max(short3, short3);
short4 = __max(short4, short4);
short8 = __max(short8, short8);
short16 = __max(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __max(short32, short32);
#endif

VMAXUH
ushort = __max(ushort, ushort);
ushort2 = __max(ushort2, ushort2);
ushort3 = __max(ushort3, ushort3);
ushort4 = __max(ushort4, ushort4);
ushort8 = __max(ushort8, ushort8);
ushort16 = __max(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __max(ushort32, ushort32);
#endif

VMAXW
int = __max(int, int);
int2 = __max(int2, int2);
int3 = __max(int3, int3);
int4 = __max(int4, int4);
int8 = __max(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __max(int16, int16);
#endif

VMAXUW
uint = __max(uint, uint);
uint2 = __max(uint2, uint2);
uint3 = __max(uint3, uint3);
uint4 = __max(uint4, uint4);
uint8 = __max(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __max(uint16, uint16);
#endif

VMAXSP
float = __max(float, float);
float2 = __max(float2, float2);
float3 = __max(float3, float3);
float4 = __max(float4, float4);
float8 = __max(float8, float8);
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __max(float16, float16);
#endif

VMAXD
long = __max(long, long);
long2 = __max(long2, long2);
long3 = __max(long3, long3);
long4 = __max(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __max(long8, long8);
#endif

VMAXUD
ulong = __max(ulong, ulong);
ulong2 = __max(ulong2, ulong2);
ulong3 = __max(ulong3, ulong3);
ulong4 = __max(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __max(ulong8, ulong8);
#endif

VMAXDP
double = __max(double, double);
double2 = __max(double2, double2);
double3 = __max(double3, double3);
double4 = __max(double4, double4);
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = __max(double8, double8);
#endif

*/

#define __max(a,b) __overload("__max",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __max_circ                                                             */
/*----------------------------------------------------------------------------*/
/*

VCMAXB
signed char = __max_circ(signed char, signed char);
char2 = __max_circ(char2, char2);
char3 = __max_circ(char3, char3);
char4 = __max_circ(char4, char4);
char8 = __max_circ(char8, char8);
char16 = __max_circ(char16, char16);
char32 = __max_circ(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __max_circ(char64, char64);
#endif

VCMAXH
short = __max_circ(short, short);
short2 = __max_circ(short2, short2);
short3 = __max_circ(short3, short3);
short4 = __max_circ(short4, short4);
short8 = __max_circ(short8, short8);
short16 = __max_circ(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __max_circ(short32, short32);
#endif

*/

#define __max_circ(a,b) __overload("__max_circ",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __max_circ_bool                                                        */
/*----------------------------------------------------------------------------*/
/*

VCMAXPB
__max_circ_bool(char2, char2&, bool2&);
__max_circ_bool(char3, char3&, bool3&);
__max_circ_bool(char4, char4&, bool4&);
__max_circ_bool(char8, char8&, bool8&);
__max_circ_bool(char16, char16&, bool16&);
__max_circ_bool(char32, char32&, bool32&);
#if __C7X_VEC_SIZE_BITS__ == 512
__max_circ_bool(char64, char64&, bool64&);
#endif

VCMAXPH
__max_circ_bool(short2, short2&, bool2&);
__max_circ_bool(short3, short3&, bool3&);
__max_circ_bool(short4, short4&, bool4&);
__max_circ_bool(short8, short8&, bool8&);
__max_circ_bool(short16, short16&, bool16&);
#if __C7X_VEC_SIZE_BITS__ == 512
__max_circ_bool(short32, short32&, bool32&);
#endif

*/

#define __max_circ_bool(a,b,c) __overload("__max_circ_bool",(a),(b),(c))((a),(b),(c))

/*----------------------------------------------------------------------------*/
/* ID: __max_index_bool                                                       */
/*----------------------------------------------------------------------------*/
/*

VMAXPB
__max_index_bool(char2, char2&, bool2&);
__max_index_bool(char3, char3&, bool3&);
__max_index_bool(char4, char4&, bool4&);
__max_index_bool(char8, char8&, bool8&);
__max_index_bool(char16, char16&, bool16&);
__max_index_bool(char32, char32&, bool32&);
#if __C7X_VEC_SIZE_BITS__ == 512
__max_index_bool(char64, char64&, bool64&);
#endif

VMAXUPB
__max_index_bool(uchar2, uchar2&, bool2&);
__max_index_bool(uchar3, uchar3&, bool3&);
__max_index_bool(uchar4, uchar4&, bool4&);
__max_index_bool(uchar8, uchar8&, bool8&);
__max_index_bool(uchar16, uchar16&, bool16&);
__max_index_bool(uchar32, uchar32&, bool32&);
#if __C7X_VEC_SIZE_BITS__ == 512
__max_index_bool(uchar64, uchar64&, bool64&);
#endif

VMAXPH
__max_index_bool(short2, short2&, bool2&);
__max_index_bool(short3, short3&, bool3&);
__max_index_bool(short4, short4&, bool4&);
__max_index_bool(short8, short8&, bool8&);
__max_index_bool(short16, short16&, bool16&);
#if __C7X_VEC_SIZE_BITS__ == 512
__max_index_bool(short32, short32&, bool32&);
#endif

VMAXUPH
__max_index_bool(ushort2, ushort2&, bool2&);
__max_index_bool(ushort3, ushort3&, bool3&);
__max_index_bool(ushort4, ushort4&, bool4&);
__max_index_bool(ushort8, ushort8&, bool8&);
__max_index_bool(ushort16, ushort16&, bool16&);
#if __C7X_VEC_SIZE_BITS__ == 512
__max_index_bool(ushort32, ushort32&, bool32&);
#endif

VMAXPW
__max_index_bool(int2, int2&, bool2&);
__max_index_bool(int3, int3&, bool3&);
__max_index_bool(int4, int4&, bool4&);
__max_index_bool(int8, int8&, bool8&);
#if __C7X_VEC_SIZE_BITS__ == 512
__max_index_bool(int16, int16&, bool16&);
#endif

VMAXUPW
__max_index_bool(uint2, uint2&, bool2&);
__max_index_bool(uint3, uint3&, bool3&);
__max_index_bool(uint4, uint4&, bool4&);
__max_index_bool(uint8, uint8&, bool8&);
#if __C7X_VEC_SIZE_BITS__ == 512
__max_index_bool(uint16, uint16&, bool16&);
#endif

VMAXPD
__max_index_bool(long2, long2&, bool2&);
__max_index_bool(long3, long3&, bool3&);
__max_index_bool(long4, long4&, bool4&);
#if __C7X_VEC_SIZE_BITS__ == 512
__max_index_bool(long8, long8&, bool8&);
#endif

VMAXUPD
__max_index_bool(ulong2, ulong2&, bool2&);
__max_index_bool(ulong3, ulong3&, bool3&);
__max_index_bool(ulong4, ulong4&, bool4&);
#if __C7X_VEC_SIZE_BITS__ == 512
__max_index_bool(ulong8, ulong8&, bool8&);
#endif

*/

#define __max_index_bool(a,b,c) __overload("__max_index_bool",(a),(b),(c))((a),(b),(c))

/*----------------------------------------------------------------------------*/
/* ID: __min                                                                  */
/*----------------------------------------------------------------------------*/
/*

VMINB
signed char = __min(signed char, signed char);
char2 = __min(char2, char2);
char3 = __min(char3, char3);
char4 = __min(char4, char4);
char8 = __min(char8, char8);
char16 = __min(char16, char16);
char32 = __min(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __min(char64, char64);
#endif

VMINUB
uchar = __min(uchar, uchar);
uchar2 = __min(uchar2, uchar2);
uchar3 = __min(uchar3, uchar3);
uchar4 = __min(uchar4, uchar4);
uchar8 = __min(uchar8, uchar8);
uchar16 = __min(uchar16, uchar16);
uchar32 = __min(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __min(uchar64, uchar64);
#endif

VMINH
short = __min(short, short);
short2 = __min(short2, short2);
short3 = __min(short3, short3);
short4 = __min(short4, short4);
short8 = __min(short8, short8);
short16 = __min(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __min(short32, short32);
#endif

VMINUH
ushort = __min(ushort, ushort);
ushort2 = __min(ushort2, ushort2);
ushort3 = __min(ushort3, ushort3);
ushort4 = __min(ushort4, ushort4);
ushort8 = __min(ushort8, ushort8);
ushort16 = __min(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __min(ushort32, ushort32);
#endif

VMINW
int = __min(int, int);
int2 = __min(int2, int2);
int3 = __min(int3, int3);
int4 = __min(int4, int4);
int8 = __min(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __min(int16, int16);
#endif

VMINUW
uint = __min(uint, uint);
uint2 = __min(uint2, uint2);
uint3 = __min(uint3, uint3);
uint4 = __min(uint4, uint4);
uint8 = __min(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __min(uint16, uint16);
#endif

VMINSP
float = __min(float, float);
float2 = __min(float2, float2);
float3 = __min(float3, float3);
float4 = __min(float4, float4);
float8 = __min(float8, float8);
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __min(float16, float16);
#endif

VMIND
long = __min(long, long);
long2 = __min(long2, long2);
long3 = __min(long3, long3);
long4 = __min(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __min(long8, long8);
#endif

VMINUD
ulong = __min(ulong, ulong);
ulong2 = __min(ulong2, ulong2);
ulong3 = __min(ulong3, ulong3);
ulong4 = __min(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __min(ulong8, ulong8);
#endif

VMINDP
double = __min(double, double);
double2 = __min(double2, double2);
double3 = __min(double3, double3);
double4 = __min(double4, double4);
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = __min(double8, double8);
#endif

*/

#define __min(a,b) __overload("__min",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __min_index_bool                                                       */
/*----------------------------------------------------------------------------*/
/*

VMINPB
__min_index_bool(char2, char2&, bool2&);
__min_index_bool(char3, char3&, bool3&);
__min_index_bool(char4, char4&, bool4&);
__min_index_bool(char8, char8&, bool8&);
__min_index_bool(char16, char16&, bool16&);
__min_index_bool(char32, char32&, bool32&);
#if __C7X_VEC_SIZE_BITS__ == 512
__min_index_bool(char64, char64&, bool64&);
#endif

VMINUPB
__min_index_bool(uchar2, uchar2&, bool2&);
__min_index_bool(uchar3, uchar3&, bool3&);
__min_index_bool(uchar4, uchar4&, bool4&);
__min_index_bool(uchar8, uchar8&, bool8&);
__min_index_bool(uchar16, uchar16&, bool16&);
__min_index_bool(uchar32, uchar32&, bool32&);
#if __C7X_VEC_SIZE_BITS__ == 512
__min_index_bool(uchar64, uchar64&, bool64&);
#endif

VMINPH
__min_index_bool(short2, short2&, bool2&);
__min_index_bool(short3, short3&, bool3&);
__min_index_bool(short4, short4&, bool4&);
__min_index_bool(short8, short8&, bool8&);
__min_index_bool(short16, short16&, bool16&);
#if __C7X_VEC_SIZE_BITS__ == 512
__min_index_bool(short32, short32&, bool32&);
#endif

VMINUPH
__min_index_bool(ushort2, ushort2&, bool2&);
__min_index_bool(ushort3, ushort3&, bool3&);
__min_index_bool(ushort4, ushort4&, bool4&);
__min_index_bool(ushort8, ushort8&, bool8&);
__min_index_bool(ushort16, ushort16&, bool16&);
#if __C7X_VEC_SIZE_BITS__ == 512
__min_index_bool(ushort32, ushort32&, bool32&);
#endif

VMINPW
__min_index_bool(int2, int2&, bool2&);
__min_index_bool(int3, int3&, bool3&);
__min_index_bool(int4, int4&, bool4&);
__min_index_bool(int8, int8&, bool8&);
#if __C7X_VEC_SIZE_BITS__ == 512
__min_index_bool(int16, int16&, bool16&);
#endif

VMINUPW
__min_index_bool(uint2, uint2&, bool2&);
__min_index_bool(uint3, uint3&, bool3&);
__min_index_bool(uint4, uint4&, bool4&);
__min_index_bool(uint8, uint8&, bool8&);
#if __C7X_VEC_SIZE_BITS__ == 512
__min_index_bool(uint16, uint16&, bool16&);
#endif

VMINPD
__min_index_bool(long2, long2&, bool2&);
__min_index_bool(long3, long3&, bool3&);
__min_index_bool(long4, long4&, bool4&);
#if __C7X_VEC_SIZE_BITS__ == 512
__min_index_bool(long8, long8&, bool8&);
#endif

VMINUPD
__min_index_bool(ulong2, ulong2&, bool2&);
__min_index_bool(ulong3, ulong3&, bool3&);
__min_index_bool(ulong4, ulong4&, bool4&);
#if __C7X_VEC_SIZE_BITS__ == 512
__min_index_bool(ulong8, ulong8&, bool8&);
#endif

*/

#define __min_index_bool(a,b,c) __overload("__min_index_bool",(a),(b),(c))((a),(b),(c))

/*----------------------------------------------------------------------------*/
/* ID: __mpy_ext                                                              */
/*----------------------------------------------------------------------------*/
/*

VMPYSUBH
short = __mpy_ext(signed char, uchar);
short2 = __mpy_ext(char2, uchar2);
short3 = __mpy_ext(char3, uchar3);
short4 = __mpy_ext(char4, uchar4);
short8 = __mpy_ext(char8, uchar8);
short16 = __mpy_ext(char16, uchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __mpy_ext(char32, uchar32);
#endif

VMPYUBH
ushort = __mpy_ext(uchar, uchar);
ushort2 = __mpy_ext(uchar2, uchar2);
ushort3 = __mpy_ext(uchar3, uchar3);
ushort4 = __mpy_ext(uchar4, uchar4);
ushort8 = __mpy_ext(uchar8, uchar8);
ushort16 = __mpy_ext(uchar16, uchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __mpy_ext(uchar32, uchar32);
#endif

MPYHW, VMPYHW
int = __mpy_ext(short, short);
int2 = __mpy_ext(short2, short2);
int3 = __mpy_ext(short3, short3);
int4 = __mpy_ext(short4, short4);
int8 = __mpy_ext(short8, short8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __mpy_ext(short16, short16);
#endif

MPYSUHW, VMPYSUHW
int = __mpy_ext(short, ushort);
int2 = __mpy_ext(short2, ushort2);
int3 = __mpy_ext(short3, ushort3);
int4 = __mpy_ext(short4, ushort4);
int8 = __mpy_ext(short8, ushort8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __mpy_ext(short16, ushort16);
#endif

MPYUHW, VMPYUHW
uint = __mpy_ext(ushort, ushort);
uint2 = __mpy_ext(ushort2, ushort2);
uint3 = __mpy_ext(ushort3, ushort3);
uint4 = __mpy_ext(ushort4, ushort4);
uint8 = __mpy_ext(ushort8, ushort8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __mpy_ext(ushort16, ushort16);
#endif

VMPYWD
long = __mpy_ext(int, int);
long2 = __mpy_ext(int2, int2);
long3 = __mpy_ext(int3, int3);
long4 = __mpy_ext(int4, int4);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __mpy_ext(int8, int8);
#endif

VMPYSUWD
long = __mpy_ext(int, uint);
long2 = __mpy_ext(int2, uint2);
long3 = __mpy_ext(int3, uint3);
long4 = __mpy_ext(int4, uint4);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __mpy_ext(int8, uint8);
#endif

VMPYUWD
ulong = __mpy_ext(uint, uint);
ulong2 = __mpy_ext(uint2, uint2);
ulong3 = __mpy_ext(uint3, uint3);
ulong4 = __mpy_ext(uint4, uint4);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __mpy_ext(uint8, uint8);
#endif

VMPYSP2DP
double = __mpy_ext(float, float);
double2 = __mpy_ext(float2, float2);
double3 = __mpy_ext(float3, float3);
double4 = __mpy_ext(float4, float4);
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = __mpy_ext(float8, float8);
#endif

VMPYUDQ
ulong2 = __mpy_ext(ulong, ulong);
ulong4 = __mpy_ext(ulong2, ulong2);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __mpy_ext(ulong4, ulong4);
#endif

*/

#define __mpy_ext(a,b) __overload("__mpy_ext",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __mpy_fx                                                               */
/*----------------------------------------------------------------------------*/
/*

C6MPY2IR
int2 = __mpy_fx(short2, int);

*/

/*----------------------------------------------------------------------------*/
/* ID: __mpy_sat                                                              */
/*----------------------------------------------------------------------------*/
/*

VSMPYWW
int = __mpy_sat(int, int);
int2 = __mpy_sat(int2, int2);
int3 = __mpy_sat(int3, int3);
int4 = __mpy_sat(int4, int4);
int8 = __mpy_sat(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __mpy_sat(int16, int16);
#endif

*/

#define __mpy_sat(a,b) __overload("__mpy_sat",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __mpy_sat_ext                                                          */
/*----------------------------------------------------------------------------*/
/*

SMPYHW, VSMPYHW
int = __mpy_sat_ext(short, short);
int2 = __mpy_sat_ext(short2, short2);
int3 = __mpy_sat_ext(short3, short3);
int4 = __mpy_sat_ext(short4, short4);
int8 = __mpy_sat_ext(short8, short8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __mpy_sat_ext(short16, short16);
#endif

*/

#define __mpy_sat_ext(a,b) __overload("__mpy_sat_ext",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __mpy_sat_fxq15                                                        */
/*----------------------------------------------------------------------------*/
/*

VSMPYR1HH
short = __mpy_sat_fxq15(short, short);
short2 = __mpy_sat_fxq15(short2, short2);
short3 = __mpy_sat_fxq15(short3, short3);
short4 = __mpy_sat_fxq15(short4, short4);
short8 = __mpy_sat_fxq15(short8, short8);
short16 = __mpy_sat_fxq15(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __mpy_sat_fxq15(short32, short32);
#endif

VSMPYRSUHH
short = __mpy_sat_fxq15(short, ushort);
short2 = __mpy_sat_fxq15(short2, ushort2);
short3 = __mpy_sat_fxq15(short3, ushort3);
short4 = __mpy_sat_fxq15(short4, ushort4);
short8 = __mpy_sat_fxq15(short8, ushort8);
short16 = __mpy_sat_fxq15(short16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __mpy_sat_fxq15(short32, ushort32);
#endif

*/

#define __mpy_sat_fxq15(a,b) __overload("__mpy_sat_fxq15",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __mpy_sat_fxq16                                                        */
/*----------------------------------------------------------------------------*/
/*

VSMPYRUHH
ushort = __mpy_sat_fxq16(ushort, ushort);
ushort2 = __mpy_sat_fxq16(ushort2, ushort2);
ushort3 = __mpy_sat_fxq16(ushort3, ushort3);
ushort4 = __mpy_sat_fxq16(ushort4, ushort4);
ushort8 = __mpy_sat_fxq16(ushort8, ushort8);
ushort16 = __mpy_sat_fxq16(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __mpy_sat_fxq16(ushort32, ushort32);
#endif

*/

#define __mpy_sat_fxq16(a,b) __overload("__mpy_sat_fxq16",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __mpy_sat_fxq16_15                                                     */
/*----------------------------------------------------------------------------*/
/*

VSMPYR17WW
int = __mpy_sat_fxq16_15(int, int);
int2 = __mpy_sat_fxq16_15(int2, int2);
int3 = __mpy_sat_fxq16_15(int3, int3);
int4 = __mpy_sat_fxq16_15(int4, int4);
int8 = __mpy_sat_fxq16_15(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __mpy_sat_fxq16_15(int16, int16);
#endif

*/

#define __mpy_sat_fxq16_15(a,b) __overload("__mpy_sat_fxq16_15",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __mpy_sat_fxq31                                                        */
/*----------------------------------------------------------------------------*/
/*

VSMPYR1WW
int = __mpy_sat_fxq31(int, int);
int2 = __mpy_sat_fxq31(int2, int2);
int3 = __mpy_sat_fxq31(int3, int3);
int4 = __mpy_sat_fxq31(int4, int4);
int8 = __mpy_sat_fxq31(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __mpy_sat_fxq31(int16, int16);
#endif

*/

#define __mpy_sat_fxq31(a,b) __overload("__mpy_sat_fxq31",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __mpy_xor                                                              */
/*----------------------------------------------------------------------------*/
/*

VXORMPYW
uint = __mpy_xor(uint, uint);
uint2 = __mpy_xor(uint2, uint2);
uint3 = __mpy_xor(uint3, uint3);
uint4 = __mpy_xor(uint4, uint4);
uint8 = __mpy_xor(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __mpy_xor(uint16, uint16);
#endif

*/

#define __mpy_xor(a,b) __overload("__mpy_xor",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __nand                                                                 */
/*----------------------------------------------------------------------------*/
/*

NANDD, NANDW, VNANDW
signed char = __nand(signed char, signed char);
char2 = __nand(char2, char2);
char3 = __nand(char3, char3);
char4 = __nand(char4, char4);
char8 = __nand(char8, char8);
char16 = __nand(char16, char16);
char32 = __nand(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __nand(char64, char64);
#endif
uchar = __nand(uchar, uchar);
uchar2 = __nand(uchar2, uchar2);
uchar3 = __nand(uchar3, uchar3);
uchar4 = __nand(uchar4, uchar4);
uchar8 = __nand(uchar8, uchar8);
uchar16 = __nand(uchar16, uchar16);
uchar32 = __nand(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __nand(uchar64, uchar64);
#endif
short = __nand(short, short);
short2 = __nand(short2, short2);
short3 = __nand(short3, short3);
short4 = __nand(short4, short4);
short8 = __nand(short8, short8);
short16 = __nand(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __nand(short32, short32);
#endif
ushort = __nand(ushort, ushort);
ushort2 = __nand(ushort2, ushort2);
ushort3 = __nand(ushort3, ushort3);
ushort4 = __nand(ushort4, ushort4);
ushort8 = __nand(ushort8, ushort8);
ushort16 = __nand(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __nand(ushort32, ushort32);
#endif
int = __nand(int, int);
int2 = __nand(int2, int2);
int3 = __nand(int3, int3);
int4 = __nand(int4, int4);
int8 = __nand(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __nand(int16, int16);
#endif
uint = __nand(uint, uint);
uint2 = __nand(uint2, uint2);
uint3 = __nand(uint3, uint3);
uint4 = __nand(uint4, uint4);
uint8 = __nand(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __nand(uint16, uint16);
#endif

NANDD, VNANDW
long = __nand(long, long);
long = __nand(long, (long)(k));
long2 = __nand(long2, long2);
long3 = __nand(long3, long3);
long4 = __nand(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __nand(long8, long8);
#endif
ulong = __nand(ulong, ulong);
ulong = __nand(ulong, (ulong)(k));
ulong2 = __nand(ulong2, ulong2);
ulong3 = __nand(ulong3, ulong3);
ulong4 = __nand(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __nand(ulong8, ulong8);
#endif

NAND
bool2 = __nand(bool2, bool2);
bool3 = __nand(bool3, bool3);
bool4 = __nand(bool4, bool4);
bool8 = __nand(bool8, bool8);
bool16 = __nand(bool16, bool16);
bool32 = __nand(bool32, bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
bool64 = __nand(bool64, bool64);
#endif

*/

#define __nand(a,b) __overload("__nand",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __negate                                                               */
/*----------------------------------------------------------------------------*/
/*

NOT
bool2 = __negate(bool2);
bool3 = __negate(bool3);
bool4 = __negate(bool4);
bool8 = __negate(bool8);
bool16 = __negate(bool16);
bool32 = __negate(bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
bool64 = __negate(bool64);
#endif

*/

#define __negate(a) __overload("__negate",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __nor                                                                  */
/*----------------------------------------------------------------------------*/
/*

NORD, NORW, VNORW
signed char = __nor(signed char, signed char);
char2 = __nor(char2, char2);
char3 = __nor(char3, char3);
char4 = __nor(char4, char4);
char8 = __nor(char8, char8);
char16 = __nor(char16, char16);
char32 = __nor(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __nor(char64, char64);
#endif
uchar = __nor(uchar, uchar);
uchar2 = __nor(uchar2, uchar2);
uchar3 = __nor(uchar3, uchar3);
uchar4 = __nor(uchar4, uchar4);
uchar8 = __nor(uchar8, uchar8);
uchar16 = __nor(uchar16, uchar16);
uchar32 = __nor(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __nor(uchar64, uchar64);
#endif
short = __nor(short, short);
short2 = __nor(short2, short2);
short3 = __nor(short3, short3);
short4 = __nor(short4, short4);
short8 = __nor(short8, short8);
short16 = __nor(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __nor(short32, short32);
#endif
ushort = __nor(ushort, ushort);
ushort2 = __nor(ushort2, ushort2);
ushort3 = __nor(ushort3, ushort3);
ushort4 = __nor(ushort4, ushort4);
ushort8 = __nor(ushort8, ushort8);
ushort16 = __nor(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __nor(ushort32, ushort32);
#endif
int = __nor(int, int);
int2 = __nor(int2, int2);
int3 = __nor(int3, int3);
int4 = __nor(int4, int4);
int8 = __nor(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __nor(int16, int16);
#endif
uint = __nor(uint, uint);
uint2 = __nor(uint2, uint2);
uint3 = __nor(uint3, uint3);
uint4 = __nor(uint4, uint4);
uint8 = __nor(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __nor(uint16, uint16);
#endif

NORD, VNORW
long = __nor(long, long);
long = __nor(long, (long)(k));
long2 = __nor(long2, long2);
long3 = __nor(long3, long3);
long4 = __nor(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __nor(long8, long8);
#endif
ulong = __nor(ulong, ulong);
ulong = __nor(ulong, (ulong)(k));
ulong2 = __nor(ulong2, ulong2);
ulong3 = __nor(ulong3, ulong3);
ulong4 = __nor(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __nor(ulong8, ulong8);
#endif

NOR
bool2 = __nor(bool2, bool2);
bool3 = __nor(bool3, bool3);
bool4 = __nor(bool4, bool4);
bool8 = __nor(bool8, bool8);
bool16 = __nor(bool16, bool16);
bool32 = __nor(bool32, bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
bool64 = __nor(bool64, bool64);
#endif

*/

#define __nor(a,b) __overload("__nor",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __norm                                                                 */
/*----------------------------------------------------------------------------*/
/*

VNORMB
signed char = __norm(signed char);
char2 = __norm(char2);
char3 = __norm(char3);
char4 = __norm(char4);
char8 = __norm(char8);
char16 = __norm(char16);
char32 = __norm(char32);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __norm(char64);
#endif

VNORMH
short = __norm(short);
short2 = __norm(short2);
short3 = __norm(short3);
short4 = __norm(short4);
short8 = __norm(short8);
short16 = __norm(short16);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __norm(short32);
#endif

VNORMW
int = __norm(int);
int2 = __norm(int2);
int3 = __norm(int3);
int4 = __norm(int4);
int8 = __norm(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __norm(int16);
#endif

VNORMD
long = __norm(long);
long2 = __norm(long2);
long3 = __norm(long3);
long4 = __norm(long4);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __norm(long8);
#endif

*/

#define __norm(a) __overload("__norm",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __norm_and_shift_elem_pair                                             */
/*----------------------------------------------------------------------------*/
/*

VNORM2UH
ushort2 = __norm_and_shift_elem_pair(ushort2);
ushort4 = __norm_and_shift_elem_pair(ushort4);
ushort8 = __norm_and_shift_elem_pair(ushort8);
ushort16 = __norm_and_shift_elem_pair(ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __norm_and_shift_elem_pair(ushort32);
#endif

VNORM2UW
uint2 = __norm_and_shift_elem_pair(uint2);
uint4 = __norm_and_shift_elem_pair(uint4);
uint8 = __norm_and_shift_elem_pair(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __norm_and_shift_elem_pair(uint16);
#endif

*/

#define __norm_and_shift_elem_pair(a) __overload("__norm_and_shift_elem_pair",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __or                                                                   */
/*----------------------------------------------------------------------------*/
/*

OR
bool2 = __or(bool2, bool2);
bool3 = __or(bool3, bool3);
bool4 = __or(bool4, bool4);
bool8 = __or(bool8, bool8);
bool16 = __or(bool16, bool16);
bool32 = __or(bool32, bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
bool64 = __or(bool64, bool64);
#endif

*/

#define __or(a,b) __overload("__or",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __orn                                                                  */
/*----------------------------------------------------------------------------*/
/*

ORND, ORNW, VORNW
signed char = __orn(signed char, signed char);
signed char = __orn(signed char, (signed char)(k));
char2 = __orn(char2, char2);
char2 = __orn(char2, (char2)(k));
char3 = __orn(char3, char3);
char3 = __orn(char3, (char3)(k));
char4 = __orn(char4, char4);
char4 = __orn(char4, (char4)(k));
char8 = __orn(char8, char8);
char16 = __orn(char16, char16);
char32 = __orn(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __orn(char64, char64);
#endif
uchar = __orn(uchar, uchar);
uchar = __orn(uchar, (uchar)(k));
uchar2 = __orn(uchar2, uchar2);
uchar2 = __orn(uchar2, (uchar2)(k));
uchar3 = __orn(uchar3, uchar3);
uchar3 = __orn(uchar3, (uchar3)(k));
uchar4 = __orn(uchar4, uchar4);
uchar4 = __orn(uchar4, (uchar4)(k));
uchar8 = __orn(uchar8, uchar8);
uchar16 = __orn(uchar16, uchar16);
uchar32 = __orn(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __orn(uchar64, uchar64);
#endif
short = __orn(short, short);
short = __orn(short, (short)(k));
short2 = __orn(short2, short2);
short2 = __orn(short2, (short2)(k));
short3 = __orn(short3, short3);
short4 = __orn(short4, short4);
short8 = __orn(short8, short8);
short16 = __orn(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __orn(short32, short32);
#endif
ushort = __orn(ushort, ushort);
ushort = __orn(ushort, (ushort)(k));
ushort2 = __orn(ushort2, ushort2);
ushort2 = __orn(ushort2, (ushort2)(k));
ushort3 = __orn(ushort3, ushort3);
ushort4 = __orn(ushort4, ushort4);
ushort8 = __orn(ushort8, ushort8);
ushort16 = __orn(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __orn(ushort32, ushort32);
#endif
int = __orn(int, int);
int = __orn(int, (int)(k));
int2 = __orn(int2, int2);
int2 = __orn(int2, (int2)(k));
int3 = __orn(int3, int3);
int3 = __orn(int3, (int3)(k));
int4 = __orn(int4, int4);
int4 = __orn(int4, (int4)(k));
int8 = __orn(int8, int8);
int8 = __orn(int8, (int8)(k));
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __orn(int16, int16);
int16 = __orn(int16, (int16)(k));
#endif
uint = __orn(uint, uint);
uint = __orn(uint, (uint)(k));
uint2 = __orn(uint2, uint2);
uint2 = __orn(uint2, (uint2)(k));
uint3 = __orn(uint3, uint3);
uint3 = __orn(uint3, (uint3)(k));
uint4 = __orn(uint4, uint4);
uint4 = __orn(uint4, (uint4)(k));
uint8 = __orn(uint8, uint8);
uint8 = __orn(uint8, (uint8)(k));
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __orn(uint16, uint16);
uint16 = __orn(uint16, (uint16)(k));
#endif

ORND, VORNW
long = __orn(long, long);
long = __orn(long, (long)(k));
long2 = __orn(long2, long2);
long3 = __orn(long3, long3);
long4 = __orn(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __orn(long8, long8);
#endif
ulong = __orn(ulong, ulong);
ulong = __orn(ulong, (ulong)(k));
ulong2 = __orn(ulong2, ulong2);
ulong3 = __orn(ulong3, ulong3);
ulong4 = __orn(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __orn(ulong8, ulong8);
#endif

ORN
bool2 = __orn(bool2, bool2);
bool3 = __orn(bool3, bool3);
bool4 = __orn(bool4, bool4);
bool8 = __orn(bool8, bool8);
bool16 = __orn(bool16, bool16);
bool32 = __orn(bool32, bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
bool64 = __orn(bool64, bool64);
#endif

*/

#define __orn(a,b) __overload("__orn",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __outer_product_matmpy                                                 */
/*----------------------------------------------------------------------------*/
/*

VOPMATMPYSP
#if __C7X_VEC_SIZE_BITS__ == 512
float4 = __outer_product_matmpy(float2, float2);
float8 = __outer_product_matmpy(float4, float4);
float16 = __outer_product_matmpy(float8, float8);
#endif

*/

#define __outer_product_matmpy(a,b) __overload("__outer_product_matmpy",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __pack                                                                 */
/*----------------------------------------------------------------------------*/
/*

PACKW
cshort2 = __pack(cshort, cshort);
int2 = __pack(int, int);
uint2 = __pack(uint, uint);
float2 = __pack(float, float);

*/

#define __pack(a,b) __overload("__pack",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __pack_consec_high                                                     */
/*----------------------------------------------------------------------------*/
/*

VBPACKH
#if __C7X_VEC_SIZE_BITS__ == 256
char32 = __pack_consec_high(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __pack_consec_high(char64, char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
uchar32 = __pack_consec_high(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __pack_consec_high(uchar64, uchar64);
#endif

VHPACKH
#if __C7X_VEC_SIZE_BITS__ == 256
cchar16 = __pack_consec_high(cchar16, cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = __pack_consec_high(cchar32, cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
short16 = __pack_consec_high(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __pack_consec_high(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ushort16 = __pack_consec_high(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __pack_consec_high(ushort32, ushort32);
#endif

VWPACKH
#if __C7X_VEC_SIZE_BITS__ == 256
cshort8 = __pack_consec_high(cshort8, cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = __pack_consec_high(cshort16, cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
int8 = __pack_consec_high(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __pack_consec_high(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
uint8 = __pack_consec_high(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __pack_consec_high(uint16, uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
float8 = __pack_consec_high(float8, float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __pack_consec_high(float16, float16);
#endif

VDPACKH
#if __C7X_VEC_SIZE_BITS__ == 256
cint4 = __pack_consec_high(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __pack_consec_high(cint8, cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
cfloat4 = __pack_consec_high(cfloat4, cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cfloat8 = __pack_consec_high(cfloat8, cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long4 = __pack_consec_high(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __pack_consec_high(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ulong4 = __pack_consec_high(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __pack_consec_high(ulong8, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
double4 = __pack_consec_high(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = __pack_consec_high(double8, double8);
#endif

*/

#define __pack_consec_high(a,b) __overload("__pack_consec_high",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __pack_consec_low                                                      */
/*----------------------------------------------------------------------------*/
/*

VBPACKL
#if __C7X_VEC_SIZE_BITS__ == 256
char32 = __pack_consec_low(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __pack_consec_low(char64, char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
uchar32 = __pack_consec_low(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __pack_consec_low(uchar64, uchar64);
#endif

VHPACKL
#if __C7X_VEC_SIZE_BITS__ == 256
cchar16 = __pack_consec_low(cchar16, cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = __pack_consec_low(cchar32, cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
short16 = __pack_consec_low(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __pack_consec_low(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ushort16 = __pack_consec_low(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __pack_consec_low(ushort32, ushort32);
#endif

VWPACKL
#if __C7X_VEC_SIZE_BITS__ == 256
cshort8 = __pack_consec_low(cshort8, cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = __pack_consec_low(cshort16, cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
int8 = __pack_consec_low(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __pack_consec_low(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
uint8 = __pack_consec_low(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __pack_consec_low(uint16, uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
float8 = __pack_consec_low(float8, float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __pack_consec_low(float16, float16);
#endif

VDPACKL
#if __C7X_VEC_SIZE_BITS__ == 256
cint4 = __pack_consec_low(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __pack_consec_low(cint8, cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
cfloat4 = __pack_consec_low(cfloat4, cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cfloat8 = __pack_consec_low(cfloat8, cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long4 = __pack_consec_low(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __pack_consec_low(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ulong4 = __pack_consec_low(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __pack_consec_low(ulong8, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
double4 = __pack_consec_low(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = __pack_consec_low(double8, double8);
#endif

*/

#define __pack_consec_low(a,b) __overload("__pack_consec_low",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __pack_even                                                            */
/*----------------------------------------------------------------------------*/
/*

VPACKP2
cchar4 = __pack_even(cchar4, cchar4);
cchar8 = __pack_even(cchar8, cchar8);
cchar16 = __pack_even(cchar16, cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = __pack_even(cchar32, cchar32);
#endif
short4 = __pack_even(short4, short4);
short8 = __pack_even(short8, short8);
short16 = __pack_even(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __pack_even(short32, short32);
#endif
ushort4 = __pack_even(ushort4, ushort4);
ushort8 = __pack_even(ushort8, ushort8);
ushort16 = __pack_even(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __pack_even(ushort32, ushort32);
#endif

*/

#define __pack_even(a,b) __overload("__pack_even",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __pack_even_cross                                                      */
/*----------------------------------------------------------------------------*/
/*

PACKX2
cchar4 = __pack_even_cross(cchar2, cchar2);

VPACKX2
cchar4 = __pack_even_cross(cchar4, cchar4);
cchar8 = __pack_even_cross(cchar8, cchar8);
cchar16 = __pack_even_cross(cchar16, cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = __pack_even_cross(cchar32, cchar32);
#endif

PACKX2
short4 = __pack_even_cross(short2, short2);

VPACKX2
short4 = __pack_even_cross(short4, short4);
short8 = __pack_even_cross(short8, short8);
short16 = __pack_even_cross(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __pack_even_cross(short32, short32);
#endif

PACKX2
ushort4 = __pack_even_cross(ushort2, ushort2);

VPACKX2
ushort4 = __pack_even_cross(ushort4, ushort4);
ushort8 = __pack_even_cross(ushort8, ushort8);
ushort16 = __pack_even_cross(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __pack_even_cross(ushort32, ushort32);
#endif

*/

#define __pack_even_cross(a,b) __overload("__pack_even_cross",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __pack_high                                                            */
/*----------------------------------------------------------------------------*/
/*

VPACKH4
char4 = __pack_high(char4, char4);
char8 = __pack_high(char8, char8);
char16 = __pack_high(char16, char16);
char32 = __pack_high(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __pack_high(char64, char64);
#endif
uchar4 = __pack_high(uchar4, uchar4);
uchar8 = __pack_high(uchar8, uchar8);
uchar16 = __pack_high(uchar16, uchar16);
uchar32 = __pack_high(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __pack_high(uchar64, uchar64);
#endif

VPACKH2
cchar2 = __pack_high(cchar2, cchar2);
cchar4 = __pack_high(cchar4, cchar4);
cchar8 = __pack_high(cchar8, cchar8);
cchar16 = __pack_high(cchar16, cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = __pack_high(cchar32, cchar32);
#endif
short2 = __pack_high(short2, short2);
short4 = __pack_high(short4, short4);
short8 = __pack_high(short8, short8);
short16 = __pack_high(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __pack_high(short32, short32);
#endif
ushort2 = __pack_high(ushort2, ushort2);
ushort4 = __pack_high(ushort4, ushort4);
ushort8 = __pack_high(ushort8, ushort8);
ushort16 = __pack_high(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __pack_high(ushort32, ushort32);
#endif

*/

#define __pack_high(a,b) __overload("__pack_high",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __pack_high_low                                                        */
/*----------------------------------------------------------------------------*/
/*

VPACKHL2
cchar2 = __pack_high_low(cchar2, cchar2);
cchar4 = __pack_high_low(cchar4, cchar4);
cchar8 = __pack_high_low(cchar8, cchar8);
cchar16 = __pack_high_low(cchar16, cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = __pack_high_low(cchar32, cchar32);
#endif
short2 = __pack_high_low(short2, short2);
short4 = __pack_high_low(short4, short4);
short8 = __pack_high_low(short8, short8);
short16 = __pack_high_low(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __pack_high_low(short32, short32);
#endif
ushort2 = __pack_high_low(ushort2, ushort2);
ushort4 = __pack_high_low(ushort4, ushort4);
ushort8 = __pack_high_low(ushort8, ushort8);
ushort16 = __pack_high_low(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __pack_high_low(ushort32, ushort32);
#endif

*/

#define __pack_high_low(a,b) __overload("__pack_high_low",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __pack_low                                                             */
/*----------------------------------------------------------------------------*/
/*

VPACKL4
char4 = __pack_low(char4, char4);
char8 = __pack_low(char8, char8);
char16 = __pack_low(char16, char16);
char32 = __pack_low(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __pack_low(char64, char64);
#endif
uchar4 = __pack_low(uchar4, uchar4);
uchar8 = __pack_low(uchar8, uchar8);
uchar16 = __pack_low(uchar16, uchar16);
uchar32 = __pack_low(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __pack_low(uchar64, uchar64);
#endif

VPACKL2
cchar2 = __pack_low(cchar2, cchar2);
cchar4 = __pack_low(cchar4, cchar4);
cchar8 = __pack_low(cchar8, cchar8);
cchar16 = __pack_low(cchar16, cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = __pack_low(cchar32, cchar32);
#endif
short2 = __pack_low(short2, short2);
short4 = __pack_low(short4, short4);
short8 = __pack_low(short8, short8);
short16 = __pack_low(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __pack_low(short32, short32);
#endif
ushort2 = __pack_low(ushort2, ushort2);
ushort4 = __pack_low(ushort4, ushort4);
ushort8 = __pack_low(ushort8, ushort8);
ushort16 = __pack_low(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __pack_low(ushort32, ushort32);
#endif

VPACKW
cshort2 = __pack_low(cshort2, cshort2);
cshort4 = __pack_low(cshort4, cshort4);
cshort8 = __pack_low(cshort8, cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = __pack_low(cshort16, cshort16);
#endif
int2 = __pack_low(int2, int2);
int4 = __pack_low(int4, int4);
int8 = __pack_low(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __pack_low(int16, int16);
#endif
uint2 = __pack_low(uint2, uint2);
uint4 = __pack_low(uint4, uint4);
uint8 = __pack_low(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __pack_low(uint16, uint16);
#endif
float2 = __pack_low(float2, float2);
float4 = __pack_low(float4, float4);
float8 = __pack_low(float8, float8);
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __pack_low(float16, float16);
#endif

*/

#define __pack_low(a,b) __overload("__pack_low",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __pack_low_high                                                        */
/*----------------------------------------------------------------------------*/
/*

VPACKLH4
char8 = __pack_low_high(char8, char8);
char16 = __pack_low_high(char16, char16);
char32 = __pack_low_high(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __pack_low_high(char64, char64);
#endif
uchar8 = __pack_low_high(uchar8, uchar8);
uchar16 = __pack_low_high(uchar16, uchar16);
uchar32 = __pack_low_high(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __pack_low_high(uchar64, uchar64);
#endif

VPACKLH2
cchar2 = __pack_low_high(cchar2, cchar2);
cchar4 = __pack_low_high(cchar4, cchar4);
cchar8 = __pack_low_high(cchar8, cchar8);
cchar16 = __pack_low_high(cchar16, cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = __pack_low_high(cchar32, cchar32);
#endif
short2 = __pack_low_high(short2, short2);
short4 = __pack_low_high(short4, short4);
short8 = __pack_low_high(short8, short8);
short16 = __pack_low_high(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __pack_low_high(short32, short32);
#endif
ushort2 = __pack_low_high(ushort2, ushort2);
ushort4 = __pack_low_high(ushort4, ushort4);
ushort8 = __pack_low_high(ushort8, ushort8);
ushort16 = __pack_low_high(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __pack_low_high(ushort32, ushort32);
#endif

*/

#define __pack_low_high(a,b) __overload("__pack_low_high",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __pack_sat                                                             */
/*----------------------------------------------------------------------------*/
/*

VSPACKHB
char2 = __pack_sat(short, short);
char4 = __pack_sat(short2, short2);
char8 = __pack_sat(short4, short4);
char16 = __pack_sat(short8, short8);
char32 = __pack_sat(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __pack_sat(short32, short32);
#endif

VSPACKWH
short2 = __pack_sat(int, int);
short4 = __pack_sat(int2, int2);
short8 = __pack_sat(int4, int4);
short16 = __pack_sat(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __pack_sat(int16, int16);
#endif

VSPACKDW
int2 = __pack_sat(long, long);
int4 = __pack_sat(long2, long2);
int8 = __pack_sat(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __pack_sat(long8, long8);
#endif

*/

#define __pack_sat(a,b) __overload("__pack_sat",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __pack_shift_sat                                                       */
/*----------------------------------------------------------------------------*/
/*

VRPACKH
short2 = __pack_shift_sat(int, int);
short4 = __pack_shift_sat(int2, int2);
short8 = __pack_shift_sat(int4, int4);
short16 = __pack_shift_sat(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __pack_shift_sat(int16, int16);
#endif

*/

#define __pack_shift_sat(a,b) __overload("__pack_shift_sat",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __pack_usat                                                            */
/*----------------------------------------------------------------------------*/
/*

VSPACKUHB
uchar2 = __pack_usat(short, short);
uchar4 = __pack_usat(short2, short2);
uchar8 = __pack_usat(short4, short4);
uchar16 = __pack_usat(short8, short8);
uchar32 = __pack_usat(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __pack_usat(short32, short32);
#endif

VSPACKUWH
ushort2 = __pack_usat(int, int);
ushort4 = __pack_usat(int2, int2);
ushort8 = __pack_usat(int4, int4);
ushort16 = __pack_usat(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __pack_usat(int16, int16);
#endif

VSPACKUDW
uint2 = __pack_usat(long, long);
uint4 = __pack_usat(long2, long2);
uint8 = __pack_usat(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __pack_usat(long8, long8);
#endif

*/

#define __pack_usat(a,b) __overload("__pack_usat",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __parallel_pack_dup_16way                                              */
/*----------------------------------------------------------------------------*/
/*

VPPACKDUP16W
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __parallel_pack_dup_16way(bool16);
#endif

*/

#define __parallel_pack_dup_16way(a) __overload("__parallel_pack_dup_16way",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __parallel_pack_dup_8way                                               */
/*----------------------------------------------------------------------------*/
/*

VPPACKDUP8W
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __parallel_pack_dup_8way(bool8);
#endif

*/

#define __parallel_pack_dup_8way(a) __overload("__parallel_pack_dup_8way",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __permute                                                              */
/*----------------------------------------------------------------------------*/
/*

VPERM
#if __C7X_VEC_SIZE_BITS__ == 256
uchar32 = __permute(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __permute(uchar64, uchar64);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __permute_cntrl                                                        */
/*----------------------------------------------------------------------------*/
/*

VPERM
#if __C7X_VEC_SIZE_BITS__ == 256
uchar32 = __permute_cntrl(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __permute_cntrl(uchar64, uchar64);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_even_char                                               */
/*----------------------------------------------------------------------------*/
/*

VPERMEEB
#if __C7X_VEC_SIZE_BITS__ == 256
uchar32 = __permute_even_even_char(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __permute_even_even_char(uchar64, uchar64, uchar64);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_even_int                                                */
/*----------------------------------------------------------------------------*/
/*

VPERMEEW
#if __C7X_VEC_SIZE_BITS__ == 256
uchar32 = __permute_even_even_int(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __permute_even_even_int(uchar64, uchar64, uchar64);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_even_long                                               */
/*----------------------------------------------------------------------------*/
/*

VPERMEED
#if __C7X_VEC_SIZE_BITS__ == 256
uchar32 = __permute_even_even_long(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __permute_even_even_long(uchar64, uchar64, uchar64);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_even_quad                                               */
/*----------------------------------------------------------------------------*/
/*

VPERMEEQ
#if __C7X_VEC_SIZE_BITS__ == 256
uchar32 = __permute_even_even_quad(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __permute_even_even_quad(uchar64, uchar64, uchar64);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_even_short                                              */
/*----------------------------------------------------------------------------*/
/*

VPERMEEH
#if __C7X_VEC_SIZE_BITS__ == 256
uchar32 = __permute_even_even_short(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __permute_even_even_short(uchar64, uchar64, uchar64);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_odd_char                                                */
/*----------------------------------------------------------------------------*/
/*

VPERMEOB
#if __C7X_VEC_SIZE_BITS__ == 256
uchar32 = __permute_even_odd_char(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __permute_even_odd_char(uchar64, uchar64, uchar64);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_odd_int                                                 */
/*----------------------------------------------------------------------------*/
/*

VPERMEOW
#if __C7X_VEC_SIZE_BITS__ == 256
uchar32 = __permute_even_odd_int(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __permute_even_odd_int(uchar64, uchar64, uchar64);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_odd_long                                                */
/*----------------------------------------------------------------------------*/
/*

VPERMEOD
#if __C7X_VEC_SIZE_BITS__ == 256
uchar32 = __permute_even_odd_long(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __permute_even_odd_long(uchar64, uchar64, uchar64);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_odd_quad                                                */
/*----------------------------------------------------------------------------*/
/*

VPERMEOQ
#if __C7X_VEC_SIZE_BITS__ == 256
uchar32 = __permute_even_odd_quad(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __permute_even_odd_quad(uchar64, uchar64, uchar64);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_odd_short                                               */
/*----------------------------------------------------------------------------*/
/*

VPERMEOH
#if __C7X_VEC_SIZE_BITS__ == 256
uchar32 = __permute_even_odd_short(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __permute_even_odd_short(uchar64, uchar64, uchar64);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __permute_high_high                                                    */
/*----------------------------------------------------------------------------*/
/*

VPERMHH
#if __C7X_VEC_SIZE_BITS__ == 256
uchar32 = __permute_high_high(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __permute_high_high(uchar64, uchar64, uchar64);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __permute_low_high                                                     */
/*----------------------------------------------------------------------------*/
/*

VPERMLH
#if __C7X_VEC_SIZE_BITS__ == 256
uchar32 = __permute_low_high(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __permute_low_high(uchar64, uchar64, uchar64);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __permute_low_low                                                      */
/*----------------------------------------------------------------------------*/
/*

VPERMLL
#if __C7X_VEC_SIZE_BITS__ == 256
uchar32 = __permute_low_low(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __permute_low_low(uchar64, uchar64, uchar64);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __permute_odd_odd_char                                                 */
/*----------------------------------------------------------------------------*/
/*

VPERMOOB
#if __C7X_VEC_SIZE_BITS__ == 256
uchar32 = __permute_odd_odd_char(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __permute_odd_odd_char(uchar64, uchar64, uchar64);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __permute_odd_odd_int                                                  */
/*----------------------------------------------------------------------------*/
/*

VPERMOOW
#if __C7X_VEC_SIZE_BITS__ == 256
uchar32 = __permute_odd_odd_int(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __permute_odd_odd_int(uchar64, uchar64, uchar64);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __permute_odd_odd_long                                                 */
/*----------------------------------------------------------------------------*/
/*

VPERMOOD
#if __C7X_VEC_SIZE_BITS__ == 256
uchar32 = __permute_odd_odd_long(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __permute_odd_odd_long(uchar64, uchar64, uchar64);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __permute_odd_odd_quad                                                 */
/*----------------------------------------------------------------------------*/
/*

VPERMOOQ
#if __C7X_VEC_SIZE_BITS__ == 256
uchar32 = __permute_odd_odd_quad(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __permute_odd_odd_quad(uchar64, uchar64, uchar64);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __permute_odd_odd_short                                                */
/*----------------------------------------------------------------------------*/
/*

VPERMOOH
#if __C7X_VEC_SIZE_BITS__ == 256
uchar32 = __permute_odd_odd_short(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __permute_odd_odd_short(uchar64, uchar64, uchar64);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __popcount                                                             */
/*----------------------------------------------------------------------------*/
/*

VBITCNTB
signed char = __popcount(signed char);
char2 = __popcount(char2);
char3 = __popcount(char3);
char4 = __popcount(char4);
char8 = __popcount(char8);
char16 = __popcount(char16);
char32 = __popcount(char32);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __popcount(char64);
#endif
uchar = __popcount(uchar);
uchar2 = __popcount(uchar2);
uchar3 = __popcount(uchar3);
uchar4 = __popcount(uchar4);
uchar8 = __popcount(uchar8);
uchar16 = __popcount(uchar16);
uchar32 = __popcount(uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __popcount(uchar64);
#endif

VBITCNTH
short = __popcount(short);
short2 = __popcount(short2);
short3 = __popcount(short3);
short4 = __popcount(short4);
short8 = __popcount(short8);
short16 = __popcount(short16);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __popcount(short32);
#endif
ushort = __popcount(ushort);
ushort2 = __popcount(ushort2);
ushort3 = __popcount(ushort3);
ushort4 = __popcount(ushort4);
ushort8 = __popcount(ushort8);
ushort16 = __popcount(ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __popcount(ushort32);
#endif

VBITCNTW
int = __popcount(int);
int2 = __popcount(int2);
int3 = __popcount(int3);
int4 = __popcount(int4);
int8 = __popcount(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __popcount(int16);
#endif
uint = __popcount(uint);
uint2 = __popcount(uint2);
uint3 = __popcount(uint3);
uint4 = __popcount(uint4);
uint8 = __popcount(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __popcount(uint16);
#endif

VBITCNTD
long = __popcount(long);
long2 = __popcount(long2);
long3 = __popcount(long3);
long4 = __popcount(long4);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __popcount(long8);
#endif
ulong = __popcount(ulong);
ulong2 = __popcount(ulong2);
ulong3 = __popcount(ulong3);
ulong4 = __popcount(ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __popcount(ulong8);
#endif

*/

#define __popcount(a) __overload("__popcount",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __recip                                                                */
/*----------------------------------------------------------------------------*/
/*

VRCPSP
float = __recip(float);
float2 = __recip(float2);
float3 = __recip(float3);
float4 = __recip(float4);
float8 = __recip(float8);
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __recip(float16);
#endif

VRCPDP
double = __recip(double);
double2 = __recip(double2);
double3 = __recip(double3);
double4 = __recip(double4);
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = __recip(double8);
#endif

*/

#define __recip(a) __overload("__recip",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __recip_sqrt                                                           */
/*----------------------------------------------------------------------------*/
/*

VRSQRSP
float = __recip_sqrt(float);
float2 = __recip_sqrt(float2);
float3 = __recip_sqrt(float3);
float4 = __recip_sqrt(float4);
float8 = __recip_sqrt(float8);
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __recip_sqrt(float16);
#endif

VRSQRDP
double = __recip_sqrt(double);
double2 = __recip_sqrt(double2);
double3 = __recip_sqrt(double3);
double4 = __recip_sqrt(double4);
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = __recip_sqrt(double8);
#endif

*/

#define __recip_sqrt(a) __overload("__recip_sqrt",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __replace                                                              */
/*----------------------------------------------------------------------------*/
/*

REPLACE, VREPLACE
long = __replace(long, (signed char)(k={0-63}), (signed char)(k={0-63}), long);
long2 = __replace(long2, (char2)(k={0-63}), (char2)(k={0-63}), long2);
long3 = __replace(long3, (char3)(k={0-63}), (char3)(k={0-63}), long3);
long4 = __replace(long4, (char4)(k={0-63}), (char4)(k={0-63}), long4);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __replace(long8, (char8)(k={0-63}), (char8)(k={0-63}), long8);
#endif
ulong = __replace(ulong, (uchar)(k={0-63}), (uchar)(k={0-63}), ulong);
ulong2 = __replace(ulong2, (uchar2)(k={0-63}), (uchar2)(k={0-63}), ulong2);
ulong3 = __replace(ulong3, (uchar3)(k={0-63}), (uchar3)(k={0-63}), ulong3);
ulong4 = __replace(ulong4, (uchar4)(k={0-63}), (uchar4)(k={0-63}), ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __replace(ulong8, (uchar8)(k={0-63}), (uchar8)(k={0-63}), ulong8);
#endif

*/

#define __replace(a,b,c,d) __overload("__replace",(a),(b),(c),(d))((a),(b),(c),(d))

/*----------------------------------------------------------------------------*/
/* ID: __reverse                                                              */
/*----------------------------------------------------------------------------*/
/*

VREVERSEB
#if __C7X_VEC_SIZE_BITS__ == 256
char32 = __reverse(char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __reverse(char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
uchar32 = __reverse(uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __reverse(uchar64);
#endif

VREVERSEH
#if __C7X_VEC_SIZE_BITS__ == 256
cchar16 = __reverse(cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = __reverse(cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
short16 = __reverse(short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __reverse(short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ushort16 = __reverse(ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __reverse(ushort32);
#endif

VREVERSEW
#if __C7X_VEC_SIZE_BITS__ == 256
cshort8 = __reverse(cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = __reverse(cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
int8 = __reverse(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __reverse(int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
uint8 = __reverse(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __reverse(uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
float8 = __reverse(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __reverse(float16);
#endif

VREVERSED
#if __C7X_VEC_SIZE_BITS__ == 256
cint4 = __reverse(cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __reverse(cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
cfloat4 = __reverse(cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cfloat8 = __reverse(cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long4 = __reverse(long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __reverse(long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ulong4 = __reverse(ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __reverse(ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
double4 = __reverse(double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = __reverse(double8);
#endif

*/

#define __reverse(a) __overload("__reverse",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __rhadd                                                                */
/*----------------------------------------------------------------------------*/
/*

VAVGB
signed char = __rhadd(signed char, signed char);
char2 = __rhadd(char2, char2);
char3 = __rhadd(char3, char3);
char4 = __rhadd(char4, char4);
char8 = __rhadd(char8, char8);
char16 = __rhadd(char16, char16);
char32 = __rhadd(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __rhadd(char64, char64);
#endif

VAVGUB
uchar = __rhadd(uchar, uchar);
uchar2 = __rhadd(uchar2, uchar2);
uchar3 = __rhadd(uchar3, uchar3);
uchar4 = __rhadd(uchar4, uchar4);
uchar8 = __rhadd(uchar8, uchar8);
uchar16 = __rhadd(uchar16, uchar16);
uchar32 = __rhadd(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __rhadd(uchar64, uchar64);
#endif

VAVGH
short = __rhadd(short, short);
short2 = __rhadd(short2, short2);
short3 = __rhadd(short3, short3);
short4 = __rhadd(short4, short4);
short8 = __rhadd(short8, short8);
short16 = __rhadd(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __rhadd(short32, short32);
#endif

VAVGUH
ushort = __rhadd(ushort, ushort);
ushort2 = __rhadd(ushort2, ushort2);
ushort3 = __rhadd(ushort3, ushort3);
ushort4 = __rhadd(ushort4, ushort4);
ushort8 = __rhadd(ushort8, ushort8);
ushort16 = __rhadd(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __rhadd(ushort32, ushort32);
#endif

VAVGW
int = __rhadd(int, int);
int2 = __rhadd(int2, int2);
int3 = __rhadd(int3, int3);
int4 = __rhadd(int4, int4);
int8 = __rhadd(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __rhadd(int16, int16);
#endif

VAVGUW
uint = __rhadd(uint, uint);
uint2 = __rhadd(uint2, uint2);
uint3 = __rhadd(uint3, uint3);
uint4 = __rhadd(uint4, uint4);
uint8 = __rhadd(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __rhadd(uint16, uint16);
#endif

VAVGD
long = __rhadd(long, long);
long2 = __rhadd(long2, long2);
long3 = __rhadd(long3, long3);
long4 = __rhadd(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __rhadd(long8, long8);
#endif

VAVGUD
ulong = __rhadd(ulong, ulong);
ulong2 = __rhadd(ulong2, ulong2);
ulong3 = __rhadd(ulong3, ulong3);
ulong4 = __rhadd(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __rhadd(ulong8, ulong8);
#endif

*/

#define __rhadd(a,b) __overload("__rhadd",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __rotate_left                                                          */
/*----------------------------------------------------------------------------*/
/*

VROTLB
uchar = __rotate_left(uchar, (uchar)(k={0-63}));
uchar2 = __rotate_left(uchar2, (uchar2)(k={0-63}));
uchar3 = __rotate_left(uchar3, (uchar3)(k={0-63}));
uchar4 = __rotate_left(uchar4, (uchar4)(k={0-63}));
uchar8 = __rotate_left(uchar8, (uchar8)(k={0-63}));
uchar16 = __rotate_left(uchar16, (uchar16)(k={0-63}));
uchar32 = __rotate_left(uchar32, (uchar32)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __rotate_left(uchar64, (uchar64)(k={0-63}));
#endif
uchar4 = __rotate_left(uchar4, uint);
uchar8 = __rotate_left(uchar8, uint2);
uchar16 = __rotate_left(uchar16, uint4);
uchar32 = __rotate_left(uchar32, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __rotate_left(uchar64, uint16);
#endif

VROTLH
ushort = __rotate_left(ushort, (ushort)(k={0-63}));
ushort2 = __rotate_left(ushort2, (ushort2)(k={0-63}));
ushort3 = __rotate_left(ushort3, (ushort3)(k={0-63}));
ushort4 = __rotate_left(ushort4, (ushort4)(k={0-63}));
ushort8 = __rotate_left(ushort8, (ushort8)(k={0-63}));
ushort16 = __rotate_left(ushort16, (ushort16)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __rotate_left(ushort32, (ushort32)(k={0-63}));
#endif
ushort2 = __rotate_left(ushort2, uint);
ushort4 = __rotate_left(ushort4, uint2);
ushort8 = __rotate_left(ushort8, uint4);
ushort16 = __rotate_left(ushort16, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __rotate_left(ushort32, uint16);
#endif

VROTLW
int = __rotate_left(int, (uchar)(k={0-63}));
int2 = __rotate_left(int2, (uchar2)(k={0-63}));
int3 = __rotate_left(int3, (uchar3)(k={0-63}));
int4 = __rotate_left(int4, (uchar4)(k={0-63}));
int8 = __rotate_left(int8, (uchar8)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __rotate_left(int16, (uchar16)(k={0-63}));
#endif
int = __rotate_left(int, uint);
int2 = __rotate_left(int2, uint2);
int3 = __rotate_left(int3, uint3);
int4 = __rotate_left(int4, uint4);
int8 = __rotate_left(int8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __rotate_left(int16, uint16);
#endif

VROTLD
ulong = __rotate_left(ulong, (uchar)(k={0-63}));
ulong2 = __rotate_left(ulong2, (uchar2)(k={0-63}));
ulong3 = __rotate_left(ulong3, (uchar3)(k={0-63}));
ulong4 = __rotate_left(ulong4, (uchar4)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __rotate_left(ulong8, (uchar8)(k={0-63}));
#endif
ulong = __rotate_left(ulong, ulong);
ulong2 = __rotate_left(ulong2, ulong2);
ulong3 = __rotate_left(ulong3, ulong3);
ulong4 = __rotate_left(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __rotate_left(ulong8, ulong8);
#endif

*/

#define __rotate_left(a,b) __overload("__rotate_left",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __saturate                                                             */
/*----------------------------------------------------------------------------*/
/*

VGSATH
short = __saturate(short, (uchar)(k={0-63}));
short2 = __saturate(short2, (uchar2)(k={0-63}));
short3 = __saturate(short3, (uchar3)(k={0-63}));
short4 = __saturate(short4, (uchar4)(k={0-63}));
short8 = __saturate(short8, (uchar8)(k={0-63}));
short16 = __saturate(short16, (uchar16)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __saturate(short32, (uchar32)(k={0-63}));
#endif

VGSATUH
ushort = __saturate(ushort, (uchar)(k={0-63}));
ushort2 = __saturate(ushort2, (uchar2)(k={0-63}));
ushort3 = __saturate(ushort3, (uchar3)(k={0-63}));
ushort4 = __saturate(ushort4, (uchar4)(k={0-63}));
ushort8 = __saturate(ushort8, (uchar8)(k={0-63}));
ushort16 = __saturate(ushort16, (uchar16)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __saturate(ushort32, (uchar32)(k={0-63}));
#endif

VGSATW
int = __saturate(int, (uchar)(k={0-63}));
int2 = __saturate(int2, (uchar2)(k={0-63}));
int3 = __saturate(int3, (uchar3)(k={0-63}));
int4 = __saturate(int4, (uchar4)(k={0-63}));
int8 = __saturate(int8, (uchar8)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __saturate(int16, (uchar16)(k={0-63}));
#endif

VGSATUW
uint = __saturate(uint, (uchar)(k={0-63}));
uint2 = __saturate(uint2, (uchar2)(k={0-63}));
uint3 = __saturate(uint3, (uchar3)(k={0-63}));
uint4 = __saturate(uint4, (uchar4)(k={0-63}));
uint8 = __saturate(uint8, (uchar8)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __saturate(uint16, (uchar16)(k={0-63}));
#endif

VGSATD
long = __saturate(long, (uchar)(k={0-63}));
long2 = __saturate(long2, (uchar2)(k={0-63}));
long3 = __saturate(long3, (uchar3)(k={0-63}));
long4 = __saturate(long4, (uchar4)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __saturate(long8, (uchar8)(k={0-63}));
#endif

VGSATUD
ulong = __saturate(ulong, (uchar)(k={0-63}));
ulong2 = __saturate(ulong2, (uchar2)(k={0-63}));
ulong3 = __saturate(ulong3, (uchar3)(k={0-63}));
ulong4 = __saturate(ulong4, (uchar4)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __saturate(ulong8, (uchar8)(k={0-63}));
#endif

*/

#define __saturate(a,b) __overload("__saturate",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __saturate_s2u                                                         */
/*----------------------------------------------------------------------------*/
/*

VGSATSUH
ushort = __saturate_s2u(short, (uchar)(k={0-63}));
ushort2 = __saturate_s2u(short2, (uchar2)(k={0-63}));
ushort3 = __saturate_s2u(short3, (uchar3)(k={0-63}));
ushort4 = __saturate_s2u(short4, (uchar4)(k={0-63}));
ushort8 = __saturate_s2u(short8, (uchar8)(k={0-63}));
ushort16 = __saturate_s2u(short16, (uchar16)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __saturate_s2u(short32, (uchar32)(k={0-63}));
#endif

VGSATSUW
uint = __saturate_s2u(int, (uchar)(k={0-63}));
uint2 = __saturate_s2u(int2, (uchar2)(k={0-63}));
uint3 = __saturate_s2u(int3, (uchar3)(k={0-63}));
uint4 = __saturate_s2u(int4, (uchar4)(k={0-63}));
uint8 = __saturate_s2u(int8, (uchar8)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __saturate_s2u(int16, (uchar16)(k={0-63}));
#endif

VGSATSUD
ulong = __saturate_s2u(long, (uchar)(k={0-63}));
ulong2 = __saturate_s2u(long2, (uchar2)(k={0-63}));
ulong3 = __saturate_s2u(long3, (uchar3)(k={0-63}));
ulong4 = __saturate_s2u(long4, (uchar4)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __saturate_s2u(long8, (uchar8)(k={0-63}));
#endif

*/

#define __saturate_s2u(a,b) __overload("__saturate_s2u",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __scale                                                                */
/*----------------------------------------------------------------------------*/
/*

VSCALESP
float = __scale(float, uint);
float2 = __scale(float2, uint2);
float3 = __scale(float3, uint3);
float4 = __scale(float4, uint4);
float8 = __scale(float8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __scale(float16, uint16);
#endif

VSCALEDP
double = __scale(double, ulong);
double2 = __scale(double2, ulong2);
double3 = __scale(double3, ulong3);
double4 = __scale(double4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = __scale(double8, ulong8);
#endif

*/

#define __scale(a,b) __overload("__scale",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __select                                                               */
/*----------------------------------------------------------------------------*/
/*

VSEL
char2 = __select(bool2, char2, char2);
char3 = __select(bool3, char3, char3);
char4 = __select(bool4, char4, char4);
char8 = __select(bool8, char8, char8);
char16 = __select(bool16, char16, char16);
char32 = __select(bool32, char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __select(bool64, char64, char64);
#endif
uchar2 = __select(bool2, uchar2, uchar2);
uchar3 = __select(bool3, uchar3, uchar3);
uchar4 = __select(bool4, uchar4, uchar4);
uchar8 = __select(bool8, uchar8, uchar8);
uchar16 = __select(bool16, uchar16, uchar16);
uchar32 = __select(bool32, uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __select(bool64, uchar64, uchar64);
#endif
cchar2 = __select(bool2, cchar2, cchar2);
cchar4 = __select(bool4, cchar4, cchar4);
cchar8 = __select(bool8, cchar8, cchar8);
cchar16 = __select(bool16, cchar16, cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = __select(bool32, cchar32, cchar32);
#endif
short2 = __select(bool2, short2, short2);
short3 = __select(bool3, short3, short3);
short4 = __select(bool4, short4, short4);
short8 = __select(bool8, short8, short8);
short16 = __select(bool16, short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __select(bool32, short32, short32);
#endif
ushort2 = __select(bool2, ushort2, ushort2);
ushort3 = __select(bool3, ushort3, ushort3);
ushort4 = __select(bool4, ushort4, ushort4);
ushort8 = __select(bool8, ushort8, ushort8);
ushort16 = __select(bool16, ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __select(bool32, ushort32, ushort32);
#endif
cshort2 = __select(bool2, cshort2, cshort2);
cshort4 = __select(bool4, cshort4, cshort4);
cshort8 = __select(bool8, cshort8, cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = __select(bool16, cshort16, cshort16);
#endif
int2 = __select(bool2, int2, int2);
int2 = __select(bool2, int2, (int2)(k));
int3 = __select(bool3, int3, int3);
int3 = __select(bool3, int3, (int3)(k));
int4 = __select(bool4, int4, int4);
int4 = __select(bool4, int4, (int4)(k));
int8 = __select(bool8, int8, int8);
int8 = __select(bool8, int8, (int8)(k));
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __select(bool16, int16, int16);
int16 = __select(bool16, int16, (int16)(k));
#endif
uint2 = __select(bool2, uint2, uint2);
uint2 = __select(bool2, uint2, (uint2)(k));
uint3 = __select(bool3, uint3, uint3);
uint3 = __select(bool3, uint3, (uint3)(k));
uint4 = __select(bool4, uint4, uint4);
uint4 = __select(bool4, uint4, (uint4)(k));
uint8 = __select(bool8, uint8, uint8);
uint8 = __select(bool8, uint8, (uint8)(k));
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __select(bool16, uint16, uint16);
uint16 = __select(bool16, uint16, (uint16)(k));
#endif
float2 = __select(bool2, float2, float2);
float2 = __select(bool2, float2, (float2)(k));
float3 = __select(bool3, float3, float3);
float3 = __select(bool3, float3, (float3)(k));
float4 = __select(bool4, float4, float4);
float4 = __select(bool4, float4, (float4)(k));
float8 = __select(bool8, float8, float8);
float8 = __select(bool8, float8, (float8)(k));
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __select(bool16, float16, float16);
float16 = __select(bool16, float16, (float16)(k));
#endif
cint2 = __select(bool2, cint2, cint2);
cint4 = __select(bool4, cint4, cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __select(bool8, cint8, cint8);
#endif
cfloat2 = __select(bool2, cfloat2, cfloat2);
cfloat4 = __select(bool4, cfloat4, cfloat4);
#if __C7X_VEC_SIZE_BITS__ == 512
cfloat8 = __select(bool8, cfloat8, cfloat8);
#endif
long2 = __select(bool2, long2, long2);
long3 = __select(bool3, long3, long3);
long4 = __select(bool4, long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __select(bool8, long8, long8);
#endif
ulong2 = __select(bool2, ulong2, ulong2);
ulong3 = __select(bool3, ulong3, ulong3);
ulong4 = __select(bool4, ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __select(bool8, ulong8, ulong8);
#endif
double2 = __select(bool2, double2, double2);
double3 = __select(bool3, double3, double3);
double4 = __select(bool4, double4, double4);
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = __select(bool8, double8, double8);
#endif
clong2 = __select(bool2, clong2, clong2);
#if __C7X_VEC_SIZE_BITS__ == 512
clong4 = __select(bool4, clong4, clong4);
#endif
cdouble2 = __select(bool2, cdouble2, cdouble2);
#if __C7X_VEC_SIZE_BITS__ == 512
cdouble4 = __select(bool4, cdouble4, cdouble4);
#endif

*/

#define __select(a,b,c) __overload("__select",(a),(b),(c))((a),(b),(c))

/*----------------------------------------------------------------------------*/
/* ID: __set                                                                  */
/*----------------------------------------------------------------------------*/
/*

SET
int = __set(int, int);

*/

/*----------------------------------------------------------------------------*/
/* ID: __shift_left                                                           */
/*----------------------------------------------------------------------------*/
/*

VSHLB
signed char = __shift_left(signed char, (signed char)(k={0-63}));
char2 = __shift_left(char2, (char2)(k={0-63}));
char3 = __shift_left(char3, (char3)(k={0-63}));
char4 = __shift_left(char4, (char4)(k={0-63}));
char8 = __shift_left(char8, (char8)(k={0-63}));
char16 = __shift_left(char16, (char16)(k={0-63}));
char32 = __shift_left(char32, (char32)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __shift_left(char64, (char64)(k={0-63}));
#endif
char4 = __shift_left(char4, int);
char8 = __shift_left(char8, int2);
char16 = __shift_left(char16, int4);
char32 = __shift_left(char32, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __shift_left(char64, int16);
#endif
uchar = __shift_left(uchar, (uchar)(k={0-63}));
uchar2 = __shift_left(uchar2, (uchar2)(k={0-63}));
uchar3 = __shift_left(uchar3, (uchar3)(k={0-63}));
uchar4 = __shift_left(uchar4, (uchar4)(k={0-63}));
uchar8 = __shift_left(uchar8, (uchar8)(k={0-63}));
uchar16 = __shift_left(uchar16, (uchar16)(k={0-63}));
uchar32 = __shift_left(uchar32, (uchar32)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __shift_left(uchar64, (uchar64)(k={0-63}));
#endif
uchar4 = __shift_left(uchar4, uint);
uchar8 = __shift_left(uchar8, uint2);
uchar16 = __shift_left(uchar16, uint4);
uchar32 = __shift_left(uchar32, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __shift_left(uchar64, uint16);
#endif

VSHLH
short = __shift_left(short, (short)(k={0-63}));
short2 = __shift_left(short2, (short2)(k={0-63}));
short3 = __shift_left(short3, (short3)(k={0-63}));
short4 = __shift_left(short4, (short4)(k={0-63}));
short8 = __shift_left(short8, (short8)(k={0-63}));
short16 = __shift_left(short16, (short16)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __shift_left(short32, (short32)(k={0-63}));
#endif
short2 = __shift_left(short2, int);
short4 = __shift_left(short4, int2);
short8 = __shift_left(short8, int4);
short16 = __shift_left(short16, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __shift_left(short32, int16);
#endif
ushort = __shift_left(ushort, (ushort)(k={0-63}));
ushort2 = __shift_left(ushort2, (ushort2)(k={0-63}));
ushort3 = __shift_left(ushort3, (ushort3)(k={0-63}));
ushort4 = __shift_left(ushort4, (ushort4)(k={0-63}));
ushort8 = __shift_left(ushort8, (ushort8)(k={0-63}));
ushort16 = __shift_left(ushort16, (ushort16)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __shift_left(ushort32, (ushort32)(k={0-63}));
#endif
ushort2 = __shift_left(ushort2, uint);
ushort4 = __shift_left(ushort4, uint2);
ushort8 = __shift_left(ushort8, uint4);
ushort16 = __shift_left(ushort16, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __shift_left(ushort32, uint16);
#endif

SHLW
int = __shift_left(int, (uchar)(k={0-63}));

SHLW, VSHLW
int = __shift_left(int, int);
int = __shift_left(int, (int)(k));
int2 = __shift_left(int2, int2);
int2 = __shift_left(int2, (int2)(k));
int3 = __shift_left(int3, int3);
int3 = __shift_left(int3, (int3)(k));
int4 = __shift_left(int4, int4);
int4 = __shift_left(int4, (int4)(k));
int8 = __shift_left(int8, int8);
int8 = __shift_left(int8, (int8)(k));
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __shift_left(int16, int16);
int16 = __shift_left(int16, (int16)(k));
#endif

SHLW
uint = __shift_left(uint, (uchar)(k={0-63}));

SHLW, VSHLW
uint = __shift_left(uint, uint);
uint = __shift_left(uint, (uint)(k));
uint2 = __shift_left(uint2, uint2);
uint2 = __shift_left(uint2, (uint2)(k));
uint3 = __shift_left(uint3, uint3);
uint3 = __shift_left(uint3, (uint3)(k));
uint4 = __shift_left(uint4, uint4);
uint4 = __shift_left(uint4, (uint4)(k));
uint8 = __shift_left(uint8, uint8);
uint8 = __shift_left(uint8, (uint8)(k));
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __shift_left(uint16, uint16);
uint16 = __shift_left(uint16, (uint16)(k));
#endif

SHLD
long = __shift_left(long, (uchar)(k={0-63}));
long = __shift_left(long, int);

VSHLD
long = __shift_left(long, long);
long = __shift_left(long, (long)(k));
long2 = __shift_left(long2, long2);
long2 = __shift_left(long2, (long2)(k));
long3 = __shift_left(long3, long3);
long3 = __shift_left(long3, (long3)(k));
long4 = __shift_left(long4, long4);
long4 = __shift_left(long4, (long4)(k));
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __shift_left(long8, long8);
long8 = __shift_left(long8, (long8)(k));
#endif

SHLD
ulong = __shift_left(ulong, (uchar)(k={0-63}));
ulong = __shift_left(ulong, uint);

VSHLD
ulong = __shift_left(ulong, ulong);
ulong = __shift_left(ulong, (ulong)(k));
ulong2 = __shift_left(ulong2, ulong2);
ulong2 = __shift_left(ulong2, (ulong2)(k));
ulong3 = __shift_left(ulong3, ulong3);
ulong3 = __shift_left(ulong3, (ulong3)(k));
ulong4 = __shift_left(ulong4, ulong4);
ulong4 = __shift_left(ulong4, (ulong4)(k));
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __shift_left(ulong8, ulong8);
ulong8 = __shift_left(ulong8, (ulong8)(k));
#endif

*/

#define __shift_left(a,b) __overload("__shift_left",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __shift_left_conditional                                               */
/*----------------------------------------------------------------------------*/
/*

VSHLCB
char2 = __shift_left_conditional(bool2, char2, char2);
char3 = __shift_left_conditional(bool3, char3, char3);
char4 = __shift_left_conditional(bool4, char4, char4);
char8 = __shift_left_conditional(bool8, char8, char8);
char16 = __shift_left_conditional(bool16, char16, char16);
char32 = __shift_left_conditional(bool32, char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __shift_left_conditional(bool64, char64, char64);
#endif
uchar2 = __shift_left_conditional(bool2, uchar2, uchar2);
uchar3 = __shift_left_conditional(bool3, uchar3, uchar3);
uchar4 = __shift_left_conditional(bool4, uchar4, uchar4);
uchar8 = __shift_left_conditional(bool8, uchar8, uchar8);
uchar16 = __shift_left_conditional(bool16, uchar16, uchar16);
uchar32 = __shift_left_conditional(bool32, uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __shift_left_conditional(bool64, uchar64, uchar64);
#endif

VSHLCH
short2 = __shift_left_conditional(bool2, short2, short2);
short3 = __shift_left_conditional(bool3, short3, short3);
short4 = __shift_left_conditional(bool4, short4, short4);
short8 = __shift_left_conditional(bool8, short8, short8);
short16 = __shift_left_conditional(bool16, short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __shift_left_conditional(bool32, short32, short32);
#endif
ushort2 = __shift_left_conditional(bool2, ushort2, ushort2);
ushort3 = __shift_left_conditional(bool3, ushort3, ushort3);
ushort4 = __shift_left_conditional(bool4, ushort4, ushort4);
ushort8 = __shift_left_conditional(bool8, ushort8, ushort8);
ushort16 = __shift_left_conditional(bool16, ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __shift_left_conditional(bool32, ushort32, ushort32);
#endif

VSHLCW
int2 = __shift_left_conditional(bool2, int2, int2);
int3 = __shift_left_conditional(bool3, int3, int3);
int4 = __shift_left_conditional(bool4, int4, int4);
int8 = __shift_left_conditional(bool8, int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __shift_left_conditional(bool16, int16, int16);
#endif
uint2 = __shift_left_conditional(bool2, uint2, uint2);
uint3 = __shift_left_conditional(bool3, uint3, uint3);
uint4 = __shift_left_conditional(bool4, uint4, uint4);
uint8 = __shift_left_conditional(bool8, uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __shift_left_conditional(bool16, uint16, uint16);
#endif

*/

#define __shift_left_conditional(a,b,c) __overload("__shift_left_conditional",(a),(b),(c))((a),(b),(c))

/*----------------------------------------------------------------------------*/
/* ID: __shift_left_full                                                      */
/*----------------------------------------------------------------------------*/
/*

VSHL
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __shift_left_full(ulong8, (uchar)(k={1-64}));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ulong4 = __shift_left_full(ulong4, (uchar)(k={1-64}));
ulong4 = __shift_left_full(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __shift_left_full(ulong8, ulong8);
#endif

*/

#define __shift_left_full(a,b) __overload("__shift_left_full",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __shift_left_merge                                                     */
/*----------------------------------------------------------------------------*/
/*

VSHLM1B
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __shift_left_merge(char64, signed char);
#endif

VSHLM1B, VSHLM2B
#if __C7X_VEC_SIZE_BITS__ == 256
char32 = __shift_left_merge(char32, signed char);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __shift_left_merge(char64, char2);
#endif

VSHLM2B, VSHLM4B
#if __C7X_VEC_SIZE_BITS__ == 256
char32 = __shift_left_merge(char32, char2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __shift_left_merge(char64, char4);
#endif

VSHLM4B, VSHLM8B
#if __C7X_VEC_SIZE_BITS__ == 256
char32 = __shift_left_merge(char32, char4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __shift_left_merge(char64, char8);
#endif

VSHLM16B, VSHLM8B
#if __C7X_VEC_SIZE_BITS__ == 256
char32 = __shift_left_merge(char32, char8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __shift_left_merge(char64, char16);
#endif

VSHLM16B
#if __C7X_VEC_SIZE_BITS__ == 256
char32 = __shift_left_merge(char32, char16);
#endif

VSHLMB
int = __shift_left_merge(int, char4);
int2 = __shift_left_merge(int2, char8);
int4 = __shift_left_merge(int4, char16);
int8 = __shift_left_merge(int8, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __shift_left_merge(int16, char64);
#endif

*/

#define __shift_left_merge(a,b) __overload("__shift_left_merge",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __shift_left_round_sat                                                 */
/*----------------------------------------------------------------------------*/
/*

VSSHLRHB
char4 = __shift_left_round_sat(short2, (uchar)(k={0-63}));
char8 = __shift_left_round_sat(short4, (uchar2)(k={0-63}));
char16 = __shift_left_round_sat(short8, (uchar4)(k={0-63}));
char32 = __shift_left_round_sat(short16, (uchar8)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __shift_left_round_sat(short32, (uchar16)(k={0-63}));
#endif
char4 = __shift_left_round_sat(short2, uint);
char8 = __shift_left_round_sat(short4, uint2);
char16 = __shift_left_round_sat(short8, uint4);
char32 = __shift_left_round_sat(short16, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __shift_left_round_sat(short32, uint16);
#endif

VSSHLURHB
uchar4 = __shift_left_round_sat(ushort2, (uchar)(k={0-63}));
uchar8 = __shift_left_round_sat(ushort4, (uchar2)(k={0-63}));
uchar16 = __shift_left_round_sat(ushort8, (uchar4)(k={0-63}));
uchar32 = __shift_left_round_sat(ushort16, (uchar8)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __shift_left_round_sat(ushort32, (uchar16)(k={0-63}));
#endif
uchar4 = __shift_left_round_sat(ushort2, uint);
uchar8 = __shift_left_round_sat(ushort4, uint2);
uchar16 = __shift_left_round_sat(ushort8, uint4);
uchar32 = __shift_left_round_sat(ushort16, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __shift_left_round_sat(ushort32, uint16);
#endif

VSSHLRWH
short2 = __shift_left_round_sat(int, (uchar)(k={0-63}));
short4 = __shift_left_round_sat(int2, (uchar2)(k={0-63}));
short8 = __shift_left_round_sat(int4, (uchar4)(k={0-63}));
short16 = __shift_left_round_sat(int8, (uchar8)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __shift_left_round_sat(int16, (uchar16)(k={0-63}));
#endif
short2 = __shift_left_round_sat(int, uint);
short4 = __shift_left_round_sat(int2, uint2);
short8 = __shift_left_round_sat(int4, uint4);
short16 = __shift_left_round_sat(int8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __shift_left_round_sat(int16, uint16);
#endif

VSSHLURWH
ushort2 = __shift_left_round_sat(uint, (uchar)(k={0-63}));
ushort4 = __shift_left_round_sat(uint2, (uchar2)(k={0-63}));
ushort8 = __shift_left_round_sat(uint4, (uchar4)(k={0-63}));
ushort16 = __shift_left_round_sat(uint8, (uchar8)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __shift_left_round_sat(uint16, (uchar16)(k={0-63}));
#endif
ushort2 = __shift_left_round_sat(uint, uint);
ushort4 = __shift_left_round_sat(uint2, uint2);
ushort8 = __shift_left_round_sat(uint4, uint4);
ushort16 = __shift_left_round_sat(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __shift_left_round_sat(uint16, uint16);
#endif

VSSHLRDW
int2 = __shift_left_round_sat(long, (uchar)(k={0-63}));
int4 = __shift_left_round_sat(long2, (uchar2)(k={0-63}));
int8 = __shift_left_round_sat(long4, (uchar4)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __shift_left_round_sat(long8, (uchar8)(k={0-63}));
#endif
int2 = __shift_left_round_sat(long, ulong);
int4 = __shift_left_round_sat(long2, ulong2);
int8 = __shift_left_round_sat(long4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __shift_left_round_sat(long8, ulong8);
#endif

VSSHLURDW
uint2 = __shift_left_round_sat(ulong, (uchar)(k={0-63}));
uint4 = __shift_left_round_sat(ulong2, (uchar2)(k={0-63}));
uint8 = __shift_left_round_sat(ulong4, (uchar4)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __shift_left_round_sat(ulong8, (uchar8)(k={0-63}));
#endif
uint2 = __shift_left_round_sat(ulong, ulong);
uint4 = __shift_left_round_sat(ulong2, ulong2);
uint8 = __shift_left_round_sat(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __shift_left_round_sat(ulong8, ulong8);
#endif

*/

#define __shift_left_round_sat(a,b) __overload("__shift_left_round_sat",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __shift_left_round_sat_to_unsigned                                     */
/*----------------------------------------------------------------------------*/
/*

VSSHLSURHB
uchar4 = __shift_left_round_sat_to_unsigned(short2, (uchar)(k={0-63}));
uchar8 = __shift_left_round_sat_to_unsigned(short4, (uchar2)(k={0-63}));
uchar16 = __shift_left_round_sat_to_unsigned(short8, (uchar4)(k={0-63}));
uchar32 = __shift_left_round_sat_to_unsigned(short16, (uchar8)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __shift_left_round_sat_to_unsigned(short32, (uchar16)(k={0-63}));
#endif
uchar4 = __shift_left_round_sat_to_unsigned(short2, uint);
uchar8 = __shift_left_round_sat_to_unsigned(short4, uint2);
uchar16 = __shift_left_round_sat_to_unsigned(short8, uint4);
uchar32 = __shift_left_round_sat_to_unsigned(short16, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __shift_left_round_sat_to_unsigned(short32, uint16);
#endif

VSSHLSURWH
ushort2 = __shift_left_round_sat_to_unsigned(int, (uchar)(k={0-63}));
ushort4 = __shift_left_round_sat_to_unsigned(int2, (uchar2)(k={0-63}));
ushort8 = __shift_left_round_sat_to_unsigned(int4, (uchar4)(k={0-63}));
ushort16 = __shift_left_round_sat_to_unsigned(int8, (uchar8)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __shift_left_round_sat_to_unsigned(int16, (uchar16)(k={0-63}));
#endif
ushort2 = __shift_left_round_sat_to_unsigned(int, uint);
ushort4 = __shift_left_round_sat_to_unsigned(int2, uint2);
ushort8 = __shift_left_round_sat_to_unsigned(int4, uint4);
ushort16 = __shift_left_round_sat_to_unsigned(int8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __shift_left_round_sat_to_unsigned(int16, uint16);
#endif

VSSHLSURDW
uint2 = __shift_left_round_sat_to_unsigned(long, (uchar)(k={0-63}));
uint4 = __shift_left_round_sat_to_unsigned(long2, (uchar2)(k={0-63}));
uint8 = __shift_left_round_sat_to_unsigned(long4, (uchar4)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __shift_left_round_sat_to_unsigned(long8, (uchar8)(k={0-63}));
#endif
uint2 = __shift_left_round_sat_to_unsigned(long, ulong);
uint4 = __shift_left_round_sat_to_unsigned(long2, ulong2);
uint8 = __shift_left_round_sat_to_unsigned(long4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __shift_left_round_sat_to_unsigned(long8, ulong8);
#endif

*/

#define __shift_left_round_sat_to_unsigned(a,b) __overload("__shift_left_round_sat_to_unsigned",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __shift_left_sat                                                       */
/*----------------------------------------------------------------------------*/
/*

VSSHLH
short = __shift_left_sat(short, (uchar)(k={0-63}));
short2 = __shift_left_sat(short2, (uchar2)(k={0-63}));
short3 = __shift_left_sat(short3, (uchar3)(k={0-63}));
short4 = __shift_left_sat(short4, (uchar4)(k={0-63}));
short8 = __shift_left_sat(short8, (uchar8)(k={0-63}));
short16 = __shift_left_sat(short16, (uchar16)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __shift_left_sat(short32, (uchar32)(k={0-63}));
#endif
short2 = __shift_left_sat(short2, uint);
short4 = __shift_left_sat(short4, uint2);
short8 = __shift_left_sat(short8, uint4);
short16 = __shift_left_sat(short16, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __shift_left_sat(short32, uint16);
#endif

VSSHLUH
ushort = __shift_left_sat(ushort, (uchar)(k={0-63}));
ushort2 = __shift_left_sat(ushort2, (uchar2)(k={0-63}));
ushort3 = __shift_left_sat(ushort3, (uchar3)(k={0-63}));
ushort4 = __shift_left_sat(ushort4, (uchar4)(k={0-63}));
ushort8 = __shift_left_sat(ushort8, (uchar8)(k={0-63}));
ushort16 = __shift_left_sat(ushort16, (uchar16)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __shift_left_sat(ushort32, (uchar32)(k={0-63}));
#endif
ushort2 = __shift_left_sat(ushort2, uint);
ushort4 = __shift_left_sat(ushort4, uint2);
ushort8 = __shift_left_sat(ushort8, uint4);
ushort16 = __shift_left_sat(ushort16, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __shift_left_sat(ushort32, uint16);
#endif

VSSHLW
int = __shift_left_sat(int, (uchar)(k={0-63}));
int2 = __shift_left_sat(int2, (uchar2)(k={0-63}));
int3 = __shift_left_sat(int3, (uchar3)(k={0-63}));
int4 = __shift_left_sat(int4, (uchar4)(k={0-63}));
int8 = __shift_left_sat(int8, (uchar8)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __shift_left_sat(int16, (uchar16)(k={0-63}));
#endif
int = __shift_left_sat(int, uint);
int2 = __shift_left_sat(int2, uint2);
int3 = __shift_left_sat(int3, uint3);
int4 = __shift_left_sat(int4, uint4);
int8 = __shift_left_sat(int8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __shift_left_sat(int16, uint16);
#endif

VSSHLUW
uint = __shift_left_sat(uint, (uchar)(k={0-63}));
uint2 = __shift_left_sat(uint2, (uchar2)(k={0-63}));
uint3 = __shift_left_sat(uint3, (uchar3)(k={0-63}));
uint4 = __shift_left_sat(uint4, (uchar4)(k={0-63}));
uint8 = __shift_left_sat(uint8, (uchar8)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __shift_left_sat(uint16, (uchar16)(k={0-63}));
#endif
uint = __shift_left_sat(uint, uint);
uint2 = __shift_left_sat(uint2, uint2);
uint3 = __shift_left_sat(uint3, uint3);
uint4 = __shift_left_sat(uint4, uint4);
uint8 = __shift_left_sat(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __shift_left_sat(uint16, uint16);
#endif

*/

#define __shift_left_sat(a,b) __overload("__shift_left_sat",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __shift_left_sat_to_unsigned                                           */
/*----------------------------------------------------------------------------*/
/*

VSSHLSUH
ushort = __shift_left_sat_to_unsigned(short, (uchar)(k={0-63}));
ushort2 = __shift_left_sat_to_unsigned(short2, (uchar2)(k={0-63}));
ushort3 = __shift_left_sat_to_unsigned(short3, (uchar3)(k={0-63}));
ushort4 = __shift_left_sat_to_unsigned(short4, (uchar4)(k={0-63}));
ushort8 = __shift_left_sat_to_unsigned(short8, (uchar8)(k={0-63}));
ushort16 = __shift_left_sat_to_unsigned(short16, (uchar16)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __shift_left_sat_to_unsigned(short32, (uchar32)(k={0-63}));
#endif
ushort2 = __shift_left_sat_to_unsigned(short2, uint);
ushort4 = __shift_left_sat_to_unsigned(short4, uint2);
ushort8 = __shift_left_sat_to_unsigned(short8, uint4);
ushort16 = __shift_left_sat_to_unsigned(short16, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __shift_left_sat_to_unsigned(short32, uint16);
#endif

VSSHLSUW
uint = __shift_left_sat_to_unsigned(int, (uchar)(k={0-63}));
uint2 = __shift_left_sat_to_unsigned(int2, (uchar2)(k={0-63}));
uint3 = __shift_left_sat_to_unsigned(int3, (uchar3)(k={0-63}));
uint4 = __shift_left_sat_to_unsigned(int4, (uchar4)(k={0-63}));
uint8 = __shift_left_sat_to_unsigned(int8, (uchar8)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __shift_left_sat_to_unsigned(int16, (uchar16)(k={0-63}));
#endif
uint = __shift_left_sat_to_unsigned(int, uint);
uint2 = __shift_left_sat_to_unsigned(int2, uint2);
uint3 = __shift_left_sat_to_unsigned(int3, uint3);
uint4 = __shift_left_sat_to_unsigned(int4, uint4);
uint8 = __shift_left_sat_to_unsigned(int8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __shift_left_sat_to_unsigned(int16, uint16);
#endif

*/

#define __shift_left_sat_to_unsigned(a,b) __overload("__shift_left_sat_to_unsigned",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __shift_left_var                                                       */
/*----------------------------------------------------------------------------*/
/*

VSHVLW
int = __shift_left_var(int, int);
int2 = __shift_left_var(int2, int2);
int3 = __shift_left_var(int3, int3);
int4 = __shift_left_var(int4, int4);
int8 = __shift_left_var(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __shift_left_var(int16, int16);
#endif

VSHVLUW
uint = __shift_left_var(uint, int);
uint2 = __shift_left_var(uint2, int2);
uint3 = __shift_left_var(uint3, int3);
uint4 = __shift_left_var(uint4, int4);
uint8 = __shift_left_var(uint8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __shift_left_var(uint16, int16);
#endif

*/

#define __shift_left_var(a,b) __overload("__shift_left_var",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __shift_left_var_sat                                                   */
/*----------------------------------------------------------------------------*/
/*

VSSHVLW
int = __shift_left_var_sat(int, int);
int2 = __shift_left_var_sat(int2, int2);
int3 = __shift_left_var_sat(int3, int3);
int4 = __shift_left_var_sat(int4, int4);
int8 = __shift_left_var_sat(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __shift_left_var_sat(int16, int16);
#endif

*/

#define __shift_left_var_sat(a,b) __overload("__shift_left_var_sat",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __shift_right                                                          */
/*----------------------------------------------------------------------------*/
/*

VSHRB
signed char = __shift_right(signed char, (signed char)(k={0-63}));
char2 = __shift_right(char2, (char2)(k={0-63}));
char3 = __shift_right(char3, (char3)(k={0-63}));
char4 = __shift_right(char4, (char4)(k={0-63}));
char8 = __shift_right(char8, (char8)(k={0-63}));
char16 = __shift_right(char16, (char16)(k={0-63}));
char32 = __shift_right(char32, (char32)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __shift_right(char64, (char64)(k={0-63}));
#endif
char4 = __shift_right(char4, int);
char8 = __shift_right(char8, int2);
char16 = __shift_right(char16, int4);
char32 = __shift_right(char32, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __shift_right(char64, int16);
#endif

VSHRUB
uchar = __shift_right(uchar, (uchar)(k={0-63}));
uchar2 = __shift_right(uchar2, (uchar2)(k={0-63}));
uchar3 = __shift_right(uchar3, (uchar3)(k={0-63}));
uchar4 = __shift_right(uchar4, (uchar4)(k={0-63}));
uchar8 = __shift_right(uchar8, (uchar8)(k={0-63}));
uchar16 = __shift_right(uchar16, (uchar16)(k={0-63}));
uchar32 = __shift_right(uchar32, (uchar32)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __shift_right(uchar64, (uchar64)(k={0-63}));
#endif
uchar4 = __shift_right(uchar4, uint);
uchar8 = __shift_right(uchar8, uint2);
uchar16 = __shift_right(uchar16, uint4);
uchar32 = __shift_right(uchar32, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __shift_right(uchar64, uint16);
#endif

VSHRH
short = __shift_right(short, (short)(k={0-63}));
short2 = __shift_right(short2, (short2)(k={0-63}));
short3 = __shift_right(short3, (short3)(k={0-63}));
short4 = __shift_right(short4, (short4)(k={0-63}));
short8 = __shift_right(short8, (short8)(k={0-63}));
short16 = __shift_right(short16, (short16)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __shift_right(short32, (short32)(k={0-63}));
#endif
short2 = __shift_right(short2, int);
short4 = __shift_right(short4, int2);
short8 = __shift_right(short8, int4);
short16 = __shift_right(short16, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __shift_right(short32, int16);
#endif

VSHRUH
ushort = __shift_right(ushort, (ushort)(k={0-63}));
ushort2 = __shift_right(ushort2, (ushort2)(k={0-63}));
ushort3 = __shift_right(ushort3, (ushort3)(k={0-63}));
ushort4 = __shift_right(ushort4, (ushort4)(k={0-63}));
ushort8 = __shift_right(ushort8, (ushort8)(k={0-63}));
ushort16 = __shift_right(ushort16, (ushort16)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __shift_right(ushort32, (ushort32)(k={0-63}));
#endif
ushort2 = __shift_right(ushort2, uint);
ushort4 = __shift_right(ushort4, uint2);
ushort8 = __shift_right(ushort8, uint4);
ushort16 = __shift_right(ushort16, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __shift_right(ushort32, uint16);
#endif

SHRW
int = __shift_right(int, (uchar)(k={0-63}));

SHRW, VSHRW
int = __shift_right(int, int);
int = __shift_right(int, (int)(k));
int2 = __shift_right(int2, int2);
int2 = __shift_right(int2, (int2)(k));
int3 = __shift_right(int3, int3);
int3 = __shift_right(int3, (int3)(k));
int4 = __shift_right(int4, int4);
int4 = __shift_right(int4, (int4)(k));
int8 = __shift_right(int8, int8);
int8 = __shift_right(int8, (int8)(k));
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __shift_right(int16, int16);
int16 = __shift_right(int16, (int16)(k));
#endif

SHRUW
uint = __shift_right(uint, (uchar)(k={0-63}));

SHRUW, VSHRUW
uint = __shift_right(uint, uint);
uint = __shift_right(uint, (uint)(k));
uint2 = __shift_right(uint2, uint2);
uint2 = __shift_right(uint2, (uint2)(k));
uint3 = __shift_right(uint3, uint3);
uint3 = __shift_right(uint3, (uint3)(k));
uint4 = __shift_right(uint4, uint4);
uint4 = __shift_right(uint4, (uint4)(k));
uint8 = __shift_right(uint8, uint8);
uint8 = __shift_right(uint8, (uint8)(k));
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __shift_right(uint16, uint16);
uint16 = __shift_right(uint16, (uint16)(k));
#endif

SHRD
long = __shift_right(long, (uchar)(k={0-63}));
long = __shift_right(long, int);

VSHRD
long = __shift_right(long, long);
long = __shift_right(long, (long)(k));
long2 = __shift_right(long2, long2);
long2 = __shift_right(long2, (long2)(k));
long3 = __shift_right(long3, long3);
long3 = __shift_right(long3, (long3)(k));
long4 = __shift_right(long4, long4);
long4 = __shift_right(long4, (long4)(k));
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __shift_right(long8, long8);
long8 = __shift_right(long8, (long8)(k));
#endif

SHRUD
ulong = __shift_right(ulong, (uchar)(k={0-63}));
ulong = __shift_right(ulong, uint);

VSHRUD
ulong = __shift_right(ulong, ulong);
ulong = __shift_right(ulong, (ulong)(k));
ulong2 = __shift_right(ulong2, ulong2);
ulong2 = __shift_right(ulong2, (ulong2)(k));
ulong3 = __shift_right(ulong3, ulong3);
ulong3 = __shift_right(ulong3, (ulong3)(k));
ulong4 = __shift_right(ulong4, ulong4);
ulong4 = __shift_right(ulong4, (ulong4)(k));
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __shift_right(ulong8, ulong8);
ulong8 = __shift_right(ulong8, (ulong8)(k));
#endif

*/

#define __shift_right(a,b) __overload("__shift_right",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __shift_right_full                                                     */
/*----------------------------------------------------------------------------*/
/*

VSHR
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __shift_right_full(long8, (uchar)(k={1-64}));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long4 = __shift_right_full(long4, (uchar)(k={1-64}));
long4 = __shift_right_full(long4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __shift_right_full(long8, ulong8);
#endif

VSHRU
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __shift_right_full(ulong8, (uchar)(k={1-64}));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ulong4 = __shift_right_full(ulong4, (uchar)(k={1-64}));
ulong4 = __shift_right_full(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __shift_right_full(ulong8, ulong8);
#endif

*/

#define __shift_right_full(a,b) __overload("__shift_right_full",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __shift_right_merge                                                    */
/*----------------------------------------------------------------------------*/
/*

VSHRM1B
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __shift_right_merge(char64, signed char);
#endif

VSHRM1B, VSHRM2B
#if __C7X_VEC_SIZE_BITS__ == 256
char32 = __shift_right_merge(char32, signed char);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __shift_right_merge(char64, char2);
#endif

VSHRM2B, VSHRM4B
#if __C7X_VEC_SIZE_BITS__ == 256
char32 = __shift_right_merge(char32, char2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __shift_right_merge(char64, char4);
#endif

VSHRM4B, VSHRM8B
#if __C7X_VEC_SIZE_BITS__ == 256
char32 = __shift_right_merge(char32, char4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __shift_right_merge(char64, char8);
#endif

VSHRM16B, VSHRM8B
#if __C7X_VEC_SIZE_BITS__ == 256
char32 = __shift_right_merge(char32, char8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __shift_right_merge(char64, char16);
#endif

VSHRM16B
#if __C7X_VEC_SIZE_BITS__ == 256
char32 = __shift_right_merge(char32, char16);
#endif

VSHRMB
int = __shift_right_merge(int, char4);
int2 = __shift_right_merge(int2, char8);
int4 = __shift_right_merge(int4, char16);
int8 = __shift_right_merge(int8, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __shift_right_merge(int16, char64);
#endif

*/

#define __shift_right_merge(a,b) __overload("__shift_right_merge",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __shift_right_round                                                    */
/*----------------------------------------------------------------------------*/
/*

VSHRRB
signed char = __shift_right_round(signed char, (uchar)(k={0-63}));
char2 = __shift_right_round(char2, (uchar2)(k={0-63}));
char3 = __shift_right_round(char3, (uchar3)(k={0-63}));
char4 = __shift_right_round(char4, (uchar4)(k={0-63}));
char8 = __shift_right_round(char8, (uchar8)(k={0-63}));
char16 = __shift_right_round(char16, (uchar16)(k={0-63}));
char32 = __shift_right_round(char32, (uchar32)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __shift_right_round(char64, (uchar64)(k={0-63}));
#endif
char4 = __shift_right_round(char4, uint);
char8 = __shift_right_round(char8, uint2);
char16 = __shift_right_round(char16, uint4);
char32 = __shift_right_round(char32, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __shift_right_round(char64, uint16);
#endif

VSHRURB
uchar = __shift_right_round(uchar, (uchar)(k={0-63}));
uchar2 = __shift_right_round(uchar2, (uchar2)(k={0-63}));
uchar3 = __shift_right_round(uchar3, (uchar3)(k={0-63}));
uchar4 = __shift_right_round(uchar4, (uchar4)(k={0-63}));
uchar8 = __shift_right_round(uchar8, (uchar8)(k={0-63}));
uchar16 = __shift_right_round(uchar16, (uchar16)(k={0-63}));
uchar32 = __shift_right_round(uchar32, (uchar32)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __shift_right_round(uchar64, (uchar64)(k={0-63}));
#endif
uchar4 = __shift_right_round(uchar4, uint);
uchar8 = __shift_right_round(uchar8, uint2);
uchar16 = __shift_right_round(uchar16, uint4);
uchar32 = __shift_right_round(uchar32, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __shift_right_round(uchar64, uint16);
#endif

VSHRRH
short = __shift_right_round(short, (uchar)(k={0-63}));
short2 = __shift_right_round(short2, (uchar2)(k={0-63}));
short3 = __shift_right_round(short3, (uchar3)(k={0-63}));
short4 = __shift_right_round(short4, (uchar4)(k={0-63}));
short8 = __shift_right_round(short8, (uchar8)(k={0-63}));
short16 = __shift_right_round(short16, (uchar16)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __shift_right_round(short32, (uchar32)(k={0-63}));
#endif
short2 = __shift_right_round(short2, uint);
short4 = __shift_right_round(short4, uint2);
short8 = __shift_right_round(short8, uint4);
short16 = __shift_right_round(short16, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __shift_right_round(short32, uint16);
#endif

VSHRURH
ushort = __shift_right_round(ushort, (uchar)(k={0-63}));
ushort2 = __shift_right_round(ushort2, (uchar2)(k={0-63}));
ushort3 = __shift_right_round(ushort3, (uchar3)(k={0-63}));
ushort4 = __shift_right_round(ushort4, (uchar4)(k={0-63}));
ushort8 = __shift_right_round(ushort8, (uchar8)(k={0-63}));
ushort16 = __shift_right_round(ushort16, (uchar16)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __shift_right_round(ushort32, (uchar32)(k={0-63}));
#endif
ushort2 = __shift_right_round(ushort2, uint);
ushort4 = __shift_right_round(ushort4, uint2);
ushort8 = __shift_right_round(ushort8, uint4);
ushort16 = __shift_right_round(ushort16, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __shift_right_round(ushort32, uint16);
#endif

VSHRRW
int = __shift_right_round(int, (uchar)(k={0-63}));
int2 = __shift_right_round(int2, (uchar2)(k={0-63}));
int3 = __shift_right_round(int3, (uchar3)(k={0-63}));
int4 = __shift_right_round(int4, (uchar4)(k={0-63}));
int8 = __shift_right_round(int8, (uchar8)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __shift_right_round(int16, (uchar16)(k={0-63}));
#endif
int = __shift_right_round(int, uint);
int2 = __shift_right_round(int2, uint2);
int3 = __shift_right_round(int3, uint3);
int4 = __shift_right_round(int4, uint4);
int8 = __shift_right_round(int8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __shift_right_round(int16, uint16);
#endif

VSHRURW
uint = __shift_right_round(uint, (uchar)(k={0-63}));
uint2 = __shift_right_round(uint2, (uchar2)(k={0-63}));
uint3 = __shift_right_round(uint3, (uchar3)(k={0-63}));
uint4 = __shift_right_round(uint4, (uchar4)(k={0-63}));
uint8 = __shift_right_round(uint8, (uchar8)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __shift_right_round(uint16, (uchar16)(k={0-63}));
#endif
uint = __shift_right_round(uint, uint);
uint2 = __shift_right_round(uint2, uint2);
uint3 = __shift_right_round(uint3, uint3);
uint4 = __shift_right_round(uint4, uint4);
uint8 = __shift_right_round(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __shift_right_round(uint16, uint16);
#endif

VSHRRD
long = __shift_right_round(long, (uchar)(k={0-63}));
long2 = __shift_right_round(long2, (uchar2)(k={0-63}));
long3 = __shift_right_round(long3, (uchar3)(k={0-63}));
long4 = __shift_right_round(long4, (uchar4)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __shift_right_round(long8, (uchar8)(k={0-63}));
#endif
long = __shift_right_round(long, ulong);
long2 = __shift_right_round(long2, ulong2);
long3 = __shift_right_round(long3, ulong3);
long4 = __shift_right_round(long4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __shift_right_round(long8, ulong8);
#endif

VSHRURD
ulong = __shift_right_round(ulong, (uchar)(k={0-63}));
ulong2 = __shift_right_round(ulong2, (uchar2)(k={0-63}));
ulong3 = __shift_right_round(ulong3, (uchar3)(k={0-63}));
ulong4 = __shift_right_round(ulong4, (uchar4)(k={0-63}));
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __shift_right_round(ulong8, (uchar8)(k={0-63}));
#endif
ulong = __shift_right_round(ulong, ulong);
ulong2 = __shift_right_round(ulong2, ulong2);
ulong3 = __shift_right_round(ulong3, ulong3);
ulong4 = __shift_right_round(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __shift_right_round(ulong8, ulong8);
#endif

*/

#define __shift_right_round(a,b) __overload("__shift_right_round",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __shift_right_var                                                      */
/*----------------------------------------------------------------------------*/
/*

VSHVRW
int = __shift_right_var(int, int);
int2 = __shift_right_var(int2, int2);
int3 = __shift_right_var(int3, int3);
int4 = __shift_right_var(int4, int4);
int8 = __shift_right_var(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __shift_right_var(int16, int16);
#endif

VSHVRUW
uint = __shift_right_var(uint, int);
uint2 = __shift_right_var(uint2, int2);
uint3 = __shift_right_var(uint3, int3);
uint4 = __shift_right_var(uint4, int4);
uint8 = __shift_right_var(uint8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __shift_right_var(uint16, int16);
#endif

*/

#define __shift_right_var(a,b) __overload("__shift_right_var",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __shift_right_var_sat                                                  */
/*----------------------------------------------------------------------------*/
/*

VSSHVRW
int = __shift_right_var_sat(int, int);
int2 = __shift_right_var_sat(int2, int2);
int3 = __shift_right_var_sat(int3, int3);
int4 = __shift_right_var_sat(int4, int4);
int8 = __shift_right_var_sat(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __shift_right_var_sat(int16, int16);
#endif

*/

#define __shift_right_var_sat(a,b) __overload("__shift_right_var_sat",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __short_to_char_sat                                                    */
/*----------------------------------------------------------------------------*/
/*

VSATHB
short = __short_to_char_sat(short);
short2 = __short_to_char_sat(short2);
short3 = __short_to_char_sat(short3);
short4 = __short_to_char_sat(short4);
short8 = __short_to_char_sat(short8);
short16 = __short_to_char_sat(short16);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __short_to_char_sat(short32);
#endif

*/

#define __short_to_char_sat(a) __overload("__short_to_char_sat",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_3way                                                         */
/*----------------------------------------------------------------------------*/
/*

VSHFL3
long = __shuffle_3way(int2, int2);
long2 = __shuffle_3way(int4, int4);
long4 = __shuffle_3way(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __shuffle_3way(int16, int16);
#endif
ulong = __shuffle_3way(uint2, uint2);
ulong2 = __shuffle_3way(uint4, uint4);
ulong4 = __shuffle_3way(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __shuffle_3way(uint16, uint16);
#endif

*/

#define __shuffle_3way(a,b) __overload("__shuffle_3way",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_bit                                                          */
/*----------------------------------------------------------------------------*/
/*

VBITSHFLW
int = __shuffle_bit(int);
int2 = __shuffle_bit(int2);
int3 = __shuffle_bit(int3);
int4 = __shuffle_bit(int4);
int8 = __shuffle_bit(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __shuffle_bit(int16);
#endif
uint = __shuffle_bit(uint);
uint2 = __shuffle_bit(uint2);
uint3 = __shuffle_bit(uint3);
uint4 = __shuffle_bit(uint4);
uint8 = __shuffle_bit(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __shuffle_bit(uint16);
#endif

VBITSHFLD
long = __shuffle_bit(long);
long2 = __shuffle_bit(long2);
long3 = __shuffle_bit(long3);
long4 = __shuffle_bit(long4);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __shuffle_bit(long8);
#endif
ulong = __shuffle_bit(ulong);
ulong2 = __shuffle_bit(ulong2);
ulong3 = __shuffle_bit(ulong3);
ulong4 = __shuffle_bit(ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __shuffle_bit(ulong8);
#endif

*/

#define __shuffle_bit(a) __overload("__shuffle_bit",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_stride2                                                      */
/*----------------------------------------------------------------------------*/
/*

VSHFL2B
#if __C7X_VEC_SIZE_BITS__ == 256
char32 = __shuffle_stride2(char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __shuffle_stride2(char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
uchar32 = __shuffle_stride2(uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __shuffle_stride2(uchar64);
#endif

VSHFL2H
#if __C7X_VEC_SIZE_BITS__ == 256
cchar16 = __shuffle_stride2(cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = __shuffle_stride2(cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
short16 = __shuffle_stride2(short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __shuffle_stride2(short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ushort16 = __shuffle_stride2(ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __shuffle_stride2(ushort32);
#endif

VSHFL2W
#if __C7X_VEC_SIZE_BITS__ == 256
cshort8 = __shuffle_stride2(cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = __shuffle_stride2(cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
int8 = __shuffle_stride2(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __shuffle_stride2(int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
uint8 = __shuffle_stride2(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __shuffle_stride2(uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
float8 = __shuffle_stride2(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __shuffle_stride2(float16);
#endif

VSHFL2D
#if __C7X_VEC_SIZE_BITS__ == 256
cint4 = __shuffle_stride2(cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __shuffle_stride2(cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
cfloat4 = __shuffle_stride2(cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cfloat8 = __shuffle_stride2(cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long4 = __shuffle_stride2(long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __shuffle_stride2(long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ulong4 = __shuffle_stride2(ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __shuffle_stride2(ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
double4 = __shuffle_stride2(double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = __shuffle_stride2(double8);
#endif

*/

#define __shuffle_stride2(a) __overload("__shuffle_stride2",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_stride2_even_even                                            */
/*----------------------------------------------------------------------------*/
/*

VSHFL2DEE
#if __C7X_VEC_SIZE_BITS__ == 256
cint4 = __shuffle_stride2_even_even(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __shuffle_stride2_even_even(cint8, cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
cfloat4 = __shuffle_stride2_even_even(cfloat4, cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cfloat8 = __shuffle_stride2_even_even(cfloat8, cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long4 = __shuffle_stride2_even_even(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __shuffle_stride2_even_even(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ulong4 = __shuffle_stride2_even_even(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __shuffle_stride2_even_even(ulong8, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
double4 = __shuffle_stride2_even_even(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = __shuffle_stride2_even_even(double8, double8);
#endif

*/

#define __shuffle_stride2_even_even(a,b) __overload("__shuffle_stride2_even_even",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_stride2_even_odd                                             */
/*----------------------------------------------------------------------------*/
/*

VSHFL2DEO
#if __C7X_VEC_SIZE_BITS__ == 256
cint4 = __shuffle_stride2_even_odd(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __shuffle_stride2_even_odd(cint8, cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
cfloat4 = __shuffle_stride2_even_odd(cfloat4, cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cfloat8 = __shuffle_stride2_even_odd(cfloat8, cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long4 = __shuffle_stride2_even_odd(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __shuffle_stride2_even_odd(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ulong4 = __shuffle_stride2_even_odd(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __shuffle_stride2_even_odd(ulong8, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
double4 = __shuffle_stride2_even_odd(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = __shuffle_stride2_even_odd(double8, double8);
#endif

*/

#define __shuffle_stride2_even_odd(a,b) __overload("__shuffle_stride2_even_odd",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_stride2_high_high                                            */
/*----------------------------------------------------------------------------*/
/*

VSHFL2HHH
#if __C7X_VEC_SIZE_BITS__ == 256
cchar16 = __shuffle_stride2_high_high(cchar16, cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = __shuffle_stride2_high_high(cchar32, cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
short16 = __shuffle_stride2_high_high(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __shuffle_stride2_high_high(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ushort16 = __shuffle_stride2_high_high(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __shuffle_stride2_high_high(ushort32, ushort32);
#endif

VSHFL2WHH
#if __C7X_VEC_SIZE_BITS__ == 256
cshort8 = __shuffle_stride2_high_high(cshort8, cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = __shuffle_stride2_high_high(cshort16, cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
int8 = __shuffle_stride2_high_high(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __shuffle_stride2_high_high(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
uint8 = __shuffle_stride2_high_high(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __shuffle_stride2_high_high(uint16, uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
float8 = __shuffle_stride2_high_high(float8, float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __shuffle_stride2_high_high(float16, float16);
#endif

VSHFL2DHH
#if __C7X_VEC_SIZE_BITS__ == 256
cint4 = __shuffle_stride2_high_high(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __shuffle_stride2_high_high(cint8, cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
cfloat4 = __shuffle_stride2_high_high(cfloat4, cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cfloat8 = __shuffle_stride2_high_high(cfloat8, cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long4 = __shuffle_stride2_high_high(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __shuffle_stride2_high_high(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ulong4 = __shuffle_stride2_high_high(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __shuffle_stride2_high_high(ulong8, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
double4 = __shuffle_stride2_high_high(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = __shuffle_stride2_high_high(double8, double8);
#endif

*/

#define __shuffle_stride2_high_high(a,b) __overload("__shuffle_stride2_high_high",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_stride2_low_high                                             */
/*----------------------------------------------------------------------------*/
/*

VSHFL2DLH
#if __C7X_VEC_SIZE_BITS__ == 256
cint4 = __shuffle_stride2_low_high(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __shuffle_stride2_low_high(cint8, cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
cfloat4 = __shuffle_stride2_low_high(cfloat4, cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cfloat8 = __shuffle_stride2_low_high(cfloat8, cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long4 = __shuffle_stride2_low_high(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __shuffle_stride2_low_high(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ulong4 = __shuffle_stride2_low_high(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __shuffle_stride2_low_high(ulong8, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
double4 = __shuffle_stride2_low_high(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = __shuffle_stride2_low_high(double8, double8);
#endif

*/

#define __shuffle_stride2_low_high(a,b) __overload("__shuffle_stride2_low_high",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_stride2_low_low                                              */
/*----------------------------------------------------------------------------*/
/*

VSHFL2HLL
#if __C7X_VEC_SIZE_BITS__ == 256
cchar16 = __shuffle_stride2_low_low(cchar16, cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = __shuffle_stride2_low_low(cchar32, cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
short16 = __shuffle_stride2_low_low(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __shuffle_stride2_low_low(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ushort16 = __shuffle_stride2_low_low(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __shuffle_stride2_low_low(ushort32, ushort32);
#endif

VSHFL2WLL
#if __C7X_VEC_SIZE_BITS__ == 256
cshort8 = __shuffle_stride2_low_low(cshort8, cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = __shuffle_stride2_low_low(cshort16, cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
int8 = __shuffle_stride2_low_low(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __shuffle_stride2_low_low(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
uint8 = __shuffle_stride2_low_low(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __shuffle_stride2_low_low(uint16, uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
float8 = __shuffle_stride2_low_low(float8, float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __shuffle_stride2_low_low(float16, float16);
#endif

VSHFL2DLL
#if __C7X_VEC_SIZE_BITS__ == 256
cint4 = __shuffle_stride2_low_low(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __shuffle_stride2_low_low(cint8, cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
cfloat4 = __shuffle_stride2_low_low(cfloat4, cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cfloat8 = __shuffle_stride2_low_low(cfloat8, cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long4 = __shuffle_stride2_low_low(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __shuffle_stride2_low_low(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ulong4 = __shuffle_stride2_low_low(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __shuffle_stride2_low_low(ulong8, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
double4 = __shuffle_stride2_low_low(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = __shuffle_stride2_low_low(double8, double8);
#endif

*/

#define __shuffle_stride2_low_low(a,b) __overload("__shuffle_stride2_low_low",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_stride2_odd_odd                                              */
/*----------------------------------------------------------------------------*/
/*

VSHFL2DOO
#if __C7X_VEC_SIZE_BITS__ == 256
cint4 = __shuffle_stride2_odd_odd(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __shuffle_stride2_odd_odd(cint8, cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
cfloat4 = __shuffle_stride2_odd_odd(cfloat4, cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cfloat8 = __shuffle_stride2_odd_odd(cfloat8, cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long4 = __shuffle_stride2_odd_odd(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __shuffle_stride2_odd_odd(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ulong4 = __shuffle_stride2_odd_odd(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __shuffle_stride2_odd_odd(ulong8, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
double4 = __shuffle_stride2_odd_odd(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = __shuffle_stride2_odd_odd(double8, double8);
#endif

*/

#define __shuffle_stride2_odd_odd(a,b) __overload("__shuffle_stride2_odd_odd",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_stride4                                                      */
/*----------------------------------------------------------------------------*/
/*

VSHFL4B
#if __C7X_VEC_SIZE_BITS__ == 256
char32 = __shuffle_stride4(char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __shuffle_stride4(char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
uchar32 = __shuffle_stride4(uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __shuffle_stride4(uchar64);
#endif

VSHFL4H
#if __C7X_VEC_SIZE_BITS__ == 256
cchar16 = __shuffle_stride4(cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = __shuffle_stride4(cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
short16 = __shuffle_stride4(short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __shuffle_stride4(short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
ushort16 = __shuffle_stride4(ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __shuffle_stride4(ushort32);
#endif

VSHFL4W
#if __C7X_VEC_SIZE_BITS__ == 256
cshort8 = __shuffle_stride4(cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = __shuffle_stride4(cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
int8 = __shuffle_stride4(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __shuffle_stride4(int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
uint8 = __shuffle_stride4(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __shuffle_stride4(uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
float8 = __shuffle_stride4(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __shuffle_stride4(float16);
#endif

*/

#define __shuffle_stride4(a) __overload("__shuffle_stride4",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __sort_asc                                                             */
/*----------------------------------------------------------------------------*/
/*

VSORTIH
#if __C7X_VEC_SIZE_BITS__ == 256
short16 = __sort_asc(short16);
#endif

VSORTIUH
#if __C7X_VEC_SIZE_BITS__ == 256
ushort16 = __sort_asc(ushort16);
#endif

VSORTIW
#if __C7X_VEC_SIZE_BITS__ == 256
int8 = __sort_asc(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __sort_asc(int16);
#endif

VSORTIUW
#if __C7X_VEC_SIZE_BITS__ == 256
uint8 = __sort_asc(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __sort_asc(uint16);
#endif

VSORTISP
#if __C7X_VEC_SIZE_BITS__ == 256
float8 = __sort_asc(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __sort_asc(float16);
#endif

*/

#define __sort_asc(a) __overload("__sort_asc",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __sort_asc_perm                                                        */
/*----------------------------------------------------------------------------*/
/*

VSORTPIW
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __sort_asc_perm(int16);
#endif

VSORTPIUW
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __sort_asc_perm(uint16);
#endif

VSORTPISP
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __sort_asc_perm(float16);
#endif

*/

#define __sort_asc_perm(a) __overload("__sort_asc_perm",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __sort_desc                                                            */
/*----------------------------------------------------------------------------*/
/*

VSORTDH
#if __C7X_VEC_SIZE_BITS__ == 256
short16 = __sort_desc(short16);
#endif

VSORTDUH
#if __C7X_VEC_SIZE_BITS__ == 256
ushort16 = __sort_desc(ushort16);
#endif

VSORTDW
#if __C7X_VEC_SIZE_BITS__ == 256
int8 = __sort_desc(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __sort_desc(int16);
#endif

VSORTDUW
#if __C7X_VEC_SIZE_BITS__ == 256
uint8 = __sort_desc(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __sort_desc(uint16);
#endif

VSORTDSP
#if __C7X_VEC_SIZE_BITS__ == 256
float8 = __sort_desc(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __sort_desc(float16);
#endif

*/

#define __sort_desc(a) __overload("__sort_desc",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __sort_desc_perm                                                       */
/*----------------------------------------------------------------------------*/
/*

VSORTPDW
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __sort_desc_perm(int16);
#endif

VSORTPDUW
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __sort_desc_perm(uint16);
#endif

VSORTPDSP
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __sort_desc_perm(float16);
#endif

*/

#define __sort_desc_perm(a) __overload("__sort_desc_perm",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __sub_cond                                                             */
/*----------------------------------------------------------------------------*/
/*

VSUBCW
uint = __sub_cond(uint, uint);
uint2 = __sub_cond(uint2, uint2);
uint3 = __sub_cond(uint3, uint3);
uint4 = __sub_cond(uint4, uint4);
uint8 = __sub_cond(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __sub_cond(uint16, uint16);
#endif

*/

#define __sub_cond(a,b) __overload("__sub_cond",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __sub_reverse                                                          */
/*----------------------------------------------------------------------------*/
/*

VSUBRB
signed char = __sub_reverse(signed char, signed char);
signed char = __sub_reverse(signed char, (signed char)(k));
char2 = __sub_reverse(char2, char2);
char2 = __sub_reverse(char2, (char2)(k));
char3 = __sub_reverse(char3, char3);
char3 = __sub_reverse(char3, (char3)(k));
char4 = __sub_reverse(char4, char4);
char4 = __sub_reverse(char4, (char4)(k));
char8 = __sub_reverse(char8, char8);
char8 = __sub_reverse(char8, (char8)(k));
char16 = __sub_reverse(char16, char16);
char16 = __sub_reverse(char16, (char16)(k));
char32 = __sub_reverse(char32, char32);
char32 = __sub_reverse(char32, (char32)(k));
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __sub_reverse(char64, char64);
char64 = __sub_reverse(char64, (char64)(k));
#endif
uchar = __sub_reverse(uchar, uchar);
uchar = __sub_reverse(uchar, (uchar)(k));
uchar2 = __sub_reverse(uchar2, uchar2);
uchar2 = __sub_reverse(uchar2, (uchar2)(k));
uchar3 = __sub_reverse(uchar3, uchar3);
uchar3 = __sub_reverse(uchar3, (uchar3)(k));
uchar4 = __sub_reverse(uchar4, uchar4);
uchar4 = __sub_reverse(uchar4, (uchar4)(k));
uchar8 = __sub_reverse(uchar8, uchar8);
uchar8 = __sub_reverse(uchar8, (uchar8)(k));
uchar16 = __sub_reverse(uchar16, uchar16);
uchar16 = __sub_reverse(uchar16, (uchar16)(k));
uchar32 = __sub_reverse(uchar32, uchar32);
uchar32 = __sub_reverse(uchar32, (uchar32)(k));
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __sub_reverse(uchar64, uchar64);
uchar64 = __sub_reverse(uchar64, (uchar64)(k));
#endif
cchar = __sub_reverse(cchar, cchar);
cchar2 = __sub_reverse(cchar2, cchar2);
cchar4 = __sub_reverse(cchar4, cchar4);
cchar8 = __sub_reverse(cchar8, cchar8);
cchar16 = __sub_reverse(cchar16, cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = __sub_reverse(cchar32, cchar32);
#endif

VSUBRH
short = __sub_reverse(short, short);
short = __sub_reverse(short, (short)(k));
short2 = __sub_reverse(short2, short2);
short2 = __sub_reverse(short2, (short2)(k));
short3 = __sub_reverse(short3, short3);
short3 = __sub_reverse(short3, (short3)(k));
short4 = __sub_reverse(short4, short4);
short4 = __sub_reverse(short4, (short4)(k));
short8 = __sub_reverse(short8, short8);
short8 = __sub_reverse(short8, (short8)(k));
short16 = __sub_reverse(short16, short16);
short16 = __sub_reverse(short16, (short16)(k));
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __sub_reverse(short32, short32);
short32 = __sub_reverse(short32, (short32)(k));
#endif
ushort = __sub_reverse(ushort, ushort);
ushort = __sub_reverse(ushort, (ushort)(k));
ushort2 = __sub_reverse(ushort2, ushort2);
ushort2 = __sub_reverse(ushort2, (ushort2)(k));
ushort3 = __sub_reverse(ushort3, ushort3);
ushort3 = __sub_reverse(ushort3, (ushort3)(k));
ushort4 = __sub_reverse(ushort4, ushort4);
ushort4 = __sub_reverse(ushort4, (ushort4)(k));
ushort8 = __sub_reverse(ushort8, ushort8);
ushort8 = __sub_reverse(ushort8, (ushort8)(k));
ushort16 = __sub_reverse(ushort16, ushort16);
ushort16 = __sub_reverse(ushort16, (ushort16)(k));
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __sub_reverse(ushort32, ushort32);
ushort32 = __sub_reverse(ushort32, (ushort32)(k));
#endif
cshort = __sub_reverse(cshort, cshort);
cshort2 = __sub_reverse(cshort2, cshort2);
cshort4 = __sub_reverse(cshort4, cshort4);
cshort8 = __sub_reverse(cshort8, cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = __sub_reverse(cshort16, cshort16);
#endif

SUBRW, VSUBRW
int = __sub_reverse(int, int);
int = __sub_reverse(int, (int)(k));
int2 = __sub_reverse(int2, int2);
int2 = __sub_reverse(int2, (int2)(k));
int3 = __sub_reverse(int3, int3);
int3 = __sub_reverse(int3, (int3)(k));
int4 = __sub_reverse(int4, int4);
int4 = __sub_reverse(int4, (int4)(k));
int8 = __sub_reverse(int8, int8);
int8 = __sub_reverse(int8, (int8)(k));
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __sub_reverse(int16, int16);
int16 = __sub_reverse(int16, (int16)(k));
#endif
uint = __sub_reverse(uint, uint);
uint = __sub_reverse(uint, (uint)(k));
uint2 = __sub_reverse(uint2, uint2);
uint2 = __sub_reverse(uint2, (uint2)(k));
uint3 = __sub_reverse(uint3, uint3);
uint3 = __sub_reverse(uint3, (uint3)(k));
uint4 = __sub_reverse(uint4, uint4);
uint4 = __sub_reverse(uint4, (uint4)(k));
uint8 = __sub_reverse(uint8, uint8);
uint8 = __sub_reverse(uint8, (uint8)(k));
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __sub_reverse(uint16, uint16);
uint16 = __sub_reverse(uint16, (uint16)(k));
#endif

VSUBRW
cint = __sub_reverse(cint, cint);
cint2 = __sub_reverse(cint2, cint2);
cint4 = __sub_reverse(cint4, cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __sub_reverse(cint8, cint8);
#endif

SUBRD, VSUBRD
long = __sub_reverse(long, long);
long = __sub_reverse(long, (long)(k));
long2 = __sub_reverse(long2, long2);
long2 = __sub_reverse(long2, (long2)(k));
long3 = __sub_reverse(long3, long3);
long3 = __sub_reverse(long3, (long3)(k));
long4 = __sub_reverse(long4, long4);
long4 = __sub_reverse(long4, (long4)(k));
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __sub_reverse(long8, long8);
long8 = __sub_reverse(long8, (long8)(k));
#endif
ulong = __sub_reverse(ulong, ulong);
ulong = __sub_reverse(ulong, (ulong)(k));
ulong2 = __sub_reverse(ulong2, ulong2);
ulong2 = __sub_reverse(ulong2, (ulong2)(k));
ulong3 = __sub_reverse(ulong3, ulong3);
ulong3 = __sub_reverse(ulong3, (ulong3)(k));
ulong4 = __sub_reverse(ulong4, ulong4);
ulong4 = __sub_reverse(ulong4, (ulong4)(k));
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __sub_reverse(ulong8, ulong8);
ulong8 = __sub_reverse(ulong8, (ulong8)(k));
#endif

VSUBRD
clong = __sub_reverse(clong, clong);
clong2 = __sub_reverse(clong2, clong2);
#if __C7X_VEC_SIZE_BITS__ == 512
clong4 = __sub_reverse(clong4, clong4);
#endif

*/

#define __sub_reverse(a,b) __overload("__sub_reverse",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __sub_sat                                                              */
/*----------------------------------------------------------------------------*/
/*

VSSUBB
signed char = __sub_sat(signed char, signed char);
signed char = __sub_sat(signed char, (signed char)(k));
char2 = __sub_sat(char2, char2);
char2 = __sub_sat(char2, (char2)(k));
char3 = __sub_sat(char3, char3);
char3 = __sub_sat(char3, (char3)(k));
char4 = __sub_sat(char4, char4);
char4 = __sub_sat(char4, (char4)(k));
char8 = __sub_sat(char8, char8);
char8 = __sub_sat(char8, (char8)(k));
char16 = __sub_sat(char16, char16);
char16 = __sub_sat(char16, (char16)(k));
char32 = __sub_sat(char32, char32);
char32 = __sub_sat(char32, (char32)(k));
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __sub_sat(char64, char64);
char64 = __sub_sat(char64, (char64)(k));
#endif
cchar = __sub_sat(cchar, cchar);
cchar2 = __sub_sat(cchar2, cchar2);
cchar4 = __sub_sat(cchar4, cchar4);
cchar8 = __sub_sat(cchar8, cchar8);
cchar16 = __sub_sat(cchar16, cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = __sub_sat(cchar32, cchar32);
#endif

VSSUBH
short = __sub_sat(short, short);
short = __sub_sat(short, (short)(k));
short2 = __sub_sat(short2, short2);
short2 = __sub_sat(short2, (short2)(k));
short3 = __sub_sat(short3, short3);
short3 = __sub_sat(short3, (short3)(k));
short4 = __sub_sat(short4, short4);
short4 = __sub_sat(short4, (short4)(k));
short8 = __sub_sat(short8, short8);
short8 = __sub_sat(short8, (short8)(k));
short16 = __sub_sat(short16, short16);
short16 = __sub_sat(short16, (short16)(k));
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __sub_sat(short32, short32);
short32 = __sub_sat(short32, (short32)(k));
#endif
cshort = __sub_sat(cshort, cshort);
cshort2 = __sub_sat(cshort2, cshort2);
cshort4 = __sub_sat(cshort4, cshort4);
cshort8 = __sub_sat(cshort8, cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = __sub_sat(cshort16, cshort16);
#endif

VSSUBW
int = __sub_sat(int, int);
int = __sub_sat(int, (int)(k));
int2 = __sub_sat(int2, int2);
int2 = __sub_sat(int2, (int2)(k));
int3 = __sub_sat(int3, int3);
int3 = __sub_sat(int3, (int3)(k));
int4 = __sub_sat(int4, int4);
int4 = __sub_sat(int4, (int4)(k));
int8 = __sub_sat(int8, int8);
int8 = __sub_sat(int8, (int8)(k));
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __sub_sat(int16, int16);
int16 = __sub_sat(int16, (int16)(k));
#endif
cint = __sub_sat(cint, cint);
cint2 = __sub_sat(cint2, cint2);
cint4 = __sub_sat(cint4, cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __sub_sat(cint8, cint8);
#endif

*/

#define __sub_sat(a,b) __overload("__sub_sat",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __swap                                                                 */
/*----------------------------------------------------------------------------*/
/*

VSWAPB
char2 = __swap(char2);
char4 = __swap(char4);
char8 = __swap(char8);
char16 = __swap(char16);
char32 = __swap(char32);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __swap(char64);
#endif
uchar2 = __swap(uchar2);
uchar4 = __swap(uchar4);
uchar8 = __swap(uchar8);
uchar16 = __swap(uchar16);
uchar32 = __swap(uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __swap(uchar64);
#endif

VSWAPH
cchar2 = __swap(cchar2);
cchar4 = __swap(cchar4);
cchar8 = __swap(cchar8);
cchar16 = __swap(cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = __swap(cchar32);
#endif
short2 = __swap(short2);
short4 = __swap(short4);
short8 = __swap(short8);
short16 = __swap(short16);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __swap(short32);
#endif
ushort2 = __swap(ushort2);
ushort4 = __swap(ushort4);
ushort8 = __swap(ushort8);
ushort16 = __swap(ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __swap(ushort32);
#endif

VSWAPW
cshort2 = __swap(cshort2);
cshort4 = __swap(cshort4);
cshort8 = __swap(cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = __swap(cshort16);
#endif
int2 = __swap(int2);
int4 = __swap(int4);
int8 = __swap(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __swap(int16);
#endif
uint2 = __swap(uint2);
uint4 = __swap(uint4);
uint8 = __swap(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __swap(uint16);
#endif
float2 = __swap(float2);
float4 = __swap(float4);
float8 = __swap(float8);
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = __swap(float16);
#endif

VSWAPD
cint2 = __swap(cint2);
cint4 = __swap(cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = __swap(cint8);
#endif
cfloat2 = __swap(cfloat2);
cfloat4 = __swap(cfloat4);
#if __C7X_VEC_SIZE_BITS__ == 512
cfloat8 = __swap(cfloat8);
#endif
long2 = __swap(long2);
long4 = __swap(long4);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __swap(long8);
#endif
ulong2 = __swap(ulong2);
ulong4 = __swap(ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __swap(ulong8);
#endif
double2 = __swap(double2);
double4 = __swap(double4);
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = __swap(double8);
#endif

*/

#define __swap(a) __overload("__swap",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __unpack_high                                                          */
/*----------------------------------------------------------------------------*/
/*

VUNPKHB
short2 = __unpack_high(char4);
short4 = __unpack_high(char8);
short8 = __unpack_high(char16);
short16 = __unpack_high(char32);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __unpack_high(char64);
#endif

VUNPKHUB
ushort2 = __unpack_high(uchar4);
ushort4 = __unpack_high(uchar8);
ushort8 = __unpack_high(uchar16);
ushort16 = __unpack_high(uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __unpack_high(uchar64);
#endif

VUNPKHH
int2 = __unpack_high(short4);
int4 = __unpack_high(short8);
int8 = __unpack_high(short16);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __unpack_high(short32);
#endif

VUNPKHUH
uint2 = __unpack_high(ushort4);
uint4 = __unpack_high(ushort8);
uint8 = __unpack_high(ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __unpack_high(ushort32);
#endif

*/

#define __unpack_high(a) __overload("__unpack_high",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __unpack_low                                                           */
/*----------------------------------------------------------------------------*/
/*

VUNPKLB
short2 = __unpack_low(char4);
short4 = __unpack_low(char8);
short8 = __unpack_low(char16);
short16 = __unpack_low(char32);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __unpack_low(char64);
#endif

VUNPKLUB
ushort2 = __unpack_low(uchar4);
ushort4 = __unpack_low(uchar8);
ushort8 = __unpack_low(uchar16);
ushort16 = __unpack_low(uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __unpack_low(uchar64);
#endif

VUNPKLH
int2 = __unpack_low(short4);
int4 = __unpack_low(short8);
int8 = __unpack_low(short16);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __unpack_low(short32);
#endif

VUNPKLUH
uint2 = __unpack_low(ushort4);
uint4 = __unpack_low(ushort8);
uint8 = __unpack_low(ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __unpack_low(ushort32);
#endif

VUNPKLW
long = __unpack_low(int2);
long2 = __unpack_low(int4);
long4 = __unpack_low(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __unpack_low(int16);
#endif

VUNPKLUW
ulong = __unpack_low(uint2);
ulong2 = __unpack_low(uint4);
ulong4 = __unpack_low(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __unpack_low(uint16);
#endif

*/

#define __unpack_low(a) __overload("__unpack_low",(a))((a))

/*----------------------------------------------------------------------------*/
/* ID: __xnor                                                                 */
/*----------------------------------------------------------------------------*/
/*

VXNORW, XNORD, XNORW
signed char = __xnor(signed char, signed char);
char2 = __xnor(char2, char2);
char3 = __xnor(char3, char3);
char4 = __xnor(char4, char4);
char8 = __xnor(char8, char8);
char16 = __xnor(char16, char16);
char32 = __xnor(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = __xnor(char64, char64);
#endif
uchar = __xnor(uchar, uchar);
uchar2 = __xnor(uchar2, uchar2);
uchar3 = __xnor(uchar3, uchar3);
uchar4 = __xnor(uchar4, uchar4);
uchar8 = __xnor(uchar8, uchar8);
uchar16 = __xnor(uchar16, uchar16);
uchar32 = __xnor(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = __xnor(uchar64, uchar64);
#endif
short = __xnor(short, short);
short2 = __xnor(short2, short2);
short3 = __xnor(short3, short3);
short4 = __xnor(short4, short4);
short8 = __xnor(short8, short8);
short16 = __xnor(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = __xnor(short32, short32);
#endif
ushort = __xnor(ushort, ushort);
ushort2 = __xnor(ushort2, ushort2);
ushort3 = __xnor(ushort3, ushort3);
ushort4 = __xnor(ushort4, ushort4);
ushort8 = __xnor(ushort8, ushort8);
ushort16 = __xnor(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = __xnor(ushort32, ushort32);
#endif
int = __xnor(int, int);
int2 = __xnor(int2, int2);
int3 = __xnor(int3, int3);
int4 = __xnor(int4, int4);
int8 = __xnor(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __xnor(int16, int16);
#endif
uint = __xnor(uint, uint);
uint2 = __xnor(uint2, uint2);
uint3 = __xnor(uint3, uint3);
uint4 = __xnor(uint4, uint4);
uint8 = __xnor(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __xnor(uint16, uint16);
#endif

VXNORW, XNORD
long = __xnor(long, long);
long = __xnor(long, (long)(k));
long2 = __xnor(long2, long2);
long3 = __xnor(long3, long3);
long4 = __xnor(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = __xnor(long8, long8);
#endif
ulong = __xnor(ulong, ulong);
ulong = __xnor(ulong, (ulong)(k));
ulong2 = __xnor(ulong2, ulong2);
ulong3 = __xnor(ulong3, ulong3);
ulong4 = __xnor(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = __xnor(ulong8, ulong8);
#endif

XNOR
bool2 = __xnor(bool2, bool2);
bool3 = __xnor(bool3, bool3);
bool4 = __xnor(bool4, bool4);
bool8 = __xnor(bool8, bool8);
bool16 = __xnor(bool16, bool16);
bool32 = __xnor(bool32, bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
bool64 = __xnor(bool64, bool64);
#endif

*/

#define __xnor(a,b) __overload("__xnor",(a),(b))((a),(b))

/*----------------------------------------------------------------------------*/
/* ID: __xor                                                                  */
/*----------------------------------------------------------------------------*/
/*

XOR
bool2 = __xor(bool2, bool2);
bool3 = __xor(bool3, bool3);
bool4 = __xor(bool4, bool4);
bool8 = __xor(bool8, bool8);
bool16 = __xor(bool16, bool16);
bool32 = __xor(bool32, bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
bool64 = __xor(bool64, bool64);
#endif

*/

#define __xor(a,b) __overload("__xor",(a),(b))((a),(b))

/* AUTOGEN MARKER */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#include <c7x_direct.h>

#ifdef __DEPRECATED_API__
#include <c7x_strm_deprecated.h>
#include <c7x_mma_deprecated.h>
#else
#include <c7x_strm.h>
#include <c7x_mma.h>
#endif

#include <c7x_luthist.h>

#undef __RD
#undef __WR
#undef __IMPURE
#undef __OVERLOADABLE
#undef __BIF
#undef __BIFM
#undef __OVBIF
#undef __OVBIFM
#undef __CST
#undef __CST_RANGE

#undef __C7X_H_INCLUDE__
#endif /* __C7X_H */
