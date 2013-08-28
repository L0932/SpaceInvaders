// Copyright (C) 2007-2009 Joe Linhoff, All Rights Reserved
// qec.h -- the C++ API to the engine
#ifndef QEC_H
#define QEC_H

#ifndef QE_H
#include "qe.h"
#endif // QE_H

/// Engine 'super-object'.  Provides engine-consistent new & delete.
/// Must inherit publicly so the new & delete are usable.  All new operations
/// zero allocated memory.
class GP_API qe {
public:
   void* operator new(size_t size); ///< alloc & zero memory for object
   void* operator new(size_t size,void *adr); ///< placement new (see note)
   void* operator new[](size_t size); ///< alloc & zero memory
   void operator delete(void *p); ///< free memory for object
   void operator delete[](void *p); ///< free memory
}; // class qe

/// \file
/// Note: The placement new operator doesn't allocate memory, you supply the 
/// address of the valid memory to use for that object.  The memory is not 
/// zerod.  Do not delete these objects. These objects are useful when you 
/// have a block of memory you would like to use or reuse for an object or 
/// for memory mapped IO.  The constructor will be called.

enum {
   QEUPDATEBASE_OP_REMOVE=1, ///< for qeUpdateBase::objOp()
};

/// Special base class, engine calls control(), update(), draw() functions
/// every loop.  final() is called when engine removes object.
/// Do not delete objects derived from this class -- use objRemove()
// JFL 24 Nov 07
// JFL 15 Jan 08
class GP_API qeUpdateBase : public qe {
public:
   ptr _oShared; ///< the engine object
private:
   virtual int control(void) {return -1;} ///< called during shared control
   virtual int update(void) {return -1;} ///< called during shared update
   virtual int draw(void) {return -1;} ///< called during shared draw
   virtual void final(void) {delete this;} ///< called by eng on destruction
protected:
   int objRemove(void); ///< call from control() update() or draw() to free
public:
   qeUpdateBase(chr *name,int8 sort,int appId); ///< sort=bigearly, appId!=0
   int objOp(uns op,...); ///< additional operations, use QEUPDATEBASE_OP_
}; // class qeUpdateBase

/// Doubly linked list  base class.
/// Inherit or embed this class.
// JFL 21 Nov 07
class GP_API qeListBase : public qe {
public:
   qeListBase *nodeNext; ///< link forward
   qeListBase *nodePrev; ///< link backward
   int nodeType; ///< type, zero reserved for list head

   // doesn't use virtual functions to keep structure small
   // doesn't use a constructor to avoid calls for every use

   void linkMakeHead(); ///< setup node as list head
   static void linkMakeHead(qeListBase *h); ///< setup node as list head
   void linkMakeNode(int type); ///< setup as simple node
   void linkBefore(qeListBase *h); ///< link node before h
   void linkAfter(qeListBase *h); ///< link node after h
   void linkUnlink(void); ///< unlink from list

   qeListBase* headFirstUnlink(); ///< unlink and return the first node
   qeListBase* headFirstType(int type); ///< get first node of type
   void headAddLast(qeListBase *n); ///< link n at end of list
   void headAddFirst(qeListBase *n); ///< link n at start of list
   void headAppend(qeListBase *n); // defunct, use add last
   void headPrepend(qeListBase *n); // defunct, use add first
}; // class qeListBase

#endif // ndef QEC_H
