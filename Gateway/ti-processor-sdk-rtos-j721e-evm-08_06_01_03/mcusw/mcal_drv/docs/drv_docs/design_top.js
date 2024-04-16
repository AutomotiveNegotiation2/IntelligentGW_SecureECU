var design_top =
[
    [ "Can Design Document", "design_can_top.html", null ],
    [ "Dio Design Document", "design_dio_top.html", null ],
    [ "Eth Design Document", "design_eth_top.html", [
      [ "Introduction", "design_eth_top.html#design_eth_intro", [
        [ "Overview", "design_eth_top.html#design_eth_intro_overview", null ],
        [ "Eth Overview", "design_eth_top.html#design_eth_eth_overview", null ],
        [ "References", "design_eth_top.html#design_eth_references", null ]
      ] ],
      [ "Requirements", "design_eth_top.html#design_eth_req", [
        [ "Features Supported", "design_eth_top.html#design_eth_features_supported", null ],
        [ "Features Not Supported / NON Compliance", "design_eth_top.html#design_eth_features_not_supported", null ],
        [ "Assumptions", "design_eth_top.html#design_eth_assumptions", null ]
      ] ],
      [ "Design Description", "design_eth_top.html#design_eth_description", [
        [ "Dynamic Behavior", "design_eth_top.html#design_eth_desc_dynamic", null ],
        [ "Sequence Diagrams", "design_eth_top.html#design_eth_seq_dia", [
          [ "Data Transmission", "design_eth_top.html#design_eth_seq_tx", null ],
          [ "Data Reception", "design_eth_top.html#design_eth_seq_rx", null ]
        ] ],
        [ "Directory Structure", "design_eth_top.html#design_eth_desc_deter_dir", null ],
        [ "Interrupt Service Routines", "design_eth_top.html#design_eth_desc_isr", null ],
        [ "Configurator", "design_eth_top.html#design_eth_desc_cfg", [
          [ "NON Standard configurable parameters", "design_eth_top.html#design_eth_desc_cfg_ti", null ]
        ] ],
        [ "Debug Information", "design_eth_top.html#design_eth_desc_dbg", null ],
        [ "Error Classification", "design_eth_top.html#design_eth_desc_error", [
          [ "Development Errors", "design_eth_top.html#design_eth_desc_error_dev", null ],
          [ "Error Detection", "design_eth_top.html#design_eth_desc_error_dev_detect", null ],
          [ "Error notification (DET)", "design_eth_top.html#design_eth_desc_error_dev_notify", null ],
          [ "Runtime Errors", "design_eth_top.html#design_eth_desc_error_runtime", null ],
          [ "Extended Production error", "design_eth_top.html#design_eth_desc_error_dem_extended", null ]
        ] ],
        [ "Resource Behavior", "design_eth_top.html#design_eth_desc_res_behave", null ],
        [ "API's", "design_eth_top.html#design_eth_low_level_api", [
          [ "Eth_Init", "design_eth_top.html#design_eth_low_level_api_init", null ],
          [ "Eth_SetControllerMode", "design_eth_top.html#design_eth_low_level_api_set_ctrl_mode", null ],
          [ "Eth_GetControllerMode", "design_eth_top.html#design_eth_low_level_api_get_ctrl_mode", null ],
          [ "Eth_GetPhysAddr", "design_eth_top.html#design_eth_low_level_api_get_phy_addr", null ],
          [ "Eth_SetPhysAddr", "design_eth_top.html#design_eth_low_level_api_set_phy_addr", null ],
          [ "Eth_UpdatePhysAddrFilter", "design_eth_top.html#design_eth_low_level_api_up_phy_addr", null ],
          [ "Eth_WriteMii", "design_eth_top.html#design_eth_low_level_api_wr_mii", null ],
          [ "Eth_ReadMii", "design_eth_top.html#design_eth_low_level_api_rd_mii", null ],
          [ "Eth_GetCounterValues", "design_eth_top.html#design_eth_low_level_api_get_counter_values", null ],
          [ "Eth_GetRxStats", "design_eth_top.html#design_eth_low_level_api_get_rx_stats", null ],
          [ "Eth_GetTxStats", "design_eth_top.html#design_eth_low_level_api_get_tx_stats", null ],
          [ "Eth_GetTxErrorCounterValues", "design_eth_top.html#design_eth_low_level_api_get_tx_error_counter_values", null ],
          [ "Eth_GetCurrentTime", "design_eth_top.html#design_eth_low_level_api_get_curr_time", null ],
          [ "Eth_EnableEgressTimeStamp", "design_eth_top.html#design_eth_low_level_api_en_egress_time", null ],
          [ "Eth_GetEgressTimeStamp", "design_eth_top.html#design_eth_low_level_api_get_egress_time", null ],
          [ "Eth_GetIngressTimeStamp", "design_eth_top.html#design_eth_low_level_api_get_ingress_time", null ],
          [ "Eth_ProvideTxBuffer", "design_eth_top.html#design_eth_low_level_api_give_tx", null ],
          [ "Eth_Transmit", "design_eth_top.html#design_eth_low_level_api_tx", null ],
          [ "Eth_Receive", "design_eth_top.html#design_eth_low_level_api_rx", null ],
          [ "Eth_TxConfirmation", "design_eth_top.html#design_eth_low_level_api_tx_confirm", null ],
          [ "Eth_GetVersionInfo", "design_eth_top.html#design_eth_low_level_api_get_ver", null ],
          [ "Eth_MainFunction", "design_eth_top.html#design_eth_low_level_api_main_function", null ]
        ] ],
        [ "Ethernet Interface Callbacks", "design_eth_top.html#design_eth_ethif_callbacks", null ],
        [ "Ethernet Switch Callbacks", "design_eth_top.html#design_eth_ethswt_callbacks", null ],
        [ "Types", "design_eth_top.html#design_eth_low_level_types", null ],
        [ "Global Variables", "design_eth_top.html#design_eth_low_level_globals", null ]
      ] ],
      [ "Decision Analysis & Resolution (DAR)", "design_eth_top.html#design_eth_dar_top", [
        [ "Packet Submission & Retrieval to CPSW: Single or Queue", "design_eth_top.html#design_eth_dar_q_or_s", [
          [ "DAR Criteria", "design_eth_top.html#design_eth_dar_q_or_s_criteria", null ],
          [ "Available Alternatives", "design_eth_top.html#design_eth_dar_alternatives_1", null ],
          [ "Decision", "design_eth_top.html#design_eth_dar_decision_1", null ]
        ] ],
        [ "Buffers Per Packet", "design_eth_top.html#design_eth_dar_buf_pack", [
          [ "DAR Criteria", "design_eth_top.html#design_eth_dar_buf_pack_criteria", null ],
          [ "Available Alternatives", "design_eth_top.html#design_eth_dar_alternatives_2", null ],
          [ "Decision", "design_eth_top.html#design_eth_dar_decision_2", null ]
        ] ]
      ] ],
      [ "Test Criteria", "design_eth_top.html#design_eth_test_top", null ],
      [ "Document Revision History", "design_eth_top.html#design_eth_rev_hist", null ]
    ] ],
    [ "Gpt Design Document", "design_gpt_top.html", null ],
    [ "Spi Design Document", "design_spi_top.html", null ],
    [ "Wdg Design Document", "design_wdg_top.html", null ],
    [ "Adc Design Document", "design_adc_top.html", null ],
    [ "Pwm Design Document", "design_pwm_top.html", [
      [ "Introduction", "design_pwm_top.html#design_pwm_intro", [
        [ "Overview", "design_pwm_top.html#design_pwm_intro_overview", null ],
        [ "PWM Overview", "design_pwm_top.html#design_pwm_overview", null ],
        [ "Hardware Overview", "design_pwm_top.html#design_hw_overview", null ],
        [ "References", "design_pwm_top.html#design_pwm_references", null ]
      ] ],
      [ "Requirements", "design_pwm_top.html#design_pwm_req", [
        [ "Features Supported", "design_pwm_top.html#design_pwm_features_supported", null ],
        [ "Features Not Supported / NON Compliance", "design_pwm_top.html#design_pwm_features_not_supported", null ],
        [ "Assumptions", "design_pwm_top.html#design_pwm_assumptions", null ],
        [ "Constraints", "design_pwm_top.html#design_pwm_constraints", null ]
      ] ],
      [ "Design Description", "design_pwm_top.html#design_pwm_description", [
        [ "Fundamental Operation", "design_pwm_top.html#design_pwm_desc_fundamental", null ],
        [ "Dynamic Behavior", "design_pwm_top.html#design_pwm_desc_dynamic", [
          [ "States for Timer", "design_pwm_top.html#design_pwm_desc_dynamic_state_timer", null ],
          [ "States for EPWM", "design_pwm_top.html#design_pwm_desc_dynamic_state_epwm", null ]
        ] ],
        [ "Time Unit Ticks", "design_pwm_top.html#design_pwm_ticks", null ],
        [ "Duty Cycle Resolution and Scaling", "design_pwm_top.html#design_pwm_resolution", null ],
        [ "Directory Structure", "design_pwm_top.html#design_pwm_desc_deter_dir", null ],
        [ "Configurator", "design_pwm_top.html#design_pwm_desc_cfg", [
          [ "NON Standard configurable parameters", "design_pwm_top.html#design_pwm_desc_cfg_ti", null ],
          [ "Variant Support", "design_pwm_top.html#design_pwm_desc_cfg_variant", null ]
        ] ],
        [ "Dependency on other modules", "design_pwm_top.html#design_pwm_desc_cfg_dependency", [
          [ "SBL", "design_pwm_top.html#design_pwm_desc_cfg_dependency_sbl", null ]
        ] ],
        [ "Error Classification", "design_pwm_top.html#design_pwm_desc_error", [
          [ "Development Errors", "design_pwm_top.html#design_pwm_desc_error_dev", null ],
          [ "Error Detection", "design_pwm_top.html#design_pwm_desc_error_dev_detect", null ],
          [ "Error notification (DET)", "design_pwm_top.html#design_pwm_desc_error_dev_notify", null ]
        ] ],
        [ "Resource Behavior", "design_pwm_top.html#design_pwm_desc_res_behave", null ],
        [ "Supporting PWM for AUTOSAR versioned 4.4.0", "design_pwm_top.html#design_pwm_desc_upgrade_44", null ]
      ] ],
      [ "Low Level Definitions", "design_pwm_top.html#design_pwm_low_level", [
        [ "MACROS, Data Types & Structures", "design_pwm_top.html#design_pwm_low_level_dtypes", [
          [ "Pwm_RegisterReadbackType", "design_pwm_top.html#design_pwm_low_level_readback_type", null ]
        ] ],
        [ "APIs", "design_pwm_top.html#design_pwm_low_level_api", [
          [ "Pwm_Init", "design_pwm_top.html#design_pwm_low_level_api_init", null ],
          [ "Pwm_DeInit", "design_pwm_top.html#design_pwm_low_level_api_deinit", null ],
          [ "Pwm_SetDutyCycle", "design_pwm_top.html#design_pwm_low_level_api_setduty", null ],
          [ "Pwm_SetPeriodAndDuty", "design_pwm_top.html#design_pwm_low_level_api_setperiodduty", null ],
          [ "Pwm_SetOutputToIdle", "design_pwm_top.html#design_pwm_low_level_api_setoptoidle", null ],
          [ "Pwm_DisableNotification", "design_pwm_top.html#design_pwm_low_level_api_disablenotification", null ],
          [ "Pwm_EnableNotification", "design_pwm_top.html#design_pwm_low_level_api_enablenotification", null ],
          [ "Pwm_GetVersionInfo", "design_pwm_top.html#design_pwm_low_level_api_versioninfo", null ],
          [ "Pwm_RegisterReadback", "design_pwm_top.html#design_pwm_low_level_api_rb", null ]
        ] ],
        [ "Global Variables", "design_pwm_top.html#design_pwm_low_level_globals", null ]
      ] ],
      [ "Safety Analysis", "design_pwm_top.html#design_pwm_safety", null ],
      [ "Decision Analysis & Resolution (DAR)", "design_pwm_top.html#design_pwm_dar_top", [
        [ "Timer Mode configuration in Overflow Only Mode for Duty cycle of 50%", "design_pwm_top.html#design_pwm_dar_timerdutycycle", [
          [ "DAR Criteria", "design_pwm_top.html#design_pwm_dar_criteria", null ],
          [ "Available Alternatives", "design_pwm_top.html#design_pwm_dar_alternatives", null ],
          [ "Decision", "design_pwm_top.html#design_pwm_dar_decision", null ]
        ] ],
        [ "Integration of GpTimer and EPWM", "design_pwm_top.html#design_pwm_dar_EPWM_GPT", [
          [ "DAR Criteria", "design_pwm_top.html#design_pwm_EPWM_GPT_dar_criteria", null ],
          [ "Available Alternatives", "design_pwm_top.html#design_pwm_EPWM_GPT_dar_alternatives", null ],
          [ "Decision", "design_pwm_top.html#design_pwm_EPWM_GPT_dar_decision", null ]
        ] ],
        [ "EHRPWM internal step size", "design_pwm_top.html#design_pwm_dar_EHRPWM", [
          [ "DAR Criteria", "design_pwm_top.html#design_pwm_EPWM_dar_EHRPWM_criteria", null ],
          [ "Available Alternatives", "design_pwm_top.html#design_pwm_EPWM_dar_alternatives", null ],
          [ "Decision", "design_pwm_top.html#design_pwm_EPWM_dar_EHRPWM_decision", null ]
        ] ],
        [ "Support each EPWM Output as a PWM Channel", "design_pwm_top.html#design_pwm_dar_EPWM_Channel", [
          [ "DAR Criteria", "design_pwm_top.html#design_pwm_EPWM_dar_Channel_criteria", null ],
          [ "Available Alternatives", "design_pwm_top.html#design_pwm_EPWM_dar_Channel_alternatives", null ],
          [ "Decision", "design_pwm_top.html#design_pwm_EPWM_dar_Channel_decision", null ]
        ] ]
      ] ],
      [ "Test Criteria", "design_pwm_top.html#design_pwm_test_top", null ],
      [ "Document Revision History", "design_pwm_top.html#design_pwm_rev_hist", null ]
    ] ],
    [ "Cdd IPC Design Document", "design_ipc_top.html", [
      [ "Introduction", "design_ipc_top.html#design_cdd_ipc_intro", [
        [ "Overview", "design_ipc_top.html#design_cdd_ipc_intro_overview", null ],
        [ "Cdd IPC Overview", "design_ipc_top.html#design_cdd_ipc_overview", [
          [ "Basic Working Principle", "design_ipc_top.html#design_cdd_ipc_basic_arch", null ],
          [ "Rational for IPC as an CDD", "design_ipc_top.html#design_cdd_ipc_rational", null ]
        ] ],
        [ "References", "design_ipc_top.html#design_cdd_ipc_references", null ]
      ] ],
      [ "Requirements", "design_ipc_top.html#design_cdd_ipc_req", [
        [ "Features Supported", "design_ipc_top.html#design_cdd_ipc_features_supported", null ],
        [ "Features Not Supported", "design_ipc_top.html#design_cdd_ipc_features_not_supported", null ],
        [ "Assumptions", "design_ipc_top.html#design_cdd_ipc_assumptions", null ],
        [ "Constraints", "design_ipc_top.html#design_cdd_ipc_constraints", null ]
      ] ],
      [ "Design Description", "design_ipc_top.html#design_cdd_ipc_description", [
        [ "Processor Identifiers", "design_ipc_top.html#design_cdd_ipc_proc_id", null ],
        [ "End Point", "design_ipc_top.html#design_cdd_ipc_ep_id", null ],
        [ "Message Buffer", "design_ipc_top.html#design_cdd_ipc_rpmsg_id", null ],
        [ "Queue in shared memory", "design_ipc_top.html#design_cdd_ipc_virtio_obj_id", null ],
        [ "Multiple End Point / Communication Channels", "design_ipc_top.html#design_cdd_ipc_multi_ep_id", null ],
        [ "Control End Point", "design_ipc_top.html#design_cdd_ipc_ctrl_ep_id", null ],
        [ "Dynamic Behavior", "design_ipc_top.html#design_cdd_ipc_desc_dynamic", [
          [ "States", "design_ipc_top.html#design_cdd_ipc_desc_dynamic_state", null ]
        ] ],
        [ "Directory Structure", "design_ipc_top.html#design_cdd_ipc_desc_deter_dir", null ],
        [ "Configurator", "design_ipc_top.html#design_cdd_ipc_desc_cfg", [
          [ "CDD IPC General Configuration parameters", "design_ipc_top.html#design_cdd_ipc_desc_cfg_gen", null ],
          [ "CDD IPC Shared Memory Configuration parameters", "design_ipc_top.html#design_cdd_ipc_desc_shared_mem", null ],
          [ "CDD IPC Processor Identifier", "design_ipc_top.html#design_cdd_ipc_desc_ownProc", null ],
          [ "CDD IPC Processor Identifier Remote", "design_ipc_top.html#design_cdd_ipc_desc_remote_proc", null ],
          [ "CDD IPC Communication Channels", "design_ipc_top.html#design_cdd_ipc_desc_com_chs", null ],
          [ "Variant Support", "design_ipc_top.html#design_cdd_ipc_desc_cfg_variant", null ]
        ] ],
        [ "Dependency on other modules", "design_ipc_top.html#design_cdd_ipc_desc_cfg_dependency", null ],
        [ "Error Classification", "design_ipc_top.html#design_cdd_ipc_desc_error", [
          [ "Development Errors", "design_ipc_top.html#design_cdd_ipc_desc_error_dev", null ],
          [ "Error Detection", "design_ipc_top.html#design_cdd_ipc_desc_error_dev_detect", null ],
          [ "Error notification (DET)", "design_ipc_top.html#design_cdd_ipc_desc_error_dev_notify", null ],
          [ "Runtime Errors", "design_ipc_top.html#design_cdd_ipc_desc_error_runtime", null ],
          [ "Error notification (DEM)", "design_ipc_top.html#design_cdd_ipc_desc_error_dev_notify_dem", null ]
        ] ],
        [ "Resource Behavior", "design_ipc_top.html#design_cdd_ipc_desc_res_behave", null ]
      ] ],
      [ "Low Level Definitions", "design_ipc_top.html#design_cdd_ipc_low_level", [
        [ "MACROS, Data Types & Structures", "design_ipc_top.html#design_cdd_ipc_low_level_dtypes", [
          [ "Maximum number of channels", "design_ipc_top.html#design_cdd_ipc_max_numchannels", null ],
          [ "Cdd_IpcMpType", "design_ipc_top.html#design_cdd_ipc_Cdd_IpcMpType", null ],
          [ "Cdd_IpcVertIoType", "design_ipc_top.html#design_cdd_ipc_Cdd_IpcVertIoType", null ],
          [ "Cdd_IpcChannelType", "design_ipc_top.html#design_cdd_ipc_Cdd_IpcChannelType", null ],
          [ "Cdd_IpcConfigType", "design_ipc_top.html#design_cdd_ipc_Cdd_IpcConfigType", null ],
          [ "Cdd_IpcRegRbValues", "design_ipc_top.html#design_cdd_ipc_low_level_readback_type", null ]
        ] ],
        [ "API's", "design_ipc_top.html#design_cdd_ipc_low_level_api", [
          [ "Cdd_IpcNewMessageNotify", "design_ipc_top.html#design_cdd_ipc_Cdd_IpcNewMessageNotify", null ],
          [ "Cdd_IpcNewCtrlMessageNotify", "design_ipc_top.html#design_cdd_ipc_Cdd_IpcCtrlNewMessageNotify", null ],
          [ "Cdd_IpcInit", "design_ipc_top.html#design_cdd_ipc_low_level_api_init", null ],
          [ "Cdd_IpcDeinit", "design_ipc_top.html#design_cdd_ipc_low_level_Cdd_IpcDeinit", null ],
          [ "Cdd_IpcSendMsg", "design_ipc_top.html#design_cdd_ipc_low_level_api_Cdd_IpcSendMsg", null ],
          [ "Cdd_IpcReceiveMsg", "design_ipc_top.html#design_cdd_ipc_low_level_api_Cdd_IpcReceiveMsg", null ],
          [ "Cdd_IpcAnnounce", "design_ipc_top.html#design_cdd_ipc_low_level_Cdd_IpcAnnounce", null ],
          [ "Cdd_IpcGetVersionInfo", "design_ipc_top.html#design_cdd_ipc_low_level_api_gver", null ],
          [ "Cdd_IpcRegisterReadBack", "design_ipc_top.html#design_cdd_ipc_low_level_api_rb", null ],
          [ "Cdd_IpcReceiveCtrlMsg", "design_ipc_top.html#design_cdd_ipc_low_level_api_Cdd_IpcReceiveCtrlMsg", null ],
          [ "Cdd_IpcIsInitDone", "design_ipc_top.html#design_cdd_ipc_low_level_api_Cdd_IpcIsInitDone", null ],
          [ "Cdd_IpcGetMaxMsgSize", "design_ipc_top.html#design_cdd_ipc_low_level_api_Cdd_IpcGetMaxMsgSize", null ]
        ] ],
        [ "Cdd_IpcNewMessageNotify ISR", "design_ipc_top.html#design_cdd_ipc_low_level_api_isr", null ],
        [ "Global Variables", "design_ipc_top.html#design_cdd_ipc_low_level_globals", null ]
      ] ],
      [ "Decision Analysis & Resolution (DAR)", "design_ipc_top.html#design_cdd_ipc_dar_top", [
        [ "Allocation of memory for LocalQ", "design_ipc_top.html#design_cdd_ipc_dar_reload", null ],
        [ "DAR Criteria", "design_ipc_top.html#design_cdd_ipc_dar_criteria", null ],
        [ "Available Alternatives", "design_ipc_top.html#design_cdd_ipc_dar_alternatives", null ],
        [ "Decision", "design_ipc_top.html#design_cdd_ipc_dar_decision", null ]
      ] ],
      [ "Test Criteria", "design_ipc_top.html#design_cdd_ipc_test_top", null ],
      [ "Document Revision History", "design_ipc_top.html#design_cdd_ipc_rev_hist", null ]
    ] ],
    [ "Fls Design Document", "design_fls_top.html", [
      [ "Introduction", "design_fls_top.html#design_fls_intro", [
        [ "Overview", "design_fls_top.html#design_fls_intro_overview", [
          [ "Fls Overview", "design_fls_top.html#design_fls_intro_fls_overview", null ],
          [ "References", "design_fls_top.html#design_fls_references", null ]
        ] ]
      ] ],
      [ "Requirements", "design_fls_top.html#design_fls_req", [
        [ "Features Supported", "design_fls_top.html#design_fls_features_supported", null ],
        [ "Features Not Supported / NON Compliance", "design_fls_top.html#design_fls_features_not_supported", null ],
        [ "Assumptions", "design_fls_top.html#design_fls_assumptions", null ]
      ] ],
      [ "Design Description", "design_fls_top.html#design_fls_description", [
        [ "Fundamental Operation", "design_fls_top.html#design_fls_fundamental_operation", null ],
        [ "Sequence Diagrams", "design_fls_top.html#design_fls_desc_seq", null ],
        [ "Resource Behavior", "design_fls_top.html#design_fls_desc_resource", null ],
        [ "Interrupt Service Routines", "design_fls_top.html#design_fls_desc_ISR", null ],
        [ "Dynamic Behavior", "design_fls_top.html#design_fls_dynamic_behaviour", null ],
        [ "Directory Structure", "design_fls_top.html#design_fls_desc_deter_dir", null ],
        [ "Configurator", "design_fls_top.html#design_fls_desc_cfg", [
          [ "NON Standard configurable parameters", "design_fls_top.html#design_fls_desc_cfg_ti", null ],
          [ "Variant Support", "design_fls_top.html#design_fls_desc_cfg_variant", null ]
        ] ],
        [ "Error Classification", "design_fls_top.html#design_fls_desc_error", [
          [ "Development Errors", "design_fls_top.html#design_fls_desc_error_dev", null ]
        ] ]
      ] ],
      [ "Low Level Definitions", "design_fls_top.html#design_fls_low_level", [
        [ "MACROS, Data Types & Structures", "design_fls_top.html#design_fls_low_level_dtypes", null ],
        [ "APIs", "design_fls_top.html#design_fls_low_level_api", [
          [ "Fls_Init", "design_fls_top.html#design_fls_low_level_api_init", null ],
          [ "Fls_Erase", "design_fls_top.html#design_fls_low_level_api_erase", null ],
          [ "Fls_Write", "design_fls_top.html#design_fls_low_level_api_write", null ],
          [ "Fls_GetStatus", "design_fls_top.html#design_fls_low_level_api_getstatus", null ],
          [ "Fls_GetJobResult", "design_fls_top.html#design_fls_low_level_api_getjobres", null ],
          [ "Fls_Read", "design_fls_top.html#design_fls_low_level_api_read", null ],
          [ "Fls_Compare", "design_fls_top.html#design_fls_low_level_api_compare", null ],
          [ "Fls_GetVersionInfo", "design_fls_top.html#design_fls_low_level_api_getverinf", null ],
          [ "Fls_BlankCheck", "design_fls_top.html#design_fls_low_level_api_blankcheck", null ],
          [ "Fls_MainFunction", "design_fls_top.html#design_fls_low_level_api_mainfunction", [
            [ "processJobs", "design_fls_top.html#design_fls_low_level_api_priv_processjobs", null ],
            [ "Fls_norRead", "design_fls_top.html#design_fls_low_level_api_priv_norRead", null ],
            [ "Fls_norWrite", "design_fls_top.html#design_fls_low_level_api_priv_norWrite", null ],
            [ "Fls_norErase", "design_fls_top.html#design_fls_low_level_api_priv_norErase", null ],
            [ "Fls_norCompare", "design_fls_top.html#design_fls_low_level_api_priv_norCompare", null ],
            [ "Fls_norBlankCheck", "design_fls_top.html#design_fls_low_level_api_priv_norBlankcheck", null ]
          ] ]
        ] ],
        [ "Global Variables", "design_fls_top.html#design_fls_low_level_globals", null ]
      ] ],
      [ "Decision Analysis & Resolution (DAR)", "design_fls_top.html#design_fls_dar_top", [
        [ "Data Transfer Mode", "design_fls_top.html#design_fls_dar_transfer_mode", [
          [ "DAR Criteria", "design_fls_top.html#design_fls_dar_criteria_transfer_mode", null ],
          [ "Available Alternatives", "design_fls_top.html#design_fls_dar_alternatives_transfer_mode", null ],
          [ "Decision", "design_fls_top.html#design_spi_dar_decision_transfer_mode", null ]
        ] ],
        [ "Selecting Flash device information structure", "design_fls_top.html#design_fls_dar_sectorstruct", [
          [ "DAR Criteria", "design_fls_top.html#design_fls_dar_criteria_sectorstruct", null ],
          [ "Available Alternatives", "design_fls_top.html#design_fls_dar_alternatives_sectorstruct", null ],
          [ "Decision", "design_fls_top.html#design_fls_dar_decision_sectorstructure", null ]
        ] ],
        [ "Selecting the SPI Driver", "design_fls_top.html#design_fls_dar_spidriver", [
          [ "DAR Criteria", "design_fls_top.html#design_fls_dar_criteria_spidriver", null ],
          [ "Available Alternatives", "design_fls_top.html#design_fls_dar_alternatives_spidriver", null ],
          [ "Decision", "design_fls_top.html#design_fls_dar_decision_spidriver", null ]
        ] ]
      ] ],
      [ "Test Criteria", "design_fls_top.html#design_fls_test_top", null ],
      [ "Document Revision History", "design_fls_top.html#design_fls_rev_hist", null ]
    ] ],
    [ "Icu Design Document", "design_icu_top.html", [
      [ "Introduction", "design_icu_top.html#design_icu_intro", [
        [ "Overview", "design_icu_top.html#design_icu_intro_overview", [
          [ "Icu Overview", "design_icu_top.html#design_icu_intro_icu_overview", null ],
          [ "References", "design_icu_top.html#design_icu_references", null ]
        ] ]
      ] ],
      [ "Requirements", "design_icu_top.html#design_icu_req", [
        [ "Features Supported", "design_icu_top.html#design_icu_features_supported", null ],
        [ "Features Not Supported / NON Compliance", "design_icu_top.html#design_icu_features_not_supported", null ],
        [ "Assumptions", "design_icu_top.html#design_icu_assumptions", null ]
      ] ],
      [ "Design Description", "design_icu_top.html#design_icu_description", [
        [ "Fundamental Operation", "design_icu_top.html#design_icu_fundamental_operation", null ],
        [ "Sequence Diagrams", "design_icu_top.html#design_icu_desc_seq", null ],
        [ "Resource Behavior", "design_icu_top.html#design_icu_desc_resource", null ],
        [ "Interrupt Service Routines", "design_icu_top.html#design_icu_desc_ISR", null ],
        [ "Time Unit Ticks", "design_icu_top.html#design_icu_ticks", null ],
        [ "Dynamic Behavior", "design_icu_top.html#design_icu_dynamic_behaviour", null ],
        [ "Directory Structure", "design_icu_top.html#design_icu_desc_deter_dir", null ],
        [ "Configurator", "design_icu_top.html#design_icu_desc_cfg", [
          [ "NON Standard configurable parameters", "design_icu_top.html#design_icu_desc_cfg_ti", null ],
          [ "Variant Support", "design_icu_top.html#design_icu_desc_cfg_variant", null ]
        ] ],
        [ "Error Classification", "design_icu_top.html#design_icu_desc_error", [
          [ "Development Errors", "design_icu_top.html#design_icu_desc_error_dev", null ]
        ] ],
        [ "Resource Behavior", "design_icu_top.html#design_icu_desc_res_behave", null ]
      ] ],
      [ "Low Level Definitions", "design_icu_top.html#design_icu_low_level", [
        [ "MACROS, Data Types & Structures", "design_icu_top.html#design_icu_low_level_dtypes", null ],
        [ "APIs", "design_icu_top.html#design_icu_low_level_api", [
          [ "Icu_Init", "design_icu_top.html#design_icu_low_level_api_init", null ],
          [ "Icu_Deinit", "design_icu_top.html#design_icu_low_level_api_deinit", null ],
          [ "Icu_SetActivationCondition", "design_icu_top.html#design_icu_low_level_api_setactivation", null ],
          [ "Icu_DisableNotification", "design_icu_top.html#design_icu_low_level_api_disablenotification", null ],
          [ "Icu_EnableNotification", "design_icu_top.html#design_icu_low_level_api_enablenotification", null ],
          [ "Icu_GetInputState", "design_icu_top.html#design_icu_low_level_api_getinputstate", null ],
          [ "Icu_StartTimestamp", "design_icu_top.html#design_icu_low_level_api_starttimestamp", null ],
          [ "Icu_StopTimestamp", "design_icu_top.html#design_icu_low_level_api_stoptimestamp", null ],
          [ "Icu_GetTimestampIndex", "design_icu_top.html#design_icu_low_level_api_gettimestamp", null ],
          [ "Icu_ResetEdgeCount", "design_icu_top.html#design_icu_low_level_api_resetEdgeCount", null ],
          [ "Icu_EnableEdgeCount", "design_icu_top.html#design_icu_low_level_api_enableEdgeCount", null ],
          [ "Icu_EnableEdgeDetection", "design_icu_top.html#design_icu_low_level_api_enableEdgeDetection", null ],
          [ "Icu_DisableEdgeDetection", "design_icu_top.html#design_icu_low_level_api_disableEdgeDetection", null ],
          [ "Icu_DisableEdgeCount", "design_icu_top.html#design_icu_low_level_api_disableEdgeCount", null ],
          [ "Icu_GetEdgeNumbers", "design_icu_top.html#design_icu_low_level_api_getedgenumbers", null ],
          [ "Icu_StartSignalMeasurement", "design_icu_top.html#design_icu_low_level_api_startsignalmeasure", null ],
          [ "Icu_StopSignalMeasurement", "design_icu_top.html#design_icu_low_level_api_stopsignalmeasure", null ],
          [ "Icu_GetTimeElapsed", "design_icu_top.html#design_icu_low_level_api_gettimeelapsed", null ],
          [ "Icu_GetDutyCycleValues", "design_icu_top.html#design_icu_low_level_api_getdutycyclevalues", null ],
          [ "Icu_GetVersionInfo", "design_icu_top.html#design_icu_low_level_api_getversioninfo", null ]
        ] ],
        [ "Global Variables", "design_icu_top.html#design_icu_low_level_globals", null ]
      ] ],
      [ "Decision Analysis & Resolution (DAR)", "design_icu_top.html#design_icu_dar_top", [
        [ "Signal Measurements API Design flow", "design_icu_top.html#design_icu_dar_signalmeasurement", [
          [ "DAR Criteria", "design_icu_top.html#design_icu_dar_criteria_signalmeasurements", null ],
          [ "Available Alternatives", "design_icu_top.html#design_icu_dar_alternatives_signalmeasurements", null ],
          [ "Decision", "design_icu_top.html#design_icu_dar_decision_signalmeasurements", null ]
        ] ],
        [ "Interrupt on Capture Registers", "design_icu_top.html#design_icu_dar_interrupt", [
          [ "DAR Criteria", "design_icu_top.html#design_icu_dar_criteria_interrupt", null ],
          [ "Available Alternatives", "design_icu_top.html#design_icu_dar_alternatives_interrupt", null ],
          [ "Decision", "design_icu_top.html#design_icu_dar_decision_interrupt", null ]
        ] ]
      ] ],
      [ "Test Criteria", "design_icu_top.html#design_icu_test_top", null ],
      [ "Document Revision History", "design_icu_top.html#design_icu_rev_hist", null ]
    ] ]
];