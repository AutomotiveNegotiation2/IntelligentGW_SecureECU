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
  [ "PDK API Guide for J721E", "index.html", [
    [ "PDK API Guide", "index.html", null ],
    [ "Enet Integration Guide", "enet_integration_guide_top.html", [
      [ "Getting Familiar with Enet LLD APIs", "enet_integration_guide_top.html#GettingFamiliarWithAPIs", [
        [ "IOCTL Interface", "enet_integration_guide_top.html#IOCTL_description", null ]
      ] ],
      [ "Integrating Enet LLD into User's Application", "enet_integration_guide_top.html#enet_integration_in_app", [
        [ "Init Sequence", "enet_integration_guide_top.html#enet_init_sequence", null ],
        [ "Peripheral Open Sequence", "enet_integration_guide_top.html#enet_open_sequence", null ],
        [ "Port Open Sequence", "enet_integration_guide_top.html#enet_openport_sequence", null ],
        [ "Packet Send/Receive Sequence", "enet_integration_guide_top.html#enet_pktrxtx_sequence", null ],
        [ "Packet Timestamping Sequence", "enet_integration_guide_top.html#enet_pktts_sequence", null ],
        [ "IOCTL Sequence", "enet_integration_guide_top.html#enet_ioctl_sequence", null ],
        [ "Port Close Sequence", "enet_integration_guide_top.html#enet_closeport_sequence", null ],
        [ "Peripheral Close Sequence", "enet_integration_guide_top.html#enet_close_sequence", null ],
        [ "Deinit Sequence", "enet_integration_guide_top.html#enet_deinit_sequence", null ],
        [ "Peripheral-specific", "enet_integration_guide_top.html#enetper_specific_handling", [
          [ "ICSSG Dual-MAC", "enet_integration_guide_top.html#enetper_icssg_dmac_specific_handling", [
            [ "Firmware", "enet_integration_guide_top.html#enetper_icssg_dmac_fw_specific_handling", null ],
            [ "Firmware Memory Pools", "enet_integration_guide_top.html#enetper_icssg_dmac_fwmem_specific_handling", null ]
          ] ],
          [ "ICSSG Switch", "enet_integration_guide_top.html#enetper_icssg_swt_specific_handling", [
            [ "Firmware", "enet_integration_guide_top.html#enetper_icssg_swt_fw_specific_handling", null ],
            [ "Firmware Memory Pools", "enet_integration_guide_top.html#enetper_icssg_swt_fwmem_specific_handling", null ]
          ] ]
        ] ]
      ] ],
      [ "Migrating from EMAC LLD", "enet_integration_guide_top.html#emac_lld_migration", [
        [ "ICSSG Migration", "enet_integration_guide_top.html#emac_lld_migration_icssg", [
          [ "Peripheral open", "enet_integration_guide_top.html#emac_lld_migration_icssg_per_open", null ],
          [ "IOCTLs", "enet_integration_guide_top.html#emac_lld_migration_icssg_ioctl", [
            [ "Asynchronous IOCTLs", "enet_integration_guide_top.html#emac_lld_migration_icssg_async_ioctl", null ],
            [ "IOCTL Command Mappings", "enet_integration_guide_top.html#emac_lld_migration_icssg_ioctl_mappings", null ]
          ] ],
          [ "Packet send and receive", "enet_integration_guide_top.html#emac_lld_migration_icssg_dma", null ]
        ] ]
      ] ]
    ] ],
    [ "Enet LLD IOCTL interface", "enet_ioctl_interface.html", [
      [ "Introduction", "enet_ioctl_interface.html#enet_ioctl_intro", [
        [ "Using the IOCTL interface", "enet_ioctl_interface.html#using_enet_ioctl", null ],
        [ "Synchronous and Asynchronous IOCTLs", "enet_ioctl_interface.html#enet_async_ioctl", null ]
      ] ]
    ] ],
    [ "Enet LLD Introduction", "enetlld_top.html", [
      [ "Introduction", "enetlld_top.html#enetlld_intro", null ],
      [ "Application Programming Interface", "enetlld_top.html#enetlld_api_overview", null ],
      [ "Enet Peripherals", "enetlld_top.html#enetlld_enetpers", [
        [ "CPSW Peripheral", "enetlld_top.html#enetper_cpsw", [
          [ "CPSW as a replacement to External Switch", "enetlld_top.html#cpsw_external_switch_replacement", null ]
        ] ],
        [ "ICSSG Peripheral", "enetlld_top.html#enetper_icssg", [
          [ "ICSSG Dual-MAC", "enetlld_top.html#enetper_icssg_dualmac", null ],
          [ "ICSSG Switch Mode", "enetlld_top.html#enetper_icssg_switch", null ]
        ] ]
      ] ],
      [ "Integration", "enetlld_top.html#enetlld_integration", null ],
      [ "Document Revision History", "enetlld_top.html#enetlld_hist", null ]
    ] ],
    [ "Ethernet PHY Integration Guide", "enetphy_guide_top.html", [
      [ "Introduction", "enetphy_guide_top.html#enetphy_guide_intro", null ],
      [ "PHY Driver", "enetphy_guide_top.html#enetphy_guide_driver", [
        [ "Device-Specific Drivers", "enetphy_guide_top.html#enetphy_guide_device_specific", null ],
        [ "PHY to Driver Binding", "enetphy_guide_top.html#enetphy_guide_binding", null ]
      ] ],
      [ "Implementing a New PHY Driver", "enetphy_guide_top.html#enetphy_guide_implementing", null ],
      [ "Appendix", "enetphy_guide_top.html#enetphy_guide_appendix", [
        [ "Appendix A", "enetphy_guide_top.html#enetphy_guide_appendix_a", null ]
      ] ]
    ] ],
    [ "Ethernet PHY Link Configuration", "enetphy_link_config_top.html", [
      [ "Link Configuration Guidelines", "enetphy_link_config_top.html#enetphy_link_config_guidelines", [
        [ "Manual Mode", "enetphy_link_config_top.html#enetphy_link_manual", [
          [ "Half-Duplex Mode", "enetphy_link_config_top.html#enetphy_link_manual_half_duplex", null ],
          [ "Full-Duplex Mode", "enetphy_link_config_top.html#enetphy_link_manual_full_duplex", null ]
        ] ],
        [ "Auto-Negotiation Mode", "enetphy_link_config_top.html#enetphy_link_autoneg", null ],
        [ "Strapping", "enetphy_link_config_top.html#enetphy_link_strapping", null ]
      ] ]
    ] ],
    [ "Modules", "modules.html", "modules" ]
  ] ]
];

var NAVTREEINDEX =
[
"enet_integration_guide_top.html",
"group__BOARD__LIB__DEVICES__FPD__DS90UB924__TYPES.html#ga1b846948e5f2e1b5315a2ca379c2407b",
"group__BOARD__LIB__DEVICES__FPD__DS90UB941__APIS.html#ga570a924ef2340cf0aa72f48398a576f3",
"group__BOARD__LIB__DEVICES__FPD__DS90UB941__TYPES.html#gafd42c0008f4a02756b813801831f71fb",
"group__BOARD__LIB__DEVICES__POWER__TPS65941__TYPES.html#ga5499b5d6e22aed76a39ef87632362e89",
"group__BOARD__LIB__DEVICES__POWER__TPS65941__TYPES.html#gac86cb58ab2419c766fa623a79cc6d8b0",
"group__BOARD__LIB__MODULE__TYPES.html#ga50aed068b7e7e58a313c10015ca7b45a",
"group__CPSW__ALE__MOD.html#ggabed7e8ccaf9e220220ce26e85697cb98ac9addf63cced15b453dc339475d928b0",
"group__CSL__CPGMAC__SL__FUNCTION.html#gac5b46849a4f36fadafdbfeaeb6aef70f",
"group__CSL__CPSWITCH__FUNCTION.html#ga939d9a8afd1a5b0e726e95b17ed23317",
"group__CSL__DRU__DATASTRUCT.html",
"group__CSL__DSSVIDEOPORT.html#ga83c39468cbfb3ce4b988e3cbd2c7aba4",
"group__CSL__UDMAP__CPPI5__DATASTRUCT.html#ga8dd419284903b6aaa4846a42d73efb0c",
"group__CSL__UDMAP__ENUM.html#gafe6d3345d9c85b58e570b80e94f23fe1",
"group__DRV__CSIRX__CFG__MODULE.html#ga441f7bf85a5d0a99bc43770e78dbb179",
"group__DRV__DSS__DCTRL__IOCTL.html#ga3d29253c153bdec7275527bd0b8fe4dc",
"group__DRV__ENET__CPSW.html#gga41173bc4b7704ac126f8be8e0bbd5805a1aee1a744ffbdcbcdc65a485d760d593",
"group__DRV__FCP__MODULE__CFG.html#gaa77ae66febbfeaa9bdb21a8aaa8bd7b4",
"group__DRV__IPC__SOC__MODULE.html#ga76655b10ef96e3444322cd2f8b39be84",
"group__DRV__MSC__MODULE__CFG.html#ga346539ae775b4af8fb5add245cae5951",
"group__DRV__OSAL__EventP.html#gae51e2359c71afbb4bc9486225cf77c0a",
"group__DRV__PMIC__API__MODULE.html#ga55203ffd4e415fe10ac2526b3582f8dc",
"group__DRV__PMIC__FSM__MODULE.html#ga61b0e0a8c3f2393aff05ebca1acc53d9",
"group__DRV__PMIC__IRQ__MODULE.html#ga7edc6b54e2c7f3e5a921f22e7d230dc0",
"group__DRV__PMIC__POWER__MODULE.html#ga78c0d3a1f9a859c9b5da8bc572492eff",
"group__DRV__PMIC__RTC__MODULE.html#ga54de7ae3f9b8a45fd582b8614255e25a",
"group__DRV__SDE__MODULE__INTERFACE.html#ga6c9cfb5809bad7902e94d50ebf3974c2",
"group__DRV__UDMA__CFG__MODULE.html#ga7e22dd400389882fc8f7768d5f9f967b",
"group__DRV__UDMA__RING__MODULE.html#ga2da129bfb0afb802d788cd1a2839a423",
"group__ENET__LWIP__DEFAULT__NETIF__API.html#ga772173eb1743e0c951b3e02bf15c95b5",
"group__ENET__MOD__MDIO.html#ga8011d3a174afba1c442a89d2d8df3205",
"group__ENET__UDMA__CPPI__PSI.html#ga80c40b331a1239902ee3a8ae9b9aeb9e",
"group__tisci__core.html#ga97b5b6e7d3bbee04f7494543e4858cb7",
"group__tisci__protocol.html#gae12a14747488a190e8240b6882ef9b8e",
"structBoard__Tps65941PwrResourceRegCfg.html#a84993a4f7f628ee9d0ef8213c2078291",
"structCSITX__EpdConfig__s.html",
"structCSL__CPSW__FLOWCNTL.html#a7189324a4dfa2eba9f4e38c555846176",
"structCSL__CsitxRevisionId.html#af58c2209b48cf2138fa670145c803ee7",
"structCSL__UdmapRT.html#a5d0a870ed68f9d49d59128581d13d931",
"structCpswAle__PortCfg.html#a9defbd0b99bd98fafc4b0b9965c441c6",
"structCpswStats__HostPort__2g.html#aedda2cec19eb13108fa6900c04d7bde3",
"structCpsw__PortRxFlowInfo.html#af1012d2cec9288711c1f69d296bee826",
"structDss__DctrlVpParams.html#aa76e94e775ed4a9146ebc8fc937c904e",
"structEnetPhy__Obj.html#ad5381dcfc88775aea033df40e7610d98",
"structEnetUdma__TxProtoInfo.html#a13ddba4a1e83b3cbe1f4d5c20a3e1553",
"structHeapP__Params.html#a76df512ef60c6a0afd6dff02450ef4ae",
"structIcssg__SetAcceptFrameCheckInArgs.html#a92da51dc0ad7c5f3234dd32b6787542f",
"structMcasp__HwSetup.html#a075c1fed9c10d3b7025c246965e345dc",
"structPmic__CoreHandle__t.html#ac31cc1499b88e6e7d8673d82f61c32e9",
"structRfe__WdrConfig.html#accdb8f4a55625da604baa3881f60e787",
"structUdma__DrvObj.html#a33e09c8e06a4f5ca6ff26d202853bc70",
"structVhwa__M2mDofCreateArgs.html",
"structtisci__boardcfg__rm__host__cfg__entry.html",
"structtisci__msg__keywriter__resp.html#a789f71e6c4a9b2cae05ae3a638180ffd",
"structtisci__msg__rm__udmap__gcfg__cfg__req.html"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';