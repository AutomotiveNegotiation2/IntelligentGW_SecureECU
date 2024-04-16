var group__ENET__RM__API =
[
    [ "EnetRm_ResourceInfo", "structEnetRm__ResourceInfo.html", [
      [ "coreId", "structEnetRm__ResourceInfo.html#a1018833da2e0120f2d3a00320704f507", null ],
      [ "numTxCh", "structEnetRm__ResourceInfo.html#adbbe5905f0481575d6175963e888ec0e", null ],
      [ "numRxCh", "structEnetRm__ResourceInfo.html#aca13bcc9d04dbc098caaf26c85c5b62b", null ],
      [ "numRxFlows", "structEnetRm__ResourceInfo.html#a0a549dc877888817d6aee43713be5cb0", null ],
      [ "numMacAddress", "structEnetRm__ResourceInfo.html#a9ef765ed82439a8b68b464d31f462d12", null ]
    ] ],
    [ "EnetRm_ResPrms", "structEnetRm__ResPrms.html", [
      [ "numCores", "structEnetRm__ResPrms.html#aef5c0203b0c02afc893b6adfc6b754e7", null ],
      [ "coreDmaResInfo", "structEnetRm__ResPrms.html#ad4f2770a69b233ecbe5befa0747144ac", null ]
    ] ],
    [ "EnetRm_IoctlPermissionEntry", "structEnetRm__IoctlPermissionEntry.html", [
      [ "cmd", "structEnetRm__IoctlPermissionEntry.html#a638b0ba77ad9e399557e0cf1708fecfb", null ],
      [ "permittedCoreMask", "structEnetRm__IoctlPermissionEntry.html#a11ceb4fbd18af1ba763af51ca189e278", null ]
    ] ],
    [ "EnetRm_IoctlPermissionTable", "structEnetRm__IoctlPermissionTable.html", [
      [ "defaultPermittedCoreMask", "structEnetRm__IoctlPermissionTable.html#a959d5d4388d3ccb68067878eba580cd5", null ],
      [ "numEntries", "structEnetRm__IoctlPermissionTable.html#a08071053bd1c71ea3e32d8a2eee43206", null ],
      [ "entry", "structEnetRm__IoctlPermissionTable.html#a07fd410ca2f791b50d3a756132d35c6c", null ]
    ] ],
    [ "EnetRm_MacAddressPool", "structEnetRm__MacAddressPool.html", [
      [ "numMacAddress", "structEnetRm__MacAddressPool.html#ad5c5b9ceccab4d022fea1a478df30689", null ],
      [ "macAddress", "structEnetRm__MacAddressPool.html#a07bcf0aacbdea04bef6324c9eff70109", null ]
    ] ],
    [ "EnetRm_AllocRxFlowInArgs", "structEnetRm__AllocRxFlowInArgs.html", [
      [ "coreKey", "structEnetRm__AllocRxFlowInArgs.html#a848ce236d3374fbe98452c50c4244357", null ],
      [ "chIdx", "structEnetRm__AllocRxFlowInArgs.html#a2704f1f39821355ae442e08774d3692e", null ]
    ] ],
    [ "EnetRm_AllocRxFlow", "structEnetRm__AllocRxFlow.html", [
      [ "startIdx", "structEnetRm__AllocRxFlow.html#ac9ed8efcaaa608c7ce0f95b28e10e66a", null ],
      [ "flowIdx", "structEnetRm__AllocRxFlow.html#ac59a0dc8031ceb00a92a4f66060e5f24", null ]
    ] ],
    [ "EnetRm_AllocMacAddrOutArgs", "structEnetRm__AllocMacAddrOutArgs.html", [
      [ "macAddr", "structEnetRm__AllocMacAddrOutArgs.html#ad6ccb4ff9f9a1c8ebbb5da31553f1a6f", null ]
    ] ],
    [ "EnetRm_FreeTxChInArgs", "structEnetRm__FreeTxChInArgs.html", [
      [ "coreKey", "structEnetRm__FreeTxChInArgs.html#a81aad5fef388841b169ffea5fe49c563", null ],
      [ "txChNum", "structEnetRm__FreeTxChInArgs.html#a31f2dba4b9dfe443f253c8ed48a149d3", null ]
    ] ],
    [ "EnetRm_FreeRxFlowInArgs", "structEnetRm__FreeRxFlowInArgs.html", [
      [ "coreKey", "structEnetRm__FreeRxFlowInArgs.html#a5950ea7268b4ec99676aabbad6e999df", null ],
      [ "chIdx", "structEnetRm__FreeRxFlowInArgs.html#aa14ccdd7888172a0793471083ac3d73b", null ],
      [ "flowIdx", "structEnetRm__FreeRxFlowInArgs.html#a58e5540082d25f5785295737474fad5a", null ]
    ] ],
    [ "EnetRm_FreeMacAddrInArgs", "structEnetRm__FreeMacAddrInArgs.html", [
      [ "coreKey", "structEnetRm__FreeMacAddrInArgs.html#ab5aaebd0400086ed85cd33bd5dd33215", null ],
      [ "macAddr", "structEnetRm__FreeMacAddrInArgs.html#a8a8324f90da7fb358eba06f588fad884", null ]
    ] ],
    [ "EnetRm_ResCfg", "structEnetRm__ResCfg.html", [
      [ "selfCoreId", "structEnetRm__ResCfg.html#a2ef2471c706c266c660b6739d3d50645", null ],
      [ "resPartInfo", "structEnetRm__ResCfg.html#adddefa12afa409bab36d2b975fd5288f", null ],
      [ "ioctlPermissionInfo", "structEnetRm__ResCfg.html#a060249de4994fa4b50e85b9233937ca9", null ],
      [ "macList", "structEnetRm__ResCfg.html#ae54273010da9be21a4d88cc5068c6a5d", null ]
    ] ],
    [ "EnetRm_ValidatePermissionInArgs", "structEnetRm__ValidatePermissionInArgs.html", [
      [ "cmd", "structEnetRm__ValidatePermissionInArgs.html#afee4be296bef29a26a72a7fe1b59e7d5", null ],
      [ "coreId", "structEnetRm__ValidatePermissionInArgs.html#ad636dcd159165bbe6139966d12189fe5", null ]
    ] ],
    [ "EnetRm_AllocInternalRxFlowInArgs", "structEnetRm__AllocInternalRxFlowInArgs.html", [
      [ "coreId", "structEnetRm__AllocInternalRxFlowInArgs.html#a11837304620ac004b25b3c4a0a65abae", null ],
      [ "chIdx", "structEnetRm__AllocInternalRxFlowInArgs.html#aef5fa5d8d10185d7fe187f1f62dd4849", null ]
    ] ],
    [ "EnetRm_FreeInternalRxFlowInArgs", "structEnetRm__FreeInternalRxFlowInArgs.html", [
      [ "coreId", "structEnetRm__FreeInternalRxFlowInArgs.html#a4418aa0b5fcaab9fca6e94392c8741ba", null ],
      [ "chIdx", "structEnetRm__FreeInternalRxFlowInArgs.html#a4f589953d651ec4da699397185c0ae64", null ],
      [ "flowIdx", "structEnetRm__FreeInternalRxFlowInArgs.html#a1b2591fc9f431736bb6b5ea16470fb32", null ]
    ] ],
    [ "EnetRm_Cfg", "structEnetRm__Cfg.html", [
      [ "enetType", "structEnetRm__Cfg.html#a2eb8d0006965a994bfe112fb3f5a836f", null ],
      [ "instId", "structEnetRm__Cfg.html#a93bdd785cbe7423e91f7dad0bf0f949f", null ],
      [ "numRxCh", "structEnetRm__Cfg.html#a4fb4d92379bee284f9dba3484440f922", null ],
      [ "rxStartFlowIdx", "structEnetRm__Cfg.html#a9ecaac9e3f8f7ba65129b3655dc10024", null ],
      [ "rxFlowIdxCnt", "structEnetRm__Cfg.html#a8415e97348b61fd0645e479daeff42b6", null ],
      [ "resPartInfo", "structEnetRm__Cfg.html#a6a02436c1f2848d7b955bd21fcae9e34", null ],
      [ "ioctlPermissionInfo", "structEnetRm__Cfg.html#a51aa884ddf359c6a5668004d24e9cd1b", null ],
      [ "macList", "structEnetRm__Cfg.html#ae0c886118203d0b1880f9f2f035db528", null ]
    ] ],
    [ "EnetRm_ResEntry_t", "structEnetRm__ResEntry__t.html", [
      [ "node", "structEnetRm__ResEntry__t.html#a10a9db281201294c75a63b218e32fef1", null ],
      [ "ownerCoreId", "structEnetRm__ResEntry__t.html#a4bde049bc18e6c699ecb1a5b0e59cb91", null ],
      [ "id", "structEnetRm__ResEntry__t.html#aaff1033f240d6ecc75f99c237cc3b9f9", null ]
    ] ],
    [ "EnetRm_CoreResInfo_t", "structEnetRm__CoreResInfo__t.html", [
      [ "coreId", "structEnetRm__CoreResInfo__t.html#aba5efbc87e40f58ab1f83421ae216e11", null ],
      [ "resQ", "structEnetRm__CoreResInfo__t.html#a505ecd2f892d8ecb8cd6f07eb602733a", null ]
    ] ],
    [ "EnetRm_CoreResTbl_t", "structEnetRm__CoreResTbl__t.html", [
      [ "numCores", "structEnetRm__CoreResTbl__t.html#a5514be5d06dc0cdf2aa3962e88313d3f", null ],
      [ "coreResTbl", "structEnetRm__CoreResTbl__t.html#ad4c813d1173128b97380353dea935b5e", null ]
    ] ],
    [ "EnetRm_TxChObj", "structEnetRm__TxChObj.html", [
      [ "txPSILThreadIdOffset", "structEnetRm__TxChObj.html#a454e4e59002a830d713b4ea23ef9f9d8", null ],
      [ "resCnt", "structEnetRm__TxChObj.html#aded9407ead424e8f7c73dc714a3369f3", null ],
      [ "txResTbl", "structEnetRm__TxChObj.html#a3a4c3a2cc69e7bb104960dec2416f54a", null ],
      [ "txRes", "structEnetRm__TxChObj.html#a9baa8fac2ac5bfed4f521cc28c32508b", null ]
    ] ],
    [ "EnetRm_RxFlowIdxObj", "structEnetRm__RxFlowIdxObj.html", [
      [ "internalAllocCoreId", "structEnetRm__RxFlowIdxObj.html#a09bfe4ff99279404f7863c3c3fa19382", null ],
      [ "internalAllocCount", "structEnetRm__RxFlowIdxObj.html#a9347c1c5b9a14c57ac00bee2199c0550", null ],
      [ "resCnt", "structEnetRm__RxFlowIdxObj.html#a7a9f147a2bc3a793d21c3403df8ab951", null ],
      [ "rxResTbl", "structEnetRm__RxFlowIdxObj.html#aee791e4dde546448d2aa1e468320c884", null ],
      [ "rxRes", "structEnetRm__RxFlowIdxObj.html#a64236c097c44f4d5c5cdcf1450aa76e0", null ]
    ] ],
    [ "EnetRm_MacAddressObj", "structEnetRm__MacAddressObj.html", [
      [ "resCnt", "structEnetRm__MacAddressObj.html#a9402aa29a9bccded021e55c7a30e92a6", null ],
      [ "macTbl", "structEnetRm__MacAddressObj.html#a63074483bef1525504b5e92a697e7773", null ],
      [ "macRes", "structEnetRm__MacAddressObj.html#aea15b2e1eecdc2b9d70faec2aef1275d", null ]
    ] ],
    [ "EnetRm_CoreAttachInfo", "structEnetRm__CoreAttachInfo.html", [
      [ "numCores", "structEnetRm__CoreAttachInfo.html#abd39218bbb16bf407b5f696ce72d8ea9", null ],
      [ "attachedCores", "structEnetRm__CoreAttachInfo.html#a1dd2dcdea3d42c45fe3bdc5138e751c9", null ]
    ] ],
    [ "EnetRm_Obj", "structEnetRm__Obj.html", [
      [ "enetMod", "structEnetRm__Obj.html#aec757fd6de915cc2f4cd703a8522929f", null ],
      [ "cfg", "structEnetRm__Obj.html#a257f54aee07dd17b117b914250f66ddd", null ],
      [ "txObj", "structEnetRm__Obj.html#ab5129f0796f664a62bb9ef7ed7db901d", null ],
      [ "rxObj", "structEnetRm__Obj.html#a01ed587358040a62146f3b2f1ddc67e2", null ],
      [ "numRxCh", "structEnetRm__Obj.html#acbfcac16e6c769488f15a2e96a5a6062", null ],
      [ "macObj", "structEnetRm__Obj.html#ada0d309e0af8c8e296ee6421588dd62d", null ],
      [ "coreAttachObj", "structEnetRm__Obj.html#a669184e069a47e0d6f688221447b99c5", null ]
    ] ],
    [ "ENET_RM_PUBLIC_IOCTL", "group__ENET__RM__API.html#gaa2b21a71007169a8d1bb36b29e24568d", null ],
    [ "ENET_RM_TXCHNUM_INVALID", "group__ENET__RM__API.html#ga595c5a08b488b4ab0d3989be2953ddee", null ],
    [ "ENET_RM_RXFLOWIDX_INVALID", "group__ENET__RM__API.html#gac02d13a16dd62cf7c9e53a82eec45a55", null ],
    [ "ENET_RM_INVALIDCORE", "group__ENET__RM__API.html#ga3dc0180310e795d3bca94290796ede95", null ],
    [ "ENET_RM_NUM_IOCTL_PERM_ENTRY_MAX", "group__ENET__RM__API.html#ga6a12a5e26f1cbda3989a7650fc655eeb", null ],
    [ "ENET_RM_NUM_MACADDR_MAX", "group__ENET__RM__API.html#gab275f4c218b8a5e44ae4a4ed884d7dad", null ],
    [ "ENET_RM_NUM_RXCHAN_MAX", "group__ENET__RM__API.html#ga7346fb5cd845c1e69f4eb10ec9e90282", null ],
    [ "ENET_RM_PRIVATE_IOCTL", "group__ENET__RM__API.html#gabe77210bd990c44812aa1261ec94cbaa", null ],
    [ "EnetRm_ValidateRxFlowInArgs", "group__ENET__RM__API.html#ga53bfd6a4e3087140c354a13664e0acff", null ],
    [ "EnetRm_Handle", "group__ENET__RM__API.html#gadb95947e3b226edb6770c0b45a65f7f5", null ],
    [ "EnetRm_Ioctls", "group__ENET__RM__API.html#ga7b4dc0ecf69d4cb3cbe8d345ad89f520", [
      [ "ENET_RM_IOCTL_ALLOC_MAC_ADDR", "group__ENET__RM__API.html#gga7b4dc0ecf69d4cb3cbe8d345ad89f520a695066a53798e9eb7b6dabc895d844bf", null ],
      [ "ENET_RM_IOCTL_FREE_MAC_ADDR", "group__ENET__RM__API.html#gga7b4dc0ecf69d4cb3cbe8d345ad89f520aa4c606a2a4e1c65c1fb8475ccd397c92", null ],
      [ "ENET_RM_IOCTL_ALLOC_RX_FLOW", "group__ENET__RM__API.html#gga7b4dc0ecf69d4cb3cbe8d345ad89f520aff661b428a7a63f9fecc196c2cd08dd1", null ],
      [ "ENET_RM_IOCTL_FREE_RX_FLOW", "group__ENET__RM__API.html#gga7b4dc0ecf69d4cb3cbe8d345ad89f520a9e158d61798406d67a9460adc1d4832a", null ],
      [ "ENET_RM_IOCTL_ALLOC_TX_CH_PEERID", "group__ENET__RM__API.html#gga7b4dc0ecf69d4cb3cbe8d345ad89f520ae6d97c8f3e43fd9944990a7c65899335", null ],
      [ "ENET_RM_IOCTL_FREE_TX_CH_PEERID", "group__ENET__RM__API.html#gga7b4dc0ecf69d4cb3cbe8d345ad89f520a7d4969535be522400692a6e85d55927d", null ]
    ] ],
    [ "EnetRm_PrivIoctls", "group__ENET__RM__API.html#gac5c115c7c1849b0e6345599a30d772b1", [
      [ "ENET_RM_IOCTL_VALIDATE_PERMISSION", "group__ENET__RM__API.html#ggac5c115c7c1849b0e6345599a30d772b1a370ad715eab1356632b75f03af550e10", null ],
      [ "ENET_RM_IOCTL_ATTACH", "group__ENET__RM__API.html#ggac5c115c7c1849b0e6345599a30d772b1a9f3a045364a66de799e4b0fe2f80f0fb", null ],
      [ "ENET_RM_IOCTL_DETACH", "group__ENET__RM__API.html#ggac5c115c7c1849b0e6345599a30d772b1a25a63affe9b9951dba703d12fdeb5ea2", null ],
      [ "ENET_RM_IOCTL_INTERNAL_ALLOC_RX_FLOW", "group__ENET__RM__API.html#ggac5c115c7c1849b0e6345599a30d772b1a30b5030a5572cfd8cf7cdb5deea7be11", null ],
      [ "ENET_RM_IOCTL_INTERNAL_FREE_RX_FLOW", "group__ENET__RM__API.html#ggac5c115c7c1849b0e6345599a30d772b1a21a09006d8a2c1ad7642524e00a386eb", null ],
      [ "ENET_RM_IOCTL_VALIDATE_RX_FLOW", "group__ENET__RM__API.html#ggac5c115c7c1849b0e6345599a30d772b1a35278a54739f6a12780542a0066ae013", null ]
    ] ],
    [ "EnetRm_open", "group__ENET__RM__API.html#ga8e027f884310f323ce2b528df1d7f630", null ],
    [ "EnetRm_rejoin", "group__ENET__RM__API.html#ga27411862100ce20276cf1f44560a8b64", null ],
    [ "EnetRm_ioctl", "group__ENET__RM__API.html#ga7eca59d39e2f4298e4f907b5e137bb8e", null ],
    [ "EnetRm_close", "group__ENET__RM__API.html#ga9b27138ca4c40c96c73c80d44422df91", null ]
];