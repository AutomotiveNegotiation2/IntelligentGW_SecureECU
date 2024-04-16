/*****************************************************************************/
/* MATHACL_INIT.C   v##### - Perform MATHACL initializations                 */
/* Copyright (c) 2021@%%%% Texas Instruments Incorporated                    */
/*****************************************************************************/
#include <stdint.h>

/*****************************************************************************/
/* __MATHACL_INIT() - This is called by the C/C++ startup routine to ensure  */
/* that the MSP math accelerator is initialized before operations can be     */
/* invoked on it.  The initialization requires a single write to the PWREN   */
/* register inside SYSCTL.                                                   */
/*                                                                           */
/* This version of __mathacl_init() is for MSP LEGO M0+ devices.  It is only */
/* linked in when the user uses a command line option to enable MATHACL      */
/* operations.                                                               */
/*****************************************************************************/
void __mathacl_init(void)
{ 
   // This value - both the enable bit set to 1 and the key bits set to 0x26 -
   // has to be written in a single 32-bit write. The key cannot be set before
   // or after the enable bit has been written to. The key acts as a protection
   // to prevent unexpected writes to this register.
   volatile uint32_t* pwren = (volatile uint32_t*)0x40410800;
   *pwren = (1 | (0x26 << 24));
}
