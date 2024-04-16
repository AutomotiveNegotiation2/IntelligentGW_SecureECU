@REM ******************************************************************************
@REM * FILE PURPOSE: Environment Setup for building PDK
@REM ******************************************************************************
@REM * FILE NAME: pdksetupenv.bat
@REM *
@REM * DESCRIPTION:
@REM *  Configures and sets up the Build Environment for PDK.
@REM *
@REM *  The batch file expects an optional argument:PDK_INSTALL_PATH: Location
@REM *  of the PDK package.  If the argument is not specified the batch file
@REM *  assumes that the PDK is installed in the same location where the batch
@REM *  file is located and is being executed.
@REM *
@REM * USAGE:
@REM *  pdksetupenv.bat "C:\ti\pdk_<device>_<version>\packages"
@REM *   --- OR ---
@REM *  pdksetupenv.bat
@REM *
@REM * Copyright (C) 2012-2019, Texas Instruments, Inc.
@REM *****************************************************************************
@echo off
@REM *******************************************************************************
@REM ********************** GET PARAMETERS PASSED THROUGH ARGUMENT   ***************
@REM *******************************************************************************
@REM Parameter Validation: Check if the argument was passed to the batch file and
@REM if so we use that else we default to the working directory where the batch
@REM file was invoked from

@REM PDK_INSTALL_PATH if it is passed as an argument.
set pdk_path=%1

set PDK_INSTALL_PATH=%CD%

if defined pdk_path (
@REM Use the PDK install path if passed as an argument
set PDK_INSTALL_PATH=%pdk_path%
)

@REM Find the PDK_SOC/PDK_VER by going to the procsdk\pdk directory.
cd %PDK_INSTALL_PATH%\..

set s=%CD:\= %
for %%a  in (%s%) do (
  set pdkdir=%%a
)
for /f "tokens=1,2,3,4,5 delims=/_" %%a in ("%pdkdir%") do set pdksoc=%%b&set v1=%%c&set v2=%%d&set v3=%%e
set pdkdir_ver=%v1%_%v2%_%v3%

@REM When pdk folder represents a device family, set a default SOC for that family
if %pdksoc% == jacinto (
    set pdksoc=j721e
)

@REM Go to the SDK install directory
cd %PDK_INSTALL_PATH%\..\..

@REM Find the SDK directory to set SDK_INSTALL_PATH if it is not already set
set sdkdir=%CD:\=/%

if not defined SDK_INSTALL_PATH (
   set SDK_INSTALL_PATH=%sdkdir%
)

@REM PDK SoC and version
if not defined PDK_SOC (
   set PDK_SOC=%pdksoc%
)

if not defined PDK_VERSION (
    set PDK_VERSION=%pdkdir_ver%
)

@REM return to the original directory (pdk_*/packages)
cd %PDK_INSTALL_PATH%

@REM Find the XDC version from pdk/packages/ti/build/pdk_tools_path.mk
for /f %%i IN ('findstr "XDC_VERSION=" %PDK_INSTALL_PATH%\ti\build\pdk_tools_path.mk') do set xdcver=%%i
for /f "tokens=1,2 delims=//=" %%a in ("%xdcver%") do set XDC_VERSION=%%b

if not defined GMAKE_INSTALL_PATH (
    set GMAKE_INSTALL_PATH=%SDK_INSTALL_PATH%/xdctools_%XDC_VERSION%
)
set GMAKE_INSTALL_PATH=%GMAKE_INSTALL_PATH:\=/%
@REM GMAKE Tool location; Uncomment the following line to set the
@REM gmake install path into env PATH variable.
set PATH=%GMAKE_INSTALL_PATH:/=\%;%PATH%

set PDK_INSTALL_PATH=%PDK_INSTALL_PATH:\=/%
@REM Define Rules.make
set RULES_MAKE=%PDK_INSTALL_PATH%/ti/build/Rules.make

@REM Print the environmental variables
@echo ***************************************************
@echo Environment Configuration:
@echo ***************************************************
@echo     SDK_INSTALL_PATH        : %SDK_INSTALL_PATH%
@echo     PDK_INSTALL_PATH        : %PDK_INSTALL_PATH%
@echo     GMAKE_INSTALL_PATH      : %GMAKE_INSTALL_PATH%
@echo     PDK_SOC                 : %PDK_SOC%
@echo     PDK_VERSION             : %PDK_VERSION%
@echo     RULES_MAKE              : %RULES_MAKE%
@echo ***************************************************
