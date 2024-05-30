#ifndef _DHAUTO_QUEUE_H_
#define _DHAUTO_QUEUE_H_

#pragma pack(push, 1)

enum
{
	QUEUE_BUFFER_STS_NORMAL,
	QUEUE_BUFFER_STS_EMPTY,
	QUEUE_BUFFER_STS_FULL,
	QUEUE_BUFFER_STS_OVERFLOW,
	QUEUE_BUFFER_STS_LOCK,
	QUEUE_BUFFER_STS_DONE
};

typedef struct 
{
	uint8_t *Buffer;
	uint32_t ReadPtr;
	uint32_t WritePtr;
	uint32_t DataSize;
	uint32_t DataNum;
	uint8_t QueueLock;
	uint8_t Status;
	uint8_t Usage;
	uint32_t PrePopCnt;
} QUEUE;

#pragma pack(pop)

void Queue_InitBuffer(QUEUE* pQueue, void *pBuffer, uint32_t DataSize, uint32_t DataNum);
void Queue_ClearBuffer(QUEUE* pQueue);
int Queue_PopBuffer(QUEUE* pQueue, void* PopData);
int Queue_PushBuffer(QUEUE* pQueue, void* PushData);
int Queue_PrePopDone(QUEUE* pQueue);
int Queue_PrePopBuffer(QUEUE* pQueue, void* PopData);
int Queue_GetPrePopCnt(QUEUE* pQueue);
int Queue_GetStatus(QUEUE* pQueue);

#endif /* _DHAUTO_QUEUE_H_ */