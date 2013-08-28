// Copyright (C) 2007-2009 Joe Linhoff, All Rights Reserved
// qesnd.h
#ifndef QESND_H
#define QESND_H

#ifndef GPTYPES_H
#include "gptypes.h"
#endif // ndef GPTYPES_H

#ifdef __cplusplus  // C in C++ wrapper
extern "C" {        //
#endif              //

///////////////////////////////////////////////////////////////////////////////
// LIBRARY

GP_API int gpsndInit();
GP_API void gpsndFinal();
GP_API int gpsndService(void);
GP_API int gpsndOpen();
GP_API void gpsndClose();

///////////////////////////////////////////////////////////////////////////////


enum {
   QESNDOP_NONE,
   QESNDOP_NAME_TIME_OF_WHOLE_SOUND, // chr* name, float *resultp -- in seconds
   QESNDOP_TIME_OF_WHOLE_SOUND, // float *resultp -- in seconds
   QESNDOP_TIME_OF_START, // float *resultp -- qeTimeFrame() of start
   QESNDOP_DEBUG, // int 0=off 1=on
   QESNDOP_GETPAN,
};

#define QESNDPAN_MAXLEFT (-255)
#define QESNDPAN_MAXRIGHT 255

#define QESNDFREQ_MIN 100
#define QESNDFREQ_MAX 100000

// note: play id is returned from qeSndPlay()
// assume that sounds can end, be killed, or replaced by the engine 
// at almost any time -- to address this, all functions that accept play ids
// will only perform the operation if the sound is still playing -- if the
// is no longer playing, the function will return a positive, non-zero result

GP_API int qeSndPlayIdOp(int idPlay,uns op,...); // operations
GP_API int qeSndLoad(chr *name); // load initial sound buffers
GP_API int qeSndUnload(chr *name); // stop sound, unload
GP_API int qeSndDelete(chr *name); // stop sound, free resources
GP_API int qeSndChStop(uns ch); // stop a channel
GP_API int qeSndPlayIdStop(int idPlay); // stop an id (if found)
GP_API int qeSndVol(chr *name,int vol); // vol for next time sound is played
GP_API int qeSndChVol(uns ch,int vol); // adjust vol on playing channel
GP_API int qeSndPlayIdVol(int idPlay,uns vol); // adjust vol of playing sound
GP_API int qeSndChLoops(uns ch); // return the number of loops
GP_API int qeSndPlayIdCh(int idPlay); // find channel sound is on
GP_API int qeSndPlayIdLoops(int idPlay); // number of loops
GP_API uns qeSndPlayingIds(int *idList,int firstChannel,int numChannels);
GP_API int qeSndChPan(uns ch,int pan); // pan playing channel
GP_API int qeSndPlayIdPan(int idPlay,int pan); // pan playing sound
GP_API int qeSndPlayIdGetPan(int idPlay); // get current pan
GP_API int qeSndChFreq(uns ch,int hertz); // playing channel
GP_API int qeSndPlayIdFreq(int idPlay,int hertz); // playing sound
GP_API int qeSndPlayIdGetFreq(int idPlay); // playing sound

///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus  // C in C++ wrapper
}                   //
#endif              //

#endif // QESND_H
