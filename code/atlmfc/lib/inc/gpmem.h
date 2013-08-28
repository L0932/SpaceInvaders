// Copyright (C) 2004-2009 Joe Linhoff - All Rights Reserved
// gpmem.h -- public interface to library (mem & thread)
#ifndef GPMEM_H
#define GPMEM_H

#ifndef GPTYPES_H
#include "gptypes.h"
#endif // ndef GPTYPES_H

#ifdef __cplusplus  // C in C++
extern "C" {        //
#endif              //

///////////////////////////////////////////////////////////////////////////////
// LIBRARY

GP_API int gpmemInit();
GP_API void gpmemFinal();

///////////////////////////////////////////////////////////////////////////////
// MEMORY

GP_API void gpMemZero(ptr dst,uns size);
GP_API void gpMemCpy(ptr dst,ptr src,uns size);

#define M_GPMEMR_USR 0x00
#define M_GPMEMR_SYS 0x01

GP_API int gpMemRawAlloc(uns memr,ptr memp,uns size);
GP_API int gpMemRawAlloz(uns memr,ptr memp,uns size);
GP_API int gpMemRawRealloc(uns memr,ptr memp,uns size,ptr oldmem);
GP_API int gpMemRawFree(uns memr,ptr mem);
GP_API int gpMemRawAllocCount(uns memr);

#define gpMemAlloc(_memp_,_size_) gpMemRawAlloc(M_GPMEMR_USR,(_memp_),(_size_))
#define gpMemAlloz(_memp_,_size_) gpMemRawAlloz(M_GPMEMR_USR,(_memp_),(_size_))
#define gpMemFree(_mem_) gpMemRawFree(M_GPMEMR_USR,(_mem_))
#define gpMemRealloc(_memp_,_size_,_oldmem_) gpMemRawRealloc(M_GPMEMR_USR,(_memp_),(_size_),(_oldmem_))
#define gpMemAllocCount() gpMemRawAllocCount(M_GPMEMR_USR)

#define gpMemAllocSys(_memp_,_size_) gpMemRawAlloc(M_GPMEMR_SYS,(_memp_),(_size_))
#define gpMemAllozSys(_memp_,_size_) gpMemRawAlloz(M_GPMEMR_SYS,(_memp_),(_size_))
#define gpMemReallocSys(_memp_,_size_,_oldmem_) gpMemRawRealloc(M_GPMEMR_SYS,(_memp_),(_size_),(_oldmem_))
#define gpMemFreeSys(_mem_) gpMemRawFree(M_GPMEMR_SYS,(_mem_))
#define gpMemAllocCountSys() gpMemRawAllocCount(M_GPMEMR_SYS)

enum {
   GPMEMOP_NONE,
   GPMEMOP_VERBOSEON, // use fncLogf for memory info
   GPMEMOP_VERBOSEOFF,
   GPMEMOP_SYSVERBOSEON,
   GPMEMOP_SYSVERBOSEOFF,
   GPMEMOP_FASTMEM, // (uns poolsize)
   GPMEMOP_INFOFMT, // (fnc_ipa fmtf) e.g. int fmtf(chr *fmt,...)
   GPMEMOP_BITMAP, // (uns8 *rgba,int rgbabytesize)
   GPMEMOP_SETCOLOR, // (ptr mem,uns color)
   GPMEMOP_SETFNCLOGF, // (fnc_ipa logf) e.g. int logf(chr *fmt,...)
   GPMEMOP_VALIDATE, // validate
   GPMEMOP_SETFNCERRADD, // (fnc_iii errAdd) int qeErrAdd(int err,int flags)
};

GP_API int gpMemOp(uns op,...);

typedef struct {
   ptr bottom; // lowest managed memory (setup adr)
   ptr low;
   ptr high;
   ptr top; // highest managed memory (first invalid)
} gpMemStackRec;

GP_API int gpMemStackSetup(gpMemStackRec *msr,ptr adr,uns byteSize);
GP_API int gpMemStackReset(gpMemStackRec *msr);
GP_API int gpMemStackLow(gpMemStackRec *msr,ptr memp,uns size);
GP_API int gpMemStackHigh(gpMemStackRec *msr,ptr memp,uns size);
GP_API int gpMemStackSetLow(gpMemStackRec *msr,ptr adr);
GP_API int gpMemStackSetHigh(gpMemStackRec *msr,ptr adr);
GP_API ptr gpMemStackGetLow(gpMemStackRec *msr);
GP_API ptr gpMemStackGetHigh(gpMemStackRec *msr);

///////////////////////////////////////////////////////////////////////////////
// LIBRARY

GP_API int gpthreadInit();
GP_API void gpthreadFinal();

///////////////////////////////////////////////////////////////////////////////

// JFL 25 Feb 07
typedef struct {
   uns lnk[4];
   uns priv[4];
} gpThreadRec;

// gpThreadCreate(&myThreadRec,"fd",myThreadFnc,&myThreadData)
//    function -> int myThreadFnc(ptr data)
//    data -> any pointer data
//    balance creation of threads with gpThreadDestroy()
GP_API int gpThreadCreate(gpThreadRec **thp,chr *sp,...);
GP_API void gpThreadDestroy(gpThreadRec *th);

GP_API int gpThreadSleepMilli(int milli); // sleep

// JFL 25 Feb 07
typedef struct {
   uns priv[8];
} gpThreadLockRec;

// initialize all locks before use, finalize locks before exit

enum {
   GPTHREADLOCKOP_NONE,

   // critical sections
   GPTHREADLOCKOP_CRITSEC_INIT, // critical section init
   GPTHREADLOCKOP_CRITSEC_FINAL, // critical section final
   GPTHREADLOCKOP_CRITSEC_BLOCK, // critical section enter
   GPTHREADLOCKOP_CRITSEC_RELEASE, // critical section leave

   // semaphores
   GPTHREADLOCKOP_SEMAPHORE_INIT, // (uns count,uns max) semaphore init
   GPTHREADLOCKOP_SEMAPHORE_FINAL, // semaphore final
   GPTHREADLOCKOP_SEMAPHORE_WAIT, // semaphore wait forever
   GPTHREADLOCKOP_SEMAPHORE_WAIT_MILLI, // (uns milli) wait milliseconds
   GPTHREADLOCKOP_SEMAPHORE_SIGNAL, // (uns numSigs) send semaphore signals

   // mutex
   GPTHREADLOCKOP_MUTEX_INIT, // mutex init
   GPTHREADLOCKOP_MUTEX_FINAL, // mutex final
   GPTHREADLOCKOP_MUTEX_BLOCK, // mutex block
   GPTHREADLOCKOP_MUTEX_BLOCK_MILLI, // (uns milli) mutex block
   GPTHREADLOCKOP_MUTEX_RELEASE, // mutex release
};
GP_API int gpThreadLockOp(gpThreadLockRec *lock,uns op,...);

// critical sections
#define gpThreadCritSecInit(_lock_) \
   gpThreadLockOp(_lock_,GPTHREADLOCKOP_CRITSEC_INIT)
#define gpThreadCritSecFinal(_lock_) \
   gpThreadLockOp(_lock_,GPTHREADLOCKOP_CRITSEC_FINAL)
#define gpThreadCritSecBlock(_lock_) \
   gpThreadLockOp(_lock_,GPTHREADLOCKOP_CRITSEC_BLOCK)
#define gpThreadCritSecBlockMilli(_lock_,_milli_) \
   gpThreadLockOp(_lock_,GPTHREADLOCKOP_CRITSEC_BLOCK_MILLI,((uns)_milli_))
#define gpThreadCritSecRelease(_lock_) \
   gpThreadLockOp(_lock_,GPTHREADLOCKOP_CRITSEC_RELEASE)

// semaphores
#define gpThreadSemaphoreInit(_lock_,_count_,_max_) \
   gpThreadLockOp(_lock_,GPTHREADLOCKOP_SEMAPHORE_INIT,_count_,_max_)
#define gpThreadSemaphoreFinal(_lock_) \
   gpThreadLockOp(_lock_,GPTHREADLOCKOP_SEMAPHORE_FINAL)
#define gpThreadSemaphoreWait(_lock_) \
   gpThreadLockOp(_lock_,GPTHREADLOCKOP_SEMAPHORE_WAIT)
#define gpThreadSemaphoreWaitMilli(_lock_,_milli_) \
   gpThreadLockOp(_lock_,GPTHREADLOCKOP_SEMAPHORE_WAIT_MILLI,((uns)_milli_))
#define gpThreadSemaphoreSignal(_lock_,_n_) \
   gpThreadLockOp(_lock_,GPTHREADLOCKOP_SEMAPHORE_SIGNAL,_n_)

enum {
   GPTHREADOP_NONE,
   GPTHREADOP_SUSPEND, // suspend thread until resume
   GPTHREADOP_RESUME, // resume suspended thread
   GPTHREADOP_ADDTOINITCOUNT, // (int val)
};

GP_API int gpThreadOp(gpThreadRec *thread,uns op,...);

#ifdef __cplusplus  // C in C++
}                   //
#endif              //

#endif // GPMEM_H
