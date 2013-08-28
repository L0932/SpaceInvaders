// Copyright (C) 2004-2009 Joe Linhoff - All Rights Reserved
// gpuno.h -- public interface to library
#ifndef GPUNO_H
#define GPUNO_H

#ifndef GPTYPES_H
#include "gptypes.h"
#endif // ndef GPTYPES_H

#ifdef __cplusplus  // C in C++ wrapper
extern "C" {        //
#endif              //

///////////////////////////////////////////////////////////////////////////////
// LIBRARY

GP_API int gpunoInit();
GP_API void gpunoFinal();

///////////////////////////////////////////////////////////////////////////////
// UNIFIED NODE OBJECT

//
// Unified Node Object
// base definition
//

// type:0sss MMMM MMMm mmmm
#define M_UNO_MNR 0x1f // mask
#define S_UNO_MNR 0 // shift
#define S_UNO_MJR 5 // shift
#define M_UNO_MJR 0x7f // mask 
#define S_UNO_SIZ 12 // shift
#define M_UNO_SIZ 0x07 // mask
#define M_UNO_MJRMNR ((M_UNO_MJR<<S_UNO_MJR)|M_UNO_MNR)
#define M_UNO_TYPE 0xfff // type

#if M_UNO_MJRMNR != M_UNO_TYPE
#error -- bit mismatch
#endif

#define M_UNOF_ERR 0xffff // error signal

// flags
#define M_UNO           0xffff // flags
#define M_UNO_L2        0x0001 // has an L2 node
#define M_UNO_L3        0x0002 // has an L3 node
#define M_UNO_ISL2      0x0004 // this is an L2 node
#define M_UNO_ISL3      0x0008 // this is an L3 node
#define M_UNO_USR       0x0010 // node is usr
#define M_UNO_NODEL     0x0020 // delete doesn't work
#define M_UNO_UNMANAGED 0x0040 // don't link or use function table
#define M_UNO_TMP       0x0080 // tmp -- use depends on context
#define M_UNO_POPVISIT  0x1000 // visit on push & pop
#define M_UNO_SKIP      0x2000 // don't visit
#define M_UNO_FREE      0x4000 // node is being freed
#define M_UNO_ALLOC     0x8000 // node was allocated
#define M_UNO_DONTVISIT (M_UNO_SKIP|M_UNO_FREE) // don't visit

// from parent to L2/L3
#define UNO_L2(_o_) (((uno*)_o_)-1)
#define UNO_L3(_o_) (((uno*)_o_)-2)

// from L2/L3 to parent
#define UNO_L2P(_o_) (((uno*)_o_)+1)
#define UNO_L3P(_o_) (((uno*)_o_)+2)

// JFL 20 Dec 09; LL uno
typedef struct uno_struct 
{
   // sizeof must match QEOBJ_SIZE=24 in qebase.h
   // must match qeLibUno in dc/dcstd.c!
	struct uno_struct *n; // next
	struct uno_struct *p; // prev
	uns16 t; // type
	uns16 f; // flags
	chr sname[12]; // short name
} uno;

typedef struct {
	uno l[2];
} unoL2;

///////////////////////////////////////////////////////////////////////////////

#define UNO_SET_NAME_SZ(_o_,_n_) \
	szcpy(((uno*)_o_)->name,sizeof(((uno*)_o_)->name),_n_,NUL);

#define UNO_NAME(_o_) ((uno*)_o_)->name

#define UNO_MJR(_o_) (((((uno*)_o_)->t)>>S_UNO_MJR)&M_UNO_MJR)
#define UNO_MNR(_o_) ((((uno*)_o_)->t)&M_UNO_MNR)
#define UNO_MM(_mjr_,_mnr_) (((_mjr_)<<S_UNO_MJR)|(_mnr_))
#define UNO_MJRMNR UNO_MM
#define UNO_MNR_SET(_o_,_n_) ((((uno*)_o_)->t)&=~M_UNO_MNR), \
	((((uno*)_o_)->t)|=(M_UNO_MNR&(_n_)))

#define UNO_ISLINKED(_o_) (((uno*)(_o_))->n!=((uno*)(_o_)))
#define UNO_HASL2(_o_) (((uno*)_o_)->f&M_UNO_L2)
#define UNO_TYPE(_o_) (((uno*)_o_)->t&M_UNO_TYPE)

enum {
	// - add to this list
	// - add entry --> order MUST match unoMjrTable[]
	UNOMJR_NONE, // must match QEOBJTYPE_NONE, --- none --
	UNOMJR_TMP,  // must match QEOBJTYPE_TMP, tmp, unknown, must be 1 for tmp
   UNOMJR_APP_FIRST, // first app, must be 2 (tools embed, lib)

	UNOMJR_APP_MAX=64, // --- max -- last
};

///////////////////////////////////////////////////////////////////////////////

#define M_UNONEW_LINKBEFORE 0x0001
#define M_UNONEW_LINKAFTER  0x0002
#define M_UNONEW_L2         0x0004
#define M_UNONEW_L3         0x0008
#define M_UNONEW_LINKALONG  0x0010
#define M_UNONEW_NOALLOC    0x0020 // mem ptr passed in
#define M_UNONEW_USR        0x0040 // usr obj
#define M_UNONEW_POPVISIT   0x0080 // pop visit
#define M_UNONEW_INDESTRUCT 0x0100 // delete doesn't kill this
#define M_UNONEW_UNMANAGED  0x0200 // don't link or use function tables

#define M_UNOSETLINK_LIST 0x001f // list enum goes here
#define M_UNOSETLINK_L2   0x0100 // use child
#define M_UNOSETLINK_NEXT 0x0200 // use next node

enum {
	UNOFNC_ZAP=1,
	UNOFNC_FREE,
};
#define M_UNOFNC 0xff

#define UNO_SCAN_DEPTH_MAX 16

typedef struct {
	chr *buf;
	uns bufSize;
	uns st[UNO_SCAN_DEPTH_MAX];
} usrDepthNameRec;

#define M_UNOSCANROP_POP      0x0001
#define M_UNOSCANROP_PUSH     0x0002
#define M_UNOSCANROP_WANTSYS  0x0004
#define M_UNOSCANROP_WANTFREE 0x0008
#define M_UNOSCANROP_POPVISIT 0x0010
#define M_UNOSCANROP_VALID    0x1000
typedef struct {
	int depth;
   int curDepth;
	uns op;
	fnc_ipp fncDepth;
	usrDepthNameRec *dat;
} UnoScanRec;

GP_API void gpUnoHead(uno *o);
GP_API void gpUnoLinkToSelf(uno *o);
GP_API void gpUnoLinkAfter(uno *head,uno *o);
GP_API void gpUnoLinkBefore(uno *head,uno *o);
GP_API void gpUnoUnlink(uno *o);
GP_API int gpUnoNew(uno **unop,uns type,uns size,uns flags,chr *name);
GP_API int gpUnoSetLink(uno *o,uns flags);
GP_API void gpUnoDelete(uno *o);
GP_API void gpUnoDeleteList(uno *list);
GP_API void gpUnoZap(uno *o);
GP_API void gpUnoZapList(uno *list);
GP_API void gpUnoZapFreeNodes(uno *list);
GP_API uno *gpUnoScanNext(uno *o,UnoScanRec *usr);
GP_API int gpUnoScanFncPath(uno *o,UnoScanRec *usr);
GP_API int gpUnoSetHandler(uns mjr,chr *name,fnc_ipu fnc,uns flags);

GP_API int gpUnoNumFreeFlagged; // bogus delete counter
GP_API int gpUnoNumFreeZapped; // bogus zap counter

#ifdef __cplusplus  // C in C++ wrapper
}                   //
#endif              //

#endif // GPUNO_H
