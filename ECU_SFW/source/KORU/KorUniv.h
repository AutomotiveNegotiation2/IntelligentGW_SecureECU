#ifndef _KORUNIV_H_
#define	_KORUNIV_H_

#if (DEBUG_KORUNIV == ON)
#define	KORUNIV_PRINTF		PRINTF
#else
#define	KORUNIV_PRINTF
#endif

void Init_KorUnivFunc(void);
void KorUnivFunc(void);

#endif /* _KORUNIV_H_ */