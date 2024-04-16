@REM ******************************************************************************
@REM * FILE PURPOSE: PDK Unit Test and Example Project Creator
@REM ******************************************************************************
@REM * FILE NAME: pdkProjectCreate.bat
@REM *
@REM * DESCRIPTION: 
@REM *  The script file is used to create the test and example projects of all
@REM *  components under PDK. These projects are available in the specified
@REM *  workspace.
@REM *
@REM * Syntax:
@REM *  pdkProjectCreate.bat [soc] [board] [endian] [module] [project type] [processor] [pdkDir]
@REM *
@REM * Description:       (first option is default)
@REM *  soc           -   AM335x / AM437x / AM571x / AM572x / AM574x / K2E / K2G / K2K / K2H / K2L /
@REM *                    C6678 / C6657 / DRA72x / DRA75x / DRA78x / OMAPL137 / OMAPL138 / C6748 / am65xx
@REM *  board         -   all (use "all" for K2X and C66X SOCs)
@REM *                    -or-
@REM *                    Refer to pdk_<soc>_<version>\packages\ti\board\lib
@REM *                    for valid board inputs for the soc
@REM *  endian        -   little / big
@REM *  module        -   all
@REM *                    -or-
@REM *                    aif2 / bcp / cppi / csl / dfe / emac / fatfs / fm / fftc / 
@REM *                    gpio / hyplnk / i2c / icss_emac / iqn2 / mcasp / mcbsp / mmap / mmcsd /
@REM *                    nimu / nimu_icss / nwal / osal / pa / pcie / pktlib / pruss / qm / rm /
@REM *                    sa /serdes-diag / spi / srio / tcp3d / tfw / transportqmss /
@REM *                    transportsrio / tsip / uart / usb / wdtimer / vps / dcan / dss / lcdc
@REM *  project type  -   all / example / test 
@REM *  processor     -   arm / dsp / m4 / mpu / mcu
@REM *  pdkDir        -   THIS FILE LOCATION / "C:\ti\pdk_<soc>_<version>\packages"
@REM *
@REM * Example:
@REM *  a) pdkProjectCreate.bat
@REM *              - Creates all module projects for the AM335x soc for arm little endian
@REM *  b) pdkProjectCreate.bat AM437x
@REM *              - Creates all module projects for the AM437x soc for arm little endian
@REM *  c) pdkProjectCreate.bat AM437x idkAM437x
@REM *              - Creates all module projects for idkAM437x device for arm little endian
@REM *  d) pdkProjectCreate.bat AM571x evmAM571x little
@REM *              - Creates all module projects for evmAM571x device for arm little endian
@REM *  e) pdkProjectCreate.bat AM571x evmAM571x little i2c all dsp
@REM *              - Creates all i2c module projects for evmAM571x device for dsp little endian
@REM *  f) pdkProjectCreate.bat K2H all little i2c example arm
@REM *              - Creates i2c module example projects for K2H device for arm little endian
@REM *  g) pdkProjectCreate.bat C6678 all little hyplnk test dsp
@REM *              - Creates hyplnk module test projects for C6678 device for dsp little endian
@REM *
@REM * Copyright (C) 2012-2019, Texas Instruments, Inc.
@REM *****************************************************************************
@echo OFF
setlocal enabledelayedexpansion

REM Lists of valid input parameters - MUST be updated as new input parameters are added
REM *****************************************************************************
set soc_list=AM335x AM437x AM571x AM572x AM574x K2E K2K K2H K2L K2G C6678 C6657 DRA72x DRA75x DRA78x OMAPL137 OMAPL138 C6748 am65xx
set endian_list=little big
set module_list=all aif2 bcp cppi csl dfe emac fatfs fm fftc gpio gpmc hyplnk i2c icss_emac iqn2 mcasp mcbsp mmap mmcsd nimu nimu_icss nwal osal pa pcie pktlib pruss qm rm sa serdes_diag spi srio tcp3d tfw transportqmss transportsrio tsip uart usb wdtimer vps dcan dss lcdc timeSync
set projectType_list=all example test
set proc_list=arm dsp m4 mpu mcu

REM Parameter Validation: Check if the argument was passed to the batch file.
REM *****************************************************************************
REM Argument [soc] is used to set SOC variable.
set tempVar1=%1
if not defined tempVar1 goto nosoc
set SOC=%tempVar1%
goto socdone
:nosoc
set SOC=AM335x
:socdone

REM Argument [board] is used to set BOARD variable.
REM This is the board type of the soc for which project are to be created.
set tempVar2=%2
if not defined tempVar2 goto noboard
set BOARD=%tempVar2%
goto boarddone
:noboard
set BOARD=all
:boarddone

REM Argument [endian] is used to set ENDIAN variable.
REM This is Endianess of the projects being created.
REM Valid Values are 'little' and 'big'. Defaults to 'little'.
set tempVar3=%3
if not defined tempVar3 goto littleendian
set ENDIAN=%tempVar3%
goto endiandone
:littleendian
set ENDIAN=little
:endiandone

REM Argument [module] is used to set MODULE variable.
REM This is specific module for which projects are created.
REM Valid Values are LLD name. Defaults to all LLD's.
set tempVar4=%4
if not defined tempVar4 goto nomodule
set MODULE=%tempVar4%
goto moduledone
:nomodule
set MODULE=all
:moduledone

REM Argument [project type] is used to set PROJECT_TYPE variable.
REM This is the type of projects that are created
REM Valid Values are all, example, or test. Defaults to all. 
set tempVar5=%5
if not defined tempVar5 goto noProjectType
set PROJECT_TYPE=%tempVar5%
goto projectTypeDone
:noProjectType
set PROJECT_TYPE=all
:projectTypeDone

REM Argument [processor] is used to set PROCESSOR variable.
REM This is specific processor type for which projects are created.
REM Valid Values are arm, dsp, or m4 . Defaults to arm.
set tempVar6=%6
if not defined tempVar6 goto noprocessor
set PROCESSOR=%tempVar6%
goto processordone
:noprocessor
set PROCESSOR=arm
:processordone

REM Argument [pdkDir] is used to set PDK_SHORT_NAME. This is PDK directory
REM where project description files are located. If there is no value passed,
REM it defaults to the file location directory. Then convert the variable to 
REM short name to avoid issues using batch file commands.
set tempVar7=%7
if not defined tempVar7 goto noparameter
set PDK_SHORT_NAME=%tempVar7%
goto done
:noparameter
set PDK_SHORT_NAME=%~sdp0
:done

if not defined SDK_INSTALL_PATH (
    set SDK_INSTALL_PATH=__SDK__INSTALL_DIR__
)

REM *****************************************************************************

echo =========================================================================
echo Configuration:
echo.   SOC             :   %SOC%
echo    BOARD           :   %BOARD%
echo.   ENDIAN          :   %ENDIAN%
echo.   MODULE          :   %MODULE%
echo.   PROJECT_TYPE    :   %PROJECT_TYPE%
echo.   PROCESSOR       :   %PROCESSOR%
echo.   PDK_SHORT_NAME  :   %PDK_SHORT_NAME%
echo =========================================================================
echo Checking Configuration...

for %%a in (%soc_list%) do (
    if %SOC% == %%a (
        goto end_soc_check
    )
)
echo ERROR: SOC (%SOC%) is invalid
goto CONFIG_ERR
:end_soc_check

if %BOARD% == all (
    goto end_board_check
)
if %BOARD% == iceAMIC110 (
    if %SOC% == AM335x (
        goto end_board_check
    )
    goto board_check_error
)
set board_type=!BOARD:%SOC%=!
if not %board_type% == %BOARD% (
    goto end_board_check
)
:board_check_error
echo ERROR: Board (%BOARD%) is invalid for the specified SOC (%SOC%)
goto CONFIG_ERR
:end_board_check

for %%a in (%endian_list%) do (
    if %ENDIAN% == %%a (
        goto end_endian_check
    )
)
echo ERROR: Endian (%ENDIAN%) is invalid
goto CONFIG_ERR
:end_endian_check

for %%a in (%module_list%) do (
    if %MODULE% == %%a (
        goto end_module_check
    )
)
echo ERROR: Module (%MODULE%) is invalid
goto CONFIG_ERR
:end_module_check

for %%a in (%projectType_list%) do (
    if %PROJECT_TYPE% == %%a (
        goto end_projectType_check
    )
)
echo ERROR: Project type (%PROJECT_TYPE%) is invalid
goto CONFIG_ERR
:end_projectType_check

for %%a in (%proc_list%) do (
    if %PROCESSOR% == %%a (
        goto end_proc_check
    )
)
echo ERROR: Processor (%PROCESSOR%) is invalid
goto CONFIG_ERR
:end_proc_check

if %SOC% == AM335x (
    if %PROCESSOR% == dsp (
        echo ERROR: The AM335x soc does not contain a DSP processor
        goto CONFIG_ERR
    ) else if %PROCESSOR% == m4 (
        echo ERROR: The AM335x soc does not contain a M4 processor
        goto CONFIG_ERR
    )

    if %ENDIAN% == big (
        echo ERROR: The AM335x soc's arm does not support big endian
        goto CONFIG_ERR
    )
) else if %SOC% == AM437x (
    if %PROCESSOR% == dsp (
        echo ERROR: The AM437x soc does not contain a DSP processor
        goto CONFIG_ERR
    ) else if %PROCESSOR% == m4 (
        echo ERROR: The AM437x soc does not contain a M4 processor
        goto CONFIG_ERR
    )

    if %ENDIAN% == big (
        echo ERROR: The AM437x soc's arm does not support big endian
        goto CONFIG_ERR
    )
) else if %SOC% == AM571x (
    if %ENDIAN% == big (
        echo ERROR: The AM571x soc's processor's do not support big endian
        goto CONFIG_ERR
    )
) else if %SOC% == AM572x (
    if %ENDIAN% == big (
        echo ERROR: The AM572x soc's processor's do not support big endian
        goto CONFIG_ERR
    )
) else if %SOC% == AM574x (
    if %ENDIAN% == big (
        echo ERROR: The AM574x soc's processor's do not support big endian
        goto CONFIG_ERR
    )
)  else if %SOC% == K2K (
    if %PROCESSOR% == m4 (
        echo ERROR: The K2K soc does not contain a M4 processor
        goto CONFIG_ERR
    )
    
    if %PROCESSOR% == arm (
        if %ENDIAN% == big (
            echo ERROR: The K2K soc's arm does not support big endian
            goto CONFIG_ERR
        )
    )
) else if %SOC% == K2H (
    if %PROCESSOR% == m4 (
        echo ERROR: The K2H soc does not contain a M4 processor
        goto CONFIG_ERR
    )
    
    if %PROCESSOR% == arm (
        if %ENDIAN% == big (
            echo ERROR: The K2H soc's arm does not support big endian
            goto CONFIG_ERR
        )
    )
) else if %SOC% == K2E (
    if %PROCESSOR% == m4 (
        echo ERROR: The K2E soc does not contain a M4 processor
        goto CONFIG_ERR
    )
    
    if %PROCESSOR% == arm (
        if %ENDIAN% == big (
            echo ERROR: The K2E soc's arm does not support big endian
            goto CONFIG_ERR
        )
    )
) else if %SOC% == K2L (
    if %PROCESSOR% == m4 (
        echo ERROR: The K2L soc does not contain a M4 processor
        goto CONFIG_ERR
    )
    
    if %PROCESSOR% == arm (
        if %ENDIAN% == big (
            echo ERROR: The K2L soc's arm does not support big endian
            goto CONFIG_ERR
        )
    )
) else if %SOC% == K2G (
    if %PROCESSOR% == m4 (
        echo ERROR: The K2G soc does not contain a M4 processor
        goto CONFIG_ERR
    )
    
    if %PROCESSOR% == arm (
        if %ENDIAN% == big (
            echo ERROR: The K2G soc's arm does not support big endian
            goto CONFIG_ERR
        )
    )
) else if %SOC% == OMAPL137 (
    if %PROCESSOR% == m4 (
        echo ERROR: The OMAPL137 soc does not contain a M4 processor
        goto CONFIG_ERR
    )
    
    if %PROCESSOR% == arm (
        if %ENDIAN% == big (
            echo ERROR: The OMAPL137 soc's arm does not support big endian
            goto CONFIG_ERR
        )
    )
	if %PROCESSOR% == dsp (
        if %ENDIAN% == big (
            echo ERROR: The OMAPL137 soc's dsp does not support big endian
            goto CONFIG_ERR
        )
    )
)  else if %SOC% == OMAPL138 (
    if %PROCESSOR% == m4 (
        echo ERROR: The OMAPL138 soc does not contain a M4 processor
        goto CONFIG_ERR
    )
    
    if %PROCESSOR% == arm (
        if %ENDIAN% == big (
            echo ERROR: The OMAPL138 soc's arm does not support big endian
            goto CONFIG_ERR
        )
    )
	if %PROCESSOR% == dsp (
        if %ENDIAN% == big (
            echo ERROR: The OMAPL138 soc's dsp does not support big endian
            goto CONFIG_ERR
        )
    )
) else if %SOC% == C6748 (
    if %PROCESSOR% == m4 (
        echo ERROR: The C6748 soc does not contain a M4 processor
        goto CONFIG_ERR
    )
	if %PROCESSOR% == arm (
        echo ERROR: The C6748 soc does not contain an arm processor
        goto CONFIG_ERR
    )
	if %PROCESSOR% == dsp (
        if %ENDIAN% == big (
            echo ERROR: The C6748 soc's dsp does not support big endian
            goto CONFIG_ERR
        )
    )
) else if %SOC% == C6678 (
    if %PROCESSOR% == m4 (
        echo ERROR: The C6678 soc does not contain a M4 processor
        goto CONFIG_ERR
    )

    if %PROCESSOR% == arm (
        echo ERROR: The C6678 soc does not contain an arm processor
        goto CONFIG_ERR
    )
) else if %SOC% == C6657 (
    if %PROCESSOR% == m4 (
        echo ERROR: The C6657 soc does not contain a M4 processor
        goto CONFIG_ERR
    )

    if %PROCESSOR% == arm (
        echo ERROR: The C6657 soc does not contain an arm processor
        goto CONFIG_ERR
    )
) else if %SOC% == DRA72x (
    if %ENDIAN% == big (
        echo ERROR: The DRA72x soc's processor's do not support big endian
        goto CONFIG_ERR
    )
) else if %SOC% == DRA75x (
    if %ENDIAN% == big (
        echo ERROR: The DRA75x soc's processor's do not support big endian
        goto CONFIG_ERR
    )
) else if %SOC% == DRA78x (
    if %ENDIAN% == big (
        echo ERROR: the DRA78x soc's processor's do not support big endian
        goto CONFIG_ERR
    )
) else if %SOC% == am65xx (
    if %PROCESSOR% == dsp (
        echo ERROR: The AM65xx soc does not contain a DSP processor
        goto CONFIG_ERR
    )
    if %PROCESSOR% == m4 (
        echo ERROR: The AM65xx soc does not contain a M4 processor
        goto CONFIG_ERR
    )
    if %ENDIAN% == big (
        echo ERROR: The AM65xx soc's processor's do not support big endian
        goto CONFIG_ERR
    )
) else (
    echo ERROR: Invalid soc
    goto CONFIG_ERR
)

goto CONFIG_COMPLETE

:CONFIG_ERR
echo Exiting...
echo =========================================================================
goto ENDSCRIPT

:CONFIG_COMPLETE
echo Complete
echo =========================================================================

REM *****************************************************************************
REM * Version Information of the various tools etc required to build the test
REM * projects. Customers are free to modify these to meet their requirements.
REM *****************************************************************************

REM This is to control the CCS version specific project create command
REM Set to 'no' when using CCSv8 or set to 'yes' when using CCSv4
set IS_CCS_VERSION_4=no

REM Set to 'no' when using QT, EVM, VDB, or other hardware. Set to 'yes' only when using the simulator.
set IS_SIMULATOR_SUPPORT_NEEDED=no

if not defined CCS_INSTALL_PATH (
    set CCS_INSTALL_PATH=C:/ti/ccs930/ccs
)

REM Workspace where the PDK projects will be created.
set MY_WORKSPACE=%PDK_SHORT_NAME%\MyExampleProjects

REM macros.ini location
set MACROS_FILE=%PDK_SHORT_NAME%\macros.ini

REM This is the format of the executable being created
REM Valid Values are 'ELF' and 'COFF'
set OUTPUT_FORMAT=ELF

REM Version of CG-Tools
set CGT_VERSION=8.3.2

REM Version of CG-ARM-Tools for M4
set CGT_M4_VERSION=18.12.5.LTS

REM Version of XDC
set XDC_VERSION=3.55.02.22

REM Version of BIOS
set BIOS_VERSION=6.76.03.01

REM Version of CG-Tools for ARM
set CGT_VERSION_ARM=GNU_7.2.1:Linaro

REM Version of CG-Tools for ARM
set CGT_VERSION_ARM_A53=GNU_7.2.1:Linaro aarch64

REM Version of CG-Tools for ARM
set CGT_VERSION_ARM9=18.12.5.LTS

REM Version of the IPC
set IPC_VERSION=3_50_04_08

REM EDMA3 Version
set EDMA_VERSION=2.12.05.30E

REM Version of the PDK
set PDK_VERSION=08_06_01_03

REM Version of the NDK
set NDK_VERSION=3.61.01.01

REM Version of UIA
set UIA_VERSION=2.30.01.02

REM PDK Part Number & Platform name
if %SOC% == K2K (
    set PDK_PARTNO=TCI6638
    set PDK_ECLIPSE_ID=com.ti.pdk.k2hk
    set RTSC_PLATFORM_NAME=ti.platforms.evmTCI6638K2K
    if %PROCESSOR% == arm (
        set RTSC_TARGET=gnu.targets.arm.A15F
        set CCS_DEVICE="Cortex A.TCI6638K2K"
    )
) else if  %SOC% == K2H (
    set PDK_PARTNO=TCI6636
    set PDK_ECLIPSE_ID=com.ti.pdk.k2hk
    set RTSC_PLATFORM_NAME=ti.platforms.evmTCI6636K2H
    if %PROCESSOR% == arm (
        set RTSC_TARGET=gnu.targets.arm.A15F
        set CCS_DEVICE="Cortex A.66AK2H12"
    )
) else if  %SOC% == K2L (
    set PDK_PARTNO=TCI6630
    set PDK_ECLIPSE_ID=com.ti.pdk.k2l
    set RTSC_PLATFORM_NAME=ti.platforms.evmTCI6630K2L
    if %PROCESSOR% == arm (
        set RTSC_TARGET=gnu.targets.arm.A15F
        set CCS_DEVICE="Cortex A.TCI6630K2L"
    )
) else if  %SOC% == K2E (
    set PDK_PARTNO=66AK2E05
    set PDK_ECLIPSE_ID=com.ti.pdk.k2e
    set RTSC_PLATFORM_NAME=ti.platforms.evmC66AK2E
    if %PROCESSOR% == arm (
        set RTSC_TARGET=gnu.targets.arm.A15F
        set CCS_DEVICE="Cortex A.66AK2E05"
    )
) else if  %SOC% == K2G (
    set PDK_PARTNO=66AK2G02
    set PDK_ECLIPSE_ID=com.ti.pdk.k2g
    set RTSC_PLATFORM_NAME=ti.platforms.evmTCI66AK2G02
    if %PROCESSOR% == arm (
        set RTSC_TARGET=gnu.targets.arm.A15F
        set CCS_DEVICE="Cortex A.66AK2G02"
    )
) else if  %SOC% == AM571x (
    set PDK_PARTNO=AM571X
    set PDK_ECLIPSE_ID=com.ti.pdk.am57xx
    set RTSC_PLATFORM_NAME=ti.platforms.idkAM571X
    if %PROCESSOR% == arm (
        set RTSC_TARGET=gnu.targets.arm.A15F
        set CCS_DEVICE="Cortex A.AM5728_RevA"
    ) else if %PROCESSOR% == m4 (
        set RTSC_TARGET=ti.targets.arm.elf.M4
        set CCS_DEVICE="Cortex M.AM5728_RevA"
    )
) else if  %SOC% == AM572x (
    set PDK_PARTNO=AM572X
    set PDK_ECLIPSE_ID=com.ti.pdk.am57xx
    if %BOARD% == idkAM572x (
        set RTSC_PLATFORM_NAME=ti.platforms.idkAM572X
    ) else (
        set RTSC_PLATFORM_NAME=ti.platforms.evmAM572X
    )
    if %PROCESSOR% == arm (
        set RTSC_TARGET=gnu.targets.arm.A15F
        set CCS_DEVICE="Cortex A.AM5728_RevA"
    ) else if %PROCESSOR% == m4 (
        set RTSC_TARGET=ti.targets.arm.elf.M4
        set CCS_DEVICE="Cortex M.AM5728_RevA"
    )
) else if  %SOC% == AM574x (
    set PDK_PARTNO=AM574X
    set PDK_ECLIPSE_ID=com.ti.pdk.am57xx
    set RTSC_PLATFORM_NAME=ti.platforms.idkAM572X
    if %PROCESSOR% == arm (
        set RTSC_TARGET=gnu.targets.arm.A15F
        set CCS_DEVICE="Cortex A.AM5728_RevA"
    ) else if %PROCESSOR% == m4 (
        set RTSC_TARGET=ti.targets.arm.elf.M4
        set CCS_DEVICE="Cortex M.AM5728_RevA"
    )
) else if  %SOC% == AM335x (
    set PDK_PARTNO=AM335
    set PDK_ECLIPSE_ID=com.ti.pdk.am335x
    set RTSC_PLATFORM_NAME=ti.platforms.evmAM3359
    set RTSC_TARGET=gnu.targets.arm.A8F
    set CCS_DEVICE="Cortex A.AM3359.ICE_AM3359"
) else if  %SOC% == AM437x (
    set PDK_PARTNO=AM437
    set PDK_ECLIPSE_ID=com.ti.pdk.am437x
    set RTSC_PLATFORM_NAME=ti.platforms.evmAM437X
    set RTSC_TARGET=gnu.targets.arm.A9F
    set CCS_DEVICE="Cortex A.AM4379.IDK_AM437X"
) else if  %SOC% == OMAPL137 (
    set PDK_PARTNO=OMAPL137
    set PDK_ECLIPSE_ID=com.ti.pdk.omapl137
    set RTSC_PLATFORM_NAME=ti.platforms.evmOMAPL137
    if %PROCESSOR% == arm (
        set RTSC_TARGET=ti.targets.arm.elf.Arm9
        set CCS_DEVICE="ARM9.OMAPL137"
    )
) else if  %SOC% == OMAPL138 (
    set PDK_PARTNO=OMAPL138
    set PDK_ECLIPSE_ID=com.ti.pdk.omapl138
    set RTSC_PLATFORM_NAME=ti.platforms.evmOMAPL138
    if %PROCESSOR% == arm (
        set RTSC_TARGET=ti.targets.arm.elf.Arm9
        set CCS_DEVICE="ARM9.OMAPL138"
    )
)else if  %SOC% == C6748 (
    REM C6748 is the alias for OMAPL138 where the OMAPL138 settings will
	REM be used to create projects for C6748 SOC.
    set SOC=OMAPL138
	set BOARD=lcdkOMAPL138
	set PDK_PARTNO=OMAPL138
    set PDK_ECLIPSE_ID=com.ti.pdk.omapl138
    set RTSC_PLATFORM_NAME=ti.platforms.evmOMAPL138
) else if  %SOC% == C6678 (
    set PDK_PARTNO=C6678L
    set PDK_ECLIPSE_ID=com.ti.pdk.c667x
    set RTSC_PLATFORM_NAME=ti.platforms.evm6678
) else if  %SOC% == C6657 (
    set PDK_PARTNO=C6657
    set PDK_ECLIPSE_ID=com.ti.pdk.c665x
    set RTSC_PLATFORM_NAME=ti.platforms.evm6657
) else if %SOC% == DRA72x (
    set PDK_PARTNO=DRA72x
    set PDK_ECLIPSE_ID=com.ti.pdk.dra7xx
    set RTSC_PLATFORM_NAME=ti.platforms.evmDRA7XX
    if %PROCESSOR% == arm (
        set RTSC_TARGET=gnu.targets.arm.A15F
        set CCS_DEVICE="Cortex A.DRA72x"
    ) else if %PROCESSOR% == m4 (
        set RTSC_TARGET=ti.targets.arm.elf.M4
        set CCS_DEVICE="Cortex M.DRA72x"
    )
) else if %SOC% == DRA75x (
    set PDK_PARTNO=DRA75x
    set PDK_ECLIPSE_ID=com.ti.pdk.dra7xx
    set RTSC_PLATFORM_NAME=ti.platforms.evmDRA7XX
    if %PROCESSOR% == arm (
        set RTSC_TARGET=gnu.targets.arm.A15F
        set CCS_DEVICE="Cortex A.DRA75x_DRA74x"
    ) else if %PROCESSOR% == m4 (
        set RTSC_TARGET=ti.targets.arm.elf.M4
        set CCS_DEVICE="Cortex M.DRA75x_DRA74x"
    )
) else if %SOC% == DRA78x (
    set PDK_PARTNO=DRA78x
    set PDK_ECLIPSE_ID=com.ti.pdk.dra7xx
    set RTSC_PLATFORM_NAME=ti.platforms.evmTDA3XX
    if %PROCESSOR% == m4 (
        set RTSC_TARGET=ti.targets.arm.elf.M4
        set CCS_DEVICE="Cortex M.TDA3x"
    )
) else if  %SOC% == am65xx (
    set PDK_PARTNO=AM65XX
    set PDK_ECLIPSE_ID=com.ti.pdk.am65xx
    if %PROCESSOR% == mpu (
        set RTSC_PLATFORM_NAME=ti.platforms.cortexA:AM65X
        set RTSC_TARGET=gnu.targets.arm.A53F
        set CCS_DEVICE="Cortex A.AM6548"
    ) else if %PROCESSOR% == mcu (
        set RTSC_PLATFORM_NAME=ti.platforms.cortexR:AM65X
        set RTSC_TARGET=ti.targets.arm.elf.R5F
        set CCS_DEVICE="Cortex R.AM6548"
    )
) else (
    REM Need to exit the batch script cleanly 
    set PDK_PARTNO=TCI6634
    set PDK_ECLIPSE_ID=ti.pdk
    set RTSC_PLATFORM_NAME=ti.platforms.simKepler
)

REM RTSC Target 
REM - Please ensure that you select this taking into account the
REM   OUTPUT_FORMAT and the RTSC_PLATFORM_NAME 
if %PROCESSOR% == dsp (
    if %ENDIAN% == big (
        set RTSC_TARGET=ti.targets.elf.C66_big_endian
        set CCS_DEVICE="com.ti.ccstudio.deviceModel.C6000.GenericC64xPlusDevice"
        set DSP_TYPE=c66
    ) else (
        if %SOC% == OMAPL137 (
            set RTSC_TARGET=ti.targets.elf.C674
            set CCS_DEVICE="com.ti.ccstudio.deviceModel.C6000.GenericC674xDevice"
            set DSP_TYPE=c674x
        ) else if %SOC% == OMAPL138 (
            set RTSC_TARGET=ti.targets.elf.C674
            set CCS_DEVICE="com.ti.ccstudio.deviceModel.C6000.GenericC674xDevice"
            set DSP_TYPE=c674x
        ) else (
            set RTSC_TARGET=ti.targets.elf.C66
            set CCS_DEVICE="com.ti.ccstudio.deviceModel.C6000.GenericC64xPlusDevice"
            set DSP_TYPE=c66
        )
    )
)

echo    PDK_PARTNO         : %PDK_PARTNO%
echo    PDK_ECLIPSE_ID     : %PDK_ECLIPSE_ID%
echo    RTSC_PLATFORM_NAME : %RTSC_PLATFORM_NAME%
echo.   RTSC_TARGET        : %RTSC_TARGET%
echo.   CCS_DEVICE         : %CCS_DEVICE%
REM *****************************************************************************
REM *****************************************************************************
REM                 Please do NOT change anything below this
REM *****************************************************************************
REM *****************************************************************************

REM Set auto create command by default for use with CCSv8
set AUTO_CREATE_COMMAND=eclipse\eclipsec -noSplash

REM If is CCS version 4 then set auto create command for use with CCSv4
if .%IS_CCS_VERSION_4% == .yes set AUTO_CREATE_COMMAND=eclipse\jre\bin\java -jar %CCS_INSTALL_PATH%\eclipse\startup.jar

REM Set project for Silicon or QT by default
set SIMULATOR_SUPPORT_DEFINE=

REM If simulator support is needed then set the define
if .%IS_SIMULATOR_SUPPORT_NEEDED% == .yes set SIMULATOR_SUPPORT_DEFINE=-ccs.setCompilerOptions "--define SIMULATOR_SUPPORT"

REM Goto the PDK Installation Path.

pushd %PDK_SHORT_NAME%

echo *****************************************************************************
echo Detecting all projects in PDK and importing them in the workspace %MY_WORKSPACE%

set RTSC_PRODUCTS=com.ti.rtsc.SYSBIOS:%BIOS_VERSION%;%PDK_ECLIPSE_ID%:%PDK_VERSION%

REM check version of the NDK  IPC EDMA and UIA
if exist "%SDK_INSTALL_PATH%/edma3_lld_%EDMA_VERSION:.=_%" (
	set RTSC_EDMA=;com.ti.sdo.edma3:%EDMA_VERSION%
)

if %SOC% == AM335x goto skip_ipc
if %SOC% == AM437x goto skip_ipc

if exist "%SDK_INSTALL_PATH%/ipc_%IPC_VERSION:.=_%" (
	set RTSC_IPC=;com.ti.rtsc.IPC:%IPC_VERSION%
)
:skip_ipc
if exist "%SDK_INSTALL_PATH%/ndk_%NDK_VERSION:.=_%" (
	set RTSC_NDK=;com.ti.rtsc.NDK:%NDK_VERSION%
)
if exist "%SDK_INSTALL_PATH%/uia_%UIA_VERSION:.=_%" (
	set RTSC_UIA=;com.ti.uia:%UIA_VERSION%
)

set RTSC_PRODUCTS="%RTSC_PRODUCTS%%RTSC_EDMA%%RTSC_IPC%%RTSC_NDK%%RTSC_UIA%"

REM Set MODULE to null string so it picks up all projects of PROCESSOR
if %MODULE% == all set MODULE=""

REM Set BOARD to equal the SOC if BOARD is set to "all".  All projects for the
REM SOC will be picked up
REM Additionally for AM335x, check for AMIC110 board
set AMIC110BOARD=
if %BOARD% == all set BOARD=%SOC%
if %BOARD% == AM335x set AMIC110BOARD="*%MODULE%*AMIC110*arm*roject.txt"
REM Set MODULE to null string so it picks up all projects of PROCESSOR
if %MODULE% == all set MODULE=""
REM Set PROJECT_TYPE to null string so it picks up all project types
if %PROJECT_TYPE% == all set PROJECT_TYPE=""

if %PROCESSOR% == dsp (
    REM Search for all the dsp test Project Files in the PDK.
    for /F %%I IN ('dir /b /s *%MODULE%*%BOARD%*%DSP_TYPE%*%PROJECT_TYPE%*roject.txt') do (
        set project_detected=1

        echo Detected Test Project: %%~nI

        REM Goto each directory where the test project file is located and create the projects.
        pushd %%~dI%%~pI

        REM Execute the command to create the project using the parameters specified above.
        %CCS_INSTALL_PATH%\%AUTO_CREATE_COMMAND% -data %MY_WORKSPACE% -application com.ti.ccstudio.apps.projectCreate -ccs.name %%~nI -ccs.outputFormat %OUTPUT_FORMAT% -ccs.setCompilerOptions "-DUSE_BIOS" -ccs.device %CCS_DEVICE% -ccs.endianness %ENDIAN% -ccs.kind executable -ccs.cgtVersion %CGT_VERSION% -rtsc.xdcVersion %XDC_VERSION% -rtsc.enableDspBios -rtsc.biosVersion %BIOS_VERSION% -rtsc.buildProfile "debug" -rtsc.products "%RTSC_PRODUCTS%" -rtsc.platform "%RTSC_PLATFORM_NAME%" -rtsc.target %RTSC_TARGET% -ccs.rts libc.a -ccs.args %%~nI%%~xI %SIMULATOR_SUPPORT_DEFINE% -ccs.overwrite full -ccs.setPostBuildStep "${TI_PDK_INSTALL_DIR}/packages/pdkAppImageCreate.bat ${TI_PDK_INSTALL_DIR}/packages ${CG_TOOL_ROOT} ${PROJECT_LOC}/${ConfigName} ${ProjName} %SOC% %PROCESSOR%"

        echo Copying macros.ini
        copy %MACROS_FILE% %MY_WORKSPACE%\%%~nI\macros.ini

        popd
    )

)

REM Setting linker option for arm projects
if %SOC% == OMAPL137 (
    set LINKER_OPT=""
    set COMPILER_OPT=""
    set COMPILER=%CGT_VERSION_ARM9%
) else if %SOC% == OMAPL138 (
    set LINKER_OPT=""
    set COMPILER_OPT=""
    set COMPILER=%CGT_VERSION_ARM9%
) else if  %SOC% == am65xx (
    set LINKER_OPT=""
    set COMPILER_OPT=""
    set COMPILER=%CGT_VERSION_ARM_A53%
) else (
    set LINKER_OPT="-L${BIOS_CG_ROOT}/packages/gnu/targets/arm/libs/install-native/arm-none-eabi/lib/hard --specs=nano.specs"
    set COMPILER_OPT="-I${CG_TOOL_ROOT}/arm-none-eabi/include/newlib-nano "
    set COMPILER=%CGT_VERSION_ARM%
)

set arm_or_mpu="F"
if %PROCESSOR% == arm set arm_or_mpu="T"
if %PROCESSOR% == mpu set arm_or_mpu="T"

if %arm_or_mpu% == "T" (
    REM Search for all the arm test Project Files in the PDK.
    for /F %%I IN ('dir /b /s *%MODULE%*%BOARD%*%PROCESSOR%*%PROJECT_TYPE%*roject.txt %AMIC110BOARD%') do (
        set project_detected=1
        
        echo Detected Test Project: %%~nI

        REM Goto each directory where the test project file is located and create the projects.
        pushd %%~dI%%~pI

        REM Expands the projectname variable which is used for identifying the baremetal and SYSBIOS project.
        set projectName=%%~nI
        REM Run CCS create command specific to baremetal and OS projects
        if "x!projectName:nonOS=!" == "x!projectName!" (
            REM Execute the command to create the OS project using the parameters specified above.
            %CCS_INSTALL_PATH%\%AUTO_CREATE_COMMAND% -data %MY_WORKSPACE% -application com.ti.ccstudio.apps.projectCreate -ccs.cmd "" -ccs.name %%~nI -ccs.outputFormat %OUTPUT_FORMAT% -ccs.setCompilerOptions %COMPILER_OPT% -ccs.setCompilerOptions "-DUSE_BIOS" -ccs.setLinkerOptions %LINKER_OPT% -ccs.device %CCS_DEVICE% -ccs.endianness %ENDIAN% -ccs.kind executable -ccs.cgtVersion "%COMPILER%" -rtsc.xdcVersion %XDC_VERSION% -rtsc.enableDspBios -rtsc.biosVersion %BIOS_VERSION% -rtsc.buildProfile "debug" -rtsc.products  "%RTSC_PRODUCTS%" -rtsc.platform "%RTSC_PLATFORM_NAME%" -rtsc.target %RTSC_TARGET% -ccs.rts libc.a libgcc.a libuart.a libm.a libnosys.a -ccs.args %%~nI%%~xI %SIMULATOR_SUPPORT_DEFINE% -ccs.overwrite full  -ccs.setPostBuildStep "${TI_PDK_INSTALL_DIR}/packages/pdkAppImageCreate.bat ${TI_PDK_INSTALL_DIR}/packages ${CG_TOOL_ROOT} ${PROJECT_LOC}/${ConfigName} ${ProjName} %SOC% %PROCESSOR%"
        ) else (
            REM Execute the command to create the baremetal project using the parameters specified above.
            %CCS_INSTALL_PATH%\%AUTO_CREATE_COMMAND% -data %MY_WORKSPACE% -application com.ti.ccstudio.apps.projectCreate -ccs.cmd "" -ccs.name %%~nI -ccs.outputFormat %OUTPUT_FORMAT% -ccs.device %CCS_DEVICE% -ccs.endianness %ENDIAN% -ccs.outputType executable -ccs.cgtVersion "%CGT_VERSION_ARM%"  -ccs.args %%~nI%%~xI -ccs.overwrite full  -ccs.setPostBuildStep "$(CG_TOOL_ROOT)/bin/arm-none-eabi-objcopy -O binary "%%~nI.out" "%%~nI.bin"

            REM Deletes the startup file generated defaultly by CCS tool
            del /q %MY_WORKSPACE%\%%~nI\*.S
		)

        echo Copying macro.ini
        copy %MACROS_FILE% %MY_WORKSPACE%\%%~nI\macros.ini

        popd
    )
)

set m4_or_mcu="F"
if %PROCESSOR% == m4 set m4_or_mcu="T"
if %PROCESSOR% == mcu set m4_or_mcu="T"

if %m4_or_mcu% == "T"  (
    REM Search for all the m4 test Project Files in the PDK.
    for /F %%I IN ('dir /b /s *%MODULE%*%BOARD%*%PROCESSOR%*%PROJECT_TYPE%*roject.txt') do (
        set project_detected=1
        
        echo Detected Test Project: %%~nI

        REM Goto each directory where the test project file is located and create the projects.
        pushd %%~dI%%~pI

        REM Execute the command to create the project using the parameters specified above.
        %CCS_INSTALL_PATH%\%AUTO_CREATE_COMMAND% -data %MY_WORKSPACE% -application com.ti.ccstudio.apps.projectCreate -ccs.cmd "" -ccs.name %%~nI -ccs.outputFormat %OUTPUT_FORMAT% -ccs.setCompilerOptions "-DUSE_BIOS" -ccs.device %CCS_DEVICE% -ccs.endianness %ENDIAN% -ccs.kind executable -ccs.cgtVersion "%CGT_M4_VERSION%" -rtsc.xdcVersion %XDC_VERSION% -rtsc.enableDspBios -rtsc.biosVersion %BIOS_VERSION% -rtsc.buildProfile "debug" -rtsc.products "%RTSC_PRODUCTS%" -rtsc.platform "%RTSC_PLATFORM_NAME%" -rtsc.target %RTSC_TARGET% -ccs.rts libc.a libgcc.a libuart.a libm.a libnosys.a -ccs.args %%~nI%%~xI %SIMULATOR_SUPPORT_DEFINE% -ccs.overwrite full -ccs.setPostBuildStep "${TI_PDK_INSTALL_DIR}/packages/pdkAppImageCreate.bat ${TI_PDK_INSTALL_DIR}/packages ${CG_TOOL_ROOT} ${PROJECT_LOC}/${ConfigName} ${ProjName} %SOC% %PROCESSOR%"

        echo Copying macro.ini
        copy %MACROS_FILE% %MY_WORKSPACE%\%%~nI\macros.ini

        popd
    )
)

popd

if not defined project_detected (
    echo No projects detected
)

echo Project generation complete
echo *****************************************************************************

:ENDSCRIPT
endlocal
