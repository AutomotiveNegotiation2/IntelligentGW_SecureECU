var group__DRV__I2C__API__MODULE =
[
    [ "I2C.h", "I2C_8h.html", null ],
    [ "I2C_Transaction", "structI2C__Transaction.html", [
      [ "validParams", "structI2C__Transaction.html#aa03dbba81b76da11a7081628ef3d6af3", null ],
      [ "writeBuf", "structI2C__Transaction.html#aa3490c2af4b443a7a4ec13f57aec6d20", null ],
      [ "writeCount", "structI2C__Transaction.html#a08959a9f098163d02d6002e73b3a4606", null ],
      [ "readBuf", "structI2C__Transaction.html#a804b918d5cb08bb75a39866d0b89e01e", null ],
      [ "readCount", "structI2C__Transaction.html#a2085d4c943f0d8617365b7c427e6a0de", null ],
      [ "slaveAddress", "structI2C__Transaction.html#a0b34e65535478ee28f671c266817c6c5", null ],
      [ "arg", "structI2C__Transaction.html#a29ec65addac2d4ef5d1235c2329e2fc1", null ],
      [ "nextPtr", "structI2C__Transaction.html#a21755edd4d999d6041d303e269596371", null ],
      [ "timeout", "structI2C__Transaction.html#ad5959435aa2266d8b9af752b1a2e14c6", null ],
      [ "masterMode", "structI2C__Transaction.html#ac0746390c0d1e37170ee8da0c0a4a466", null ],
      [ "expandSA", "structI2C__Transaction.html#ab3fba2e46341efc0ff19e21a13194b17", null ]
    ] ],
    [ "I2C_Params", "structI2C__Params.html", [
      [ "transferMode", "structI2C__Params.html#a79c5c51380ffbdb21df1dff6cb57de0e", null ],
      [ "transferCallbackFxn", "structI2C__Params.html#a35bbacc05eb01214ac7d09c5f03c1d50", null ],
      [ "bitRate", "structI2C__Params.html#ad31857f6dbedb77c60c92cc8cd8cde0c", null ],
      [ "custom", "structI2C__Params.html#a2416cc06d853e6cc24e1f294dfebb194", null ]
    ] ],
    [ "I2C_FxnTable", "structI2C__FxnTable.html", [
      [ "closeFxn", "structI2C__FxnTable.html#a02f4e6a7daeb64d6741372a5636eedb5", null ],
      [ "controlFxn", "structI2C__FxnTable.html#af23db6bdc9b619633fb70ddff44412ea", null ],
      [ "initFxn", "structI2C__FxnTable.html#ae27540a7175c9ad14b590ddc92e06390", null ],
      [ "openFxn", "structI2C__FxnTable.html#afb8c5f67ba6d0941f6265707083b16f8", null ],
      [ "transferFxn", "structI2C__FxnTable.html#a16048b22814e3d123f82a7674599b15c", null ]
    ] ],
    [ "I2C_Config", "structI2C__Config.html", [
      [ "fxnTablePtr", "structI2C__Config.html#a225800ca2923178397645d520bc6a0c1", null ],
      [ "object", "structI2C__Config.html#abeb7af699744bd43dc1fc5019073fd2c", null ],
      [ "hwAttrs", "structI2C__Config.html#a1c623e253c0d5f896ad8037635f0c719", null ]
    ] ],
    [ "I2C_CMD_RESERVED", "group__DRV__I2C__API__MODULE.html#ga760ec0a6fdb876ccc67b6f06301d53ec", null ],
    [ "I2C_CMD_PROBE", "group__DRV__I2C__API__MODULE.html#gac180b6227ed3fdbeaee729c7142be292", null ],
    [ "I2C_CMD_SET_BUS_FREQUENCY", "group__DRV__I2C__API__MODULE.html#ga3b3af5c8efc2035485a769e056451a4a", null ],
    [ "I2C_CMD_RECOVER_BUS", "group__DRV__I2C__API__MODULE.html#ga5eb5c8eb4dfa903256744e611350d166", null ],
    [ "I2C_CMD_SMBUS_TYPE", "group__DRV__I2C__API__MODULE.html#ga514007e93fddd909e8a318ed6d4dd5c5", null ],
    [ "I2C_STATUS_RESERVED", "group__DRV__I2C__API__MODULE.html#gacfd04572fe349d087c2547501cbc7e0a", null ],
    [ "I2C_STATUS_SUCCESS", "group__DRV__I2C__API__MODULE.html#gaa0bcf3acd26ac82bd8ff91daba2c78c4", null ],
    [ "I2C_STATUS_ERROR", "group__DRV__I2C__API__MODULE.html#ga7323fe57c39c46d0da9910e17f5f0b06", null ],
    [ "I2C_STATUS_UNDEFINEDCMD", "group__DRV__I2C__API__MODULE.html#ga11c31c9869ed2441789205d9e5967d66", null ],
    [ "I2C_STS_SUCCESS", "group__DRV__I2C__API__MODULE.html#ga436bc81547d25cbe81ce05723f52b07d", null ],
    [ "I2C_STS_RESTART", "group__DRV__I2C__API__MODULE.html#ga38b0b690d277c28a31e0d54adff41576", null ],
    [ "I2C_STS_ERR", "group__DRV__I2C__API__MODULE.html#gaa1ef9c5b5af75eebd526d463caaa6ebb", null ],
    [ "I2C_STS_ERR_TIMEOUT", "group__DRV__I2C__API__MODULE.html#gafd84b85e7e90ce51a193e009a10f93b5", null ],
    [ "I2C_STS_ERR_BUS_BUSY", "group__DRV__I2C__API__MODULE.html#gaa4609322c95a91f3087cf8cedeaf50dc", null ],
    [ "I2C_STS_ERR_NO_ACK", "group__DRV__I2C__API__MODULE.html#ga45f7e0ce66230391b0b2bff9a2a125da", null ],
    [ "I2C_STS_ERR_ARBITRATION_LOST", "group__DRV__I2C__API__MODULE.html#ga914692b73c08c5b4f416c99bbba1b1df", null ],
    [ "I2C_STS_ERR_ACCESS_ERROR", "group__DRV__I2C__API__MODULE.html#ga764c02df1aa2b1eabc660900f6c0e5fd", null ],
    [ "I2C_STS_ERR_COMMAND_FAILURE", "group__DRV__I2C__API__MODULE.html#ga4b55fae2bff33fbbe7b989042413e039", null ],
    [ "I2C_STS_ERR_INVALID_COMMAND", "group__DRV__I2C__API__MODULE.html#gaf895f1f3d50b692c2327c3f2cdec9742", null ],
    [ "I2C_TRANS_VALID_PARAM_MASTER_MODE", "group__DRV__I2C__API__MODULE.html#ga2082eaca20d22df76ee7c03ec9ff7852", null ],
    [ "I2C_TRANS_VALID_PARAM_EXPAND_SA", "group__DRV__I2C__API__MODULE.html#gaadd15612272a2c28f4e68ab6ab07d58d", null ],
    [ "I2C_WAIT_FOREVER", "group__DRV__I2C__API__MODULE.html#ga4eb2bf76d4186e8752bcd32b32908b6c", null ],
    [ "I2C_MAX_CONFIG_CNT", "group__DRV__I2C__API__MODULE.html#ga0672a0d5ee2baf6f3d3763e3f2087ce3", null ],
    [ "I2C_Handle", "group__DRV__I2C__API__MODULE.html#gadd75c22230842b00010efe1d992b8979", null ],
    [ "I2C_CallbackFxn", "group__DRV__I2C__API__MODULE.html#ga37389d5eec0eb91fe25e1524e2f339bc", null ],
    [ "I2C_CloseFxn", "group__DRV__I2C__API__MODULE.html#ga083200108e980a0ef61e458f0b9fb9e7", null ],
    [ "I2C_ControlFxn", "group__DRV__I2C__API__MODULE.html#ga83c5698318ecfc08ca3d536992af0fa3", null ],
    [ "I2C_InitFxn", "group__DRV__I2C__API__MODULE.html#gadfb2451c8a1ce70402e43e4743c5fedf", null ],
    [ "I2C_OpenFxn", "group__DRV__I2C__API__MODULE.html#gafb3800d49a9dd7c11f7e39223600dabf", null ],
    [ "I2C_TransferFxn", "group__DRV__I2C__API__MODULE.html#gaed1191de07b33b334d5ad2204d76fc03", null ],
    [ "I2C_config_list", "group__DRV__I2C__API__MODULE.html#gad37b08cb8435a1540db5d743f5db00d3", null ],
    [ "I2C_TransferMode", "group__DRV__I2C__API__MODULE.html#ga39f3b9340fc4ee241b0d2da9b2841c26", [
      [ "I2C_MODE_BLOCKING", "group__DRV__I2C__API__MODULE.html#gga39f3b9340fc4ee241b0d2da9b2841c26abe065350be2a0ae5c9beb24624626c75", null ],
      [ "I2C_MODE_CALLBACK", "group__DRV__I2C__API__MODULE.html#gga39f3b9340fc4ee241b0d2da9b2841c26a129731a7edeb285f43a54b2cf9f5ac72", null ]
    ] ],
    [ "I2C_BitRate", "group__DRV__I2C__API__MODULE.html#gac954e3197f04c50293db466c4abb6fbe", [
      [ "I2C_100kHz", "group__DRV__I2C__API__MODULE.html#ggac954e3197f04c50293db466c4abb6fbea966fd2df13b3a9825615c50335cf1987", null ],
      [ "I2C_400kHz", "group__DRV__I2C__API__MODULE.html#ggac954e3197f04c50293db466c4abb6fbea83cc3750242e6ae9194cd7ed94f764d9", null ],
      [ "I2C_1P0Mhz", "group__DRV__I2C__API__MODULE.html#ggac954e3197f04c50293db466c4abb6fbea0a22b170b199fca1e43ef75ad430bb10", null ],
      [ "I2C_3P4Mhz", "group__DRV__I2C__API__MODULE.html#ggac954e3197f04c50293db466c4abb6fbeae619ec9344c1dda3c922121a0844053c", null ]
    ] ],
    [ "I2C_close", "group__DRV__I2C__API__MODULE.html#ga17b3618e4c0b145bc6d32c50d33c0818", null ],
    [ "I2C_control", "group__DRV__I2C__API__MODULE.html#ga20f44c5f041a281b4b0e631a765c6cd2", null ],
    [ "I2C_init", "group__DRV__I2C__API__MODULE.html#ga9ff51ddf1d325776fef90cce0223772b", null ],
    [ "I2C_open", "group__DRV__I2C__API__MODULE.html#gaab59fd6d22b790182114033b8056b36b", null ],
    [ "I2C_Params_init", "group__DRV__I2C__API__MODULE.html#gab11636302074d67180207ab81ceb323c", null ],
    [ "I2C_transfer", "group__DRV__I2C__API__MODULE.html#ga890f328870fd7c23c0f76dc12de222b2", null ],
    [ "I2C_transactionInit", "group__DRV__I2C__API__MODULE.html#ga2c232ab5d02e8722fc5270240aba7467", null ]
];