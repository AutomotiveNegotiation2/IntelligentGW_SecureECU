/*
@ @licstart  The following is the entire license notice for the
JavaScript code in this file.

Copyright (C) 1997-2017 by Dimitri van Heesch

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

@licend  The above is the entire license notice
for the JavaScript code in this file
*/
var NAVTREE =
[
  [ "MCUSW", "index.html", [
    [ "User Guide", "mcusw_c_ug_top.html", [
      [ "Integrated MCU", "mcusw_c_ug_top.html#mcusw_c_ug_mcu", null ],
      [ "Getting access to MCUSW", "mcusw_c_ug_top.html#mcusw_c_ug_access", null ],
      [ "License for Configurator", "mcusw_c_ug_top.html#mcusw_c_ug_cfg_licenses", null ],
      [ "Supported Device Families", "mcusw_c_ug_top.html#mcusw_supported_family", null ],
      [ "Package Contents", "mcusw_c_ug_top.html#mcusw_c_ug_pkg_contents", [
        [ "MCU Demos", "mcusw_c_ug_top.html#mcusw_c_ug_mcu_demos", null ],
        [ "MCAL", "mcusw_c_ug_top.html#mcusw_c_ug_mcal", null ],
        [ "Supported Drivers", "mcusw_c_ug_top.html#mcusw_c_ug_core_list", null ]
      ] ],
      [ "Dependencies", "mcusw_c_ug_top.html#mcusw_instal_top", [
        [ "Hardware Dependencies", "mcusw_c_ug_top.html#mcusw_depend_hw", [
          [ "J721E EVM", "mcusw_c_ug_top.html#mcusw_depend_evm_j721e", null ],
          [ "J721S2 EVM", "mcusw_c_ug_top.html#mcusw_depend_evm_j721s2", null ],
          [ "J784S4 EVM", "mcusw_c_ug_top.html#mcusw_depend_evm_j784s4", null ],
          [ "J721E/J7200/J721S2 EVM NO Boot Mode / CCS", "mcusw_c_ug_top.html#mcusw_depend_evm_j721e_ccs", null ],
          [ "J784S4 EVM NO Boot Mode / CCS", "mcusw_c_ug_top.html#mcusw_depend_evm_j784s4_ccs", null ],
          [ "J721E/J7200/J721S2 EVM MMC/SD Boot Mode", "mcusw_c_ug_top.html#mcusw_depend_evm_j721e_mmcsd", null ],
          [ "J784S4 EVM MMC/SD Boot Mode", "mcusw_c_ug_top.html#mcusw_depend_evm_j784s4_mmcsd", null ],
          [ "J721E/J7200 EVM OSPI Boot Mode", "mcusw_c_ug_top.html#mcusw_depend_evm_j721e_ospi", null ],
          [ "J721S2 EVM OSPI Boot Mode", "mcusw_c_ug_top.html#mcusw_depend_evm_j721s2_ospi", null ],
          [ "J784S4 EVM OSPI Boot Mode", "mcusw_c_ug_top.html#mcusw_depend_evm_j784s4_ospi", [
            [ "Built in emulator", "mcusw_c_ug_top.html#mcusw_depend_inbuilt_jtag_j721e", null ]
          ] ],
          [ "Emulator", "mcusw_c_ug_top.html#mcusw_depend_jtag", null ],
          [ "Compiler & Code generation Tools", "mcusw_c_ug_top.html#mcusw_depend_compiler", null ],
          [ "PDK", "mcusw_c_ug_top.html#mcusw_depend_pdk", [
            [ "CSL", "mcusw_c_ug_top.html#mcusw_depend_pdk_csl", null ],
            [ "UDMA", "mcusw_c_ug_top.html#mcusw_depend_pdk_udma", null ],
            [ "IPC", "mcusw_c_ug_top.html#mcusw_depend_pdk_ipc", null ],
            [ "MCAL Example Application", "mcusw_c_ug_top.html#mcusw_depend_eg", null ],
            [ "MCU SW Demo Application", "mcusw_c_ug_top.html#mcusw_demo_depend_eg", null ],
            [ "MCAL module dependencies on PDK", "mcusw_c_ug_top.html#mcusw_mcal_pdk_depend_eg", null ]
          ] ],
          [ "MCAL Configurator : Elektrobit Tresos", "mcusw_c_ug_top.html#mcusw_depend_cfg_eb", null ]
        ] ],
        [ "IDE (CCS)", "mcusw_c_ug_top.html#mcusw_instal_ccs", [
          [ "J721E/J7200/J721S2/J784S4", "mcusw_c_ug_top.html#mcusw_instal_ccs_gel_setup", null ]
        ] ]
      ] ],
      [ "Installation Steps", "mcusw_c_ug_top.html#mcusw_instal_steps", [
        [ "J721E/J7200/J721S2/J784S4", "mcusw_c_ug_top.html#mcuw_post_install_j721e", null ]
      ] ],
      [ "Directory Structure", "mcusw_c_ug_top.html#mcusw_dir", [
        [ "MCAL", "mcusw_c_ug_top.html#mcusw_dir_mcal", [
          [ "MCAL Examples", "mcusw_c_ug_top.html#mcusw_dir_mcal_eg", null ],
          [ "MCAL Examples Configuration", "mcusw_c_ug_top.html#mcusw_dir_mcal_eg_cfg", null ]
        ] ],
        [ "MCUSS Demonstration Applications", "mcusw_c_ug_top.html#mcusw_dir_mcuss_demos", [
          [ "MCAL Dependencies", "mcusw_c_ug_top.html#mcusw_dir_mcuss_mcal", null ],
          [ "Utilities", "mcusw_c_ug_top.html#mcusw_dir_mcuss_utils", null ],
          [ "Demos", "mcusw_c_ug_top.html#mcusw_dir_mcuss_demos_apps", null ]
        ] ]
      ] ],
      [ "Build", "mcusw_c_ug_top.html#mcusw_build_top", [
        [ "Setup Build Environment", "mcusw_c_ug_top.html#mcusw_build_setup_env", [
          [ "J721E", "mcusw_c_ug_top.html#mcusw_build_setup_env_j721e", null ],
          [ "J7200", "mcusw_c_ug_top.html#mcusw_build_j7200", null ]
        ] ],
        [ "Build Everything MCAL", "mcusw_c_ug_top.html#mcusw_build_all_mcal", null ],
        [ "Build All Demos", "mcusw_c_ug_top.html#mcusw_build_all_demos", null ],
        [ "Profiles", "mcusw_c_ug_top.html#mcusw_build_profiles", null ],
        [ "Other useful commands", "mcusw_c_ug_top.html#mcusw_build_lib", null ],
        [ "Examples Linker File (Select memory location to hold example binary)", "mcusw_c_ug_top.html#mcusw_build_eg_linker", null ]
      ] ],
      [ "Porting MCAL module example applications to other cores", "mcusw_c_ug_top.html#mcusw_c_ug_support_mcal_other_cores", null ],
      [ "Running Examples", "mcusw_c_ug_top.html#mcusw_run_eg", [
        [ "IDE", "mcusw_c_ug_top.html#mcusw_run_ccs", [
          [ "CCS", "mcusw_c_ug_top.html#mcusw_run_ccs_setup", [
            [ "Load Example Binaries", "mcusw_c_ug_top.html#mcusw_run_ccs_load_binary", null ]
          ] ]
        ] ],
        [ "SBL", "mcusw_c_ug_top.html#mcusw_run_sbl", [
          [ "J721E/J7200/J721S2/J784S4", "mcusw_c_ug_top.html#mcusw_run_sbl_j721e", [
            [ "SD/MMC", "mcusw_c_ug_top.html#mcusw_run_sbl_j721e_mmc", null ],
            [ "OSPI", "mcusw_c_ug_top.html#mcusw_run_sbl_j721e_ospi", null ]
          ] ]
        ] ]
      ] ],
      [ "Compiler Flags used", "mcusw_c_ug_top.html#mcusw_cflag", [
        [ "MCAL Drivers - Profile : Release", "mcusw_c_ug_top.html#mcusw_cflag_drv_rel", null ],
        [ "MCAL Examples - Profile : Release", "mcusw_c_ug_top.html#mcusw_cflag_eg", null ]
      ] ],
      [ "Steps to build in windows environment", "mcusw_c_ug_top.html#mcusw_j721e_win_build", null ],
      [ "Document Revision History", "mcusw_c_ug_top.html#mcusw_rev_history", null ]
    ] ],
    [ "Validation", "val_notes_mainpage.html", "val_notes_mainpage" ],
    [ "MCAL Configurator User Guide", "mcusw_cfg_ug_top.html", [
      [ "Introduction", "mcusw_cfg_ug_top.html#mcusw_cfg_ug_intro", [
        [ "Software Dependencies", "mcusw_cfg_ug_top.html#mcusw_cfg_ug_dep_sw", null ],
        [ "Reference Modules", "mcusw_cfg_ug_top.html#mcusw_cfg_ug_dep_mod", null ],
        [ "Directory Structure", "mcusw_cfg_ug_top.html#mcusw_cfg_ug_dir_top", null ],
        [ "A Typical Driver or Module Directory", "mcusw_cfg_ug_top.html#mcusw_cfg_ug_dir_drv", null ],
        [ "Reference EB Documentation", "mcusw_cfg_ug_top.html#mcusw_cfg_ug_ref", null ]
      ] ],
      [ "Installation", "mcusw_cfg_ug_top.html#mcusw_cfg_ug_install", [
        [ "Installing Configurator package", "mcusw_cfg_ug_top.html#mcusw_cfg_ug_install_package", null ],
        [ "Installing Elektrobit Tresos", "mcusw_cfg_ug_top.html#mcusw_cfg_ug_install_EB", [
          [ "Requesting Activation Key", "mcusw_cfg_ug_top.html#mcusw_cfg_ug_req_activation_key", null ],
          [ "Client License Administrator", "mcusw_cfg_ug_top.html#mcusw_cfg_ug_install_EB_CLA", null ],
          [ "EB", "mcusw_cfg_ug_top.html#mcusw_cfg_ug_install_EB_EB", null ],
          [ "Elektrobit Tresos License Troubleshooting", "mcusw_cfg_ug_top.html#mcusw_cfg_ug_install_EB_L_TB", null ]
        ] ]
      ] ],
      [ "MCAL Configuration Generation", "mcusw_cfg_ug_top.html#mcusw_cfg_ug_gen", [
        [ "Generation using tresos Studio GUI", "mcusw_cfg_ug_top.html#mcusw_cfg_ug_gen_gui", [
          [ "Launch <b>tresos Studio</b>", "mcusw_cfg_ug_top.html#mcusw_cfg_ug_gen_01", null ],
          [ "Configuration Project", "mcusw_cfg_ug_top.html#mcusw_cfg_ug_gen_02", null ],
          [ "Project Name", "mcusw_cfg_ug_top.html#mcusw_cfg_ug_gen_03", null ],
          [ "Target Name", "mcusw_cfg_ug_top.html#mcusw_cfg_ug_gen_04", null ],
          [ "Choose Required modules", "mcusw_cfg_ug_top.html#mcusw_cfg_ug_gen_05", null ],
          [ "Project Created", "mcusw_cfg_ug_top.html#mcusw_cfg_ug_gen_06", null ],
          [ "Generate Configuration", "mcusw_cfg_ug_top.html#mcusw_cfg_ug_gen_07", null ]
        ] ],
        [ "Generation using tresos Studio Command Line Interface", "mcusw_cfg_ug_top.html#mcusw_cfg_ug_gen_cmd", null ],
        [ "Generation of EPD and ARXML", "mcusw_cfg_ug_top.html#mcusw_cfg_ug_gen_epd_arxml", [
          [ "Generation of EPD", "mcusw_cfg_ug_top.html#mcusw_cfg_ug_gen_epd", null ],
          [ "Generation of ARXML", "mcusw_cfg_ug_top.html#mcusw_cfg_ug_gen_arxml", null ]
        ] ]
      ] ]
    ] ],
    [ "MCAL Module User Guide", "mcal_ug_top.html", "mcal_ug_top" ],
    [ "MCAL Module Design", "design_top.html", "design_top" ],
    [ "MCUSS Demo Applications", "demo_top.html", "demo_top" ],
    [ "Modules", "modules.html", "modules" ]
  ] ]
];

var NAVTREEINDEX =
[
"demo_boot_app_mcu_rtos_top.html",
"design_icu_top.html#design_icu_low_level_api_gettimeelapsed",
"group__MCAL__ADC__CFG.html#ga487f701743eacb79225e3b53caaf24dc",
"group__MCAL__DIO__CFG.html#ga080928af20d9548fac977e095f39a18d",
"group__MCAL__DIO__CFG.html#ga93c25230fff51930cb1d7301e6505dc6",
"group__MCAL__ETH__API.html#ga8f07fe106f2a485310764183bf002a42",
"group__MCAL__ETH__CFG.html#gaf2f3d77d5702d1bb540286fb8cc28af5",
"group__MCAL__ICU__API.html",
"group__MCAL__IPC__CFG.html#gada51736eb7354a9d1ca2017bfba0308d",
"group__MCAL__SPI__CFG.html#gga4fb500adb5b1ace36a9e51785b771f61afdcd6899ab13dd85ae7bc5b5baece8b7",
"structCan__ConfigType.html",
"structFls__ConfigType.html#ab5f0a832a284d02b417a7227b4b3988d",
"ug_cdd_ipc_top.html#ug_cdd_ipc_eg_log_j721e_mcu21",
"ug_icu_top.html#ug_icu_functional_cfg_v_wakeup"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';