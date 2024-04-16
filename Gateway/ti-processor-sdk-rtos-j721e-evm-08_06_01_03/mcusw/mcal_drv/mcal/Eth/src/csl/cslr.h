/*  ============================================================================
 *  Copyright (C) 2002-2019 Texas Instruments Incorporated
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
 *
*/
/** ============================================================================
 *   \file  cslr.h
 *
 *   \brief  This file contains the macro definations for Register layer
 *
 */

/* Register layer central -- contains field-manipulation macro definitions */

#ifndef CSLR_H
#define CSLR_H

#include "tistdtypes.h"
#include "cslr64.h"


/* the "expression" macros */

/* the Field MaKe macro */
#define CSL_FMK(PER_REG_FIELD, val)                                         \
    (((val) << CSL_##PER_REG_FIELD##_SHIFT) & CSL_##PER_REG_FIELD##_MASK)

/* the Field EXTract macro */
#define CSL_FEXT(reg, PER_REG_FIELD)                                        \
    (((reg) & CSL_##PER_REG_FIELD##_MASK) >> CSL_##PER_REG_FIELD##_SHIFT)

/* the Field INSert macro */
#define CSL_FINS(reg, PER_REG_FIELD, val)                                   \
    ((reg) = ((reg) & ~CSL_##PER_REG_FIELD##_MASK)                          \
      | (((val) << CSL_##PER_REG_FIELD##_SHIFT) & CSL_##PER_REG_FIELD##_MASK))


/* the "token" macros */

/* the Field MaKe (Token) macro */
#define CSL_FMKT(PER_REG_FIELD, TOKEN)                                      \
    (((CSL_##PER_REG_FIELD##_##TOKEN) << CSL_##PER_REG_FIELD##_SHIFT) & CSL_##PER_REG_FIELD##_MASK)

/* the Field INSert (Token) macro */
#define CSL_FINST(reg, PER_REG_FIELD, TOKEN)                                \
    ((reg) = ((reg) & ~CSL_##PER_REG_FIELD##_MASK)                          \
      | (((CSL_##PER_REG_FIELD##_##TOKEN) << CSL_##PER_REG_FIELD##_SHIFT) & CSL_##PER_REG_FIELD##_MASK))


/* the "raw" macros */
#define kw_val (1u)                                             \

/* the Field MaKe (Raw) macro */
#define CSL_FMKR(msb, lsb, val)                                             \
    (((val) & ((((Uint32)1U) << ((msb) - (lsb) + ((Uint32)1U))) - ((Uint32)1U))) << (lsb))

/* the Field EXTract (Raw) macro */
#define CSL_FEXTR(reg, msb, lsb)                                            \
    (((reg) >> (lsb)) & ((((Uint32)1U) << ((msb) - (lsb) + ((Uint32)1U))) - ((Uint32)1U)))

/* the Field INSert (Raw) macro */
#define CSL_FINSR(reg, msb, lsb, val)                                       \
    ((reg) = ((reg) & (~(((((Uint32)1U) << ((msb) - (lsb) + ((Uint32)1U))) - ((Uint32)1U)) << (lsb))))         \
    | CSL_FMKR((msb), (lsb), (val)))

/**
 *  \brief   This macro reads a pointer from a provided address
 *           and returns the value. The access type is implicit based on
 *           the pointer declaration.
 *
 *  \param   p      Pointer to the memory or hardware register.
 *
 *  \return  Value read from the pointer.
 */
#define CSL_REG_RD(p)           (*(p))

/**
 *  \brief   This macro writes a value to the pointer. The access type is
 *           implicit based on the pointer declaration.
 *
 *  \param   p      Pointer to the memory or hardware register.
 *  \param   v      Value which has to be written to the pointer.
 */
#define CSL_REG_WR(p, v)        (*(p) = (v))

/**
 *  \brief   This macro reads a 32-bit value from a hardware register
 *           and returns the value.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *
 *  \return  Unsigned 32-bit value read from a register.
 */
#define CSL_REG32_RD(p)         (CSL_REG32_RD_RAW((volatile Uint32 *) (p)))

/**
 *  \brief   This macro writes a 32-bit value to a hardware register.
 *
 *  \param   p       Address of the memory mapped hardware register.
 *  \param   v       Unsigned 32-bit value which has to be written to the
 *                   register.
 */
#define CSL_REG32_WR(p, v)      (CSL_REG32_WR_RAW( \
                                    (volatile Uint32 *) (p), (Uint32) (v)))

/**
 *  \brief   This macro reads a 16-bit value from a hardware register
 *           and returns the value.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *
 *  \return  Unsigned 16-bit value read from a register.
 */
#define CSL_REG16_RD(p)         (CSL_REG16_RD_RAW((volatile Uint16 *) (p)))

/**
 *  \brief   This macro writes a 16-bit value to a hardware register.
 *
 *  \param   p       Address of the memory mapped hardware register.
 *  \param   v       Unsigned 16-bit value which has to be written to the
 *                   register.
 */
#define CSL_REG16_WR(p, v)      (CSL_REG16_WR_RAW( \
                                    (volatile Uint16 *) (p), (Uint16) (v)))

/**
 *  \brief   This macro reads a 8-bit value from a hardware register
 *           and returns the value.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *
 *  \return  Unsigned 8-bit value read from a register.
 */
#define CSL_REG8_RD(p)          (CSL_REG8_RD_RAW((volatile Uint8 *) (p)))

/**
 *  \brief   This macro writes a 8-bit value to a hardware register.
 *
 *  \param   p       Address of the memory mapped hardware register.
 *  \param   v       Unsigned 8-bit value which has to be written to the
 *                   register.
 */
#define CSL_REG8_WR(p, v)       (CSL_REG8_WR_RAW( \
                                    (volatile Uint8 *) (p), (Uint8) (v)))

/**
 *  \brief   This macro reads a 32-bit value from a hardware register
 *           with an offset and returns the value.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *  \param   off    Offset in bytes.
 *
 *  \return  Unsigned 32-bit value read from a register.
 */
#define CSL_REG32_RD_OFF(p, off)    (CSL_REG32_RD_OFF_RAW( \
                                        (volatile Uint32 *) (p), \
                                        (Uint32) (off)))

/**
 *  \brief   This macro writes a 32-bit value to a hardware register with
 *           an offset.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *  \param   off    Offset in bytes.
 *  \param   v      Unsigned 32-bit value which has to be written to the
 *                  register.
 */
#define CSL_REG32_WR_OFF(p, off, v) (CSL_REG32_WR_OFF_RAW( \
                                        (volatile Uint32 *) (p), \
                                        (Uint32) (off), \
                                        (Uint32) (v)))

/**
 *  \brief This macro calls read field API for 32 bit register. It also
 *         frames the mask and shift from register field macro.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *  \param   fld    Peripheral register bit field name, from which
 *                  specified bit-field value has to be read.
 *
 *  \return Value of the bit-field (absolute value - shifted to LSB position)
 */
#define CSL_REG32_FEXT(p, fld)      (CSL_REG32_FEXT_RAW( \
                                        ((volatile Uint32 *) (p)), \
                                        ((Uint32) CSL_##fld##_MASK), \
                                        ((Uint32) CSL_##fld##_SHIFT)))

/**
 *  \brief This macro calls read field API for 16 bit register. It also
 *         frames the mask and shift from register field macro.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *  \param   fld    Peripheral register bit field name, from which
 *                  specified bit-field value has to be read.
 *
 *  \return Value of the bit-field (absolute value - shifted to LSB position)
 */
#define CSL_REG16_FEXT(p, fld)      (CSL_REG16_FEXT_RAW( \
                                        ((volatile Uint16 *) (p)), \
                                        ((Uint16) CSL_##fld##_MASK), \
                                        ((Uint32) CSL_##fld##_SHIFT)))

/**
 *  \brief This macro calls read field API for 8 bit register. It also
 *         frames the mask and shift from register field macro.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *  \param   fld    Peripheral register bit field name, from which
 *                  specified bit-field value has to be read.
 *
 *  \return Value of the bit-field (absolute value - shifted to LSB position)
 */
#define CSL_REG8_FEXT(p, fld)       (CSL_REG8_FEXT_RAW( \
                                        ((volatile Uint8 *) (p)), \
                                        ((Uint8) CSL_##fld##_MASK), \
                                        ((Uint32) CSL_##fld##_SHIFT)))

/**
 *  \brief This macro calls read-modify-write API for 32 bit register. It also
 *         frames the mask and shift from register field macro.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *  \param   fld    Peripheral register bit field name, from which
 *                  specified bit-field value has to be set.
 *  \param   v      Value of the field which has to be set.
 */
#define CSL_REG32_FINS(p, fld, v)   (CSL_REG32_FINS_RAW( \
                                        ((volatile Uint32 *) (p)), \
                                        ((Uint32) CSL_##fld##_MASK), \
                                        ((Uint32) CSL_##fld##_SHIFT), \
                                        ((Uint32) v)))

/**
 *  \brief This macro calls read-modify-write API for 16 bit register. It also
 *         frames the mask and shift from register field macro.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *  \param   fld    Peripheral register bit field name, from which
 *                  specified bit-field value has to be set.
 *  \param   v      Value of the field which has to be set.
 */
#define CSL_REG16_FINS(p, fld, v)   (CSL_REG16_FINS_RAW( \
                                        ((volatile Uint16 *) (p)), \
                                        ((Uint16) CSL_##fld##_MASK), \
                                        ((Uint32) CSL_##fld##_SHIFT), \
                                        ((Uint16) v)))

/**
 *  \brief This macro calls read-modify-write API for 8 bit register. It also
 *         frames the mask and shift from register field macro.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *  \param   fld    Peripheral register bit field name, from which
 *                  specified bit-field value has to be set.
 *  \param   v      Value of the field which has to be set.
 */
#define CSL_REG8_FINS(p, fld, v)    (CSL_REG8_FINS_RAW( \
                                        ((volatile Uint8 *) (p)), \
                                        ((Uint8) CSL_##fld##_MASK), \
                                        ((Uint32) CSL_##fld##_SHIFT), \
                                        ((Uint8) v)))

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief   This function reads a 32-bit value from a hardware register
 *           and returns the value.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *
 *  \return  Unsigned 32-bit value read from a register.
 */
static inline Uint32 CSL_REG32_RD_RAW(volatile const Uint32 * const p);
static inline Uint32 CSL_REG32_RD_RAW(volatile const Uint32 * const p)
{
    return (*p);
}

/**
 *  \brief   This function writes a 32-bit value to a hardware register.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *  \param   v      Unsigned 32-bit value which has to be written to the
 *                  register.
 */
static inline void CSL_REG32_WR_RAW(volatile Uint32 * const p, Uint32 v);
static inline void CSL_REG32_WR_RAW(volatile Uint32 * const p, Uint32 v)
{
    *p = v;
    return;
}

/**
 *  \brief   This function reads a 16-bit value from a hardware register
 *           and returns the value.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *
 *  \return  Unsigned 16-bit value read from a register.
 */
static inline Uint16 CSL_REG16_RD_RAW(volatile const Uint16 * const p);
static inline Uint16 CSL_REG16_RD_RAW(volatile const Uint16 * const p)
{
    return (*p);
}

/**
 *  \brief   This function writes a 16-bit value to a hardware register.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *  \param   v      Unsigned 16-bit value which has to be written to the
 *                  register.
 */
static inline void CSL_REG16_WR_RAW(volatile Uint16 * const p, Uint16 v);
static inline void CSL_REG16_WR_RAW(volatile Uint16 * const p, Uint16 v)
{
    *p = v;
    return;
}

/**
 *  \brief   This function reads a 8-bit value from a hardware register
 *           and returns the value.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *
 *  \return  Unsigned 8-bit value read from a register.
 */
static inline Uint8 CSL_REG8_RD_RAW(volatile const Uint8 * const p);
static inline Uint8 CSL_REG8_RD_RAW(volatile const Uint8 * const p)
{
    return (*p);
}

/**
 *  \brief   This function writes a 8-bit value to a hardware register.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *  \param   v      Unsigned 8-bit value which has to be written to the
 *                  register.
 */
static inline void CSL_REG8_WR_RAW(volatile Uint8 * const p, Uint8 v);
static inline void CSL_REG8_WR_RAW(volatile Uint8 * const p, Uint8 v)
{
    *p = v;
    return;
}

/**
 *  \brief   This function reads a 32 bit register, masks specific set of bits
 *           and returns the left shifted value.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *  \param   mask   Mask for the bit field.
 *  \param   shift  Bit field shift from LSB.
 *
 *  \return  Bit-field value (absolute value - shifted to LSB position)
 */
static inline Uint32 CSL_REG32_FEXT_RAW(volatile const Uint32 * const p,
                                          Uint32 mask,
                                          Uint32 shift);
static inline Uint32 CSL_REG32_FEXT_RAW(volatile const Uint32 * const p,
                                          Uint32 mask,
                                          Uint32 shift)
{
    Uint32 regVal = CSL_REG32_RD_RAW(p);
    regVal = (regVal & mask) >> shift;
    return (regVal);
}

/**
 *  \brief   This function reads a 16 bit register, masks specific set of bits
 *           and returns the left shifted value.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *  \param   mask   Mask for the bit field.
 *  \param   shift  Bit field shift from LSB.
 *
 *  \return  Bit-field value (absolute value - shifted to LSB position)
 */
static inline Uint16 CSL_REG16_FEXT_RAW(volatile const Uint16 * const p,
                                          Uint16 mask,
                                          Uint32 shift);
static inline Uint16 CSL_REG16_FEXT_RAW(volatile const Uint16 * const p,
                                          Uint16 mask,
                                          Uint32 shift)
{
    Uint16 regVal = CSL_REG16_RD_RAW(p);
    regVal = (regVal & mask) >> shift;
    return (regVal);
}

/**
 *  \brief   This function reads a 8 bit register, masks specific set of bits
 *           and returns the left shifted value.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *  \param   mask   Mask for the bit field.
 *  \param   shift  Bit field shift from LSB.
 *
 *  \return  Bit-field value (absolute value - shifted to LSB position)
 */
static inline Uint8 CSL_REG8_FEXT_RAW(volatile const Uint8 * const p,
                                        Uint8 mask,
                                        Uint32 shift);
static inline Uint8 CSL_REG8_FEXT_RAW(volatile const Uint8 * const p,
                                        Uint8 mask,
                                        Uint32 shift)
{
    Uint8 regVal = CSL_REG8_RD_RAW(p);
    regVal = (regVal & mask) >> shift;
    return (regVal);
}

/**
 *  \brief   This function reads a 32 bit register, modifies specific set of
 *           bits and writes back to the register.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *  \param   mask   Mask for the bit field.
 *  \param   shift  Bit field shift from LSB.
 *  \param   v      Value to be written to bit-field.
 */
static inline void CSL_REG32_FINS_RAW(volatile Uint32 * const p,
                                      Uint32 mask,
                                      Uint32 shift,
                                      Uint32 v);
static inline void CSL_REG32_FINS_RAW(volatile Uint32 * const p,
                                      Uint32 mask,
                                      Uint32 shift,
                                      Uint32 v)
{
    Uint32 regVal = CSL_REG32_RD_RAW(p);
    regVal = (regVal & ~(mask));
    regVal |= (v << shift) & mask;
    CSL_REG32_WR_RAW(p, regVal);
    return;
}

/**
 *  \brief   This function reads a 16 bit register, modifies specific set of
 *           bits and writes back to the register.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *  \param   mask   Mask for the bit field.
 *  \param   shift  Bit field shift from LSB.
 *  \param   v      Value to be written to bit-field.
 */
static inline void CSL_REG16_FINS_RAW(volatile Uint16 * const p,
                                      Uint16 mask,
                                      Uint32 shift,
                                      Uint16 v);
static inline void CSL_REG16_FINS_RAW(volatile Uint16 * const p,
                                      Uint16 mask,
                                      Uint32 shift,
                                      Uint16 v)
{
    Uint16 regVal = CSL_REG16_RD_RAW(p);
    regVal = (regVal & ~(mask));
    regVal |= (v << shift) & mask;
    CSL_REG16_WR_RAW(p, regVal);
    return;
}

/**
 *  \brief   This function reads a 8 bit register, modifies specific set of
 *           bits and writes back to the register.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *  \param   mask   Mask for the bit field.
 *  \param   shift  Bit field shift from LSB.
 *  \param   v      Value to be written to bit-field.
 */
static inline void CSL_REG8_FINS_RAW(volatile Uint8 * const p,
                                     Uint8 mask,
                                     Uint32 shift,
                                     Uint8 v);
static inline void CSL_REG8_FINS_RAW(volatile Uint8 * const p,
                                     Uint8 mask,
                                     Uint32 shift,
                                     Uint8 v)
{
    Uint8 regVal = CSL_REG8_RD_RAW(p);
    regVal = (regVal & ~(mask));
    regVal |= (v << shift) & mask;
    CSL_REG8_WR_RAW(p, regVal);
    return;
}

#endif /* CSLR_H_ */
