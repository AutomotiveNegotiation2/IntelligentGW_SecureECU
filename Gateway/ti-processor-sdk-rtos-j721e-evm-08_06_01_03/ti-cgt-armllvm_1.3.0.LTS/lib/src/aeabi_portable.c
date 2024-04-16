/****************************************************************************/
/*  aeabi_portable.c v#####                                                 */
/*  Copyright (c) 2006@%%%%  Texas Instruments Incorporated                 */
/****************************************************************************/
#define _AEABI_PORTABILITY_LEVEL 1

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/*****************************************************************************/
/* ARM's CLIB ABI (GENC-003539) supports two models:                         */
/*   1. Compiler and RTS are from the same toolset.                          */
/*   2. Compiler and RTS are from different toolset.                         */
/* A toolset should provide a portable version of the C library functionality*/
/* to support model 2 above.  This file contains functions required by the   */
/* CLIB ABI under _AEABI_PORTABILITY_LEVEL!=0                                */
/*****************************************************************************/

/****************************************************************************/
/* __aeabi_assert() - Implements the assert macro. Unlike the TI version    */
/*                    the expr has already been evaluated before this       */
/*                    function is called.                                   */
/****************************************************************************/
void __aeabi_assert(const char *expr, const char *file, int line)
{
   int   size = strlen(expr) + strlen(file) + 38;
   char *buf  = (char *)malloc(size);
   if (!buf)
   {
      _abort_msg("malloc failed in assert");
      return;
   }
   sprintf(buf,"Assertion failed, (%s), file %s, line %d\n", expr, file, line);
   _abort_msg(buf);
   return;
}

/****************************************************************************/
/* __aeabi_errno_addr() - return the address of the "global" aeabi_errno.   */
/*                        __aeabi_errno should be an "global" or TLS.       */
/****************************************************************************/
int __aeabi_errno = 0;

__attribute__((weak))
volatile int *__aeabi_errno_addr(void)
{
     return &__aeabi_errno;
}


/****************************************************************************/
/* __aeabi_MB_CUR_MAX - At this time, only NON multithread version is       */
/*                     provided.                                            */
/****************************************************************************/
int __aeabi_MB_CUR_MAX(void)
{
    return 1;
}

/****************************************************************************/
/* __aeabi_localeconv - Like localeconv, but returns AEABI's __aeabi_lconv, */
/*                      which has the fields in a different order.  Because */
/*                      we don't actually allow users to change the locale, */
/*                      this doesn't have to communicate with localeconv.   */
/****************************************************************************/
#include <locale.h>
#include <limits.h>

static struct __aeabi_lconv C_locale =
{
	/* char *decimal_point;       */    ".",
	/* char *thousands_sep;       */    "",
	/* char *grouping;            */    "",
	/* char *int_curr_symbol;     */    "",
	/* char *currency_symbol;     */    "",
	/* char *mon_decimal_point;   */    "",
	/* char *mon_thousands_sep;   */    "",
	/* char *mon_grouping;        */    "",
	/* char *positive_sign;       */    "",
	/* char *negative_sign;       */    "",
	/* char int_frac_digits;      */    CHAR_MAX,
	/* char frac_digits;          */    CHAR_MAX,
	/* char p_cs_precedes;        */    CHAR_MAX,
	/* char p_sep_by_space;       */    CHAR_MAX,
	/* char n_cs_precedes;        */    CHAR_MAX,
	/* char n_sep_by_space;       */    CHAR_MAX,
	/* char p_sign_posn;          */    CHAR_MAX,
	/* char n_sign_posn;          */    CHAR_MAX,
};

struct __aeabi_lconv *__aeabi_localeconv(void)
{
   return &C_locale;
}
