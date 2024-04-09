#ifndef _DHAUTO_SEQUENCE_H_
#define	_DHAUTO_SEQUENCE_H_

#define PROC_NORMAL_MODE			0
#define PROC_EMERGENCY_MODE			1

#pragma pack(push, 4)

typedef enum GlobalSeq
{
	GB_SEQ_START,		// NULL not use
	GB_SEQ_BATT_OFF,	// 1
	GB_SEQ_DN_BATT_OFF,	// 2
	GB_SEQ_UP_ACC_OFF, 	// 3
#if defined (_INCLUDE_CAN_DRIVER_)
	GB_SEQ_NTWRK_WKUP, 	// 4
#endif
	GB_SEQ_ACC_OFF,		// 5
	GB_SEQ_DN_ACC_OFF,	// 6
	GB_SEQ_UP_ACC_ON,	// 7
	GB_SEQ_ACC_ON,		// 8

#ifdef DEBUG_GLOBAL_SEQ_BAT_6V5_EN
	GB_SEQ_DN_BATT_6V5_OFF,
	GB_SEQ_BATT_6V5_OFF,
	GB_SEQ_UP_BATT_6V5_ON,
#endif

	GB_SEQ_END			// NULL not use
} eGLOBAL_SEQ;

typedef enum LocalSeq
{
	LO_SEQ_START,	//0x00
	LO_SEQ_01,		//0x01
	LO_SEQ_02,		//0x02
	LO_SEQ_03,		//0x03
	LO_SEQ_04,		//0x04
	LO_SEQ_05,		//0x05
	LO_SEQ_06,		//0x06
	LO_SEQ_07,		//0x07
	LO_SEQ_08,		//0x08
	LO_SEQ_09,		//0x09
	LO_SEQ_10,		//0x0A
	LO_SEQ_11,		//0x0B
	LO_SEQ_12,		//0x0C
	LO_SEQ_13,		//0x0D
	LO_SEQ_14,		//0x0E
	LO_SEQ_FINISH=15,//0x0F End of Sequence	
	LO_ALL_FINISH=0xFFFFFFFF // End of all procedure sequence
} eLOCAL_SEQ;

typedef union
{
	uint32_t U;
	struct TagLocalProc    
	{
		//uint32_t SEQ_POWER  :4;
		//uint32_t SEQ_IDLE	:4;
     	uint32_t SEQ_CAN    :4;
		uint32_t SEQ_ENET_100M	:4;
		uint32_t SEQ_APP	:4;
		uint32_t SEQ_IOCTRL	:4;
		uint32_t SEQ_RES	:16;	// reserved
	} B;
} LOCAL_PROC_SEQ;

typedef struct TagMuteFlag
{
	uint8_t PWR_AMP;
	uint8_t DSP;
	uint8_t SCALER;
	uint8_t LCD_BACK;
	uint8_t RSE_VIDEO;
	uint8_t RSE_AUDIO;
} MUTE_FLAG;

typedef struct TagPowerFlag
{
	uint8_t SYSTEM;
	uint8_t APOWER;
	uint8_t DSP;
	uint8_t TUNER;
	uint8_t DECK;
	uint8_t SCALER;
	uint8_t PWR_AMP;
	uint8_t MTB;
	uint8_t MTB_SUB;
	uint8_t FAN;
	uint8_t LED;
	uint8_t RVC;
	uint8_t ANT;	
	uint8_t RVC_OPT;
	uint8_t GNAVI;
	uint8_t CAN;
} POWER_FLAG;

typedef struct TagGlobalSequence
{
	eGLOBAL_SEQ    	GSeq;
	LOCAL_PROC_SEQ 	LSeq;
	POWER_FLAG		PFlag;
	MUTE_FLAG		MFlag;

} GLOBAL_PROC_SEQUENCE;
/////////////////////////////////////////////////////////

typedef enum ProcedureID
{
	PROC_ID_POWER,
	PROC_ID_CAN,
	PROC_ID_COMM,
	PROC_ID_IOCTRL,
	PROC_END_OF_ID
} ePROC_ID;

#pragma pack(pop)

extern GLOBAL_PROC_SEQUENCE GlobalPocSeq;
extern uint8_t gFlagSystemActive;

void GlobalSeqSwitch(eGLOBAL_SEQ GSEQ);
void GlobalSequence(void);
void GlobalSequence_Init(void);

#endif /* _DHAUTO_SEQUENCE_H_ */