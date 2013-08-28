// Copyright (C) 2007-2009 Joe Linhoff, All Rights Reserved
// qevid.h
#ifndef QEVID_H
#define QEVID_H

#ifndef GPTYPES_H
#include "gptypes.h"
#endif // ndef GPTYPES_H

#ifdef __cplusplus  // C in C++ wrapper
extern "C" {        //
#endif              //

///////////////////////////////////////////////////////////////////////////////
// LIBRARY

GP_API int gpvidInit();
GP_API void gpvidFinal();
GP_API int gpvidService();

///////////////////////////////////////////////////////////////////////////////

#define M_QEVIDNEW_DONTRECORDNOTFOUND 0x0002 ///< ignore error if not found
#define M_QEVIDNEW_REPLACE            0x0004 ///< OK to replace

GP_API int qeVidNew(chr *name,uns flags, chr *path); ///< register video
GP_API int qeVidOpen(chr *name); ///< return vidid, neg on err
GP_API int qeVidPlay(int vidid); ///< start video
GP_API int qeVidCheckIfDone(int vidid); /// non-zero if done, neg on err
GP_API int qeVidCloseAll(); ///< stop & close all videos

#define M_QEVIDFLAGS_PLAYING 0x01 ///< playing
#define M_QEVIDFLAGS_DONE    0x02 ///< done

enum {
   QEVIDOP_NONE,
   QEVIDOP_DRAW,
   QEVIDOP_GETVIDFLAGS, // int vidid
   QEVIDOP_DONTCOINIT, // dont CoInitialize() or CoUninitialize()
};

GP_API int qeVidOp(uns op,...); // operations

///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus  // C in C++ wrapper
}                   //
#endif              //

#endif // QEVID_H
