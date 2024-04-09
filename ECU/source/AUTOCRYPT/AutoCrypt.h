#ifndef _AUTOCRYPT_H_
#define	_AUTOCRYPT_H_

#if (DEBUG_AUTOCRYPT == ON)
#define	AUTOCRYPT_PRINTF	PRINTF
#else
#define	AUTOCRYPT_PRINTF
#endif

void Init_AutoCryptFunc(void);
void AutoCryptFunc(void);

#endif /* _AUTOCRYPT_H_ */