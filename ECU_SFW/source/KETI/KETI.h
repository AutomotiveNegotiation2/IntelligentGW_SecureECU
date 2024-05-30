#ifndef _KETI_H_
#define	_KETI_H_

#if (DEBUG_KETI == ON)
#define	KETI_PRINTF			PRINTF
#else
#define	KETI_PRINTF
#endif

void Init_KetiFunc(void);
void KetiFunc(void);

#endif /* _KETI_H_ */
