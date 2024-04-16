/*****************************************************************************/
/* linkage.h   v#####                                                        */
/* Copyright (c) 1998@%%%% Texas Instruments Incorporated                    */
/*****************************************************************************/

#ifndef _LINKAGE
#define _LINKAGE

_TI_PROPRIETARY_PRAGMA("diag_push")
_TI_PROPRIETARY_PRAGMA("CHECK_MISRA(\"-19.4\")")
/* No modifiers are needed to access code or data */

#define _CODE_ACCESS
#define _DATA_ACCESS
#define _DATA_ACCESS_NEAR

/*--------------------------------------------------------------------------*/
/* Define _IDECL ==> how inline functions are declared                      */
/*--------------------------------------------------------------------------*/
#ifdef _INLINE
#define _IDECL static __inline
#define _IDEFN static __inline
#else
#define _IDECL extern _CODE_ACCESS
#define _IDEFN _CODE_ACCESS
#endif



_TI_PROPRIETARY_PRAGMA("diag_pop")

#endif /* ifndef _LINKAGE */
