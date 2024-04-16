/*****************************************************************************/
/* __MPU_INIT.C   v##### - Perform application-specific mpu initializations  */
/* Copyright (c) 2015@%%%% Texas Instruments Incorporated                    */
/*****************************************************************************/

/*****************************************************************************/
/* __MPU_INIT() - __mpu_init() is called in the C/C++ startup routine,       */
/* _c_int00(), and provides a mechanism for tailoring mpu init by device     */
/* prior to calling main().                                                  */
/*                                                                           */
/* The version of __mpu_init() below is skeletal and is provided to          */
/* illustrate the interface and provide default behavior.  To replace this   */
/* version rewrite the routine and include it as part of the current project.*/
/* The linker will include the updated version if it is linked in prior to   */
/* linking with the C/C++ runtime library.                                   */
/*****************************************************************************/

void __mpu_init(void)
{ 
}
