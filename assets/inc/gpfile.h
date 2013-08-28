// Copyright (C) 2004-2009 Joe Linhoff - All Rights Reserved
// gpfile.h -- public interface to library
#ifndef GPFILE_H
#define GPFILE_H

#ifndef GPTYPES_H
#include "gptypes.h"
#endif // ndef GPTYPES_H

#ifdef __cplusplus  // C in C++ wrapper
extern "C" {        //
#endif              //

///////////////////////////////////////////////////////////////////////////////
// LIBRARY

GP_API int gpfileInit();
GP_API void gpfileFinal();

///////////////////////////////////////////////////////////////////////////////

#define M_GPFILEREC_OPEN        0x0001
#define M_GPFILEREC_WRITE       0x0002
#define M_GPFILEREC_ENDIAN_SWAP 0x1000
#define M_GPFILEREC_MEMFILE     0x2000
#define M_GPFILEREC_ERROR       0x8000
typedef struct {
   uns flags;
   ptr fh;
   uns priv[4];
} gpFileRec;

#define M_GPFILEOPEN_WRITE 0x0010

GP_API int gpFilePathFind(chr *fpath,chr *bigBuf,uns bigBufSize);
GP_API int gpFilePathSize(chr *path);
GP_API int gpFileLogOutput(chr *buf,uns len);
GP_API int gpFileLogCheckToDelete(uns toobig);
GP_API int gpFileOpen(gpFileRec *fr,chr *fpath,uns flags);
GP_API void gpFileClose(gpFileRec *fr);
GP_API int gpFileSize(gpFileRec *fr);
GP_API int gpFileRead(gpFileRec *fr,ptr buf,uns size);
GP_API int gpFileWrite(gpFileRec *fr,ptr buf,uns size);
GP_API int gpFileSeek(gpFileRec *fr,uns off);
GP_API int gpFileSkip(gpFileRec *fr,int off);
GP_API int gpFileTell(gpFileRec *fr,uns *offp);
GP_API uns32 gpFileR32U(gpFileRec *fr);
GP_API uns16 gpFileR16U(gpFileRec *fr);
GP_API int gpFileDelete(chr *fpath);
GP_API int gpFileSetCurDir(chr *path);
GP_API int gpFileGetCurDir(chr *buf,uns bufSize);
GP_API int gpFileOpenCount();

// read-only mem-based file
GP_API int gpFileOpenMemFile(gpFileRec *fr,uns8 *buf,uns bufSize,uns flags);

///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus  // C in C++ wrapper
}                   //
#endif              //

#endif // GPFILE_H
