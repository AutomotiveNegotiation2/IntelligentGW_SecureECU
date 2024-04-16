/*****************************************************************************/
/*  AEABI_ATEXIT.C                                                           */
/*                                                                           */
/* Copyright (c) 2019 Texas Instruments Incorporated                         */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/
/*-
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <errno.h>
#include <_mutex.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define	ATEXIT_FN_EMPTY	0
#define	ATEXIT_FN_STD	1
#define	ATEXIT_FN_CXA	2
#define ATEXIT_SIZE 8

#define _MUTEX_LOCK(x)    __TI_resource_lock(__TI_LOCK_ATEXIT)
#define _MUTEX_UNLOCK(x)  __TI_resource_unlock(__TI_LOCK_ATEXIT)
/*
  Mutexes destroyed as part of exit so this can be left defined to nothing
*/
#define _MUTEX_DESTROY(x)

/*
  Data structure for atexit registered functions
*/
struct atexit {
  struct atexit *next;			/* next in list */
  int ind;				/* next index in this table */
  struct atexit_fn {
    int fn_type;			/* ATEXIT_? from above */
    union {
      void (*std_func)(void);
      void (*cxa_func)(void *);
    } fn_ptr;			        /* function pointer */
    void *fn_arg;			/* argument for CXA callback */
    void *fn_dso;			/* shared module handle */
  } fns[ATEXIT_SIZE];			/* the table itself */
};

static struct atexit *__atexit;		/* points to head of LIFO structure */
extern void _DATA_ACCESS (*__TI_dtors_ptr)(int); /* points to __cxa_ia64_exit */
void __cxa_ia64_exit(int status);       /* calls finalize */

/*
 * Register the function described by 'fptr' to be called at application
 * exit or when loaded shared objects are unloaded as they would on application
 * exit. This is a helper function for atexit and __cxa_atexit.
 */
static int
atexit_register(struct atexit_fn *fptr)
{
  /*
    atexit_register() is always called when a function is registered to be
    called at exit so this assignment is placed here
 */
  __TI_dtors_ptr = __cxa_ia64_exit;

  static struct atexit __atexit0;	/* one guaranteed table */
  struct atexit *p;

  _MUTEX_LOCK(&atexit_mutex);
  if ((p = __atexit) == NULL)
    __atexit = p = &__atexit0;          /* top of stack, first table needed */
  /*
    Create a new struct if the current one is full.
  */
  else while (p->ind >= ATEXIT_SIZE) {
      struct atexit *old__atexit;
      old__atexit = __atexit;
      _MUTEX_UNLOCK(&atexit_mutex);
      if ((p = (struct atexit *)malloc(sizeof(*p))) == NULL)
        return (-1);                    /* failed to register, atexit fails */
      _MUTEX_LOCK(&atexit_mutex);
      if (old__atexit != __atexit) {
        /*
          Lost race, retry operation
        */
        _MUTEX_UNLOCK(&atexit_mutex);
        free(p);
	_MUTEX_LOCK(&atexit_mutex);
        p = __atexit;
        continue;
      }
      /*
        Top of stack is updated
      */
      p->ind = 0;
      p->next = __atexit;
      __atexit = p;
    }
  /*
    stack location points to correct function
  */
  p->fns[p->ind++] = *fptr;
  _MUTEX_UNLOCK(&atexit_mutex);

  return 0;                             /* return success */
}

/*
 * Register a function to be performed at exit.
 */
int
atexit(void (*func)(void))
{
  struct atexit_fn fn;
  int error;

  fn.fn_type = ATEXIT_FN_STD;
  fn.fn_ptr.std_func = func;
  fn.fn_arg = NULL;
  fn.fn_dso = NULL;

  error = atexit_register(&fn);
  return (error);                       /* 0 is success */
}


/*
 * Register a function to be performed at exit or when an shared object
 * with given dso handle is unloaded dynamically.
 */
int
__cxa_atexit(void (*func)(void *), void *arg, void *dso)
{
  struct atexit_fn fn;
  int error;

  fn.fn_type = ATEXIT_FN_CXA;
  fn.fn_ptr.cxa_func = func;
  fn.fn_arg = arg;
  fn.fn_dso = dso;

  error = atexit_register(&fn);
  return (error);                       /* 0 is success */
}


static int global_exit;

/*
 * Call all handlers registered with __cxa_atexit for the shared
 * object owning 'dso' and call all functions registered with atexit.
 * Note: if 'dso' is NULL, then all remaining handlers are called.
 * Note: dso support is not enabled for this definition of __cxa_finalize.
 */
void
__cxa_finalize(void *dso)
{
  struct atexit *p;
  struct atexit_fn fn;
  int n;

  _MUTEX_LOCK(&atexit_mutex);

  /*
    keep looping while there is a "top"
  */
  while (__atexit != NULL ) {
    /*
      set p and n to top of stack
    */
    p = __atexit;
    n = p->ind-1;
    /*
      All functions in the current struct have been executed if n is -1.
      If next is NULL, the loop will end.
    */
    if (n == -1) {
      __atexit = __atexit->next;
      /*
        Do not call free for p if this is the "one guaranteed table" created
        with __atexit0 in atexit_register(). Only additional tables created with
        malloc should be freed.
      */
        if(__atexit != NULL)
          free(p);
        continue;
    }
    /*
      There are still functions to be called.
    */
    else {
      __atexit->ind--;                  /* Decrement the top's index */
    /*
      FREEBSD implementation for calling the function.
      fn is the function to be called in the current iteration.
    */
    fn = p->fns[n];
    /*
      Mark entry to indicate that this particular handler
      has already been called.
    */
    _MUTEX_UNLOCK(&atexit_mutex);
    /*
      Call the function of correct type.
    */
    if (fn.fn_type == ATEXIT_FN_CXA)
      fn.fn_ptr.cxa_func(fn.fn_arg);
    else if (fn.fn_type == ATEXIT_FN_STD)
      fn.fn_ptr.std_func();

    _MUTEX_LOCK(&atexit_mutex);
    }                                   /* end else */
  }                                     /* end while */

  _MUTEX_UNLOCK(&atexit_mutex);
  if (dso == NULL)
    _MUTEX_DESTROY(&atexit_mutex);
}

/*
 * Called from exit() through __TI_dtors_ptr
 */
void
__cxa_ia64_exit(int status)
{
  __cxa_finalize(NULL);
}
