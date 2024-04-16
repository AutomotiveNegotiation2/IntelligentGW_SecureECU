
#ifndef APP_FC_CFG_H_
#define APP_FC_CFG_H_

App_MscTestCfg gAppMscTestCfg[] =
{
    #include <ti/drv/vhwa/examples/include/vhwa_msc_test_cfg.h>
};

Vhwa_M2mFcGraphPathInfo gPathInfo[] =
{
    /* Start Path DDR->VISS->MSC->DDR */
    /* 0 */
    {
        6,
        {
            {VHWA_FC_PORT_DDR, VHWA_FC_PORT_VISS_IN_0},
            {VHWA_FC_PORT_VISS_OUT_Y8, VHWA_FC_PORT_DDR},
            {VHWA_FC_PORT_VISS_OUT_UV8, VHWA_FC_PORT_DDR},
            {VHWA_FC_PORT_VISS_OUT_Y8, VHWA_FC_PORT_MSC0_IN_Y},
            {VHWA_FC_PORT_MSC0_OUT_0, VHWA_FC_PORT_DDR},
            {VHWA_FC_PORT_MSC0_OUT_1, VHWA_FC_PORT_DDR}
        }
    },
    /* 1 */
    /* VISS->MSC0, VISS->MSC1 */
    {
        7,
        {
            {VHWA_FC_PORT_DDR, VHWA_FC_PORT_VISS_IN_0},
            {VHWA_FC_PORT_VISS_OUT_Y8, VHWA_FC_PORT_MSC0_IN_Y},
            {VHWA_FC_PORT_MSC0_OUT_0, VHWA_FC_PORT_DDR},
            {VHWA_FC_PORT_MSC0_OUT_1, VHWA_FC_PORT_DDR},
            {VHWA_FC_PORT_VISS_OUT_UV8, VHWA_FC_PORT_MSC1_IN_Y},
            {VHWA_FC_PORT_MSC1_OUT_2, VHWA_FC_PORT_DDR},
            {VHWA_FC_PORT_MSC1_OUT_3, VHWA_FC_PORT_DDR}
        }
    },
};


AppFc_TestParams gAppFcTestPrms[] =
{
    /* DDR->VISS->MSC->DDR start */
    {
        "TC_001",                   /* Test Name */
        1,                          /* Num Handles */
        3,                          /* Repeate Count */
        FALSE,                      /* Is Performance */
        TRUE,                      /* isVissEnabled */
        TRUE,                       /* Is Msc0Enabled */
        FALSE,                       /* isMsc1Enabled */
        {                           /* Test Config */
            &gPathInfo[0],
            &gAppVissTestConfig[11],
            &gAppMscTestCfg[20],
            NULL
        },
        TRUE,    /* isEnableTest */
        FALSE,   /* vissIsSwitchGlbceCtx */
        FALSE,   /* vissChCfgOnEachIter  */
    },
    /* DDR->VISS->MSC0/MSC1->DDR start */
    {
        "TC_002",                   /* Test Name */
        1,                          /* Num Handles */
        3,                          /* Repeate Count */
        FALSE,                      /* Is Performance */
        TRUE,                      /* isVissEnabled */
        TRUE,                       /* Is Msc0Enabled */
        TRUE,                       /* isMsc1Enabled */
        {                           /* Test Config */
            &gPathInfo[1],
            &gAppVissTestConfig[11],
            &gAppMscTestCfg[20], 
            &gAppMscTestCfg[21]
        },
        TRUE,    /* isEnableTest */
        FALSE,   /* vissIsSwitchGlbceCtx */
        FALSE,   /* vissChCfgOnEachIter  */
    },
};

#endif

