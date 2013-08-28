// Copyright (C) 2004-2009 Joe Linhoff - All Rights Reserved
// qeeng.h -- public interface to library
#ifndef QEENG_H
#define QEENG_H

// notes:
// - functions that use multiple libraries

#ifndef GPTYPES_H
#include "gptypes.h"
#endif // ndef GPTYPES_H

#ifdef __cplusplus  // C in C++ wrapper
extern "C" {        //
#endif              //

///////////////////////////////////////////////////////////////////////////////
// LIBRARY

GP_API int gpengInit();
GP_API void gpengFinal();

///////////////////////////////////////////////////////////////////////////////

#define QE_H_VERS 0x00000070 ///< version of the API

/// open & close the platform
GP_API int qeInit(void);
GP_API void qeFinal(void);
GP_API int qeOpen(void); ///< open engine
GP_API void qeClose(void); ///< close engine
GP_API int qeObjAddInitial(uns op); ///< setup engine object list
extern int qeMain(int argc,chr *argv[]); ///< user's main (extern)

/// two ways to run the engine
GP_API int qeForever(void); ///< does not return until closed
GP_API int qeOneLoop(chr *sp,...); ///< executes one engine loop & returns
GP_API int qeSleep(float time); ///< sleep in seconds

/// engine setup and control
GP_API int qeAbort(int code); ///< signal engine to abort
GP_API int qePauseOnExit(void); ///< pause for key on exit
GP_API int qeWindowTitle(chr *name); ///< window title
GP_API int qeWindowSize(int width,int height); ///< window size (0,0=scr size)
GP_API int qeFullscreen(int op,...); ///< 1=full 0=window 2=flip
GP_API int qeGetWindowSize(float *w,float *h); ///< get cur window size
GP_API int qeUpdateWindowSize(float w,float h); ///< system update, resized
GP_API chr *qeVersion(void); ///< get version string
GP_API int qeSwapBuffers(void); ///< swap screen buffers
GP_API int qeConsRGB(float r,float g,float b); ///< set color for console
GP_API int qeConsClear(void); ///< clear console

/// font
GP_API int qeFontPrintf(chr *fmt,...); ///< printf w/font system
GP_API int qeFontHeight(void); ///< get font height in pixels
GP_API int qeFontStringWidth(chr *str,chr *strx); ///< string width in pixels
GP_API void qeFontPos(float x,float y); ///< set font position
GP_API void qeFontRGB(float r,float g,float b); ///< set font color

/// output
GP_API int qePrintf(chr *fmt,...); ///< print a message
GP_API int qeLogf(chr *fmt,...); ///< log a message

/// check for errors, unfreed resources, more..
GP_API int qefnCheckForCleanExit(void);

///////////////////////////////////////////////////////////////////////////////

#define M_QESYSSTEP_STEP 0x0001
#define M_QESYSSTEP_HOLD 0x0002

#define M_QESYSDRAW_WIRE    0x0001
#define M_QESYSDRAW_JOINTS  0x0002
#define M_QESYSDRAW_NORMALS 0x0004

#define M_QESYSDEBUG_DUMP_ANIMATION_CHANNELS 0x0001

enum {
   QEENGOP_GETFLAGS_SYSSTEP=1,
   QEENGOP_SETFLAGS_SYSSTEP, // (uns flags)
   QEENGOP_GETFLAGS_SYSDRAW,
   QEENGOP_GETFLAGS_SYSDEBUG,
   QEENGOP_SETLOGOUTPUTFNC, // (fnc_ipu fnc) int fnc(chr *buf,uns len), 0=none
   QEENGOP_RESETLOGOUTPUTFNC, // reset to normal
   QEENGOP_SETINTERNALSLEEPMILLI, // (uns millisec) set min internal sleep
   QEENGOP_SETINTERNALTGTLOOPMILLI, // (uns millisec) set target loop time
};

GP_API int qeEngOp(uns op,...);

//
// KEYFRAMES
//

#define M_QEKEYFRAME_TX  0x1 
#define M_QEKEYFRAME_TY  0x2 
#define M_QEKEYFRAME_TZ  0x4 
#define M_QEKEYFRAME_RX  0x10 
#define M_QEKEYFRAME_RY  0x20 
#define M_QEKEYFRAME_RZ  0x40 
#define M_QEKEYFRAME_SX  0x100 
#define M_QEKEYFRAME_SY  0x200 
#define M_QEKEYFRAME_SZ  0x400
#define M_QEKEYFRAME_VIS 0x1000 

#define M_QEKEYANI_LOOP      0x01
#define M_QEKEYANI_DONTLOOP  0x02
#define M_QEKEYANI_FIRSTLAST 0x04

typedef struct {
   float t;
   int flags;
} qeKeyFrameTimeRec;

typedef struct {
   float time;
   bit vis;
   float tx;
   float ty;
   float tz;
   float rx;
   float ry;
   float rz;
   float sx;
   float sy;
   float sz;
} qeKeyFrameKey;

typedef struct {
   int numKeys; // number of keyframes
   int aniFlags; // M_QEKEYANI_
   int keyFrameFlags; // M_QEKEYFRAME_
} qeKeyFrameAni;

GP_API int qeKeyFrameCatmullRom(qeKeyFrameKey *dst,float t,
   qeKeyFrameAni *keyframeani,qeKeyFrameTimeRec *timeflags,float *values);

///////////////////////////////////////////////////////////////////////////////

//
// TIMERS
//

/// high speed timer record
typedef struct {
   uns64 priv[1];
} qeTimerRec;

/// high speed timer enums
enum {
   QETIMEROP_NONE,
   QETIMEROP_START,
   QETIMEROP_STOP,
   QETIMEROP_TICKS,
   QETIMEROP_TICK_RESTART,
   QETIMEROP_TICKSPERSECOND,
   QETIMEROP_TICKSPERMILLISECOND,
};

GP_API void qeTimeReset(void); ///< reset game timer
GP_API int qeTimeFakeFrameRate(float sec); ///< force time per frame, 0 to run
GP_API float qeTimeFrame(void); ///< total game time in seconds
GP_API float qeTimeDelta(void); ///< delta time for the frame
GP_API float qeTimeSinceReset(void); ///< use qeTimeFrame -- this free runs
GP_API void qeLoopReset(void); ///< reset loop count
GP_API uns qeLoopFrame(void); ///< loop count since reset
GP_API int qeTimeMul(float mul); ///< 0 for normal
GP_API int64 qeTimerOp(qeTimerRec *timerec,uns op,...); ///< high speed timer operations

//
// SOUND
//

// sound defines & masks for qeSndNew()
#define M_SNDNEW_LOOPING    0x00100000 ///< loop the sound
#define M_SNDNEW_STREAM     0x00200000 ///< stream from file
#define M_SNDNEW_DONTSTREAM 0x00400000 ///< don't stream (load into RAM)
#define M_SNDNEW_PREDEFINED 0x00800000 ///< special named sound
#define M_SNDNEW_DONTRECORDNOTFOUND 0x01000000 ///< don't record this error
#define M_SNDNEW_LOAD       0x02000000 ///< pre-load
#define M_SNDNEW_PRI        0x0000000f ///< priority bits
#define S_SNDNEW_PRI        0          ///< priority shift (priority 0..15)
#define M_SNDNEW_CHMASK     0x00000ff0 ///< channel bits
#define S_SNDNEW_CHMASK     4          ///< channel shift (channel mask 0x00..0xff)

// expanded bit fields
#define M_SNDNEW_CH_1       0x00000010  ///< channel 1
#define M_SNDNEW_CH_2       0x00000020  ///< channel 2
#define M_SNDNEW_CH_3       0x00000040  ///< channel 3
#define M_SNDNEW_CH_4       0x00000080  ///< channel 4
#define M_SNDNEW_CH_5       0x00000100  ///< channel 5
#define M_SNDNEW_CH_6       0x00000200  ///< channel 6
#define M_SNDNEW_CH_7       0x00000400  ///< channel 7
#define M_SNDNEW_CH_8       0x00000800  ///< channel 8
#define M_SNDNEW_PRI_0      0x00000000  ///< lowest priority (no priority)
#define M_SNDNEW_PRI_1      0x00000001  ///< priority
#define M_SNDNEW_PRI_2      0x00000002  ///< priority
#define M_SNDNEW_PRI_3      0x00000003  ///< priority
#define M_SNDNEW_PRI_4      0x00000004  ///< priority
#define M_SNDNEW_PRI_5      0x00000005  ///< priority
#define M_SNDNEW_PRI_6      0x00000006  ///< priority
#define M_SNDNEW_PRI_7      0x00000007  ///< priority
#define M_SNDNEW_PRI_8      0x00000008  ///< priority
#define M_SNDNEW_PRI_9      0x00000009  ///< priority
#define M_SNDNEW_PRI_10     0x0000000a  ///< priority
#define M_SNDNEW_PRI_11     0x0000000b  ///< priority
#define M_SNDNEW_PRI_12     0x0000000c  ///< priority
#define M_SNDNEW_PRI_13     0x0000000d  ///< priority
#define M_SNDNEW_PRI_14     0x0000000e  ///< priority
#define M_SNDNEW_PRI_15     0x0000000f  ///< highest

#define QESNDVOL_MAX 255  ///< loudest sound, volume 0 is silent

GP_API int qeSndNew(chr *name,uns flags,uns tProtect,chr *path); ///< register
GP_API int qeSndPlay(chr *name); ///< returns play id on success
GP_API int qeSndStopAll(void); ///< stop all sounds
GP_API int qeSndMasterVol(int vol); ///< set master volume for all sounds

///////////////////////////////////////////////////////////////////////////////

GP_API int qeSysStep(int mode); ///< step-mode for the engine
GP_API int qeSysRun(void); ///< run-mode
GP_API int qeSysWipeout(void); ///< wipeout all user data

///////////////////////////////////////////////////////////////////////////////

//
// OPTIONS
//

// options for qeOption*()
#define M_QEOPTION_CLEARSCREEN  0x0000001 ///< clear screen every loop
#define M_QEOPTION_AUTOCAM      0x0000002 ///< add first (arcball) camera
#define M_QEOPTION_FULLFLIP     0x0000004 ///< full page flip & clear
#define M_QEOPTION_DRAWCONSOLE  0x0000100 ///< draw console
#define M_QEOPTION_INITGL       0x0000200 ///< init OpenGL
#define M_QEOPTION_DRAWMODE     0x0000400 ///< black on white
#define M_QEOPTION_FIRSTLIGHT   0x0000800 ///< add first light
#define M_QEOPTION_LOGPRINTF    0x0002000 ///< qePrintf() output also to log
#define M_QEOPTION_CHECKLOGSIZE 0x0004000 ///< check & delete log if too big
#define M_QEOPTION_INERNALSLEEP 0x0008000 ///< sleep inside the engine loop
#define M_QEOPTION_CLEARSTENCIL 0x0010000 ///< clear stencil buffer every loop
#define M_QEOPTION_PAGEFLIP     0x0020000 ///< flip pages
#define M_QEOPTION_SOUNDSYS     0x0040000 ///< sound system
#define M_QEOPTION_ESCABORT     0x0080000 ///< escape aborts
#define M_QEOPTION_RESIZEOK     0x0100000 ///< allow window resizing
#define M_QEOPTION_FKEYCOMMANDS 0x0200000 ///< no function key extras
#define M_QEOPTION_EVENTS       0x0400000 ///< drain messages and events
#define M_QEOPTION_WINDOW       0x0800000 ///< engine manages window

// option control
GP_API int qeOptionTurnOff(uns flags); ///< turn options off
GP_API int qeOptionTurnOn(uns flags); ///< turn options on
GP_API uns qeOptionCurrent(void); ///< get current options

// Engine flags
#define M_QEFLAG_WIREFRAME    0x0001 ///< draw wireframe mode
#define M_QEFLAG_JOINTS       0x0002 ///< draw joint mode
#define M_QEFLAG_NORMALS      0x0004 ///< draw normal mode
#define M_QEFLAG_STEP         0x0008 ///< stepping
#define M_QEFLAG_APPFOCUS     0x0010 ///< window is in focus
#define M_QEFLAG_APPACTIVE    0x0020 ///< app is active (not minimized)
#define M_QEFLAG_FULLSCREEN   0x0040 ///< running in fullscreen mode
GP_API uns qeGetFlags(void); ///< get engine flags
GP_API int qeSetFlags(uns changeThese,uns flags); ///< set (some) eng flags

enum { // qeAbort() codes
   QEABORT_USERQUIT=1,
}; // qeAbort() codes

///////////////////////////////////////////////////////////////////////////////

#define M_QE_ARCBALL_VALID       0x0001
#define M_QE_ARCBALL_AB_SETUP    0x0002
#define M_QE_ARCBALL_CAM_SETUP   0x0004
#define M_QE_ARCBALL_INP         0x0008
#define M_QE_ARCBALL_INP_LBUTTON 0x0010
#define M_QE_ARCBALL_INP_RBUTTON 0x0020
#define M_QE_ARCBALL_INP_ALT     0x0040
#define M_QE_ARCBALL_NOWHEEL     0x0080
#define M_QE_ARCBALL_RESETVALID  0x0100
#define M_QE_ARCBALL_DRAGGING    0x1000
typedef struct {
   uns flags; // flags
   uns wSetup; // width as setup
   uns hSetup; // height as setup
   float inpXY[2]; // input
   int   inpWheel; // input
   float inpPrevXY[2]; // input
   float aWidth; // inv-adj width
   float aHeight; // inv-adj height
   float aWDivH;
   float start[3];
   float end[3];
   float m9base[9];
   float m9cur[9];
   float resetDist; // reset dist
   float resetM9[9]; // reset cur m9
   float resetLookAt[3]; // camera look at
   float camFOV; // camera field of view
   float camNearClip; // camera near clip
   float camFarClip; // camera far clip
   float camDist; // camera distance
   float camLookAt[3]; // camera look at
   float xfmCamPos[3]; // transformed camera pos
   float xfmCamUp[3]; // transformed camera up
} qefnArcBallRec;

GP_API int qefnCamArcBall(qefnArcBallRec *ab); ///< persp: arcball

GP_API int qefnCamArcBallSetCam(qefnArcBallRec *ab,float fovRad,
   float clipNear,float clipFar,
   float *xyzLookAt,float *xyzPos,float *m9);

///////////////////////////////////////////////////////////////////////////////

enum {
   QENAMEID_NONE,
   QENAMEID_CAMAUTO,
   QENAMEID_CLEARSCREEN,
   QENAMEID_DRAWCONS,
   QENAMEID_DRAWMODE,
   QENAMEID_FIRSTLIGHT,
   QENAMEID_MARK_SHARED,
   QENAMEID_MARK_CONTROL,
   QENAMEID_MARK_UPDATE,
   QENAMEID_MARK_DRAW,
};

GP_API chr *qeNameGet(uns qenameid);

///////////////////////////////////////////////////////////////////////////////

// PLATFORM OPERATIONS
// be careful when using these, they will likely make your application non-portable
enum {
   QEPLATFORMOP_NONE,
   QEPLATFORMOP_GETHWND, // (HWND *pHwnd)
   QEPLATFORMOP_GETHDC, // (HDC *pHDC)
   QEPLATFORMOP_GETHGLRC, // (HGLRC *pHGLRC)
   QEPLATFORMOP_WINPAINT_CALLBACK, // (chr *sp,callback,this)
   QEPLATFORMOP_WINDISPLAYCHANGE_CALLBACK, // (chr *sp,callback,this)
   QEPLATFORMOP_WINRESIZE_CALLBACK, // (chr *sp,callback,this)
   QEPLATFORMOP_GETDISPLAY_SIZE, // (int *dstWidth,int *dstHeight)
   QEPLATFORMOP_ENUMDISPLAY_SIZES, // (int *dstWidth,int *dstHeight,int num)
   QEPLATFORMOP_LICENSE, // chr *string
};

GP_API int qePlatformOp(int op,...);

///////////////////////////////////////////////////////////////////////////////

//
// OBJECTS
//

typedef uns qeObj; // qeObj

enum {
	QESYSFNCOP_NONE,
	QESYSFNCOP_INIT,
	QESYSFNCOP_FINAL,
};
#define M_QESYSFNCOP 0xff

/// engine objects
GP_API qeObj* qeObjAddFnc(fnc_iv fnc); ///< add C function obj
GP_API qeObj* qeObjAddFncSP(ptr adr,chr *sp,...); ///< add C func w/sp
GP_API qeObj* qeObjAddCFnc(ptr classptr,...); ///< add C++ function obj
GP_API qeObj* qeObjAddCFncSP(ptr classptr,...); ///< add C++ func obj w/sp
GP_API qeObj* qeObjAddCpr(fnc_ii fnc); ///< add co-process routine obj
GP_API qeObj* qeObjAddCprSP(ptr fnc,chr *sp,...); ///< add cpr obj w/sp
GP_API qeObj* qeObjAddInst(ptr adr,uns type); ///< add instance
GP_API qeObj* qeObjAddInstSP(ptr adr,uns type,chr *sp,...); ///< add inst w/sp
GP_API qeObj* qeObjAddSharedSP(uns recsize,chr *sp,...); ///< add shared w/sp
GP_API qeObj* qeObjAddCSharedSP(ptr classptr,chr *sp,...); ///< add C++ shared w/sp

///////////////////////////////////////////////////////////////////////////////

//
// LIB
//

// qeObjScan
// scanning record
typedef struct {
   qeObj *o;
   uns32 priv[32];
   chr *buf;
   uns bufSize;
} qeObjScan;

#define qeLibScanRec qeObjScan

/// library chunk
typedef struct {
   chr *name;
   uns32 type;
   ptr data;
   qeObj* libObj;
} qeLibChunk;

#define M_QELIBNEW_LOAD        0x0001
#define M_QELIBNEW_START       0x0002
#define M_QELIBNEW_STARTIMAGES 0x0004
#define qeLibNew(_name_,_flags_,_path_) qeLibNewSP(_name_,_flags_,"p",_path_)
GP_API int qeLibNewSP(chr *name,uns flags,chr *sp,...); ///< register new lib
GP_API int qeLibDelete(chr *name); ///< delete the lib
GP_API int qeLibLoad(chr *name); ///< load the lib
GP_API int qeLibUnload(chr *name); ///< unload the lib from memory
#define qeLibStart(_name_) qeLibStartSP(_name_,NUL)
GP_API int qeLibStartSP(chr *name,chr *sp,...); ///< start all instances in lib
#define qeLibScanFirst(_sr_) MEMZ(*(_sr_)) ///< init for scan
GP_API int qeLibScanNext(qeObjScan *sr,qeLibChunk *lib,chr *name,chr *namex); ///< find next
GP_API chr *qeLibScanLibName(qeObj *o); ///< get the scan name
GP_API int qeLibFind(qeLibChunk *dst,chr *name,chr *namex,uns32 type); ///< chk
GP_API ptr qeLibDataFind(chr *name,chr *namex); ///< find user data
GP_API qeObj *qeLibObjFind(chr *name,chr *namex); ///< find lib object
GP_API int qeLibFindPathless(qeLibChunk *dst,chr *name,chr *namex,uns32 type); ///< find w/o path
GP_API int qeLibFindSibling(qeLibChunk *dst,
   qeObj *o,chr *name,chr *namex,uns32 type); ///< find chunk, search siblings
GP_API int qeLibNextSibling(qeLibChunk *libck,
   chr *name,chr *namex,uns32 type); ///< next chunk
GP_API qeObj *qeLibFirst(void); ///< get first system lib obj
GP_API qeObj *qeLibListHead(void);
GP_API qeObj *qeLibLoaded(chr *name); ///< get loaded lib

GP_API int qeObjModelCreateSP(qeObj **dstObjp,chr *libName,chr *sp,...); ///< create obj inst from lib

GP_API int qeInstStartSP(ptr adr,uns type,chr *sp,...);

///////////////////////////////////////////////////////////////////////////////

enum {
   QEOBJTYPE_NONE,
   QEOBJTYPE_TMP,
   QEOBJTYPE_LIB,
   QEOBJTYPE_INST,
   QEOBJTYPE_SHR,
}; // QEOBJTYPE_

typedef struct {
   uns32 typeC4; // type
   chr *name; // name
   uns16 nameSize; // size of name buffer
   uns16 flags; // flags
   ptr p; // lib/def data
} qeObjInst;

typedef struct {
   chr *name; // name
   uns16 nameSize; // size of name buffer
   uns16 flags; // flags
   ptr p; // lib/def data
} qeObjLib;

#define M_QEOBJ_HASCHILD 0x0001 // has a child
#define M_QEOBJ_SKIP     0x2000 // don't visit

#define QEOBJ_NAMESIZE 11 // does not include terminator

GP_API uns qeObjType(qeObj *o); // get type
GP_API uns qeObjFlags(qeObj *o); // get flags
GP_API chr* qeObjName(qeObj *o); // get name

GP_API int qeObjNew(qeObj **op,uns type,uns size,uns flags,chr *name);
GP_API void qeObjZap(qeObj *o); // immediately free all resources
GP_API void qeObjDelete(qeObj *o); // free all resources
GP_API qeObj* qeObjEngineCur(uns op); // get current engine object

GP_API int qeObjRename(qeObj *o,chr *name,chr *namex);
GP_API qeObj *qeObjFindName(chr *name,chr *namex);
#define M_QEOBJSETLINK_BEFORE 0x01
#define M_QEOBJSETLINK_AFTER  0x02
GP_API void qeObjSetLink(qeObj *o,uns op);
GP_API qeObj *qeObjScanNext(qeObjScan *scn,
   chr *nameBuf,uns nameBufSize,int *depthp);
GP_API qeObj *qeObjScanN(qeObjScan *scn);
GP_API qeObj *qeObjFirst(void);
GP_API qeObj *qeObjSharedFirst(void);
GP_API qeObj *qeObjListHead(void);
GP_API qeObj* qeObjFindPath(ptr scanrec,qeObj *o,chr *path,chr *pathx);

GP_API void qeObjHead(qeObj *o);
GP_API void qeObjLinkAfter(qeObj *h,qeObj *o);
GP_API void qeObjLinkBefore(qeObj *h,qeObj *o);
GP_API void qeObjUnlink(qeObj *o);

GP_API qeObj* qeObjNext(qeObj *o); // next
GP_API qeObj* qeObjPrev(qeObj *o); // prev
GP_API qeObj *qeObjNextLoop(qeObj *o); // next, loop
GP_API qeObj *qeObjPrevLoop(qeObj *o); // prev, loop
GP_API qeObj* qeObjChild(qeObj *o); // child
GP_API qeObj* qeObjParent(qeObj *o); // parent

GP_API ptr qeObjExt(qeObj *o); // get ext or inst data area (type dependent)
GP_API ptr qeObjNode(qeObj *o); // get node (normally, use qeObjExt())
GP_API qeObj *qeInstObj(ptr inst);

enum {
   QEOBJSHAREDOP_SET_I=1, // int i, return previous
   QEOBJSHAREDOP_GET_I, // return current
   QEOBJSHAREDOP_GET_THIS, // ptr *thisp
};
GP_API int qeObjSharedOp(qeObj *o,uns op,...);

///////////////////////////////////////////////////////////////////////////////

enum {
	QECPROP_RUN, // op: run
	QECPROP_INIT, // op: init
	QECPROP_FINAL // op: final
};
#define M_QECPROP 0xff

GP_API int qeCprSleep(float t); // sleep, seconds
GP_API int qeCprSloop(int t); // sleep, loops

///////////////////////////////////////////////////////////////////////////////

typedef struct {
   qeObj *o;
   uns32 pad;
   uns64 ticks;
} qeObjProfileRec;

GP_API int qeObjProfileSetTable(qeObjProfileRec *dstRecs,int *dstNump,int max);

#define M_CPUINFO_FEATURE1_MMX   (1<<23)
#define M_CPUINFO_FEATURE1_SSE   (1<<25)
#define M_CPUINFO_FEATURE1_SSE2  (1<<26)

#define M_CPUINFO_FEATURE2_SSE2  (1<<0)
#define M_CPUINFO_FEATURE2_SSSE3 (1<<9)
#define M_CPUINFO_FEATURE2_SSSE41 (1<<19)
#define M_CPUINFO_FEATURE2_SSSE42 (1<<20)

typedef struct {
   // structure layout assumed by qeCPUInfo()
   uns flags;
   chr vendor[20];
   uns signature;
   uns feature1;
   uns feature2;
   uns feature3;
   uns exhighest;
   uns exinfo1;
   uns exinfo2;
} qeCPUInfoRec;

GP_API int qeCPUInfo(qeCPUInfoRec *dst);

///////////////////////////////////////////////////////////////////////////////

//
// IMAGES
//

#define M_QEIMGNEW_LOAD               0x0001 ///< load into memory
#define M_QEIMGNEW_DONTRECORDNOTFOUND 0x0002 ///< ignore error if not found
#define M_QEIMGNEW_REPLACE            0x0004 ///< OK to replace
#define M_QEIMGNEW_SCLAMP             0x0008 ///< else repeat
#define M_QEIMGNEW_TCLAMP             0x0010 ///< else repeat
#define M_QEIMGNEW_MAGNEAREST         0x0020 ///< else linear
#define M_QEIMGNEW_MINNEAREST         0x0040 ///< else linear
#define M_QEIMGNEW_NOMIPMAPS          0x0100 ///< do not generate MIP maps
#define M_QEIMGNEW_BIND               0x0200 ///< bind
GP_API int qeImgNew(chr *imgName,uns flags,chr *path); ///< register image
GP_API int qeImgNewRGBA(chr *imgName,uns width,uns height,uns8 *rgba); ///< data
// sp: p (uns8 *rgba) points to rgba array
//     b (uns bytesPerPix) 3 or 4 usually
//     w (uns width,uns height) width & height of image in pixels
//     f (uns glfmt) OpenGL format, ex: GL_RGB, norm defaults w/bytesPerPix
//     R replace current image (swap)
//     P (float priority) set texture priority 0..1
GP_API int qeImgNewSP(chr *name,chr *sp,...); ///< register image
GP_API int qeImgLoad(chr *imgName); ///< load image from file into main memory
GP_API int qeImgUnload(chr *imgName); ///< unload image from main memory
GP_API int qeImgDelete(chr *imgName); ///< delete image
#define M_QEIMGINFO_FMT_GLFMT 0x00ffff ///< OpenGL bits
#define M_QEIMGINFO_FMT_ALPHA 0x010000 ///< has alpha
GP_API int qeImgInfo(chr *imgName,uns *widthp,uns *heightp,uns *fmt,void *pixp);
GP_API int qeImgPixGet(uns8 *rgba,chr *name,int x,int y); ///< get pixel from image
GP_API int qeImgRename(chr *name,chr *newname); ///< rename image
enum {
   QEIMGOP_NONE,
   QEIMGOP_INDESTRUCTIBLESET, // set indestructible flag (won't auto delete)
   QEIMGOP_INDESTRUCTIBLECLR, // clear indestrictible flag
   QEIMGOP_FILLWHOLE_RGBA, // (float r,float g,float b,float a) fill whole image
   QEIMGOP_DUMPNAMES, // dump all image names
   QEIMGOP_COUNT, // count images
};
GP_API int qeImgOp(chr *name,uns op,...); ///< use QEIMGOP_

//
// TEXTURES
//

/// flags for texture operations
#define M_QETEX_S_CLAMP     0x0001
#define M_QETEX_T_CLAMP     0x0002
#define M_QETEX_MAG_NEAREST 0x0004
#define M_QETEX_MIN_NEAREST 0x0008
#define M_QETEX_NOMIPMAPS   0x0010

enum {
   QETEXOP_NONE,
   QETEXOP_SETFLAGS, ///< M_QETEX_
   QETEXOP_GETFLAGS, ///< M_QETEX_
   QETEXOP_GETBIND, ///< get texture object number
};

GP_API int qeTexOp(chr *imgName,uns op,...); ///< use QETEXOP_
GP_API int qeTexLoad(chr *imgName); ///< load texture
GP_API int qeTexUnload(chr *imgName); ///< unload texture
#define M_QETEXBIND_ALPHA 0x0001 ///< qeTexBind() return bit if alpha
GP_API int qeTexBind(chr *imgName); ///< bind texture, 0 to unbind

///////////////////////////////////////////////////////////////////////////////

GP_API int qefnConsDraw(void); ///< draw console

///////////////////////////////////////////////////////////////////////////////

//
// RANDOM
//

#define QERAND_MAX 32767 ///< maximum random number from qeRand()
GP_API uns qeRand(void); ///< get random 0..QERAND_MAX
GP_API float qeRand01(void); ///< get random 0..1
GP_API float qeRandMinMaxf(float min,float max); ///< get random min..max
GP_API int qeRandMinMaxi(int min,int max); ///< get random min..max
GP_API uns qeRandSeed(uns seed); ///< set random seed

///////////////////////////////////////////////////////////////////////////////

enum {
   QE_PTRID_NONE, /// reserved
   QE_PTRID_BOXONGND_GEO1, ///< box on the ground
   QE_PTRID_PYRAMID_GEO1, ///< pyramid on the ground
   QE_PTRID_JET01_GEO1, ///< created by Vadim Flaks
   QE_PTRID_TUBBY_GEO1, ///< ship
   QE_PTRID_TUBBY_GEO2, ///< ship
   QE_PTRID_REVBOXONGND_GEO1, ///< reversed box on the ground
   QE_PTRID_QUADONGND_GEO1, ///< quad on the ground
   QE_PTRID_RANDOM_GEO1, ///< random selection of GEO1
   QE_PTRID_BOX_GEO1, ///< box
};

enum {
   QE_PTRTYPE_NONE, /// reserved
   QE_PTRTYPE_GEO1, /// geometry type 1
   QE_PTRTYPE_GEO2, /// geometry type 2
};

enum {
   QE_PTROP_NONE, /// reserved
   QE_PTROP_GETTYPE, /// get type
};

GP_API ptr qefnPtrGet(uns qePtrId); ///< Get pointer to QE_PTRID_ item
GP_API int qefnPtrOp(uns qePtrId,uns op,...); ///< Get type of pointer

///////////////////////////////////////////////////////////////////////////////

//
// COLLISIONS
//

#define M_QECOLCONTACTREC_PLANE 0x01
#define M_QECOLCONTACTREC_EDGE  0x02
#define M_QECOLCONTACTREC_POINT 0x04
#define M_QECOLCONTACTREC_TYPE  0x07
// collision contact record
typedef struct {
   float tFrac; // collision fraction
   float overlap; // overlap
   float xyz[3]; // collision point
   float nrm[3]; // collision normal
   float restitution; // bounciness
   uns flags; // flags
} qeColContactRec;

/// collide a line segment against a sphere
GP_API int qeColSegSphere(float *cxyz,float *cnrm,float *cfrac,
   float *xyzStart,float *xyzEnd,float *xyz,float rr);
/// collide a line segment against a GEO1 format polygon object
GP_API int qeColSegPoly(float *dstXYZ,float *dstNrm,float *dstFrac,
   float *xyzStart,float *xyzEnd,
   float *m12,float *verts,int *faces,int numFaces);
/// collide a ray against a lib col object
GP_API int qeColSegLibObj(float *dstXYZ,float *dstNrm,float *dstFrac,
   float *xyzStart,float *xyzEnd,
   float *m12,qeObj *libColObj);
/// draw the lib col object
GP_API int qeColLibObjDrawSP(qeObj *libColObj,chr *sp,...);
/// point inside a mesh
GP_API int qeColPointInsideMesh(float *xyz,float *m12,
   float *verts,int *faces,float *nrmk,int numf);
/// swept sphere v swept sphere
GP_API int qeColSweptSpheres(qeColContactRec *ccr,
   float *start1,float *end1,float r1,
   float *start2,float *end2,float r2);
/// collide a swept sphere against 
// - mesh: m12,numv,numf,verts,faces
// - plane: numv=-1,verts=nrmk for plane
GP_API int qeColSweptSphere(qeColContactRec *dstCol,
   float *xyzStartSS,float *xyzEndSS,float radiusSS,
   float *m12,int numv,int numf,float *verts,int *faces);

typedef struct {
   LLNode lnk;
   qeColContactRec col;
} qeColContactListRec;

// collide a swept sphere against 
// sp: l (LLNode *list) list head
//     S (float *xyzStart,float *xyzEnd,float radius) swept sphere info
//     m (float *mat12) mat12 for mesh or plane
//     M (int numv,int numf,float *verts,int *faces) mesh info
//     P (float *nrmk) plane info
//     D debug info printed
GP_API int qeColSweptSphereSP(chr *sp,...);

typedef struct {
   float *mat12; // ref to current mat12
   float *prev3; // ref to previous xyz

   float *vel3; // ref to velocity xyz

   float *angVel3; // ref to ang vel xyz
   float *invWorldTensor9; // ref to inv world tensor

   //float *accPrev3; // ref to vec3
   float invMass; // inverse mass (zero = unmovable)
} qeColBody;

// resolve a collision between bodies
// sp: b (qeColBody *body) set body, may be multiple entries
//     f (float friction) 0..1, applied in dir of velocity along surface
//     R rigid body method (auto when invWorldTensor9 is set)
// example: qeColResolveSP(ccr,"bb",b1,b2)
//  where: qeColContactRec *ccr; qeColBody *b1,*b2;
GP_API int qeColResolveSP(qeColContactRec *cr,chr *sp,...);

// defunct -- use qeColSweptSphere()
typedef struct {
   int numf; // number of faces
   int numv; // number of verts
   float *verts; // verts of poly in col-space
   int *faces; // faces (default is GEO1 format)
   float *start; // starting point
   float *delta; // move
   float *mat12Poly; // mat12 for polygons
   float *mat12Sphere; // mat12 for sphere
   float radius; // radius of sphere
   float radiusSquared; // squared
   float lenDelta; // length of move
   float lenDeltaSquared; // length of move squared
   float distA; // used for keeping track of best col
   ptr list;
   uns8 flags; // flags (in and out)
   uns8 pad[2];
   uns8 collision; ///< collision found flag
   float tCol; ///< time to collision
   float xyzCol[3]; ///< collision point
   float nrmCol[3]; ///< collision normal
   float overlapCol; ///< overlap distance (always positive)
} qeColSweptSpherePolyRec;

// -- defunct -- use qeColSweptSphere()
#define qeColSweptSphereVPoly(_cr_) qeDefunctSSVP(_cr_)
GP_API int qeDefunctSSVP(qeColSweptSpherePolyRec *cr);

// --- defunct -- use qeColSweptSphere()
#define M_QECOLSWEPTSPHEREPOLY_EDGE       0x01 // out col type
#define M_QECOLSWEPTSPHEREPOLY_VERT       0x02 // out col type
#define M_QECOLSWEPTSPHEREPOLY_TYPE       0x70 // in type
#define M_QECOLSWEPTSPHEREPOLY_PLANE      0x10 // in M_QECOLSWEPTSPHEREPOLY_TYPE
#define M_QECOLSWEPTSPHEREPOLY_SINGLEPOLY 0x20 // in M_QECOLSWEPTSPHEREPOLY_TYPE
#define M_QECOLSWEPTSPHEREPOLY_SIMPLEMESH 0x30 // in M_QECOLSWEPTSPHEREPOLY_TYPE

///////////////////////////////////////////////////////////////////////////////

/// Scan verts to compute the culling center and radius.
/// @param[out] xyzrDst pointer to 4 floats set
/// @param[in] verts vertices
/// @param[in] numv number of vertices
GP_API int qefnCullXYZR(float *xyzrDst,float *verts,uns numv);

/// Using currently set camera (modelview matrix) find the ray at the window
/// coordinates
GP_API int qefnWinPickRay(float *xyzRay,float *dirRay,int winx,int winy);

/// Given all the camera information, find the ray at the window coordinates
GP_API int qefnWinPickRayCam(float *xyzRay,float *dirRay,int winx,int winy,
   float winW,float winH,float camAspect,float camNearHeight,float camNearZ,
   float *camM12);

// qefnBuildAABBFromMinMax
//    y
//    |
//    *--x
//   /
//  z
//
//    7 -- 4
//    |    | back
//    6 -- 5
//
// 3 -- 0
// |    | front
// 2 -- 1
GP_API int qefnBuildAABBFromMinMax(float *dstEightVerts,float *xyzMin,float *xyzMax);

///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus  // C in C++ wrapper
}                   //
#endif              //

#endif // QEENG_H
