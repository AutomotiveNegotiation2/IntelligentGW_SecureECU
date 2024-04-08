#ifndef _IL_H_
#define _IL_H_

#pragma pack(push, 4)

typedef struct {
	bool	firstCanStart;	
} ilMsgCtrl_t;

#pragma pack(pop)

void ilInit(void);
void ilStart(void);
void ilTxTask(void);
void Debug_ilRxTask(void);

bool ilGetFirstCanOpStatus(void);

#endif /* _IL_H_ */
