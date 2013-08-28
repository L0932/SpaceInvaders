// Copyright (C) 2004-2009 Joe Linhoff - All Rights Reserved
// gperr.h -- public interface to library
#ifndef GPERR_H
#define GPERR_H

#ifndef GPTYPES_H
#include "gptypes.h"
#endif // ndef GPTYPES_H

#ifdef __cplusplus  // C in C++ wrapper
extern "C" {        //
#endif              //

///////////////////////////////////////////////////////////////////////////////
// LIBRARY

GP_API int gperrInit();
GP_API void gperrFinal();

///////////////////////////////////////////////////////////////////////////////
//

enum {
   ///< ERR_ codes

   // - add entry to qeErrStrTable[]

	ERR_MEM_ALLOC=-1099,
   ERR_MEM_FREE,
   ERR_MEM_POOLALLOC,
   ERR_MEM_FINDALLOC,
   ERR_MEM_NOINIT,
   ERR_MEM_INTERNAL1,
   ERR_MEM_FREEINVALID1,
   ERR_MEM_FREEINVALID2,
   ERR_MEM_FREEINVALID3,
   ERR_MEM_FREEINVALID4,

	ERR_FS_OPEN=-1199,
	ERR_FS_READ,
	ERR_FS_WRITE,
	ERR_FS_INVALID,
	ERR_FS_SEEK,
	ERR_FS_NOTFOUND,
	ERR_FS_EOF,

	// general errors
	ERR_SYNTAX=-1299,
	ERR_LOAD,
	ERR_INIT,
	ERR_OVERFLOW,
	ERR_UNDERFLOW,
	ERR_ROOT,
	ERR_LINK,
	ERR_PARAM,
	ERR_SIZE,
	ERR_ABORT,
	ERR_STEP,
	ERR_ONLYIFABORT,
   ERR_ERR_OVERFLOW,

	ERR_APP_NOTHANDLED=-1399,

   ERR_SZ_RES1=-1449, // system-wide define -- joeco.h
	ERR_SZ_RES2,
	ERR_SZ_RES3,
	ERR_SZ_RES4,
	ERR_SZ_RES5,
	ERR_SZ_RES6,
	ERR_SZ_RES7,

   ERR_SND_FORMAT=-1499,
   ERR_SND_FILENOTFOUND,
   ERR_SND_FILESCANNING,
   ERR_SND_SYSTEMBUFFER,
   ERR_SND_NOCHANNELAVAIL,
   ERR_SND_BADPARAMETERS,
   ERR_SND_NOBUFAVAIL,
   ERR_SND_DRIVERSTART,

   ERR_IMG_FILENOTFOUND=-1599,
   ERR_IMG_FORMAT,
   ERR_IMG_FILESCANNING,

   ERR_TEX_NOTLOADED=-1550,
   ERR_TEX_GENTEXTURES, // probably inside glBegin()..glEnd()

   ERR_LIB_FILENOTFOUND=-1699,
   ERR_LIB_FORMAT,
   ERR_LIB_BUFFER,
   ERR_LIB_EMPTY,
   ERR_LIB_NAMENOTFOUND,
   
   ERR_VID_FILENOTFOUND=-1750,
   ERR_VID_FORMAT,

   ERR_OBJ_OPTIONNOTHANDLED=-1799,

   ERR_ANI_JOINTNAMEVISIT=-1850,

   ERR_INP_INTERNALBUF_OVERFLOW=-1899,

   ERR_SHADER_FILENOTFOUND=-1999,

   ERR_GL_UNSUPPORTEDFUNCTION=-2099,
   ERR_GL_NODRIVERSHADERSUPPORT,
   ERR_GL_NODRIVERFBOSUPPORT,
   ERR_GL_ALLOC,
   ERR_GL_BUFFER,

   ERR_NET_CONNECTION=-2199,
   ERR_NET_SEND,

   ERR_COL_PARAMS=-2299,
};

enum {
   QEDEBUGOP_DUMP_ANIMATION_CHANNELS=1, // 0 or 1
};

#define M_QEERRADD_NODUP 0x0001
GP_API int qeErrAdd(int err,uns flags); ///< add error
GP_API int qeErrCount(void); ///< get current error count
GP_API int qeErrNext(void); ///< get next error
GP_API int qeErrNotClean(int err);; ///<
GP_API chr *qeErrString(int err); ///< turn error number into string
GP_API int qeDebugOp(uns op,...); ///< use QEDEBUGOP_

///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus  // C in C++ wrapper
}                   //
#endif              //

#endif // GPERR_H
