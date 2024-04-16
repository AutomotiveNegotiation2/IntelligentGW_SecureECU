/* lwIP includes. */
#include "lwip/debug.h"
#include "lwip/def.h"
#include "lwip/sys.h"
#include "lwip/mem.h"
#include "lwip/stats.h"
#include "arch/sys_arch.h"

#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Mailbox.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Task.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/HeapStd.h>
#include <ti/sysbios/gates/GateMutexPri.h>
#include <ti/sysbios/hal/Hwi.h>

#include <ti/sysbios/BIOS.h>
#include <string.h>
#include <stdlib.h>


#include <ti/sysbios/hal/Seconds.h>
//#include <ti/sysbios/interfaces/ISeconds.h>

#define ISeconds_Time ti_sysbios_interfaces_ISeconds_Time

extern sys_mutex_t lock_tcpip_core;

int mail_count;

/********************Structure Definition****************/

struct thread_locker{
	GateMutexPri_Struct GateMutexPriStruct;
    GateMutexPri_Handle hMutex;
	IArg key;
} sys_arch_lock;

struct tcpip_locker{
	GateMutexPri_Struct GateMutexPriStruct;
    GateMutexPri_Handle hMutex;
	IArg key;
} tcpip_lock;

static sys_prot_t sys_arch_protect_nesting;

/********************Static Functions********************/

static void
get_monotonic_time(struct ISeconds_Time *ts)
{
    Seconds_getTime(ts);
}
/*****************************************************/
/********************Lib Functions********************/
/*****************************************************/

/*------------------- init -------------------*/
void sys_init()
{
    GateMutexPri_Params params;
    IArg key;
    
    key = Hwi_disable();
    
    sys_mutex_new(&lock_tcpip_core);
    
    GateMutexPri_Params_init(&params);
    
    GateMutexPri_construct(&tcpip_lock.GateMutexPriStruct, &params);
    tcpip_lock.hMutex = GateMutexPri_handle(&tcpip_lock.GateMutexPriStruct);
    
    GateMutexPri_construct(&sys_arch_lock.GateMutexPriStruct, &params);
    sys_arch_lock.hMutex = GateMutexPri_handle(&sys_arch_lock.GateMutexPriStruct);
    
    sys_arch_protect_nesting = 0;
    Hwi_restore(key);
    return;
}

/*------------------ Time --------------------*/

/* Return time is millisecs */
u32_t sys_now()
{
    struct ISeconds_Time ts;

    get_monotonic_time(&ts);
    return (u32_t)(ts.secs * 1000L + ts.nsecs / 1000000L);
}

/* Returns time in clock ticks */
u32_t sys_jiffies()
{
    return Clock_getTicks();
}

/*------------------- Semaphores -------------------*/

/* Creates new semaphore */
err_t sys_sem_new(sys_sem_t *sem, u8_t count)
{
    Semaphore_Params_init(&(sem->semParams));
    sem->semParams.mode = Semaphore_Mode_COUNTING;
	sem->semHandle = Semaphore_create(count, &(sem->semParams), &(sem->eb));
	return (!(sem->semHandle)) ? ERR_MEM : ERR_OK;
}

/* Free semaphore */
void sys_sem_free(sys_sem_t *sem)
{
	Semaphore_delete(&(sem->semHandle));
}

/* Posts to a semaphore*/
void sys_sem_signal(sys_sem_t *sem)
{
	Semaphore_post(sem->semHandle);
}

/* 
 * Pends a semaphore for a given period and returns time for which the task was blocked
 * if the wait time was less than the supplied timeout period.
 */
u32_t sys_arch_sem_wait(sys_sem_t *sem, u32_t timeout)
{
	u32_t ticksStart, ticksEnd, millisecDifference, updatedTimeout;
	updatedTimeout = (timeout == 0) ? BIOS_WAIT_FOREVER: timeout;
	int stat;
	
	ticksStart = sys_now();

	if(timeout == 1) {
		updatedTimeout = BIOS_NO_WAIT;
	}
	stat = Semaphore_pend(sem->semHandle, updatedTimeout);
	if(!stat)
	{
		return SYS_ARCH_TIMEOUT;
	}
	ticksEnd = sys_now();
	millisecDifference = ticksEnd - ticksStart;

	/* Return how long until semaphore was acquired */
	return millisecDifference;
}

/* Checks validity of the semaphore */
int sys_sem_valid(sys_sem_t *sem)
{
	return (int) ( ((sem) != NULL) && ( sem->semHandle != NULL) );
}

/* Nothing to do here. Called always after sys_sem_free() which already sets the handler to NULL*/
void sys_sem_set_invalid(sys_sem_t *sem)
{
	return;
}

/*------------------- Mutexes -------------------*/

/* Just Binary Semaphores */
err_t sys_mutex_new(sys_mutex_t *mutex)
{
    Semaphore_Params_init(&(mutex->semParams));
    mutex->semParams.mode = Semaphore_Mode_BINARY;
	mutex->semHandle = Semaphore_create(1, &(mutex->semParams), &(mutex->eb));

	return ((mutex->semHandle) == NULL) ? ERR_MEM : ERR_OK;
}

/* Frees a mutex */
void sys_mutex_free(sys_mutex_t *mutex)
{
	sys_sem_free(mutex);
}

/* Locks a mutex */
void sys_mutex_lock(sys_mutex_t *mutex)
{
	sys_arch_sem_wait(mutex, 0);
}

/* Unlocks a mutex */
void sys_mutex_unlock(sys_mutex_t *mutex)
{
	sys_sem_signal(mutex);
}

/* Checks validity of a mutex */
int sys_mutex_valid(sys_mutex_t *mutex)
{
	return sys_sem_valid(mutex);
}

/* 
 * Sets a mutex to invalid. Since this function is called after the mutex is
 * freed. Hence, just as the semaphore, there is nothing to do here.
 */
void sys_mutex_set_invalid(sys_mutex_t *mutex)
{
	sys_sem_set_invalid(mutex);
}

/*------------------- Mailboxes -------------------*/
/*
 * mail_count is used only to debug if the mailbox is working properly.
 * Can be removed during release !!!!
 */
 
/* Creates a new mailbox */
err_t sys_mbox_new(sys_mbox_t *mbox, int size)
{
    Mailbox_Params_init(&(mbox->mboxParams));
    mbox->mboxHandle = Mailbox_create(sizeof(void *), size, &(mbox->mboxParams), &(mbox->eb));
	return (mbox->mboxHandle) ? ERR_OK : ERR_MEM;
}

/* Frees a mailbox */
void sys_mbox_free(sys_mbox_t *mbox)
{
	Mailbox_delete(&(mbox->mboxHandle));
}

/* Posts to a mailbox */
void sys_mbox_post(sys_mbox_t *mbox, void *msg)
{
	Mailbox_post(mbox->mboxHandle, &msg, BIOS_WAIT_FOREVER);
	mail_count++;
}

/* Post and return whether post was successful or not */
err_t sys_mbox_trypost(sys_mbox_t *mbox, void *msg)
{
    mail_count++;
	return (Mailbox_post(mbox->mboxHandle, &msg, BIOS_NO_WAIT)) ? ERR_OK : ERR_MEM;
}

/* Fetches from the mailbox and return time taken to do so */
u32_t sys_arch_mbox_fetch(sys_mbox_t *mbox, void **msg, u32_t timeout)
{
	u32_t ticksStart, ticksEnd, millisecDifference, updatedTimeout;
	updatedTimeout = (timeout == 0) ? BIOS_WAIT_FOREVER: timeout;

	ticksStart = sys_now();
	if(!Mailbox_pend(mbox->mboxHandle, &mbox->msg, updatedTimeout))
	{
		return SYS_ARCH_TIMEOUT;
	}
	ticksEnd = sys_now();

	// If msg is NULL, message from mailbox should be dropped.
	if(msg)
	{
		*msg = mbox->msg;
	}

	millisecDifference = ticksEnd - ticksStart;

	mail_count--;
	// Return how long until message was acquired
	return millisecDifference;
}

/* Fetches from a mailbox and returns error if fetch fails */
u32_t sys_arch_mbox_tryfetch(sys_mbox_t *mbox, void **msg)
{
	if(!Mailbox_pend(mbox->mboxHandle, &mbox->msg, BIOS_NO_WAIT))
	{
			return SYS_MBOX_EMPTY;
	}

	// If msg is NULL, message from mailbox should be dropped.
	if(msg)
	{
		*msg = mbox->msg;
	}

	mail_count--;
	return ERR_OK;
}

/* Checks validity of mailbox */
int sys_mbox_valid(sys_mbox_t *mbox)
{
	return (int)(((mbox) != NULL) && (mbox->mboxHandle != NULL));
}

// Nothing to do here. Called always after sys_sem_free() which already sets the handler to NULL.
void sys_mbox_set_invalid(sys_mbox_t *mbox)
{
	return;
}


/*------------------- Threads -------------------*/

/*
 * threadFunc is void func pointer with void* arg
 * threadArg is void*
 */
 
typedef void Thread_FuncPtr(void*);

Void taskFunc(UArg threadFunc, UArg threadArg)
{
	((Thread_FuncPtr*)(threadFunc)) ((void*)threadArg);
}

/* Initializes thread */
sys_thread_t sys_thread_new(const char *name, void (* thread)(void *arg), void *arg, int stacksize, int prio)
{
	sys_thread_t newThread = (sys_thread_t)mem_malloc(sizeof(struct sys_thread));

	if (newThread != NULL)
	{
		Error_init(&(newThread->eb));

		/* Init thread params */
		Task_Params_init(&(newThread->taskParams));
		newThread->taskParams.instance->name = name;
		newThread->taskParams.stackSize = stacksize;
		newThread->taskParams.priority = prio;
		newThread->taskParams.arg0 = (UArg)thread;
		newThread->taskParams.arg1 = (UArg)arg;
	
		newThread->taskHandle = Task_create(taskFunc, &(newThread->taskParams), &(newThread->eb));
	}

	return newThread;
}

/*-----------------------Thread protection---------------------*/
/*
 * Protects the thread. Ported from the linux port shipped with the lwip-contrib
 */
static u8_t lwip_core_lock_count;
sys_thread_handle lwip_core_lock_holder_thread_id;


void sys_lock_tcpip_core(void)
{
    tcpip_lock.key = GateMutexPri_enter(tcpip_lock.hMutex);
    if (lwip_core_lock_count == 0) {
        lwip_core_lock_holder_thread_id = Task_self();
    }
    lwip_core_lock_count++;
}

void sys_unlock_tcpip_core(void)
{
    lwip_core_lock_count--;
    if (lwip_core_lock_count == 0) {
        lwip_core_lock_holder_thread_id = 0;
    }
    GateMutexPri_leave(tcpip_lock.hMutex, tcpip_lock.key);
}

sys_prot_t sys_arch_protect()
{
    sys_prot_t prev;

    sys_arch_lock.key = GateMutexPri_enter(sys_arch_lock.hMutex);
    /* every nested call to sys_arch_protect() returns an increased number */
    prev = sys_arch_protect_nesting;
    sys_arch_protect_nesting++;
    LWIP_ASSERT("sys_arch_protect overflow", sys_arch_protect_nesting > prev);

    return (sys_prot_t)sys_arch_lock.key;
}

void sys_arch_unprotect(sys_prot_t pval)
{
    LWIP_ASSERT("unprotect returning wrong key", pval == sys_arch_lock.key);
    LWIP_ASSERT("unexpected sys_arch_protect_nesting", sys_arch_protect_nesting > 0);
    sys_arch_protect_nesting--;
    GateMutexPri_leave(sys_arch_lock.hMutex, sys_arch_lock.key);
}

sys_thread_handle lwip_tcpip_thread_id;
void sys_check_core_locking()
{
	if(lwip_tcpip_thread_id != 0 && lwip_core_lock_holder_thread_id != 0)
	{
	    sys_thread_handle current_thread_id;
	    current_thread_id = Task_self();
	    LWIP_ASSERT("Different function than core locker function", current_thread_id == lwip_core_lock_holder_thread_id);
	}
}

void sys_mark_tcpip_thread(void)
{
	lwip_tcpip_thread_id = Task_self();
}
