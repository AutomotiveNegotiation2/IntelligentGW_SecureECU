#include "Includes.h"

#define	FALSE	0
#define	TRUE	1

void Queue_InitBuffer(QUEUE* pQueue, void *pBuffer, uint32_t DataSize, uint32_t DataNum)
{
	pQueue->Buffer = (uint8_t *)pBuffer;
	pQueue->ReadPtr = 0;
	pQueue->WritePtr = 0;
	pQueue->DataSize = DataSize;
	pQueue->DataNum = DataNum;
	pQueue->Status = QUEUE_BUFFER_STS_EMPTY;
	pQueue->QueueLock = FALSE;
	pQueue->Usage = 0;
	pQueue->PrePopCnt = 0;

	memset(pQueue->Buffer, 0, DataSize*DataNum);
}

void Queue_ClearBuffer(QUEUE* pQueue)
{
	pQueue->ReadPtr = 0;
	pQueue->WritePtr = 0;
	pQueue->QueueLock = FALSE;
	pQueue->Status = QUEUE_BUFFER_STS_EMPTY;
	
	memset(pQueue->Buffer, 0, pQueue->DataSize * pQueue->DataNum);
}

int Queue_PopBuffer(QUEUE* pQueue, void* PopData)
{
	int tmp, tmp2;
	uint8_t * tBuf;
	
	tBuf = pQueue->Buffer;

	tmp2 = pQueue->DataNum;
	if (pQueue->WritePtr < pQueue->ReadPtr)
	{
		tmp = tmp2 - pQueue->ReadPtr + pQueue->WritePtr;
	}
	else
	{
		tmp = pQueue->WritePtr - pQueue->ReadPtr;
	}

	pQueue->Usage = (tmp * 100) / tmp2;

	if (pQueue->QueueLock == TRUE)
	{
		return QUEUE_BUFFER_STS_LOCK;
	}
	
	//pQueue->QueueLock = TRUE;

	if (pQueue->Status == QUEUE_BUFFER_STS_OVERFLOW)
	{
		pQueue->Usage = 100;

		pQueue->ReadPtr = 0;
		pQueue->WritePtr = 0;
		pQueue->Status = QUEUE_BUFFER_STS_EMPTY;
		pQueue->QueueLock = FALSE;
		memset(pQueue->Buffer, 0, pQueue->DataSize * pQueue->DataNum);

		return pQueue->Status;
	}

	if (pQueue->Status == QUEUE_BUFFER_STS_EMPTY)
	{
		if (pQueue->ReadPtr == pQueue->WritePtr)
		{
			pQueue->Status = QUEUE_BUFFER_STS_EMPTY;
		}
		else
		{
			pQueue->Status = QUEUE_BUFFER_STS_NORMAL;
		}
	}

	tBuf = pQueue->Buffer + pQueue->ReadPtr*pQueue->DataSize;

	if (pQueue->Status == QUEUE_BUFFER_STS_NORMAL || pQueue->Status == QUEUE_BUFFER_STS_FULL)
	{
		//memcpy(PopData, &(pQueue->Buffer)[pQueue->ReadPtr*pQueue->DataSize], pQueue->DataSize);
		memcpy(PopData, tBuf, pQueue->DataSize);

		//pQueue->ReadPtr = (++pQueue->ReadPtr) % pQueue->DataNum;
		pQueue->ReadPtr++;
		pQueue->ReadPtr %= pQueue->DataNum;

		if (pQueue->ReadPtr == pQueue->WritePtr)
		{
			pQueue->Status = QUEUE_BUFFER_STS_EMPTY;
		}
		else
		{
			pQueue->Status = QUEUE_BUFFER_STS_NORMAL;
		}

		pQueue->QueueLock = FALSE;

		return QUEUE_BUFFER_STS_DONE;
	}
	else
	{
		PopData = 0x00;
	}

	// pQueue->QueueLock = FALSE;
	return pQueue->Status;
}

int Queue_GetPrePopCnt(QUEUE* pQueue)
{
	return pQueue->PrePopCnt;
}

int Queue_GetStatus(QUEUE* pQueue)
{
	return pQueue->Status;
}

int Queue_PrePopBuffer(QUEUE* pQueue, void* PopData)
{
	int tmp, tmp2;
	uint8_t * tBuf;

	tBuf = pQueue->Buffer;

	tmp2 = pQueue->DataNum;
	if (pQueue->WritePtr < pQueue->ReadPtr)
	{
		tmp = tmp2 - pQueue->ReadPtr + pQueue->WritePtr;
	}
	else
	{
		tmp = pQueue->WritePtr - pQueue->ReadPtr;
	}

	pQueue->Usage = (tmp * 100) / tmp2;

	if (pQueue->Status == QUEUE_BUFFER_STS_OVERFLOW)
	{
		pQueue->Usage = 100;

		pQueue->ReadPtr = 0;
		pQueue->WritePtr = 0;
		pQueue->Status = QUEUE_BUFFER_STS_EMPTY;
		pQueue->QueueLock = FALSE;
		pQueue->PrePopCnt = 0;
		memset(pQueue->Buffer, 0, pQueue->DataSize * pQueue->DataNum);

		return pQueue->Status;
	}

	if (pQueue->Status == QUEUE_BUFFER_STS_EMPTY)
	{
		if (pQueue->ReadPtr == pQueue->WritePtr)
		{
			pQueue->Status = QUEUE_BUFFER_STS_EMPTY;
		}
		else
		{
			pQueue->Status = QUEUE_BUFFER_STS_NORMAL;
		}
	}

	tBuf = pQueue->Buffer + pQueue->ReadPtr*pQueue->DataSize;

	if (pQueue->Status == QUEUE_BUFFER_STS_NORMAL || pQueue->Status == QUEUE_BUFFER_STS_FULL)
	{
		memcpy(PopData, tBuf, pQueue->DataSize);

		pQueue->PrePopCnt++;

		return QUEUE_BUFFER_STS_DONE;
	}
	else
	{
		PopData = 0x00;
	}

	return pQueue->Status;
}

int Queue_PrePopDone(QUEUE* pQueue)
{
	pQueue->PrePopCnt = 0;

	if (pQueue->Status == QUEUE_BUFFER_STS_OVERFLOW)
	{
		pQueue->ReadPtr = 0;
		pQueue->WritePtr = 0;
		pQueue->Status = QUEUE_BUFFER_STS_EMPTY;
		pQueue->QueueLock = FALSE;
		pQueue->PrePopCnt = 0;
		memset(pQueue->Buffer, 0, pQueue->DataSize * pQueue->DataNum);

		return pQueue->Status;
	}

	if (pQueue->Status == QUEUE_BUFFER_STS_NORMAL || pQueue->Status == QUEUE_BUFFER_STS_FULL)
	{
		/* temp register is used to remove a warning message */
		int temp;
		temp = (++pQueue->ReadPtr) % pQueue->DataNum;
		pQueue->ReadPtr = temp;

		if (pQueue->ReadPtr == pQueue->WritePtr)
		{
			pQueue->Status = QUEUE_BUFFER_STS_EMPTY;
		}
		else
		{
			pQueue->Status = QUEUE_BUFFER_STS_NORMAL;
		}

		return QUEUE_BUFFER_STS_DONE;
	}

	return pQueue->Status;
}

int Queue_PushBuffer(QUEUE* pQueue, void* PushData)
{
	uint8_t * tBuf;

	tBuf = pQueue->Buffer;
	
	if (pQueue->QueueLock == TRUE)
	{
		return QUEUE_BUFFER_STS_LOCK;
	}

	pQueue->QueueLock = TRUE;

	if (pQueue->Status == QUEUE_BUFFER_STS_FULL)
	{
		if (pQueue->WritePtr == pQueue->ReadPtr)
		{
			pQueue->Status = QUEUE_BUFFER_STS_OVERFLOW;

			pQueue->ReadPtr = 0;
			pQueue->WritePtr = 0;
			pQueue->Status = QUEUE_BUFFER_STS_EMPTY;
			pQueue->QueueLock = FALSE;
			memset(pQueue->Buffer, 0, pQueue->DataSize * pQueue->DataNum);
		}
		else
		{
			pQueue->Status = QUEUE_BUFFER_STS_NORMAL;
		}
	}

	tBuf = pQueue->Buffer + pQueue->WritePtr*pQueue->DataSize;

	if (pQueue->Status == QUEUE_BUFFER_STS_NORMAL || pQueue->Status == QUEUE_BUFFER_STS_EMPTY)
	{
		memcpy(tBuf, PushData, pQueue->DataSize);

		/* temp register is used to remove a warning message */
		int temp;		
		temp = (++pQueue->WritePtr) % pQueue->DataNum;
		pQueue->WritePtr = temp;
		
		if (pQueue->WritePtr == pQueue->ReadPtr)
		{
			pQueue->Status = QUEUE_BUFFER_STS_FULL;
		}
		else
		{
			pQueue->Status = QUEUE_BUFFER_STS_NORMAL;
		}

		pQueue->QueueLock = FALSE;
		
		return QUEUE_BUFFER_STS_DONE;
	}

	pQueue->QueueLock = FALSE;

	return pQueue->Status;
}



