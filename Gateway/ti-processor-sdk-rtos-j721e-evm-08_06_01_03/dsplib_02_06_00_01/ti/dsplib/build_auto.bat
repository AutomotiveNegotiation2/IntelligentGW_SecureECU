@echo off
:: *************************************************************************
::  FILE           : build_auto.bat
::  DESCRIPTION    :
::
::     This batch script installs all tools and creates all VLIB releases
::
:: *************************************************************************

:: *************************************************************************
:: *** Enter the scripts directory
:: *************************************************************************
@cd scripts


:: *************************************************************************
:: *** Install all tools
:: *************************************************************************
call install_tools

:: *************************************************************************
:: *** Check build target command line input (ARG1)
:: *************************************************************************
:check_target
if "%1" == ""      goto call_build
if "%1" == "all"   goto call_build
if "%1" == "C66"   goto call_build
if "%1" == "C71"  goto call_build


:: USAGE:
echo ERROR: Option "%1" supplied is invalid...
echo .
echo . Usage: %0 [all C66 C71 Verify] (defaults to "all")
echo .
echo .     "all"    : Build all targets 
echo .     "C66"    : Build just the C66x vxlib targets 
echo .     "C71"    : Build just the C71x vxlib targets 
goto end


:: *************************************************************************
:: *** Build all artifacts
:: *************************************************************************
:call_build

@cd scripts

call build_release %1 %2


:: *************************************************************************
:: *** Archive and label all artifacts
:: *************************************************************************
:call_archive
@cd scripts
bash reporevs.sh
@cd ..


:end
:: *************************************************************************
:: *** Nothing past this point
:: *************************************************************************

